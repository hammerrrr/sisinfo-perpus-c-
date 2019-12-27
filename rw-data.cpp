#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void getArr() {
    ifstream data;
    data.open("database/buku.csv");

    if(!data.is_open()) cout << "DB tdk ada \n";

    string line, id, judul, pengarang, penerbit, stock;
    int count = 0;
    while(data.good()) {
        count++;
        cout << count;
        while(getline(data, line)) {
            //cout << line << endl;
        }
    }

    string arr[count][5];

    int i = 0;
    while(data.good()) {
        while(getline(data, line)) {
            cout << line << endl;
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, judul, ',');
            getline(ss, pengarang, ',');
            getline(ss, penerbit, ',');
            getline(ss, stock);

            arr[i][0] = id;
            arr[i][1] = judul;
            arr[i][2] = pengarang;
            arr[i][3] = penerbit;
            arr[i][4] = stock;
            cout << line;


        }
    }

    cout << arr[1][0];
    cout << count;
}
void read_data() {
    cout << "Read Data: \n";
    ifstream data;
    data.open("database/buku.csv");

    if(!data.is_open()) cout << "data tidak ada\n";

    string id, judul, pengarang, penerbit, stock, line;
    int count = 0;
    while(data.good()) {
        getline(data, line);

        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, judul, ',');
        getline(ss, pengarang, ',');
        getline(ss, penerbit, ',');
        getline(ss, stock);

        cout << id << endl;

        // cout << "ID Buku\t\t: " << id << endl
        //      << "Judul\t\t: " << judul << endl
        //      << "Pengarang\t: " << pengarang << endl
        //      << "Penerbit\t: " << penerbit << endl
        //      << "Stock\t\t: " << stock << endl
        //      << "==========================" << endl;
        count++;
    }

    cout << count << "endl";
}

void find_data() {
    cout << "Read Data: \n";
    ifstream data;
    data.open("database/buku.csv");

    if(!data.is_open()) cout << "data tidak ada\n";

    string id, judul, pengarang, penerbit, stock, cari;
    int count = 0;

    cout << "Masukkan Data yang dicari: ";
    cin >> cari;
    
    while(data.good()) {
        getline(data, id, ',');
        getline(data, judul, ',');
        getline(data, pengarang, ',');
        getline(data, penerbit, ',');
        getline(data, stock, '\n');

        if(cari == id) {
            cout << "ID Buku\t\t: " << id << endl
             << "Judul\t\t: " << judul << endl
             << "Pengarang\t: " << pengarang << endl
             << "Penerbit\t: " << penerbit << endl
             << "Stock\t\t: " << stock << endl
             << "==========================" << endl;

             count = 1;
        }
    }

    if(count == 0) cout << "Data tidak ditemukan\n";
}

void write_data() {

}

int main() {

   
    cout << "Menu: " << endl
         << "1. Read Data" << endl
         << "2. Write Data" << endl
         << "3. Cari Data" << endl
         << "4. Keluar" << endl
         << "5. DBG::Get Array" << endl;
    
    int pilihan;
    cout << "Masukkan Pilihan: ";
    cin >> pilihan;

    switch(pilihan) {
        case 1:
            read_data();
            break;
        case 2:
            write_data();
            break;
        case 3:
            find_data();
            break;
        case 4:
            break;
        case 5:
            getArr();
            break;
    }
}
