#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <limits>

using namespace std;

// struct buku
struct Book {
    string id, judul, pengarang, penerbit;
    int stock;
};

struct Pinjam {
    struct Book buku;
    string nim, nama, status, borrow_at, return_at;
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

void kembalikanBuku();

bool loopInput(char &opt);

// fungsi untuk mengubah string ke lowercase
string toLower(string data) {
    for_each(data.begin(), data.end(), [](char &c) {
        c = ::tolower(c);
    });

    return data;

}

// Fungsi untuk menampilkan menu awal program
void home();

fstream connectDB(string DB);

// Fungsi untuk check database kosong atau tidak
int getDBSize(string DB);

string genTime() {
    auto start = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(start);

    char * tc = ctime(&end_time);
    string str = string {tc};

    str.pop_back();
    return str;
}

int main() {
    bool status = true;
    char opt;

    while(status) {
        home();

        cout << "  Apakah ingin kembali ke menu awal? [y/n]: ";
        cin >> opt;

        status = loopInput(opt);

    }

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
         << "| 5. Kembalikan Buku       |\n"
         << "| 6. Login Admin           |\n"
         << "| 7. Keluar                |\n"
         << "+==========================+\n";

    reOption:
    cout << "  Masukkan Pilihan: ";
    cin >> opt;

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<  "  Pilihan tidak valid, silahkan masukkan lagi\n";
        goto reOption;
    }

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
                kembalikanBuku();
                break;
            case 6:
                authAdmin();
                break;
            case 7:
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
        cout << "Database " << DB << " tidak ditemukan! \n";
        data.open("database\\" + DB, ios::trunc | ios::out | ios::app);
        exit(0);
    }

    return data;
}

