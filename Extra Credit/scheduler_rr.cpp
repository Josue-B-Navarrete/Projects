/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Josue Navarrete and Xahn Millsape
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"
#include <iostream>

// Constructor with time quantum parameter
SchedulerRR::SchedulerRR(int time_quantum) {
    this->time_quantum = time_quantum;
    // Intitalize the sums of the all the wait times and turnaround times in the process list respectively
    total_wait_time = 0;
    total_turnaround_time = 0;
}

// Destructor
SchedulerRR::~SchedulerRR() {
    // Clean up data structures
    process_list.clear();
    wait_times.clear();
    turnaround_times.clear();
    remaining_time.clear();
}

// Initialize the scheduler with the given process list
void SchedulerRR::init(std::vector<PCB>& processes) {
    // Store the process list
    process_list = processes;
    
    // Initialize arrays
    int n = process_list.size();
    wait_times.resize(n, 0);
    turnaround_times.resize(n, 0);
    
    // Initialize remaining burst time for each process
    remaining_time.resize(n);
    for (int i = 0; i < n; i++) {
        remaining_time[i] = process_list[i].burst_time;
    }
}

// Simulate the Round Robin scheduling algorithm
void SchedulerRR::simulate() {
    int n = process_list.size();
    int completed = 0;
    int current_time = 0;
    
    // Queue to keep track of ready processes
    std::queue<int> ready_queue;
    
    // Initially, add all processes to the ready queue
    for (int i = 0; i < n; i++) {
        ready_queue.push(i);
    }
    
    // Continue until all processes are complete
    while (completed < n) {
        // Get the next process from the ready queue
        int current_process = ready_queue.front();
        ready_queue.pop();
        
        // Determine how long this process will run
        int execute_time = std::min(time_quantum, remaining_time[current_process]);
        
        // Print which process is running and for how long
        std::cout << "Running Process " << process_list[current_process].name 
                  << " for " << execute_time << " time units" << std::endl;
        
        // Update remaining time for the process
        remaining_time[current_process] -= execute_time;
        
        // Update current time
        current_time += execute_time;
        
        // Update wait time for all other processes that are ready and not finished
        for (int i = 0; i < n; i++) {
            if (i != current_process && remaining_time[i] > 0) {
                wait_times[i] += execute_time;
            }
        }
        
        // Check if the process is completed
        if (remaining_time[current_process] == 0) {
            completed++;
            
            // Calculate turnaround time for this process
            turnaround_times[current_process] = current_time - process_list[current_process].arrival_time;
            
            // Update statistics
            total_wait_time += wait_times[current_process];
            total_turnaround_time += turnaround_times[current_process];
        }
        else {
            // If the process is not completed, add it back to the ready queue
            ready_queue.push(current_process);
        }
    }
}

// Print the results of the simulation
void SchedulerRR::print_results() {
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