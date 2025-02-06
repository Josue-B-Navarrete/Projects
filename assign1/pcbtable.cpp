/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Xahn Millsape and Josue Navarrete
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
    // Uses the resize member function to dynamically change the size of the table as needed
    table.resize(size, nullptr);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // Delete all the PCBs in the table
   // Delete all PCB objects stored in the vector
   for (PCB* pcb : table) {
        if (pcb != nullptr) {
            delete pcb;
        }
    }
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // Returns a null pointer should the index be beyond the scope of the table
    // Otherwise, returns the value at the index
    if (idx >= table.size()) {
        return nullptr;
    }
    return table[idx];
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // Add a PCB pointer to the PCBTable at index idx.
    // Check if index is within bounds
    if (idx >= table.size()) {
        return;
    }
    // If there's already a PCB at this index, delete it first
    if (table[idx] != nullptr) {
        delete table[idx];
    }
    // Add the new PCB
    table[idx] = pcb;
}
