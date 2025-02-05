#include <iostream>
#include "readyqueue.h"

using namespace std;

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code

/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     capacity = 100;  
     currentSize = 0;
     heap = new PCB*[capacity];
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete heap;
}
/**
 * @brief Copy Constructor
 */
ReadyQueue::ReadyQueue(const ReadyQueue& other){
    capacity = other.capacity;
    currentSize = other.currentSize;
    heap = new PCB*[capacity];
}

/**
 * @brief Overload =operator
 */
ReadyQueue& ReadyQueue::operator=(const ReadyQueue& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }

    // Free the existing heap array
    delete[] heap; // Correctly deallocate the array

    // Copy primitive members
    capacity = other.capacity;
    currentSize = other.currentSize;

    // Allocate new heap array
    heap = new PCB*[capacity];

    for (int i = 0; i < currentSize; ++i) {
        heap[i] = other.heap[i];
    }

    return *this;
}



/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    // when adding, change its state to READY.
    if (currentSize >= capacity) {
        return;
    }
    // set state to READY and add to heap
    pcbPtr->setState(ProcState::READY);
    heap[currentSize] = pcbPtr;
    heapifyUp(currentSize);
    currentSize++;
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    // when removing, change its state to RUNNING.
        if (currentSize == 0) {
        return nullptr;
    }

    // get the highest priority PCB
    PCB* highestPriorityPCB = heap[0];
    highestPriorityPCB->setState(ProcState::RUNNING);

    // replace root with last element and heapify down
    heap[0] = heap[currentSize - 1];
    currentSize--;
    
    if (currentSize > 0) {
        heapifyDown(0);
    }

    return highestPriorityPCB;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return currentSize;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < currentSize; i++) {
        heap[i]->display();
    }
}

/**
 * @brief Helper function to maintain heap property upward
 * @param Index The index of the node to start heapifying upward
 */
void ReadyQueue::heapifyUp(int index) {
    // while not at the root
    while (index > 0) {
        // calculate parent index
        int parent = (index - 1) / 2;
        // if current node has a higher priority than parent, SWAP
        if (heap[index]->getPriority() > heap[parent]->getPriority()) {
            swap(index, parent);
            // store parents index
            index = parent;
        } else {
            break;
        }
    }
}

/**
 * @brief Helper function to maintain heap property downward
 * @param Index The index of the node to start heapifying upward
 */
void ReadyQueue::heapifyDown(int index) {
    while (true) {
        // set current node as largest
        int maxIndex = index;
        // childern indices
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        // check if childern exist and has higher prioroty
        if (left < currentSize && 
            heap[left]->getPriority() > heap[maxIndex]->getPriority()) {
            maxIndex = left;
        }
        if (right < currentSize && 
            heap[right]->getPriority() > heap[maxIndex]->getPriority()) {
            maxIndex = right;
        }

        // if the largest is not the current node, SWAP
        if (maxIndex != index) {
            swap(index, maxIndex);
            index = maxIndex;
        } else {
            break;
        }
    }
}

/**
 * @brief Helper function to swap two elements in the heap
 * @param i The index of the first element to swap
 * @param j The index of the second element to swap
 */
void ReadyQueue::swap(int i, int j) {
    // temp
    PCB* temp = heap[i];
    // swap
    heap[i] = heap[j];
    heap[j] = temp;
}
