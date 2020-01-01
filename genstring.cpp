#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;



int main() {
    auto start = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(start);
    
    char * tc = ctime(&end_time);
    string str = string {tc};

    str.pop_back();
    cout << str;
    
    cout << "tes";
    //cout << genstr(4);
}