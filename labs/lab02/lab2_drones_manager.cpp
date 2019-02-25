#include <iostream>

#include "lab2_drones_manager.hpp"

using namespace std;

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
    first = NULL;
    last = NULL;
    size = 0;
}

DronesManager::~DronesManager() {

}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	return lhs.droneID == rhs.droneID &&
        lhs.range == rhs.range &&
        lhs.yearBought == rhs.yearBought &&
        lhs.droneType == rhs.droneType &&
        lhs.manufacturer == rhs.manufacturer &&
        lhs.description == rhs.description &&
        lhs.batteryType == rhs.batteryType;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	return size < 1 && first == NULL && last == NULL;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (empty()) return DroneRecord(0);

    DronesManager::DroneRecord* selected = first;
    int i = 0;
    while (i < index && selected != NULL) {
        selected = selected->next;
        i++;
    }

    return selected != NULL ? *selected : *last;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (empty()) return 0;

    DronesManager::DroneRecord* found = first;
    int i = 0;
    while (i < get_size() && found != NULL) {
        if (*found == value) break;
        found = found->next;
        i++;
    }

    return i;
}

void DronesManager::print() const {
    DronesManager::DroneRecord* found = first;
    for (int i = 0; i < get_size(); i++) {
        cout << i << ": " << found->droneID << endl;
        found = found->next;
    }
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (0 > index || get_size() <= index) return false;
    DronesManager::DroneRecord* found = first;
    for (int i = 0; i < index - 1; i++) {
        found = found->next;
    }
    if (found == NULL) return false;

    DroneRecord* newDrone = value.copy();
    newDrone->prev = found;
    newDrone->next = found->next;
    found->next = newDrone;

    size++;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    DroneRecord* newDrone = value.copy();
    if (empty()) {
        last = newDrone;
        newDrone->prev = NULL;
        newDrone->next = NULL;
    } else {
        newDrone->prev = NULL;
        newDrone->next = first;
        first->prev = newDrone;
    }
    first = newDrone;

    size++;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
    DroneRecord* newDrone = value.copy();
    if (empty()) {
        first = newDrone;
        newDrone->prev = NULL;
        newDrone->next = NULL;
    } else {
        newDrone->prev = last;
        newDrone->next = NULL;
        last->next = newDrone;
    }
    last = newDrone;

    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
	if (0 > index || get_size() <= index) return false;
    DronesManager::DroneRecord* cur = first;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    cur->prev->next = cur->next;

    size--;
    return true;
}

bool DronesManager::remove_front() {
	if (first == NULL) return false;
    first = first->next;
    if (first != NULL) {
        first->prev = NULL;
    }

    size--;
    if (get_size() < 1) last = NULL;
    return true;
}

bool DronesManager::remove_back() {
	if (last == NULL) return false;
    last = last->prev;
    if (last != NULL) {
        last->next = NULL;
    }

    size--;
    if (get_size() < 1) first = NULL;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (0 > index || get_size() <= index) return false;
    DronesManager::DroneRecord* newDrone = value.copy();
    DronesManager::DroneRecord* cur = first;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    newDrone->prev = cur->prev;
    newDrone->next = cur->next;
    if (index == 0) {
        first = newDrone;
        cur->next->prev = newDrone;
    } else if (index == get_size() - 1) {
        last = newDrone;
        cur->prev->next = newDrone;
    } else {
        cur->prev->next = newDrone;
        cur->next->prev = newDrone;
    }
    return true;
}

bool DronesManager::reverse_list() {
    DronesManager::DroneRecord* cur = first;
    first = last;
    last = cur;
    while (cur != NULL) {
        DronesManager::DroneRecord* tmp = cur->next;
        cur->next = cur->prev;
        cur->prev = tmp;
        cur = tmp;
    }
    return true;
}

bool DronesManagerSorted::is_sorted_asc() const {
    if (get_size() <= 1) return true;

    DronesManager::DroneRecord* cur = first;
    while (cur != NULL) {
        if (cur->droneID > cur->next->droneID) return false; 
        cur = cur->next;
    }
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    if (get_size() <= 1) return true;

    DronesManager::DroneRecord* cur = first;
    while (cur != NULL) {
        if (cur->droneID < cur->next->droneID) return false; 
        cur = cur->next;
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord value) {
    DronesManager::DroneRecord* newDrone = value.copy();
	if (empty()) {
        newDrone->prev = NULL;
        newDrone->next = NULL;
        first = newDrone;
        last = newDrone;
    } else if (first->droneID >= newDrone->droneID) {
        newDrone->prev = NULL;
        newDrone->next = first;
        first = newDrone;
    } else if (last->droneID <= newDrone->droneID) {
        newDrone->prev = last;
        newDrone->next = NULL;
        last = newDrone;
    } else {
        DronesManager::DroneRecord* cur = first;
        while (cur->next != NULL && cur->droneID < newDrone->droneID) {
            cur = cur->next;
        }
        newDrone->prev = cur->prev;
        newDrone->next = cur;
        cur->prev = newDrone;
    }

    return true;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord value) {
	DronesManager::DroneRecord* newDrone = value.copy();
	if (empty()) {
        newDrone->prev = NULL;
        newDrone->next = NULL;
        first = newDrone;
        last = newDrone;
    } else if (first->droneID <= newDrone->droneID) {
        newDrone->prev = NULL;
        newDrone->next = first;
        first = newDrone;
    } else if (last->droneID >= newDrone->droneID) {
        newDrone->prev = last;
        newDrone->next = NULL;
        last = newDrone;
    } else {
        DronesManager::DroneRecord* cur = first;
        while (cur->next != NULL && cur->droneID > newDrone->droneID) {
            cur = cur->next;
        }
        newDrone->prev = cur->prev;
        newDrone->next = cur;
        cur->prev = newDrone;
    }

    return true;
}

// utility function for swapping two elements
template<typename T>
void swap(T* a, T* b) {
    T t = *a;
    *a = *b;
    *b = t;
}

/* Considers last element as pivot, places the pivot element at its 
   correct position in sorted array, and places all smaller (smaller than 
   pivot) to left of pivot and all greater elements to right of pivot */
DronesManager::DroneRecord* DronesManagerSorted::partition(DroneRecord* l, DroneRecord* h, int direction) {
    // set pivot as h element 
    unsigned int x  = h->droneID; 
  
    // similar to i = l-1 for array implementation 
    DroneRecord* i = l->prev; 
 
    for (DroneRecord* j = l; j != h; j = j->next) {
        if (direction > 0 ? j->droneID <= x : j->droneID <= x) {
            i = (i == NULL) ? l : i->next; 
            swap(&(i->droneID), &(j->droneID)); 
        }
    }
    i = (i == NULL) ? l : i->next; // Similar to i++ 
    swap(&(i->droneID), &(h->droneID)); 
    return i; 
} 
  
/* A recursive implementation of quicksort for linked list */  
void DronesManagerSorted::quickSort(DroneRecord* l, DroneRecord* h, int direction) {
    if (h != NULL && l != h && l != h->next) {
        DroneRecord* p = partition(l, h, direction); 
        quickSort(l, p->prev, direction); 
        quickSort(p->next, h, direction); 
    }
} 

void DronesManagerSorted::sort_asc() {
    quickSort(first, last, 1);
}
    
void DronesManagerSorted::sort_desc() {
    quickSort(first, last, -1);
}
