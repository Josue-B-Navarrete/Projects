/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author ??? (TODO: your name)
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

 #include "buffer.h"
 #include <iostream>
 
 /**
  * @brief Construct a new Buffer object with the specified size
  * @param bufferSize Size of the buffer (default is 5)
  */
 Buffer::Buffer(int bufferSize) {
     size = bufferSize;
     buff = new int[size];
     front = 0;
     rear = -1;
     currentSize = 0;
 }
 
 /**
  * @brief Destroy the Buffer object and free allocated memory
  */
 Buffer::~Buffer() {
     delete[] buff;
 }
 
 /**
  * @brief Insert an item into the buffer
  * @param item The item to insert
  * @return true if insertion successful, false if buffer is full
  */
 bool Buffer::insert_item(buffer_item item) {
     // Check if buffer is full
     if (is_full()) {
         return false;
     }
     
     // Update rear pointer and insert item
     rear = (rear + 1) % size;
     buff[rear] = item;
     currentSize++;
     return true;
 }
 
 /**
  * @brief Remove an item from the buffer
  * @param item Pointer to store the removed item
  * @return true if removal successful, false if buffer is empty
  */
  bool Buffer::remove_item(buffer_item *item) {
    // Check if buffer is empty
    if (is_empty()) {
        return false;
    }
    
    // Get the item at the front position and store it in the provided pointer
    *item = buff[front];
    
    // Update front pointer with wrap-around
    front = (front + 1) % size;
    currentSize--;
    
    // Handle the case when the buffer becomes empty
    if (currentSize == 0) {
        // You could reset pointers here if desired
         front = 0;
         rear = -1;
    }
    
    return true;
}
 
 /**
  * @brief Get the maximum size of the buffer
  * @return The maximum size of the buffer
  */
 int Buffer::get_size() {
     return size;
 }
 
 /**
  * @brief Get the current number of items in the buffer
  * @return The current number of items
  */
 int Buffer::get_count() {
     return currentSize;
 }
 
 /**
  * @brief Check if the buffer is empty
  * @return true if empty, false otherwise
  */
 bool Buffer::is_empty() {
     return currentSize == 0;
 }
 
 /**
  * @brief Check if the buffer is full
  * @return true if full, false otherwise
  */
 bool Buffer::is_full() {
     return currentSize == size;
 }
 
 /**
  * @brief Print the current contents of the buffer
  */
 void Buffer::print_buffer() {
    if (is_empty()) {
        std::cout << "Buffer: []" << std::endl;
        return;
    }
    
    std::cout << "Buffer: [";
    int index = front;
    for (int count = 0; count < currentSize; count++) {
        std::cout << buff[index];
        if (count < currentSize - 1) {
            std::cout << ", ";
        }
        index = (index + 1) % size;
    }
    std::cout << "]" << std::endl;
}