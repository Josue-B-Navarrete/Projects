/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

 #include <iostream>
 #include <pthread.h>
 #include <unistd.h>
 #include <mutex>
 #include <condition_variable>
 #include <cstdlib>
 #include "buffer.h"
 
 using namespace std;
 
 // Global variables
 Buffer* buffer;
 mutex buffer_mutex;
 condition_variable not_full;
 condition_variable not_empty;
 int sleep_time;
 int num_producers;
 int num_consumers;
 
 /**
  * @brief Producer thread function
  * @param param Pointer to the producer ID
  * @return void pointer (not used)
  */
 void* producer(void* param) {
     // Each producer inserts its own ID into the buffer
     int producer_id = *((int*)param);
     buffer_item item = producer_id;
     
     while (true) {
         // Sleep for a random period of time
         usleep(rand() % 1000000);
         
         // Critical section - try to insert an item
         unique_lock<mutex> lock(buffer_mutex);
         
         // Wait until buffer is not full
         not_full.wait(lock, []{return !buffer->is_full();});
         
         if (buffer->insert_item(item)) {
             cout << "Producer " << producer_id << ": Inserted item " << item << endl;
             buffer->print_buffer();
             
             // Signal that buffer is not empty
             not_empty.notify_one();
         } else {
             cout << "Producer error condition" << endl;  // shouldn't come here
         }
     }
     
     return nullptr;
 }
 
 /**
  * @brief Consumer thread function
  * @param param Pointer to the consumer ID (not used in output)
  * @return void pointer (not used)
  */
 void* consumer(void* param) {
     buffer_item item;
     // Consumer ID is not used in the output format
     
     while (true) {
         // Sleep for a random period of time
         usleep(rand() % 1000000);
         
         // Critical section - try to remove an item
         unique_lock<mutex> lock(buffer_mutex);
         
         // Wait until buffer is not empty
         not_empty.wait(lock, []{return !buffer->is_empty();});
         
         if (buffer->remove_item(&item)) {
             // Format matches expected output - no consumer ID
             cout << "Consumer Removed item " << item << endl;
             buffer->print_buffer();
             
             // Signal that buffer is not full
             not_full.notify_one();
         } else {
             cout << "Consumer error condition" << endl;  // shouldn't come here
         }
     }
     
     return nullptr;
 }
 
 /**
  * @brief Main function
  * @param argc Argument count
  * @param argv Argument vector
  * @return 0 on successful execution
  */
 int main(int argc, char* argv[]) {
     // 1. Get command line arguments
     if (argc != 4) {
         cout << "Usage: " << argv[0] << " <sleep time> <num producers> <num consumers>" << endl;
         return 1;
     }
     
     sleep_time = atoi(argv[1]);
     num_producers = atoi(argv[2]);
     num_consumers = atoi(argv[3]);
     
     // 2. Initialize buffer and seed random number generator
     buffer = new Buffer(5);  // Create buffer with size 5
     srand(time(nullptr));
    
     
     // 3. Create producer thread(s)
     pthread_t producer_threads[num_producers];
     int producer_ids[num_producers];
     
     for (int i = 0; i < num_producers; i++) {
         producer_ids[i] = i + 1;  // Producer IDs start from 1
         pthread_create(&producer_threads[i], nullptr, producer, &producer_ids[i]);
     }
     
     // 4. Create consumer thread(s)
     pthread_t consumer_threads[num_consumers];
     int consumer_ids[num_consumers];
     
     for (int i = 0; i < num_consumers; i++) {
         consumer_ids[i] = i + 1;  // Consumer IDs start from 1
         pthread_create(&consumer_threads[i], nullptr, consumer, &consumer_ids[i]);
     }
     
     // 5. Main thread sleep
     sleep(sleep_time);
     
     
     delete buffer;
     return 0;
 }