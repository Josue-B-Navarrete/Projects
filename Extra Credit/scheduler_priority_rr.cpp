/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Josue Navarrete and Xahn Millsape
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"
#include <queue>

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) {
    this->time_quantum = time_quantum;
    // Intitalize the sums of the all the wait times and turnaround times in the process list respectively
    total_wait_time = 0;
    total_turnaround_time = 0;
}

SchedulerPriorityRR::~SchedulerPriorityRR() {
    // Clean up data structures
    process_list.clear();
    wait_times.clear();
    turnaround_times.clear();
    remaining_time.clear();
    completed.clear();
}

void SchedulerPriorityRR::init(std::vector<PCB>& processes) {
    // Store the process list
    process_list = processes;

    // Initialize arrays
    int n = process_list.size();
    wait_times.resize(n, 0);
    turnaround_times.resize(n, 0);
    completed.resize(n, false);

    // Initialize remaining burst time for each process
    remaining_time.resize(n);
    for (int i = 0; i < n; i++) {
        remaining_time[i] = process_list[i].burst_time;
    }
}

// Simulate the scheduling algorithm as though it were using priority with round robin
void SchedulerPriorityRR::simulate() {
    int n = process_list.size();
    int completed_prr = 0;
    int current_time = 0;

    // Queue to keep track of ready processes
    std::queue<int> ready_queue;

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

    // Inserts the sorted processes by priority (descending order) into the ready queue
    for (int i = 0; i < n; i++) {
        ready_queue.push(i);
    }

    while (completed_prr < n) {
        int current_process = ready_queue.front();
        ready_queue.pop();

        if (process_list[current_process].priority == process_list[ready_queue.front()].priority) {
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
                completed_prr++;
                
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
        } else {
            // Process each job in order of priority
            int proc_idx = process_order[current_process];
            
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

            completed_prr++;
        }
      }
}
    /*
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

*/
 // Print the results of the simulation
 void SchedulerPriorityRR::print_results() {
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