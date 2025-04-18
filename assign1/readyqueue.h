/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Xahn Millsape and Josue Navarrete
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:

    PCB** heap;          // array for PCB pointers
    int capacity;        // capacity of the heap
    int currentSize;     // count in the heap

    // helper functions for heap 
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);

public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    /**
     * @brief Destructor
     */
    ~ReadyQueue();

	// You may add additional member functions, but don't change the definitions of the following four member functions.
   
   
    /**
     * @brief Copy Constructor
     *
     * @param other: ReadyQueue object
     */
    ReadyQueue(const ReadyQueue& other);

    /**
     * @brief Overloaded =operator
     *
     * @param obj: ReadyQueue object
     * @returns this: A reference to current object being modified during the assignment operation
     **/
    ReadyQueue& operator=(ReadyQueue const& obj);

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};
