/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Josue Navarrete and Xahn Millsape
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <vector>
#include <iostream>
#include <limits>

// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here

// Constructor
SchedulerSJF::SchedulerSJF() {
     // Intitalize the sums of the all the wait times and turnaround times in the process list respectively
    total_wait_time = 0;
    total_turnaround_time = 0;
}

// Destructor
SchedulerSJF::~SchedulerSJF() {
    // Clean up data structures
    process_list.clear();
    wait_times.clear();
    turnaround_times.clear();
    completed.clear();
}

// Initialize the scheduler with the given process list
void SchedulerSJF::init(std::vector<PCB>& processes) {
    // Store the process list
    process_list = processes;
    
    // Initialize arrays
    int n = process_list.size();
    wait_times.resize(n, 0);
    turnaround_times.resize(n, 0);
    completed.resize(n, false);
    
    // Initialize statistics
    //total_wait_time = 0;
    //total_turnaround_time = 0;
}

// Simulate the SJF scheduling algorithm
void SchedulerSJF::simulate() {
    int n = process_list.size();
    int completed_count = 0;
    int current_time = 0;
    
    // Continue until all processes are complete
    while (completed_count < n) {
        // Find the shortest job among the available processes
        int shortest_job_index = -1;
        int shortest_burst_time = numeric_limits<int>::max();
        
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and is not yet completed
            if (!completed[i] && process_list[i].arrival_time <= current_time) {
                if (process_list[i].burst_time < shortest_burst_time) {
                    shortest_burst_time = process_list[i].burst_time;
                    shortest_job_index = i;
                }
            }
        }
        
        // If no process is available at current time, advance time
        if (shortest_job_index == -1) {
            current_time++;
            continue;
        }
        
        // Process the shortest job
        int i = shortest_job_index;
        
        // Print which process is running and for how long
        std::cout << "Running Process " << process_list[i].name 
                  << " for " << process_list[i].burst_time << " time units" << std::endl;
        

        // Calculate wait time for this process
        wait_times[i] = current_time - process_list[i].arrival_time;
        if (wait_times[i] < 0) wait_times[i] = 0; // Ensure non-negative wait time
        
        // Calculate turnaround time for this process
        turnaround_times[i] = wait_times[i] + process_list[i].burst_time;
        
        // Update current time and mark the process as completed
        current_time += process_list[i].burst_time;
        completed[i] = true;
        completed_count++;
        
        // Update statistics
        total_wait_time += wait_times[i];
        total_turnaround_time += turnaround_times[i];
    }
}

// Print the results of the simulation
void SchedulerSJF::print_results() {
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