#include <iostream>
#include <string>

using namespace std;

struct Node {
    string namaBarang;
    int hargaBarang;
    int jumlahBarang;
    Node* next;

    Node(string nama, int harga, int jumlah) {
        namaBarang = nama;
        hargaBarang = harga;
        jumlahBarang = jumlah;
        next = NULL;
    }
};

Node* head = NULL;
Node* tail = NULL;

void tambahBelakang(string nama, int harga, int jumlah) {
    Node* newNode = new Node(nama, harga, jumlah);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void hapusBarang(string nama) {
    if (head == NULL) {
        cout << "Barang tidak ada." << endl;
        return;
    }

    if (head->namaBarang == nama) {
        Node* temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        delete temp;
        return; 
    }

    Node* current = head->next;
    Node* prev = head;

    while (current != NULL) {
        if (current->namaBarang == nama) {
            prev->next = current->next;
            if (current == tail) {
                tail = prev;
            }
            delete current;
            return; 
        }
        prev = current;
        current = current->next;
    }

    cout << "Barang tidak ada." << endl;
}

void tampilkanKeranjang() {
    Node* current = head;
    int totalNodes = 0;
    long long totalHarga = 0;

    while (current != NULL) {
        cout << current->namaBarang << " - Rp" << current->hargaBarang 
             << " x" << current->jumlahBarang << endl;
        
        totalHarga += (long long)current->hargaBarang * current->jumlahBarang;
        totalNodes++;
        
        current = current->next;
    }

    cout << "\nTotal barang: " << totalNodes << endl;
    cout << "Total harga: Rp" << totalHarga << endl;
}

int main() {
    int jumlahAwal;
    cout << "Masukkan jumlah barang awal: ";
    cin >> jumlahAwal;
    cin.ignore(); 

    for (int i = 0; i < jumlahAwal; i++) {
        string nama;
        int harga, jumlah;

        cout << "Barang " << (i + 1) << ":" << endl;
        cout << "Nama: ";
        getline(cin, nama);
        cout << "Harga: ";
        cin >> harga;
        cout << "Jumlah: ";
        cin >> jumlah;
        cin.ignore(); 

        tambahBelakang(nama, harga, jumlah);
    }

    char pilihanHapus;
    cout << "\nApakah ingin menghapus barang? (y/n): ";
    cin >> pilihanHapus;
    cin.ignore(); 

    if (pilihanHapus == 'y' || pilihanHapus == 'Y') {
        string namaHapus;
        cout << "Masukkan nama barang yang ingin dihapus: ";
        getline(cin, namaHapus);
        hapusBarang(namaHapus);
    }

    cout << "\nContoh Keluaran :" << endl;
    tampilkanKeranjang();

    return 0;
}