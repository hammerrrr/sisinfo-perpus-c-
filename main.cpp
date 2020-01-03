#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <conio.h>

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

// Utilize
void textcolor (int color);
bool loopInput(string &opt);
string genTime();
string toLower(string data);

// Fungsi Buku
void tampilBuku();
void tambahBuku();
void cariBuku();
void editBuku();
void hapusBuku();

// Fungsi Peminjam
void tampilPeminjam();
void pinjamBuku();
void kembalikanBuku();

// Fungsi Admin
void admin();
void authAdmin();

// About Us
void about();

// Fungsi Database
fstream connectDB(string DB);
int getDBSize(string DB);

// Fungsi Home
void home();

int main() {
    bool status = true;
    string opt;

    textcolor(15);
    while(status) {
        home();

        cout << "  Apakah ingin kembali ke menu awal? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);

    }

    return 0;
}
void home(){
    system("cls");
    string opt;

    cout << "+==========================+\n"
         << "|      PERPUSTAKAAN        |\n"
         << "+==========================+\n"
         << "| 1. Lihat Daftar Buku     |\n"
         << "| 2. Lihat Daftar Peminjam |\n"
         << "| 3. Cari Buku             |\n"
         << "| 4. Pinjam Buku           |\n"
         << "| 5. Pengembalian Buku     |\n"
         << "| 6. Login Admin           |\n"
         << "| 7. Keluar                |\n"
         << "| 8. Tentang               |\n"
         << "+==========================+\n";

    reOption:
    cout << "  Masukkan Pilihan: ";
    textcolor(2);
    cin >> opt;
    textcolor(15);

    // while(cin.fail()) {
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //     cout <<  "  Pilihan tidak valid, silahkan masukkan lagi\n";
    //     goto reOption;
    // }

    if (opt == "1") {
        tampilBuku();
    }else if(opt == "2") {
        tampilPeminjam();
    }else if (opt == "3") {
        cariBuku();
    }else if(opt == "4") {
        pinjamBuku();
    }else if(opt == "5") {
        kembalikanBuku();
    }else if(opt == "6") {
        authAdmin();
    }else if(opt == "7"){
        exit(0);
    }else if(opt == "8"){
        about();
    }else{
        textcolor(4);
        cout <<  "  ->  Pilihan tidak valid, silahkan masukkan lagi\n\n";
        textcolor(15);
        Sleep(500);
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
bool loopInput(string &opt) {
    if((opt == "n") || (opt == "N")) return false;
    else if((opt == "y") || (opt == "Y")) return true;
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
string toLower(string data) {
    for_each(data.begin(), data.end(), [](char &c) {
        c = ::tolower(c);
    });

    return data;

}
string genTime() {
    auto start = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(start);

    char * tc = ctime(&end_time);
    string str = string {tc};

    str.pop_back();
    return str;
}
void textcolor (int color) {
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}
void removeTempData() {
    remove("database/newBuku.csv");
    remove("database/newPeminjam.csv");
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
        cout << "| ";
        textcolor(14); 
        cout << "Tidak Ada Buku \t\t\t\t\t\t\t";
        cout << "|\n";

        textcolor(15);
        cout << "+=======================================================================+\n";
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
                cout << "+=======================================================================+\n";
                cout << "| ID Buku      : " << readBook.id << endl
                     << "| Judul Buku   : " << readBook.judul << endl
                     << "| Pengarang    : " << readBook.pengarang << endl
                     << "| Penerbit     : " << readBook.penerbit << endl
                     << "| Stock Buku   : " << stock << endl;
            }
        }
        Sleep(500);
        cout << "+=======================================================================+\n";
    }

    data.close();
};
void tambahBuku(){
    bool status = true;
    string opt;

    while(status) {
        system("cls");

        cout << "+=======================================================================+\n"
             << "|                              TAMBAH BUKU                              |\n"
             << "+=======================================================================+\n";

        fstream data    = connectDB("buku.csv");

        Book addBook, checkBook;
        int jumlah, countAdd = 0;


        string lines, stock;

        int isID = 0;

        cout << "|  Masukkan ID Buku\t: ";
        textcolor(2);
        cin >> addBook.id;
        textcolor(15);

        cin.ignore();

        while(data.good()) {
            getline(data, lines);

            stringstream line(lines);

            getline(line, checkBook.id, ',');
            getline(line, checkBook.judul, ',');
            getline(line, checkBook.pengarang, ',');
            getline(line, checkBook.penerbit, ',');
            getline(line, stock, ',');

            if(lines != "") {
                if(addBook.id == checkBook.id) {
                    isID = 1;
                }
            }
        }

        data.close();
        data = connectDB("buku.csv");

        if(isID == 0) {
            cout << "|  Masukkan Judul Buku\t: ";
            textcolor(2);
            getline(cin, addBook.judul);
            textcolor(15);

            cout << "|  Masukkan Pengarang\t: ";
            textcolor(2);
            getline(cin, addBook.pengarang);
            textcolor(15);

            cout << "|  Masukkan Penerbit\t: ";
            textcolor(2);
            getline(cin, addBook.penerbit);
            textcolor(15);

            cout << "|  Masukkan Stock Buku\t: ";
            textcolor(2);
            cin >> addBook.stock;
            textcolor(15);

            cout << "+=======================================================================+\n";


            data << addBook.id << ","
                 << addBook.judul << ","
                 << addBook.pengarang << ","
                 << addBook.penerbit << ","
                 << addBook.stock << "\n";
        }else {
            textcolor(14);
            cout << "   -|  ID Buku Sudah ada. Silahkan masukkan yang lain\n\n";
            textcolor(15);
        }
        

        cout << "  Ingin melanjutkan tambah data? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);
    }

};
void cariBuku(){
    bool status = true;
    string opt;

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

            textcolor(2);
            getline(cin, cari);
            textcolor(15);

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
                                 << "| Judul Buku\t: " << findBook.judul << endl
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

            if((countCari == 0)) {
                cout << "\n  -|  Data dengan Keyword "; 

                textcolor(3);
                cout << "\"" << cari << "\"";
                textcolor(15);

                cout << " tidak ditemukan \n\n";
            }


        data.close();

        cout << "  Ingin melanjutkan pencarian? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);
    }
}
void editBuku(){

    cin.ignore();
    bool status = true;
    string opt;

    while(status) {
        system("cls");

        removeTempData();

        fstream data    = connectDB("buku.csv");
        fstream newData = connectDB("newBuku.csv");

        cout << "+=======================================================================+\n"
             << "|                               EDIT BUKU                               |\n"
             << "+=======================================================================+\n";

            string stock, line, idBuku, newVal, element;
            int countEdit = 0;

            cout << "|  Masukkan ID Buku: ";

            textcolor(2);
            cin >> idBuku;
            cin.ignore();
            textcolor(15);

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
                         << "| Judul Buku\t: " << editBook.judul << endl
                         << "| Pengarang\t: " << editBook.pengarang << endl
                         << "| Penerbit\t: " << editBook.penerbit << endl
                         << "| Stock Buku\t: " << stock << endl;
                    cout << "+=======================================================================+\n";

                    cout << "\n  Pilih data yang akan diedit: \n";

                    reElement:
                    textcolor(3);
                    cout << "  1. Judul, 2. Pengarang, 3. Penerbit, 4. Stock: ";
                    textcolor(15);

                    textcolor(2);
                    cin >> element;
                    textcolor(15);

                    cin.ignore();

                    if(element == "1" || element == "2" || element == "3" || element == "4") {
                        cout << "\n  Masukkan Data Baru: ";

                        textcolor(2);
                        getline(cin, newVal);
                        textcolor(15);
                    }else {
                        textcolor(14);
                        cout << "  -| Pilihan tidak valid, masukkan ulang\n\n";
                        textcolor(15);
                        goto reElement;
                    }

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

                            countEdit = 1;

                            if(element == "1") {
                                newData << editBook.id << ","
                                        << newVal << ","
                                        << editBook.pengarang << ","
                                        << editBook.penerbit << ","
                                        << stock << "\n";
                            }else if(element == "2") {
                                newData << editBook.id << ","
                                        << editBook.judul << ","
                                        << newVal << ","
                                        << editBook.penerbit << ","
                                        << stock << "\n";
                            }else if(element == "3") {
                                newData << editBook.id << ","
                                        << editBook.judul << ","
                                        << editBook.pengarang << ","
                                        << newVal << ","
                                        << stock << "\n";
                            }else if(element == "4") {
                                newData << editBook.id << ","
                                        << editBook.judul << ","
                                        << editBook.pengarang << ","
                                        << editBook.penerbit << ","
                                        << newVal << "\n";
                            }
                            countEdit = 1;
                        }
                    }
                }

            }

            data.close();
            newData.close();

            if((countEdit == 1)) {
                cout << "\n  -|  Data pada Buku dengan ID: ";

                textcolor(3);
                cout << "\"" << idBuku << "\"";
                textcolor(15);

                cout << " telah diubah \n\n";

                remove("database/buku.csv");
                rename("database/newBuku.csv", "database/buku.csv");
            } else {
                cout << "\n  -|  Buku dengan ID: ";

                textcolor(3);
                cout << "\"" << idBuku << "\"";
                textcolor(15);

                cout << " tidak ditemukan \n\n";
                removeTempData();
            }


        cout << "  Ingin melanjutkan pengeditan data? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        cin.ignore();

        status = loopInput(opt);
    }
};
void hapusBuku(){

    cin.ignore();
    bool status = true;
    string opt;

    while(status) {
        system("cls");

        removeTempData();

        fstream data    = connectDB("buku.csv");
        fstream newData = connectDB("newBuku.csv");

        cout << "+=======================================================================+\n"
             << "|                              HAPUS BUKU                               |\n"
             << "+=======================================================================+\n";

            string stock, line, idBuku;
            int countDel = 0;

            cout << "|  Masukkan ID Buku: ";

            textcolor(2);
            cin >> idBuku;
            textcolor(15);

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

            data.close();
            newData.close();

            if((countDel == 1)) {
                cout << "\n  -|  Buku dengan ID: ";

                textcolor(3);
                cout << "\"" << idBuku << "\""; 
                textcolor(15);

                cout << " telah dihapus \n\n";

                

                remove("database/buku.csv");
                rename("database/newBuku.csv", "database/buku.csv");
            } else {
                cout << "\n  -|  Buku dengan ID: ";

                textcolor(3);
                cout << "\"" << idBuku << "\"";
                textcolor(15);

                cout << " tidak ditemukan \n\n";

                removeTempData();
            }


        

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
       cout << "| ";

       textcolor(14);
       cout << " Tidak Ada Data Peminjam ";
       textcolor(15);

       cout << "\t\t\t\t\t\t|\n"
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
                cout << "| NIM              : " << readPeminjam.nim << endl
                     << "| Nama Mhs         : " << readPeminjam.nama << endl
                     << "| ID Buku          : " << readPeminjam.buku.id << endl
                     << "| Judul Buku       : " << readPeminjam.buku.judul << endl
                     << "| Status           : " << readPeminjam.status << endl
                     << "| Tanggal Pinjam   : " << readPeminjam.borrow_at << endl
                     << "| Tanggal Kembali  : " << readPeminjam.return_at << endl;
            }
        }
        
        Sleep(500);
        cout << "+=======================================================================+\n";
    }

    data.close();

};
void pinjamBuku(){
    bool status = true;
    string opt;

    while(status) {
        system("cls");

        removeTempData();

        Pinjam pinjam;
        Book book, checkBook;

        fstream dataMhs  = connectDB("mhs.csv");
        fstream buku     = connectDB("buku.csv");
        fstream newBuku  = connectDB("newBuku.csv");
        fstream peminjam = connectDB("peminjam.csv");
        
        string lines, nim, idBuku, stock, judulBuku;

        vector<string> vecID, vecJudul;

        int isBuku = 0, isNIM = 0, isStock = 1, isPinjam = 0;

        while(buku.good()) {
            getline(buku, lines);

            stringstream line(lines);

            getline(line, checkBook.id , ',');
            getline(line, checkBook.judul , ',');
            getline(line, checkBook.pengarang , ',');
            getline(line, checkBook.penerbit , ',');
            getline(line, stock , ',');
            checkBook.stock = stoi(stock);

            if(lines != "") {
                if(checkBook.stock > 0) {
                    vecID.push_back(checkBook.id);
                    vecJudul.push_back(checkBook.judul);
                }
            }
        }

        buku.close();
        buku = connectDB("buku.csv");

        cout << "+=======================================================================+\n"
             << "|                             PINJAM BUKU                               |\n"
             << "+=======================================================================+\n";
        
        reinputNim:
        cout << "|  Masukkan NIM\t\t: ";
        textcolor(2);
        cin >> nim;
        textcolor(15);
        cout << "+=======================================================================+\n";

        while(dataMhs.good()) {
            getline(dataMhs, lines);
            
            stringstream line(lines);

            getline(line, pinjam.nim, ',');
            getline(line, pinjam.nama);

            if(lines != "") {

                if(nim == pinjam.nim) {
                    isNIM = 1;
                    Pinjam checkPeminjam;

                    while(peminjam.good()) {
                        getline(peminjam, lines);

                        stringstream line(lines);

                        getline(line, checkPeminjam.nim, ',');
                        getline(line, checkPeminjam.nama, ',');
                        getline(line, checkPeminjam.buku.id, ',');
                        getline(line, checkPeminjam.buku.judul, ',');
                        getline(line, checkPeminjam.status, ',');
                        getline(line, checkPeminjam.borrow_at, ',');
                        getline(line, checkPeminjam.return_at, ',');

                        if(nim == checkPeminjam.nim) {
                            if(checkPeminjam.status == "Pinjam") {
                                cout << "\n  -|  Anda sudah meminjam buku, Peminjaman Max. 1 per Mahasiswa\n";
                                isPinjam = 1;
                                break;
                            }
                        }
                    }

                    peminjam.close();
                    peminjam = connectDB("peminjam.csv");

                    if(isPinjam == 0) {
                        cout << "|  Buku yang tersedia\t: \n";

                        for( int i = 0; i < vecID.size(); i++ ) {
                            cout << "|  [" << vecID[i] << "] - " << vecJudul[i] << endl;
                        }
                        cout << "+=======================================================================+\n";

                        
                        cout << "|  Masukkan ID Buku\t: ";
                        textcolor(2);
                        cin >> idBuku;
                        textcolor(15);
                        cout << "+=======================================================================+\n";

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

                        if(isBuku == 0) {
                            textcolor(14);
                            cout << "\n  -|  Buku yang dipinjam tidak ditemukan \n";
                            textcolor(15);
                        } else {
                            
                            if(isStock == 0)  {
                                textcolor(14);
                                cout << "\n  -|  Stock 0, Buku tidak bisa dipinjam\n";
                                textcolor(15);
                            } else {
                                    cout << "\n  -|  Buku ";

                                    textcolor(3);
                                    cout << judulBuku;
                                    textcolor(15);

                                    cout << " berhasil dipinjam \n";

                                    newBuku.close();
                                    buku.close();

                                    remove("database/buku.csv");
                                    rename("database/newBuku.csv", "database/buku.csv");
                            }
                        }

                        
                    }
                }
            }
        }

        
        if(isNIM == 0){
                textcolor(14);
                cout << "\n  -|  Mahasiswa tidak ditemukan \n";
                textcolor(15);
                newBuku.close();
                removeTempData();
        }
        

        cout << "\n  Apakah Ingin melanjutkan peminjaman? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);

    }
};
void kembalikanBuku(){
    bool status = true;
    string opt;

    while(status) {
        system("cls");

        removeTempData();

        Pinjam kembali;
        Book book;

        fstream peminjam        = connectDB("peminjam.csv");
        fstream newPeminjam     = connectDB("newPeminjam.csv");
        fstream newBuku         = connectDB("newBuku.csv");
        fstream buku            = connectDB("buku.csv");
        
        string lines, lines2, nim, idBuku, stock, judulBuku;
        int isBuku = 0, isNIM = 0, isPinjam = 0;

        cout << "+=======================================================================+\n"
             << "|                         PENGEMBALIAN BUKU                             |\n"
             << "+=======================================================================+\n";
        
        reinputNim:
        cout << "|  Masukkan NIM\t\t: ";

        textcolor(2);
        cin >> nim;
        textcolor(15);

        cout << "+=======================================================================+\n";        

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
                    
                    if(kembali.status != "Dikembalikan") {
                        isPinjam = 1;
                        cout << "|  Buku yang dipinjam\t: [" << kembali.buku.id << "]-" << kembali.buku.judul << endl;
                        cout << "+=======================================================================+\n";
                        
                        cout << "|  Masukkan ID Buku\t: ";

                        textcolor(2);
                        cin >> idBuku;
                        textcolor(15);

                        cout << "+=======================================================================+\n";


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
                    
                }else {
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

        if(isNIM == 1) {
            
            if(isBuku == 1) {
                cout << "\n  -|  Buku \"";

                textcolor(3);
                cout << judulBuku;
                textcolor(15);

                cout << "\" berhasil dikembalikan.\n";
            }

            if(isPinjam == 0) {
                cout << "\n  Anda tidak sedang meminjam buku\n";
            } else {

                remove("database/buku.csv");
                rename("database/newBuku.csv", "database/buku.csv");

                remove("database/peminjam.csv");
                rename("database/newPeminjam.csv", "database/peminjam.csv");
            }
        } else {
            cout << "\n  -|  NIM \"";

            textcolor(3);
            cout << nim;
            textcolor(15);

            cout << "\" tidak meminjam buku \n";

            removeTempData();
        }
        

        cout << "\n  Apakah Ingin melanjutkan pengembalian? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);

    }
}
void admin(){
    bool status = true;
    string opt;
    string option;

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

        textcolor(2);
        cin >> option;
        textcolor(15);

        // while(cin.fail()) {
        //     cin.clear();
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //     cout <<  "  Pilihan tidak valid, silahkan masukkan lagi\n";
        //     goto reOption;
        // }

        if(option == "1") {
            tampilBuku();
        }else if(option == "2") {
            tambahBuku();
        }else if(option == "3") {
            editBuku();
        }else if(option == "4") {
            hapusBuku();
        }else if(option == "5") {
            textcolor(14);
            cout << "\n  -|  Anda telah keluar..\n";
            textcolor(15);

            Sleep(1000);
            home();
        }else {

            textcolor(4);
            cout <<  "  -| Pilihan tidak valid, silahkan masukkan lagi\n";
            textcolor(15);

            Sleep(500);
            goto reOption;
        }

        cout << "  Apakah ingin melanjutkan ke menu Admin? [y/n]: ";

        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);
    }
};
void authAdmin(){
    bool status = true;
    string opt;

    while(status) {
        string username, password;

        cout << "\n  Login Administrator \n";
        relogin:
        cout << "  Masukkan Username: ";
        textcolor(2);
        cin >> username;
        textcolor(15);

        cout << "  Masukkan Passowrd: ";
        textcolor(2);
        cin >> password;
        textcolor(15);

        if((username == "admin") && (password == "admin")) {
            Sleep(1000);
            admin();
        } else {
            Sleep(1000);
            textcolor(4);
            cout << "  -|  Username atau Password salah! Silahkan cek ulang\n\n";
            textcolor(15);
            goto relogin;
        }

        textcolor(14);
        cout << "  -|  Anda telah keluar, Apakah ingin login kembali? [y/n]: ";
        textcolor(2);
        cin >> opt;
        textcolor(15);

        status = loopInput(opt);
    }
};
void about() {
    system("cls");
    Sleep(500);
    cout << "+=====================================================================+\n"
         << "|                          Tentang Kami                               |\n"
         << "+=====================================================================+\n"
         << "|                      SISINFO PERPUSTAKAAN                           |\n"
         << "+=====================================================================+\n"
         << "|      Anggota:                                                       |\n"
         << "+---------------------------------------------------------------------+\n"
         << "|      1. Ivan Nur Ilham Syah                                         |\n"
         << "|      2. Umi Solihah                                                 |\n"
         << "|      3. Muhammad Fathur Rizqi                                       |\n"
         << "|      4. Alma Monika Ivo                                             |\n"
         << "|      5. Stefanus Yoseph M.A. Meak                                   |\n"
         << "|      6. Khias Nurlatif Ari Subekti                                  |\n"
         << "|      7. Muhammad Vicri Ariadi                                       |\n"
         << "|      8. Cahya Laksana                                               |\n"
         << "+---------------------------------------------------------------------+\n";

    cout << "|      SC: ";
    textcolor(3);
    cout << "https://github.com/hammerrrr/sisinfo-perpus-cpp";
    textcolor(15);
    cout << "            |\n";
    cout << "+=====================================================================+\n";
}

