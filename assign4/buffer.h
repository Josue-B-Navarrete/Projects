/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Josue Navarrete and Xahn Millsape
 * @brief header file for the buffer class
 * @version 0.1
 */
 #ifndef ASSIGN4_BUFFER_H
 #define ASSIGN4_BUFFER_H
 
 // Define the data type of the buffer items
 typedef int buffer_item;
 
 /**
  * @brief The bounded buffer class. The number of items in the buffer cannot exceed the size of the buffer.
  */
 class Buffer {
 private:
     int size;           // Maximum capacity of the buffer
     int currentSize;    // Current number of items in the buffer
     int front;          // Index of the front item
     int rear;           // Index of the rear item
     int *buff;          // Array to store buffer items
 
 public:
     /**
      * @brief Construct a new Buffer object
      * @param size the size of the buffer
      */
     Buffer(int size = 5);
     
     /**
      * @brief Copy constructor
      * @param other The buffer to copy from
      */
     Buffer(const Buffer& other);
     
     /**
      * @brief Assignment operator
      * @param other The buffer to assign from
      * @return Reference to this buffer
      */
     Buffer& operator=(const Buffer& other);
 
     /**
      * @brief Destroy the Buffer object
      */
     ~Buffer();
 
     /**
      * @brief Insert an item into the buffer
      * @param item the item to insert
      * @return true if successful
      * @return false if not successful
      */
     bool insert_item(buffer_item item);
 
     /**
      * @brief Remove an item from the buffer
      * @param item the item to remove
      * @return true if successful
      * @return false if not successful
      */
     bool remove_item(buffer_item *item);
 
     /**
      * @brief Get the size of the buffer
      * @return the size of the buffer
      */
     int get_size();
 
     /**
      * @brief Get the number of items in the buffer
      * @return the number of items in the buffer
      */
     int get_count();
 
     /**
      * @brief Check if the buffer is empty
      * @return true if the buffer is empty, else false
      */
     bool is_empty();
 
     /**
      * @brief Check if the buffer is full
      * @return true if the buffer is full, else false
      */
     bool is_full();
 
     /**
      * @brief Print the buffer
      */
     void print_buffer();
 };
 
 #endif //ASSIGN4_BUFFER_H
