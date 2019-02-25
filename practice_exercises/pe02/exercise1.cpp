#include <iostream>
using namespace std;

//
// Created by Kyle Lane on 2019-02-25.
//

struct TwinPair {
    int val1, val2;
    TwinPair() : val1(0), val2(0) {}
};

int is_prime(int n) {
    bool flag = true;

    for(int i = 2; i <= n/2; ++i)
    {
        if(n%i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

TwinPair find_twin_primes(unsigned int chosen_index){
    unsigned int at_index = 0;
    unsigned int current_val = 2; // start after 1
    TwinPair result;
    while(true) {

        if( is_prime(current_val) && is_prime(current_val+2) ) {
            at_index ++;
            if(at_index == chosen_index){
                result.val1 = current_val;
                result.val2 = current_val + 2;
                return(result);
            }
        }
        current_val ++;
    }
}

int main() {
    TwinPair res = find_twin_primes(10);
    cout << res.val1 << "\n" << res.val2 << "\n";
    return 0;
}