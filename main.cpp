#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>

using namespace std;

// struct buku
struct Book {
    string id, judul, pengarang, penerbit, stock;
};

// Fungsi untuk menampilkan buku dari databse
void tampilBuku();

// Fungsi untuk menambah buku ke databse
void tambahBuku();

// Fungsi untuk mencari data buku
void cariBuku();

// Fungsi untuk mengedit data buku
void editBuku();

// Fungsi untuk menghapus data buku dari databse
void hapusBuku();

// Fungsi untuk menampilkan data peminjam dari databse
void tampilPeminjam();

// Fungsi untuk menampilkan menu admin
void admin();

// Fungsi untuk menontroll login admin
void authAdmin();

// Fungsi untuk mengontroll peminjaman
void pinjamBuku();

// Fungsi untuk menampilkan menu awal program
void home();

fstream connectDB(string DB);

// Fungsi untuk check database kosong atau tidak
int getDBSize(string DB);


int main() {
    bool status = true;
    char opt;
    do {
        home();
        
        cout << "  Apakah ingin kembali ke menu awal? [y/n]: ";
        cin >> opt;

        if((opt == 'n') || (opt == 'N')) status = false;

    } while(status);

    return 0;
}

void home(){
    system("cls");
    int opt;
    
    cout << "+==========================+\n"
         << "|      PERPUSTAKAAN        |\n"
         << "+==========================+\n"
         << "| 1. Lihat Daftar Buku     |\n"
         << "| 2. Lihat Daftar Peminjam |\n"
         << "| 3. Cari Buku             |\n"
         << "| 4. Pinjam Buku           |\n"
         << "| 5. Login Admin           |\n"
         << "| 6. Keluar                |\n"
         << "+==========================+\n";

    reOption:
    cout << "  Masukkan Pilihan: ";
    cin >> opt;

    if((opt >= 1) && (opt <= 6)) {
        switch(opt) {
            case 1:
                tampilBuku();
                break;
            case 2:
                tampilPeminjam();
                break;
            case 3:
                cariBuku();
                break;
            case 4:
                pinjamBuku();
                break;
            case 5:
                authAdmin();
                break;
            case 6:
                exit(0);
                break;
        }
    } else {
        cout <<  "Pilihan tidak valid, silahkan masukkan lagi\n";
        //Sleep(1000);
        goto reOption;
    }
         
};

fstream connectDB(string DB) {
    fstream data;
    data.open("database\\" + DB, ios::in | ios::out | ios::app);

    if(!data.is_open()) {
        cout << "Database buku tidak ditemukan! \n";
        data.open("database\\" + DB, ios::trunc | ios::out | ios::app);
        exit(0);
    }

    return data;
}

