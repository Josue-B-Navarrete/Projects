/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Josue Navarrete and Xahn Millsape
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */

 #include "scheduler_priority.h"
 #include <iostream>
 
 // Constructor
 SchedulerPriority::SchedulerPriority() {
     // Nothing to initialize in the constructor
 }
 
 // Destructor
 SchedulerPriority::~SchedulerPriority() {
     // Clean up data structures
     process_list.clear();
     wait_times.clear();
     turnaround_times.clear();
     completed.clear();
 }
 
 // Initialize the scheduler with the given process list
 void SchedulerPriority::init(std::vector<PCB>& processes) {
     // Store the process list
     process_list = processes;
     
     // Initialize arrays
     int n = process_list.size();
     wait_times.resize(n, 0);
     turnaround_times.resize(n, 0);
     completed.resize(n, false);
     
     // Initialize statistics
     total_wait_time = 0;
     total_turnaround_time = 0;
 }
 
 // Simulate the Priority scheduling algorithm
void SchedulerPriority::simulate() {
    int n = process_list.size();
    int current_time = 0;
    
    // Sort processes by priority in descending order (highest priority first)
    std::vector<int> process_order;
    for (int i = 0; i < n; i++) {
        process_order.push_back(i);
    }
    
    // Simple bubble sort by priority (descending)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (process_list[process_order[j]].priority < process_list[process_order[j+1]].priority) {
                // Swap
                int temp = process_order[j];
                process_order[j] = process_order[j+1];
                process_order[j+1] = temp;
            }
        }
    }
    
    // Process each job in order of priority
    for (int i = 0; i < n; i++) {
        int proc_idx = process_order[i];
        
        // Print which process is running and for how long
        std::cout << "Running Process " << process_list[proc_idx].name 
                  << " for " << process_list[proc_idx].burst_time << " time units" << std::endl;
        
        // Calculate wait time for this process
        wait_times[proc_idx] = current_time;
        
        // Update current time
        current_time += process_list[proc_idx].burst_time;
        
        // Calculate turnaround time for this process
        turnaround_times[proc_idx] = current_time;
        
        // Mark the process as completed
        completed[proc_idx] = true;
        
        // Update statistics
        total_wait_time += wait_times[proc_idx];
        total_turnaround_time += turnaround_times[proc_idx];
    }
}

 
 // Print the results of the simulation
 void SchedulerPriority::print_results() {
     int n = process_list.size();
     
     for(int i = 0; i < n; i++) {
         std::cout << process_list[i].name 
                   << " turn-around time = " << turnaround_times[i]
                   << ", waiting time = " << wait_times[i] << std::endl;
     }
     
     // Print average statistics
     std::cout << "Average turn-around time = " << static_cast<double>(total_turnaround_time) / n << ", ";
     std::cout << "Average waiting time = " << static_cast<double>(total_wait_time) / n << std::endl;
 }