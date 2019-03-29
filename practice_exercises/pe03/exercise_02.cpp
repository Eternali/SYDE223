#include <iostream>
#include <string>
#include <vector>

using namespace std;


void output_permutations(string s, vector<int> left, vector<int> built_up){
    // slow bc doing dumb operations to call recursion
    if(left.size() == 0) {
        for(int i = 0; i<built_up.size(); i++) {
            cout << s[built_up[i]];
        }
        cout << endl;
        return;
    }
    for(int i = 0; i<left.size(); i++) {
        vector<int> temp_bu = built_up; // Would be so much cleaner if I could just add to array when calling function..
        vector<int> temp_left = left;  // These operations make this function sooo slow :(
        temp_bu.push_back(left[i]);
        temp_left.erase(temp_left.begin() + i);
        output_permutations(s, temp_left, temp_bu);
    }
}

void output_all_permutations(string s) {
    vector<int> l;
    vector<int> b;
    for(int i=0; i<s.length(); i++) {  // build up initial vector
        l.push_back(i);
    }
    output_permutations(s, l, b);
}

int main() {
    // test cases are assuming that string will always be passed in..
    // otherwise would need to test different types

    output_all_permutations("abc"); // normal test case
    output_all_permutations(""); // empty string
    output_all_permutations("bbb"); // same letter multiple times
    output_all_permutations("bbac"); // same letter with other letters
    output_all_permutations("bacb"); // same letter not repetitive
    output_all_permutations("a"); // single letter in string
    output_all_permutations(" "); // only space character in string
    output_all_permutations("a b c"); // spaces between letters in string
    output_all_permutations("a   b   c"); // multiple spaces in a row between letters
    output_all_permutations(" abc "); // spaces to start and end string
    output_all_permutations("12345"); // integers inside string
    output_all_permutations("askdjasdfasasdffhaklsjdhfaksdhfka"); // long string to ensure adequate run time
    output_all_permutations("[]!@#$]["); // will work with strange characters

    return 0;
}