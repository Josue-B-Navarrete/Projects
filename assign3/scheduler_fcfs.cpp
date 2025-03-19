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
    process.clear();
}

SchedulerFCFS::void init(vector<PCB>& process_list){
    // Store the process list
    process_list = processes;
}

// Simulate the FCFS scheduling algorithm
void SchedulerFCFS::simulate() {
    int n = process_list.size();
    total_wait_time = 0;
    total_turnaround_time = 0;
    
    // For FCFS, we process in the order of arrival (by index in this case)
    int current_time = 0;
    
    for(int i = 0; i < n; i++) {
        // Update the wait time for the current process
        process_list[i].wait_time = current_time;
        
        // Update turnaround time (wait time + burst time)
        process_list[i].turnaround_time = process_list[i].wait_time + process_list[i].burst_time;
        
        // Move time forward after processing this job
        current_time += process_list[i].burst_time;
        
        // Accumulate statistics
        total_wait_time += process_list[i].wait_time;
        total_turnaround_time += process_list[i].turnaround_time;
    }
}

// Print the results of the simulation
void SchedulerFCFS::print_results() {
    
    // Print average statistics
    std::cout << "\nAverage Wait Time: " << static_cast<double>(total_wait_time) / n << std::endl;
    std::cout << "Average Turnaround Time: " << static_cast<double>(total_turnaround_time) / n << std::endl;
}