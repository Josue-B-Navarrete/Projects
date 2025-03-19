/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Josue Navarrete and Xahn Millsape
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"
#include <vector>
#include <iostream>

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerFCFS::SchedulerFCFS(){

}

SchedulerFCFS::~SchedulerFCFS(){
    process_list.clear();
}

// Initialize the scheduler with the given process list
void SchedulerFCFS::init(std::vector<PCB>& processes) {
    // Store the process list
    process_list = processes;
    // Initialize wait times and turnaround times arrays
    wait_times.resize(process_list.size(), 0);
    turnaround_times.resize(process_list.size(), 0);
}

// Simulate the FCFS scheduling algorithm
void SchedulerFCFS::simulate() {
    int n = process_list.size();
    total_wait_time = 0;
    total_turnaround_time = 0;
    
    // For FCFS, we process in the order of arrival (by index in this case)
    int current_time = 0;
    
    for(int i = 0; i < n; i++) {
        // Print which process is running and for how long
        std::cout << "Running Process " << process_list[i].name 
                  << " for " << process_list[i].burst_time << " time units" << std::endl;

        // Update the wait time for the current process
        wait_times[i] = current_time;
        
        // Update turnaround time (wait time + burst time)
        turnaround_times[i] = wait_times[i] + process_list[i].burst_time;
        
        // Move time forward after processing this job
        current_time += process_list[i].burst_time;
        
        // Accumulate statistics
        total_wait_time += wait_times[i];
        total_turnaround_time += turnaround_times[i];
    }
}

// Print the results of the simulation
void SchedulerFCFS::print_results() {
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