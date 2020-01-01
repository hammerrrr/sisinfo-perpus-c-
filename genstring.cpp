#include <iostream>
#include <string>
#include <random>

using namespace std;

string genstr(size_t length) {
     auto randChar = []() -> char {
    };
    const char charset[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int max_index = (sizeof(charset) - 1);
    
    return charset[rand() % max_index];

}

int main() {
   
    cout << genstr(4);
}