bool loopInput(char &opt) {
    if((opt == 'n') || (opt == 'N')) return false;
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
            getline(ss, stock);

            Sleep(500);
            if(line != "") {
                cout << "| ID Buku\t: " << readBook.id << endl
                     << "| Judul Buku\t: " << readBook.judul << endl
                     << "| Pengarang\t: " << readBook.pengarang << endl
                     << "| Penerbit\t: " << readBook.penerbit << endl
                     << "| Stock Buku\t: " << stock << endl;
                cout << "+=======================================================================+\n";
            }
        }
    }

    data.close();
};
void tambahBuku(){
    bool status = true;
    char opt;

    while(status) {
        cout << "\n  Tambah Buku  \n";

        fstream data = connectDB("buku.csv");

        Book addBook;
        int jumlah, countAdd = 0;

        cout << "  Masukkan Jumlah Buku: ";

        cin >> jumlah;

        string line, tmpid, stock;

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

        status = loopInput(opt);
    }

};
void cariBuku(){
    bool status = true;
    char opt;

    while(status) {
        cin.ignore();
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
                getline(ssline, stock);

                string tmp;

                stringstream ssjudul(findBook.judul);
                stringstream sspengarang(findBook.pengarang);
                stringstream sspenerbit(findBook.penerbit);


                if( line != "" ) {
                    while(getline(ssjudul, tmp, ' ') || getline(sspengarang, tmp, ' ') || getline(sspenerbit, tmp, ' ')) {
                        //cout << "Judul: " << tmp;
                        if((toLower(cari) == toLower(tmp)) ||(toLower(cari) == toLower(findBook.id)) || (toLower(cari) == toLower(findBook.judul)) || (toLower(cari) == toLower(findBook.pengarang)) || (toLower(cari) == toLower(findBook.penerbit))) {
                            cout << "| ID Buku\t: " << findBook.id << endl
                                 << "| Judul Bukut\t: " << findBook.judul << endl
                                 << "| Pengarang\t: " << findBook.pengarang << endl
                                 << "| Penerbit\t: " << findBook.penerbit << endl
                                 << "| Stock Buku\t: " << stock << endl;
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

        status = loopInput(opt);
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
                getline(ssline, stock);

                if(idBuku == editBook.id) {
                    cout << "+=======================================================================+\n"
                         << "| ID Buku\t: " << editBook.id << endl
                         << "| Judul Bukut\t: " << editBook.judul << endl
                         << "| Pengarang\t: " << editBook.pengarang << endl
                         << "| Penerbit\t: " << editBook.penerbit << endl
                         << "| Stock Buku\t: " << stock << endl;
                    cout << "+=======================================================================+\n";

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
                                    << stock << "\n";

                        } else {

                            switch(element){
                                case 1:
                                    newData << editBook.id << ","
                                            << newVal << ","
                                            << editBook.pengarang << ","
                                            << editBook.penerbit << ","
                                            << stock << "\n";
                                    break;
                                case 2:
                                    newData << editBook.id << ","
                                            << editBook.judul << ","
                                            << newVal << ","
                                            << editBook.penerbit << ","
                                            << stock << "\n";
                                    break;
                                case 3:
                                    newData << editBook.id << ","
                                            << editBook.judul << ","
                                            << editBook.pengarang << ","
                                            << newVal << ","
                                            << stock << "\n";
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

        status = loopInput(opt);
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
                getline(ssline, stock);

                string tmp;

                stringstream ssid(delBook.id);

                if( line != "" ) {
                    while(getline(ssid, tmp)) {
                        if((idBuku != tmp)) {
                            newData << delBook.id << ","
                                    << delBook.judul << ","
                                    << delBook.pengarang << ","
                                    << delBook.penerbit << ","
                                    << stock << "\n";
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

        status = loopInput(opt);
    }
};
void tampilPeminjam(){
    system("cls");

    fstream data = connectDB("peminjam.csv");

    int isEmptyData = getDBSize("peminjam.csv");

    cout << "+=======================================================================+\n"
         << "|                            PEMINJAM BUKU                              |\n"
         << "+=======================================================================+\n";


    if(isEmptyData == 0) {
       cout << "| Tidak Ada Data Peminjam \t\t\t\t\t\t|\n"
            << "+=======================================================================+\n";
    } else {

        string line;

        Pinjam readPeminjam;

        while(data.good()) {

            getline(data, line);

            stringstream ss(line);

            getline(ss, readPeminjam.nim, ',');
            getline(ss, readPeminjam.nama, ',');
            getline(ss, readPeminjam.buku.id, ',');
            getline(ss, readPeminjam.buku.judul, ',');
            getline(ss, readPeminjam.status, ',');
            getline(ss, readPeminjam.borrow_at, ',');
            getline(ss, readPeminjam.return_at);

            Sleep(500);
            if(line != "") {
                
                cout << "+=======================================================================+\n";
                cout << "| NIM\t\t\t: " << readPeminjam.nim << endl
                     << "| Nama Mhs\t\t: " << readPeminjam.nama << endl
                     << "| ID Buku\t\t: " << readPeminjam.buku.id << endl
                     << "| Judul Buku\t\t: " << readPeminjam.buku.judul << endl
                     << "| Status\t\t: " << readPeminjam.status << endl
                     << "| Tanggal Pinjam\t: " << readPeminjam.borrow_at << endl
                     << "| Tanggal Kembali\t: " << readPeminjam.return_at << endl;
                cout << "+=======================================================================+\n";
            }
        }
    }

    data.close();

};
void admin(){
    bool status = true;
    char opt;
    int option;

    while(status) {
        system("cls");
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

        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<  "  Pilihan tidak valid, silahkan masukkan lagi\n";
            goto reOption;
        }

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

        status = loopInput(opt);
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

        status = loopInput(opt);
    }
};
void pinjamBuku(){
    bool status = true;
    char opt;

    while(status) {
        system("cls");

        Pinjam pinjam;
        Book book;

        fstream dataMhs  = connectDB("mhs.csv");
        fstream buku     = connectDB("buku.csv");
        fstream newBuku  = connectDB("newBuku.csv");
        fstream peminjam = connectDB("peminjam.csv");
        
        string lines, nim, idBuku, stock, judulBuku;
        int isBuku = 0, isNIM = 0, isStock = 1;
        
        reinputNim:
        cout << "\n  Masukkan NIM: ";
        cin >> nim;

        while(dataMhs.good()) {
            getline(dataMhs, lines);
            
            stringstream line(lines);

            getline(line, pinjam.nim, ',');
            getline(line, pinjam.nama);

            if(lines != "") {

                if(nim == pinjam.nim) {
                    isNIM = 1;
                    
                    cout << "  Masukkan ID Buku: ";
                    cin >> idBuku;
                    while(buku.good()) {
                        getline(buku, lines);

                        stringstream line(lines);

                        getline(line, book.id, ',');
                        getline(line, book.judul, ',');
                        getline(line, book.pengarang, ',');
                        getline(line, book.penerbit, ',');
                        getline(line, stock);

                        book.stock = stoi(stock);

                        if(lines != "") {
                            if(idBuku == book.id) {
                                    isBuku = 1;
                                    if(book.stock > 0) {
                                        peminjam    << pinjam.nim << ","
                                                    << pinjam.nama << ","
                                                    << book.id << ","
                                                    << book.judul << ","
                                                    << "Pinjam" << ","
                                                    << genTime() << ","
                                                    << "-" << "\n";

                                        peminjam.close();

                                        newBuku     << book.id << ","
                                                    << book.judul << ","
                                                    << book.pengarang << ","
                                                    << book.penerbit << ","
                                                    << book.stock - 1 << "\n";

                                        judulBuku = book.judul;
                                    } else {
                                        isStock = 0;
                                        newBuku << book.id << ","
                                                << book.judul << ","
                                                << book.pengarang << ","
                                                << book.penerbit << ","
                                                << book.stock << "\n";
                                    }
                                } else {
                                    newBuku     << book.id << ","
                                                << book.judul << ","
                                                << book.pengarang << ","
                                                << book.penerbit << ","
                                                << book.stock << "\n";
                                }
                        }
                    }
                }
            }
        }

        
        if(isNIM == 0){
                cout << "\n  Mahasiswa tidak ditemukan \n";
                newBuku.close();
                remove("newBuku.csv");
        } else {
            if(isBuku == 0) {
                    cout << "  Buku yang dipinjam tidak ditemukan \n";
            } else {
                if(isStock == 0)  {
                    cout << "  Stock 0, Buku tidak bisa dipinjam\n";
                } else {
                        cout << "\n  Buku " << judulBuku << " berhasil dipinjam \n";
                        newBuku.close();
                        buku.close();
                        remove("database/buku.csv");
                        rename("database/newBuku.csv", "database/buku.csv");
                }
            }
        }

        
        

        cout << "\n  Apakah Ingin melanjutkan peminjaman? [y/n]: ";
        cin >> opt;

        status = loopInput(opt);

    }
};

void kembalikanBuku(){
    bool status = true;
    char opt;

    while(status) {
        system("cls");

        Pinjam kembali;
        Book book;

        fstream peminjam        = connectDB("peminjam.csv");
        fstream newPeminjam     = connectDB("newPeminjam.csv");
        fstream newBuku         = connectDB("newBuku.csv");
        fstream buku            = connectDB("buku.csv");
        
        string lines, lines2, nim, idBuku, stock, judulBuku;
        int isBuku = 0, isNIM = 0;
        
        reinputNim:
        cout << "\n  Masukkan NIM: ";
        cin >> nim;

        

        while(peminjam.good()) {
            getline(peminjam, lines);
            
            stringstream line(lines);


            getline(line, kembali.nim, ',');
            getline(line, kembali.nama, ',');
            getline(line, kembali.buku.id, ',');
            getline(line, kembali.buku.judul, ',');
            getline(line, kembali.status, ',');
            getline(line, kembali.borrow_at, ',');
            getline(line, kembali.return_at);

            if(lines != "") {

                if(nim == kembali.nim) {
                    isNIM = 1;

                    cout << "  Buku yang dipinjam: [" << kembali.buku.id << "]-" << kembali.buku.judul << endl;
                    
                    cout << "\n  Masukkan ID Buku: ";
                    cin >> idBuku;

                    while(buku.good()) {
                        getline(buku, lines);

                        stringstream line(lines);
                        
                        getline(line, book.id, ',');
                        getline(line, book.judul, ',');
                        getline(line, book.pengarang, ',');
                        getline(line, book.penerbit, ',');
                        getline(line, stock);

                        book.stock = stoi(stock);

                        if(lines != "") {
                            if(idBuku == kembali.buku.id) {
                                isBuku = 1;

                                if(idBuku == book.id) {
                                    newBuku << book.id << ","
                                        << book.judul << ","
                                        << book.pengarang << ","
                                        << book.penerbit << ","
                                        << book.stock + 1 << "\n";

                                }else {
                                    newBuku << book.id << ","
                                        << book.judul << ","
                                        << book.pengarang << ","
                                        << book.penerbit << ","
                                        << book.stock << "\n";
                                }

                                judulBuku = kembali.buku.judul;

                            }else {
                                newBuku << book.id << ","
                                        << book.judul << ","
                                        << book.pengarang << ","
                                        << book.penerbit << ","
                                        << book.stock << "\n";
                                        
                            }
                        }
                    }

                    if(isBuku == 1) {
                        newPeminjam << kembali.nim << ","
                                    << kembali.nama << ","
                                    << kembali.buku.id << ","
                                    << kembali.buku.judul << ","
                                    << "Dikembalikan" << ","
                                    << kembali.borrow_at << ","
                                    << genTime() << "\n";
                    }else {
                        newPeminjam << kembali.nim << ","
                                << kembali.nama << ","
                                << kembali.buku.id << ","
                                << kembali.buku.judul << ","
                                << kembali.status << ","
                                << kembali.borrow_at << ","
                                << kembali.return_at << "\n";
                    }
                } else {
                    newPeminjam << kembali.nim << ","
                                << kembali.nama << ","
                                << kembali.buku.id << ","
                                << kembali.buku.judul << ","
                                << kembali.status << ","
                                << kembali.borrow_at << ","
                                << kembali.return_at << "\n";
                }
            } 
        }

            
        newBuku.close();
        peminjam.close();
        newPeminjam.close();
        buku.close();

        if(isBuku == 1) cout << "\n  Buku " << judulBuku << " berhasil dikembalikan.\n";
        if(isNIM == 1) {
            remove("database/buku.csv");
            rename("database/newBuku.csv", "database/buku.csv");

            remove("database/peminjam.csv");
            rename("database/newPeminjam.csv", "database/peminjam.csv");
        } else {
            remove("database/newBuku.csv");
            remove("database/newPeminjam.csv");
            cout << "\n  NIM " << nim << " tidak meminjam buku \n";
        }
        

        cout << "\n  Apakah Ingin melanjutkan pengembalian? [y/n]: ";
        cin >> opt;

        status = loopInput(opt);

    }
}