int getDBSize(string DBName){
    fstream data = connectDB(DBName);

    int count = 0;
    string line;
    while(data.good()) {
        while(getline(data, line)) {
            count++;
        }
    }

    return count;
    data.close();

}
void tampilBuku(){
    /*
        tampilBuku() digunakan untuk menampilkan data buku dari database.
        1. Deklarasi data sbg ifstream
        2. Buka database dg data.open()
        3. check apakah data kosong atau tidak
        4. Deklrasi dan inisialisasi var isEmptyData untuk mengecek apakah database kosong atau tidak
        5. Jika database kosong, tampilkan "Tidak Ada Buku"
        6. Jika data ada, tampilkan semua data
    */
    system("cls");

    fstream data = connectDB("buku.csv");

    int isEmptyData = getDBSize("buku.csv");

    cout << "+=======================================================================+\n"
         << "|                              DAFTAR BUKU                              |\n"
         << "+=======================================================================+\n";


    if(isEmptyData == 0) {
       cout << "| Tidak Ada Buku \t\t\t\t\t\t\t|\n"
            << "+=======================================================================+\n";
    } else {

        string stock;
        string line;

        Book readBook;        

        while(data.good()) {
    
            getline(data, line);

            stringstream ss(line);

            getline(ss, readBook.id, ',');
            getline(ss, readBook.judul, ',');
            getline(ss, readBook.pengarang, ',');
            getline(ss, readBook.penerbit, ',');
            getline(ss, readBook.stock);

            Sleep(500);
            if(line != "") {
                cout << "| ID Buku\t: " << readBook.id << endl
                     << "| Judul Bukut\t: " << readBook.judul << endl
                     << "| Pengarang\t: " << readBook.pengarang << endl
                     << "| Penerbit\t: " << readBook.penerbit << endl
                     << "| Stock Buku\t: " << readBook.stock << endl;
                cout << "+=======================================================================+\n";
            } 
        }
    }

    data.close();
};
void tambahBuku(){
    bool status = true;
    char opt;

    cout << "\n  Tambah Buku  \n";

    while(status) {

        fstream data = connectDB("buku.csv");
        
        Book addBook;
        int jumlah, countAdd = 0;

        cout << "  Masukkan Jumlah Buku: ";

        cin >> jumlah; 

        for(int i = 0; i < jumlah; i++) {

            reID:
            cout << "\n  Masukkan ID Buku\t: ";
            cin >> addBook.id;
            cin.ignore();

            cout << "  Masukkan Judul Buku\t: ";
            getline(cin, addBook.judul);
            cout << "  Masukkan Pengarang\t: ";
            getline(cin, addBook.pengarang);
            cout << "  Masukkan Penerbit\t: ";
            getline(cin, addBook.penerbit);
            cout << "  Masukkan Stock Buku\t: ";
            cin >> addBook.stock;

            data << addBook.id << ","
                 << addBook.judul << ","
                 << addBook.pengarang << ","
                 << addBook.penerbit << ","
                 << addBook.stock << "\n";
        }

        data.close();

        cout << "  Ingin melanjutkan tambah data? [y/n]: ";
        cin >> opt;

        if((opt == 'n') || (opt == 'N')) status = false;
    }
    
};
void cariBuku(){
    cin.ignore();
    bool status = true;
    char opt;

    while(status) {
        system("cls");

        fstream data = connectDB("buku.csv");

        cout << "+=======================================================================+\n"
             << "|                               PENCARIAN                               |\n"
             << "+=======================================================================+\n";

            string stock, line, cari;
            int countCari = 0;

            cout << "|  Masukkan kata Kunci: ";
            getline(cin, cari);
            cout << "+=======================================================================+\n";
            
            Book findBook;

            while(data.good()) {

                getline(data, line);
                stringstream ssline(line);

                getline(ssline, findBook.id, ',');
                getline(ssline, findBook.judul, ',');
                getline(ssline, findBook.pengarang, ',');
                getline(ssline, findBook.penerbit, ',');
                getline(ssline, findBook.stock);

                string tmp;
                
                stringstream ssjudul(findBook.judul);
                stringstream sspengarang(findBook.pengarang);
                stringstream sspenerbit(findBook.penerbit);


                if( line != "" ) {
                    while(getline(ssjudul, tmp, ' ') || getline(sspengarang, tmp, ' ') || getline(sspenerbit, tmp, ' ')) {
                        //cout << "Judul: " << tmp;
                        if((cari == tmp) ||(cari == findBook.id) || (cari == findBook.judul) || (cari == findBook.pengarang) || (cari == findBook.penerbit)) {
                            cout << "| ID Buku\t: " << findBook.id << endl
                                 << "| Judul Bukut\t: " << findBook.judul << endl
                                 << "| Pengarang\t: " << findBook.pengarang << endl
                                 << "| Penerbit\t: " << findBook.penerbit << endl
                                 << "| Stock Buku\t: " << findBook.stock << endl;
                            cout << "+=======================================================================+\n";
                            countCari = 1;
                            break;
                        }
                    }
                }
                
            }

            if((countCari == 0)) cout << "\n  Data dengan Keyword " << "\"" << cari << "\"" << " tidak ditemukan \n\n";


        data.close();

        cout << "  Ingin melanjutkan pencarian? [y/n]: ";
        cin >> opt;
        cin.ignore();
        
        if((opt == 'n') || (opt == 'N')) status = false;
    }
}
void editBuku(){
    cout << "  Halaman Edit Buku\n";

    cin.ignore();
    bool status = true;
    char opt;

    while(status) {
        system("cls");

        fstream data = connectDB("buku.csv");
        fstream newData = connectDB("newBuku.csv");

        cout << "+=======================================================================+\n"
             << "|                               EDIT BUKU                               |\n"
             << "+=======================================================================+\n";

            string stock, line, idBuku, newVal;
            int countEdit = 0, element;

            cout << "|  Masukkan ID Buku: ";
            cin >> idBuku;
            cout << "+=======================================================================+\n";

            
            
            Book editBook;

            while(data.good()) {

                getline(data, line);
                stringstream ssline(line);

                getline(ssline, editBook.id, ',');
                getline(ssline, editBook.judul, ',');
                getline(ssline, editBook.pengarang, ',');
                getline(ssline, editBook.penerbit, ',');
                getline(ssline, editBook.stock);

                if(idBuku == editBook.id) {
                    cout << "\n  Pilih data yang akan diedit\n"
                         << "  1. Judul, 2. Pengarang, 3. Penerbit, 4. Stock: ";
                    cin >> element;
                    
                    cin.ignore();

                    cout << "\n  Masukkan Data Baru: ";
                    getline(cin, newVal);
                    countEdit = 1;
                } 

                string tmp;
                
                stringstream ssid(editBook.id);


                if( line != "" ) {
                    while(getline(ssid, tmp)) {

                        if((idBuku != tmp)) {

                            newData << editBook.id << ","
                                    << editBook.judul << ","
                                    << editBook.pengarang << ","
                                    << editBook.penerbit << ","
                                    << editBook.stock << "\n";

                        } else {

                            switch(element){
                                case 1:
                                    newData << editBook.id << ","
                                            << newVal << ","
                                            << editBook.pengarang << ","
                                            << editBook.penerbit << ","
                                            << editBook.stock << "\n";
                                    break;
                                case 2:
                                    newData << editBook.id << ","
                                            << editBook.judul << ","
                                            << newVal << ","
                                            << editBook.penerbit << ","
                                            << editBook.stock << "\n";
                                    break;
                                case 3:
                                    newData << editBook.id << ","
                                            << editBook.judul << ","
                                            << editBook.pengarang << ","
                                            << newVal << ","
                                            << editBook.stock << "\n";
                                    break;
                                case 4:
                                    newData << editBook.id << ","
                                            << editBook.judul << ","
                                            << editBook.pengarang << ","
                                            << editBook.penerbit << ","
                                            << newVal << "\n";
                                    break;
                            }
                            countEdit = 1;
                        }
                    }
                }
                
            }

            if((countEdit == 1)) {
                cout << "\n  Data pada Buku dengan ID: " << "\"" << idBuku << "\"" << " telah diubah \n\n";
            } else {
                cout << "\n  Buku dengan ID: " << "\"" << idBuku << "\"" << " tidak ditemukan \n\n";
            }


        data.close();
        newData.close();

        remove("database/buku.csv");
        rename("database/newBuku.csv", "database/buku.csv");

        cout << "  Ingin melanjutkan pengeditan data? [y/n]: ";
        cin >> opt;
        cin.ignore();
        
        if((opt == 'n') || (opt == 'N')) status = false;
    }
};
void hapusBuku(){
    cout << "  Halaman Hapus Buku\n";

    cin.ignore();
    bool status = true;
    char opt;

    while(status) {
        system("cls");

        fstream data = connectDB("buku.csv");
        fstream newData = connectDB("newBuku.csv");

        cout << "+=======================================================================+\n"
             << "|                              HAPUS BUKU                               |\n"
             << "+=======================================================================+\n";

            string stock, line, idBuku;
            int countDel = 0;

            cout << "|  Masukkan ID Buku: ";
            cin >> idBuku;
            cout << "+=======================================================================+\n";
            
            Book delBook;

            while(data.good()) {

                getline(data, line);
                stringstream ssline(line);

                getline(ssline, delBook.id, ',');
                getline(ssline, delBook.judul, ',');
                getline(ssline, delBook.pengarang, ',');
                getline(ssline, delBook.penerbit, ',');
                getline(ssline, delBook.stock);

                string tmp;
                
                stringstream ssid(delBook.id);

                if( line != "" ) {
                    while(getline(ssid, tmp)) {
                        if((idBuku != tmp)) {
                            newData << delBook.id << ","
                                    << delBook.judul << ","
                                    << delBook.pengarang << ","
                                    << delBook.penerbit << ","
                                    << delBook.stock << "\n";
                        } else {
                            countDel = 1;
                        }
                    }
                }
                
            }

            if((countDel == 1)) {
                cout << "\n  Buku dengan ID: " << "\"" << idBuku << "\"" << " telah dihapus \n\n";
            } else {
                cout << "\n  Buku dengan ID: " << "\"" << idBuku << "\"" << " tidak ditemukan \n\n";
            }


        data.close();
        newData.close();

        remove("database/buku.csv");
        rename("database/newBuku.csv", "database/buku.csv");

        cout << "  Ingin melanjutkan penghapusan data? [y/n]: ";
        cin >> opt;
        cin.ignore();
        
        if((opt == 'n') || (opt == 'N')) status = false;
    }
};
void tampilPeminjam(){
    cout << "  Halaman Tampil Peminjam\n";
};
void admin(){
    bool status = true;
    char opt;

    while(status) {
        system("cls");
        int option;
        cout << "+==========================+\n"
             << "|      ADMINISTRATOR       |\n"
             << "+==========================+\n"
             << "| 1. Lihat Daftar Buku     |\n"
             << "| 2. Tambah Buku           |\n"
             << "| 3. Edit Buku             |\n"
             << "| 4. Hapus Buku            |\n"
             << "| 5. Logout                |\n"
             << "+==========================+\n";

        reOption:
        cout << "  Masukkan Pilihan: ";
        cin >> option;

        if((option >= 1) && (option <= 6)) {
            switch(option) {
                case 1:
                    tampilBuku();
                    break;
                case 2:
                    tambahBuku();
                    break;
                case 3:
                    editBuku();
                    break;
                case 4:
                    hapusBuku();
                    break;
                case 5:
                    cout << "\n  Anda telah keluar..\n";
                    Sleep(1000);
                    home();
                    break;
            }
        } else {
            cout <<  "Pilihan tidak valid, silahkan masukkan lagi\n";
            //Sleep(1000);
            goto reOption;
        }

        cout << "  Apakah ingin melanjutkan ke menu Admin? [y/n]: ";
        cin >> opt;

        if((opt == 'n') || (opt == 'N')) status = false;
    }
};
void authAdmin(){
    bool status = true;
    char opt;
    
    while(status) {
        string username, password;

        cout << "\n  Login Administrator \n";
        relogin:
        cout << "  Masukkan Username: ";
        cin >> username;
        cout << "  Masukkan Passowrd: ";
        cin >> password;

        if((username == "admin") && (password == "admin")) {
            Sleep(1000);
            admin();
        } else {
            Sleep(1000);
            cout << "  Username atau Password salah! Silahkan cek ulang\n";
            goto relogin;
        }

        cout << "  Anda telah keluar, Apakah ingin login kembali? [y/n]: ";
        cin >> opt;
        
        if((opt == 'n') || (opt == 'N')) status = false;
    }
};
void pinjamBuku(){
    cout << "  Halaman Pinjam Buku\n";
};
