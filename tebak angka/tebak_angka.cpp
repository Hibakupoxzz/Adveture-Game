#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Inisialisasi seed random berdasarkan waktu
    int angkaRahasia = rand() % 100 + 1; // Angka acak antara 1 dan 100
    int tebakan;
    int jumlahTebakan = 0;

    cout << "=== Game Tebak Angka ===" << endl;
    cout << "Tebak angka antara 1 sampai 100!" << endl;

    do {
        cout << "Masukkan tebakanmu: ";
        cin >> tebakan;
        jumlahTebakan++;

        if (tebakan > angkaRahasia) {
            cout << "Terlalu besar!" << endl;
        } else if (tebakan < angkaRahasia) {
            cout << "Terlalu kecil!" << endl;
        } else {
            cout << "Selamat! Kamu menebak dengan benar!" << endl;
            cout << "Jumlah tebakan: " << jumlahTebakan << endl;
        }
    } while (tebakan != angkaRahasia);

    return 0;
}
