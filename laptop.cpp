#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "select.h"
using namespace std;

struct Laptop {
    int laptop_id;
    string merk;
    string model;
    string spesifikasi;
    int stok;
    double harga;
    Laptop* next;

    Laptop(int id, string m, string mdl, string spec, int stk, double hrg)
        : laptop_id(id), merk(m), model(mdl), spesifikasi(spec), stok(stk), harga(hrg), next(nullptr) {}
};

struct Pesanan {
    int pesanan_id;
    string pelanggan_nama;
    string pelanggan_alamat;
    string pelanggan_telepon;
    int laptop_id;
    int jumlah;
    double total_harga;
    Pesanan* next;

    Pesanan(int id, string nama, string alamat, string telepon, int l_id, int qty, double total)
        : pesanan_id(id), pelanggan_nama(nama), pelanggan_alamat(alamat), pelanggan_telepon(telepon),
          laptop_id(l_id), jumlah(qty), total_harga(total), next(nullptr) {}
};

Laptop* laptopHead = nullptr;
Pesanan* pesananHead = nullptr;
static int lastLaptopId = 0;

Laptop* findLaptopById(int id) {
    Laptop* current = laptopHead;
    while (current != nullptr && current->laptop_id != id) {
        current = current->next;
    }
    return current;
}

void addLaptop(string merk, string model, string spesifikasi, int stok, double harga) {
    int id = ++lastLaptopId;
    Laptop* newLaptop = new Laptop(id, merk, model, spesifikasi, stok, harga);
    newLaptop->next = laptopHead;
    laptopHead = newLaptop;
}

void displayLaptops() {
    Laptop* current = laptopHead;
    while (current != nullptr) {
        cout << "ID: " << current->laptop_id << ", Merk: " << current->merk
             << ", Model: " << current->model << ", Spesifikasi: " << current->spesifikasi
             << ", Stok: " << current->stok << ", Harga: Rp" << std::fixed << std::setprecision(2) << current->harga << endl;
        current = current->next;
    }
}

void addPesanan(int pesanan_id, string nama, string alamat, string telepon, int laptop_id, int jumlah) {
    Laptop* laptop = findLaptopById(laptop_id);
    
    if (!laptop || laptop->stok < jumlah) {
        cout << "Laptop tidak tersedia atau stok kurang.\n";
        return;
    }

    double total_harga = laptop->harga * jumlah;
    Pesanan* newPesanan = new Pesanan(pesanan_id, nama, alamat, telepon, laptop_id, jumlah, total_harga);

    if (!pesananHead) {
        pesananHead = newPesanan;
    } else {
        Pesanan* current = pesananHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPesanan;
    }

    laptop->stok -= jumlah;
    cout << "Pesanan berhasil dibuat.\n";
}

void displayPesanan() {
    Pesanan* current = pesananHead;
    while (current != nullptr) {
        cout << "ID Pesanan: " << current->pesanan_id << ", Nama: " << current->pelanggan_nama
             << ", Alamat: " << current->pelanggan_alamat << ", Telepon: " << current->pelanggan_telepon
             << ", Laptop ID: " << current->laptop_id << ", Jumlah: " << current->jumlah
             << ", Total Harga: Rp" << std::fixed << std::setprecision(2) << current->total_harga << endl;
        current = current->next;
    }
}

void completePesananFromFront() {
    if (!pesananHead) {
        cout << "Tidak ada pesanan untuk diselesaikan.\n";
        return;
    }

    Pesanan* toDelete = pesananHead;
    pesananHead = pesananHead->next;

    delete toDelete;
    cout << "Pesanan telah diselesaikan.\n";
}

void completePesananFromBack() {
    if (!pesananHead) {
        cout << "Tidak ada pesanan untuk diselesaikan.\n";
        return;
    }

    if (!pesananHead->next) {
        delete pesananHead;
        pesananHead = nullptr;
        cout << "Pesanan telah diselesaikan.\n";
        return;
    }

    Pesanan* current = pesananHead;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
    cout << "Pesanan telah diselesaikan.\n";
}

bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    getline(cin, username);
    cout << "Masukkan password admin: ";
    getline(cin, password);
    return (username == "admin" && password == "admin123");
}

void inputPesanan() {
    string nama, alamat, telepon;
    int laptop_id, jumlah;
    cout << "Nama Pelanggan: ";
    getline(cin, nama);
    cout << "Alamat: ";
    getline(cin, alamat);
    cout << "Telepon: ";
    getline(cin, telepon);
    cout << "Masukkan ID Laptop yang ingin dibeli: ";
    cin >> laptop_id; cin.ignore();
    Laptop* laptop = findLaptopById(laptop_id);

    if (!laptop) {
        cout << "Laptop dengan ID " << laptop_id << " tidak ditemukan.\n";
        return;
    }

    cout << "Membeli " << laptop->merk << " " << laptop->model << endl;
    cout << "Masukkan jumlah: ";
    cin >> jumlah; cin.ignore();
    addPesanan(rand() % 1000 + 1, nama, alamat, telepon, laptop_id, jumlah);
}

