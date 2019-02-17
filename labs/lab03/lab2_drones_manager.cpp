#include <iostream>

#include "lab2_drones_manager.hpp"

using namespace std;

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
    first = nullptr;
    last = nullptr;
    size = 0;
}

DronesManager::~DronesManager() {
    delete first;
    delete last;
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
	return size < 1;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (get_size() < 1) return DroneRecord(0);

    int i = 0;
    DronesManager::DroneRecord* selected = first;
    while (i <= index && selected != nullptr) {
        selected = selected->next;
    }

    return selected != nullptr ? *selected : *last;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (get_size() < 1) return 0;

    DronesManager::DroneRecord* found = first;
    int i = 0;
    while (i < get_size() && found == nullptr) {
        if ((*found) == value) break;
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
    DronesManager::DroneRecord* found = first;
    for (int i = 0; i < index - 1; i++) {
        found = found->next;
    }
    if (found == nullptr) return false;
    *found->next = value;
    value.next = found->next->next;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	value.next = first;
    first = &value;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	*last->next = value;
    last = &value;
    return true;
}

bool DronesManager::remove(unsigned int index) {
	if (0 > index || get_size() >= index) return false;
    DronesManager::DroneRecord* cur = first;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    cur->prev->next = cur->next;
    return true;
}

bool DronesManager::remove_front() {
	if (first == nullptr) return false;
    first = first->next;
    return true;
}

bool DronesManager::remove_back() {
	if (last == nullptr) return false;
    last = last->prev;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (0 > index || get_size() >= index) return false;
    DronesManager::DroneRecord* cur = first;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    
}

bool DronesManager::reverse_list() {
	return false;
}

bool DronesManagerSorted::is_sorted_asc() const {
	return false;
}

bool DronesManagerSorted::is_sorted_desc() const {
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {
	return false;
}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {
	return false;
}

void DronesManagerSorted::sort_asc() {
}
    
void DronesManagerSorted::sort_desc() {
}
