#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
    //
    bool populate_data(DronesManager& manager, int n) {
        for (int i = 0; i < n; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)));
		}
        return n;
    }

	// PURPOSE: New empty list is valid
    bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
    }

	// PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
    }

	// PURPOSE: select() and search() work properly
    bool test3() {
		DronesManager manager1;
		
		const int num_elems = 5;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(i*100)))
		}

		unsigned int idx = 3;
		ASSERT_TRUE(manager1.search(manager1.select(idx)) == idx)
		ASSERT_TRUE(manager1.select(num_elems + 1) == DronesManager::DroneRecord(400))
		ASSERT_TRUE(manager1.search(1000) == manager1.get_size())
		
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager1.select(i) == DronesManager::DroneRecord(i*100))
		}
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
	    return true;
    }
    
    // PURPOSE: remove_front() and remove_back() on one-element list
    bool test4() {
		DronesManager manager1, manager2;
		ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(100)))
		ASSERT_TRUE(manager2.insert_front(DronesManager::DroneRecord(100)))
		ASSERT_TRUE(manager1.remove_front())
		ASSERT_TRUE(manager2.remove_back())
		
		ASSERT_TRUE(manager1.first == NULL && manager1.last == NULL)
		ASSERT_TRUE(manager2.first == NULL && manager2.last == NULL)
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 0)
		ASSERT_TRUE(manager1.empty() == true && manager2.empty() == true)
		
	    return true;
    }
    
    // PURPOSE: replace() and reverse_list() work properly
    bool test5() {
    	DronesManager manager;
		const int num_elems = 8;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
		}
	
		ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(8)))
		ASSERT_TRUE(manager.replace(3, DronesManager::DroneRecord(9)))
		ASSERT_TRUE(manager.replace(7, DronesManager::DroneRecord(10)))
	
		ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(8))
		ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(10))
		ASSERT_TRUE(*(manager.first->next->next->next) == DronesManager::DroneRecord(9))
	
		int test_values[8] = {10, 6, 5, 4, 9, 2, 1, 8};
		ASSERT_TRUE(manager.reverse_list());
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]))
		}
	
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
		
	    return true;
    }
    
    // PURPOSE: insert_front() keeps moving elements forward
    bool test6() {
    	DronesManager manager;
		const int num_elems = 5;
		for (int i = 0; i < num_elems; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
			ASSERT_TRUE(manager.get_size() == (i + 1))
			ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(i))
	        
			DronesManager::DroneRecord* n = manager.first;
			for (int j = 0; j <= i; j++) {
				DronesManager::DroneRecord expected_value = DronesManager::DroneRecord(i - j);
				ASSERT_TRUE(n != NULL && *n == expected_value)
				n = n->next;
			}
		}	
		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
    }
    
    // PURPOSE: inserting at different positions in the list
    bool test7() {
		DronesManager manager;
		int num_elems = populate_data(manager, 5);

        int indices[3] = {3, 1, 4};
        for (int i : indices) {
            ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(num_elems + i), i));

            DronesManager::DroneRecord* n = manager.first;
            for (int j = 0; j < manager.get_size(); j++) {
                DronesManager::DroneRecord expected_value = DronesManager::DroneRecord(num_elems + i - j);
                ASSERT_TRUE(n != NULL && *n == expected_value)
                n = n->next;
            }
        }

		ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
    }
    
    // PURPOSE: try to remove too many elements, then add a few elements
    bool test8() {
    	DronesManager manager;
		int num_elems = populate_data(manager, 5);

        for (int i = 0; i < num_elems; i++) {
            ASSERT_TRUE(manager.remove_back());
        }

        ASSERT_FALSE(manager.remove_back());
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(0)));
		ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(1)));

        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
    }
    
 	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
        DronesManager manager;
		int num_elems = populate_data(manager, 5);

        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(num_elems + 1), manager.get_size() + 100));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(num_elems + 2), manager.get_size() - 2));
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(num_elems + 3), -100));
        ASSERT_TRUE(manager.remove(manager.get_size() + 200));
        ASSERT_TRUE(manager.remove(manager.get_size() - 4));

        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
	}    
	    	
	// PURPOSE: insert into an unsorted list, then sort the list
	bool test10() {
        DronesManagerSorted manager;
		int indices[4] = {0, 1, 3, 6};
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(indices[1])));
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(indices[0])));
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(indices[3])));
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(indices[2])));

        manager.sort_asc();

        DronesManager::DroneRecord* n = manager.first;
        for (int i = 0; i < manager.get_size(); i++) {
            DronesManager::DroneRecord expected_value = DronesManager::DroneRecord(indices[i]);
            ASSERT_TRUE(n != NULL && *n == expected_value)
            n = n->next;
        }
        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
	}  
	
	// PURPOSE: insert and remove into sorted manager in ascending order
	bool test11() {
		DronesManager manager;


        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
	}
	
	// PURPOSE: insert and remove into sorted manager in descending order
	bool test12() {
		DronesManager manager;


        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
	    return true;
	}  
};


#endif
