//
// Purpose: Comment on memory bugs in provided program
// Author: Conrad Heidebrecht
//

// BUG: Forgot to add includes and namespace:
//     #include <string>
//     using namespace std;

class Blobber {
public: // BUG: There should not be two "public:"s
    struct Test {
        string a;
    };
private:
    Test** data;
    int size;
public: // BUG: There should not be two "public:"s
    Blobber() : size(0) {
        Test** data = new Test*[100]();
    }
    ~Blobber() {
        // BUG: should replace i <= size with i < size
        for (int i = 0; i <= size; ++i) {
            delete data[i];
        }
        delete data;
    }
    void insert_test_values(Test new_test) {
        // BUG: does not check if it's adding past array capacity
        data[size++] = &new_test;
    }

    Test remove_test_values() {
        // BUG: deleting a value that doesn't exist
        //     (size is past the index of the last assigned element)
        //     should replace with:
        //         delete data[--size];
        //     and remove the size--;
        delete data[size];
        // BUG: a pointer should not be set to NULL, instead use nullptr
        //     but this is not really necessary
        data[size] = NULL;
        size--;
        // BUG: returning a meaningless memory location
        return *data[size+1];
    }
};

int main() {
    Blobber b;
    Blobber::Test t;
    t.a = "new";

    b.insert_test_values(t);
    b.insert_test_values(t);
    b.insert_test_values(t);
    b.remove_test_values();
    b.remove_test_values();

    return 0;
}