void searchLaptops(const string& query) {
    Laptop* current = laptopHead;
    bool found = false;
    while (current != nullptr) {
        if (current->merk.find(query) != string::npos || current->model.find(query) != string::npos) {
            cout << "ID: " << current->laptop_id << ", Merk: " << current->merk
                 << ", Model: " << current->model << ", Spesifikasi: " << current->spesifikasi
                 << ", Stok: " << current->stok << ", Harga: Rp" << std::fixed << std::setprecision(2) << current->harga << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Laptop tidak ditemukan.\n";
    }
}

void sortLaptopsByPrice(bool ascending = true) {
    vector<Laptop*> laptops;
    for (Laptop* current = laptopHead; current != nullptr; current = current->next) {
        laptops.push_back(current);
    }

    sort(laptops.begin(), laptops.end(), [ascending](Laptop* a, Laptop* b) {
        return ascending ? a->harga < b->harga : a->harga > b->harga;
    });

    for (auto laptop : laptops) {
        cout << "ID: " << laptop->laptop_id << ", Merk: " << laptop->merk
             << ", Model: " << laptop->model << ", Spesifikasi: " << laptop->spesifikasi
             << ", Stok: " << laptop->stok << ", Harga: Rp" << std::fixed << std::setprecision(2) << laptop->harga << endl;
    }
}

void inputLaptop(string &merk, string &model, string &spesifikasi, int &stok, double &harga) {
    cout << "Merk: ";
    getline(cin, merk);
    cout << "Model: ";
    getline(cin, model);
    cout << "Spesifikasi: ";
    getline(cin, spesifikasi);
    cout << "Stok: ";
    cin >> stok; cin.ignore();
    cout << "Harga: ";
    cin >> harga; cin.ignore();
}

void deleteLaptop(int id) {
    if (!laptopHead) {
        cout << "Tidak ada laptop untuk dihapus.\n";
        return;
    }

    if (laptopHead->laptop_id == id) {
        Laptop* toDelete = laptopHead;
        laptopHead = laptopHead->next;
        delete toDelete;
        cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
        return;
    }

    Laptop* current = laptopHead;
    while (current->next != nullptr && current->next->laptop_id != id) {
        current = current->next;
    }

    if (current->next == nullptr) {
        cout << "Laptop dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    Laptop* toDelete = current->next;
    current->next = current->next->next;
    delete toDelete;
    cout << "Laptop dengan ID " << id << " berhasil dihapus.\n";
}

void showAdminMenu() {
    string menuAdmin[] = {"Lihat Laptop", "Tambah Laptop", "Ubah Laptop", "Hapus Laptop", "Lihat Pesanan", "Keluar"};
    int choice = showmenu(6, menuAdmin, "Menu Admin");

    switch (choice) {
        case 0: displayLaptops(); break;
        case 1: {
            string merk, model, spesifikasi;
            int stok;
            double harga;
            inputLaptop(merk, model, spesifikasi, stok, harga);
            addLaptop(merk, model, spesifikasi, stok, harga);
            break;
        }
        case 2: {
            int id;
            cout << "Masukkan ID Laptop yang ingin diubah: ";
            cin >> id; cin.ignore();
            updateLaptop(id);
            break;
        }
        case 3: {
            int id;
            cout << "Masukkan ID Laptop yang ingin dihapus: ";
            cin >> id; cin.ignore();
            deleteLaptop(id);
            break;
        }
        case 4: displayPesanan(); break;
        case 5: cout << "Keluar\n"; break;
        default: cout << "Pilihan tidak valid.\n"; break;
    }
}

void showCustomerMenu() {
    string menuCustomer[] = {"Lihat Laptop", "Beli Laptop", "Keluar"};
    int pilihan;
    while (true) {
        pilihan = showmenu(3, menuCustomer, "Menu Utama");

        if (pilihan == 0) {
            displayLaptops();
        } else if (pilihan == 1) {
            string query;
            cout << "Masukkan kata kunci untuk pencarian: ";
            getline(cin, query);
            searchLaptops(query);

            cout << "Sort berdasarkan harga?\n1. Ascending\n2. Descending\nPilihan: ";
            int sortChoice;
            cin >> sortChoice; cin.ignore();
            sortLaptopsByPrice(sortChoice == 1);
            inputPesanan();
        } else {
            cout << "Terima kasih, program selesai.\n";
            break;
        }
    }
}

int main() {
    // Menambahkan 3 laptop default
    addLaptop("Asus", "ROG Strix G15", "Intel i7, 16GB RAM, GTX 1660", 10, 15000.00);
    addLaptop("Dell", "XPS 13", "Intel i5, 8GB RAM, 512GB SSD", 15, 20000.00);
    addLaptop("Lenovo", "ThinkPad X1", "Intel i7, 16GB RAM, 1TB SSD", 5, 25000.00);

    int pilihan;
    string menu[] = {"Login Admin", "Beli Laptop", "Keluar"};
    while (true) {
        pilihan = showmenu(3, menu, "Menu Utama");

        if (pilihan == 0) {
            if (loginAdmin()) {
                showAdminMenu();
            } else {
                cout << "Login gagal! Coba lagi.\n";
            }
        } else if (pilihan == 1) {
            showCustomerMenu();
        } else {
            cout << "Terima kasih, program selesai.\n";
            break;
        }
    }
    return 0;
}
