#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int jumlah = 5;
    Mahasiswa mhs[jumlah];

    for(int i = 0; i < jumlah; i++) {
        cout << "Data Mahasiswa ke-" << i+1 << endl;
        cout << "Nama : ";
        getline(cin, mhs[i].nama);

        cout << "NIM  : ";
        cin >> mhs[i].nim;

        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cout << endl;
    }

    int indeksMax = 0;
    for(int i = 1; i < jumlah; i++) {
        if(mhs[i].ipk > mhs[indeksMax].ipk) {
            indeksMax = i;
        }
    }

    cout << "Mahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama : " << mhs[indeksMax].nama << endl;
    cout << "NIM  : " << mhs[indeksMax].nim << endl;
    cout << "IPK  : " << mhs[indeksMax].ipk << endl;

    return 0;
}