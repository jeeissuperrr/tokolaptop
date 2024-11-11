#include <iostream>
#include "select.h"
using namespace std;

struct Account {
    string username;
    string password;
};

struct Laptop {
    int id;
    string brand;
    string model;
};

struct Accounts {
    Account akun;
    Accounts *next;
};

struct Laptops {
    Laptop data;
    Laptops *next;
};

struct Database {
    Accounts *admin;
    Laptops *laptops;
};

void menuMain() {
    string opsi[] = {"Login", "Register", "Exit"};
    string opsi_header = "Selamat Datang di Jahron Cyber";
    int jumlah_opsi = 3;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            // login();
            break;
        case 1:
            // register();
            break;
        case 2:
            // exit();
            break;
    }
}

void menuAdmin() {
    string opsi[] = {"List Laptop", "Tambah Laptop", "Ubah Laptop", "Hapus Laptop", "Logout"};
    string opsi_header = "Menu Admin";
    int jumlah_opsi = 5;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            // listLaptop();
            break;
        case 1:
            // tambahLaptop();
            break;
        case 2:
            // ubahLaptop();
            break;
        case 3:
            // hapusLaptop();
            break;
        case 4:
            // logout();
            break;
    }
}

void menuUser() {
    string opsi[] = {"Lihat Laptop", "Beli Laptop", "Cari Laptop", "Logout"};
    string opsi_header = "Menu User";
    int jumlah_opsi = 4;
    int pilih = showmenu(jumlah_opsi, opsi, opsi_header);
    switch (pilih) {
        case 0:
            // lihatLaptop();
            break;
        case 1:
            // beliLaptop();
            break;
        case 2:
            // CariLaptop();
            break;
        case 3:
            // logout();
            break;
    }
}

int main() {
    menuMain();
    return 0;
}