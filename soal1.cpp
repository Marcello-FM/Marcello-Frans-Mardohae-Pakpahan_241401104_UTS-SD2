#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Pesanan {
    string namaHewan;
    string menuPesanan;
    int waktuKedatangan;
    int statusVip;
};

string toUpper(string s) {
    for (char &c : s) {
        c = toupper(c);
    }
    return s;
}

bool bandingkanPesanan(const Pesanan& a, const Pesanan& b) {
    if (a.statusVip != b.statusVip) {
        return a.statusVip > b.statusVip;
    }
    return a.waktuKedatangan < b.waktuKedatangan;
}

int main() {
    int jumlahPesanan;
    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlahPesanan;

    vector<Pesanan> antrian;
    cin.ignore(); 

    for (int i = 0; i < jumlahPesanan; i++) {
        Pesanan p;
        p.waktuKedatangan = i + 1;

        cout << "Pesanan " << (i + 1) << ":" << endl;
        cout << "Nama hewan: ";
        getline(cin, p.namaHewan);
        
        cout << "Menu pesanan: ";
        getline(cin, p.menuPesanan);
        
        cout << "Status VIP (1=biasa, 2=VIP): ";
        cin >> p.statusVip;
        
        cin.ignore(); 

        antrian.push_back(p);
    }

    sort(antrian.begin(), antrian.end(), bandingkanPesanan);

    for (int i = 0; i < antrian.size(); i++) {
        Pesanan& p = antrian[i];
        cout << (i + 1) << ". " << toUpper(p.namaHewan) << " - " << p.menuPesanan;
        if (p.statusVip == 2) {
            cout << " [VIP]";
        }
        cout << endl;
    }

    return 0;
}