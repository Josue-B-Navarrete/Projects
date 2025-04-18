/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Josue Navarrete and Xahn Millsape
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

 #include <iostream>
 #include <pthread.h>
 #include <unistd.h>
 #include <semaphore.h>
 #include <cstdlib>
 #include <ctime>
 #include "buffer.h"
 
 using namespace std;
 
 // Global variables
 Buffer* buffer;
 pthread_mutex_t mutex;
 sem_t empty;
 sem_t full;
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
         
         // Wait if buffer is full
         sem_wait(&empty);
         
         // Enter critical section
         pthread_mutex_lock(&mutex);
         
         // Insert item into buffer
         if (buffer->insert_item(item)) {
             cout << "Producer " << producer_id << ": Inserted item " << item << endl;
             buffer->print_buffer();
         } else {
             cout << "Producer error condition" << endl;  // shouldn't come here
         }
         
         // Exit critical section
         pthread_mutex_unlock(&mutex);
         
         // Signal that buffer has one more item
         sem_post(&full);
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
     
     while (true) {
         // Sleep for a random period of time
         usleep(rand() % 1000000);
         
         // Wait if buffer is empty
         sem_wait(&full);
         
         // Enter critical section
         pthread_mutex_lock(&mutex);
         
         // Remove item from buffer
         if (buffer->remove_item(&item)) {
             // Format matches expected output - no consumer ID
             cout << "Consumer Removed item " << item << endl;
             buffer->print_buffer();
         } else {
             cout << "Consumer error condition" << endl;  // shouldn't come here
         }
         
         // Exit critical section
         pthread_mutex_unlock(&mutex);
         
         // Signal that buffer has one less item
         sem_post(&empty);
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
     
     // 2. Initialize buffer, mutex, and semaphores
     buffer = new Buffer(5);  // Create buffer with size 5
     
     // Initialize mutex
     pthread_mutex_init(&mutex, nullptr);
     
     // Initialize semaphores
     sem_init(&empty, 0, buffer->get_size());  // Initially buffer is empty, so all slots are available
     sem_init(&full, 0, 0);  // Initially buffer is empty, so no items are available
     
     // Seed random number generator
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
     

     
     // Clean up resources (in a real implementation, you would properly terminate threads)
     pthread_mutex_destroy(&mutex);
     sem_destroy(&empty);
     sem_destroy(&full);
     
     delete buffer;
     return 0;
 }
