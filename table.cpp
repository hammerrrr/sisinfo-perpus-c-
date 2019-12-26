#include <iostream>
#include<iomanip>
#include<math.h>

using namespace std;

int main() {
    double n=1;
    int colWidth=30;
    //table header
    cout << setfill('=') << setw(3*colWidth) << "=" << endl;
    cout << setfill('\t') << fixed;
    cout << "|\t" << setw(2) << "ID" << "\t|" << setw(2)
         << "\t" << setw(2) << "ID" << "\t|" << setw(2)
         << "\t" << setw(2) << "ID";
    return 0;

}