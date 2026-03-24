#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Hewan
{
    int id;
    string nama;
    string jenisLayanan;
    int harga;
};

void swap(Hewan *a, Hewan *b)
{
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

void tambahData(Hewan *arr, int *n)
{
    if (*n >= 100)
    {
        cout << "Kapasitas penuh!" << endl;
        return;
    }

    (arr + *n)->id = *n + 1;
    cout << "ID                : " << (arr + *n)->id << endl;
    cout << "Nama              : ";
    cin.ignore();
    getline(cin, (arr + *n)->nama);
    cout << "Layanan/Tindakan  : ";
    getline(cin, (arr + *n)->jenisLayanan);
    cout << "Harga (Rp)        : ";
    cin >> (arr + *n)->harga;
    (*n)++;
    cout << "Data berhasil ditambahkan!" << endl;
}

void tampilData(Hewan *arr, int n)
{
    if (n == 0)
    {
        cout << "Belum ada data!" << endl;
        return;
    }
    cout << "========================================================" << endl;
    cout << "ID\tNama      \tLayanan\t\t\tHarga" << endl;
    cout << "========================================================" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << (arr + i)->id << "\t"
            << (arr + i)->nama << "\t\t"
            << (arr + i)->jenisLayanan << "\t\t\tRp "
            << (arr + i)->harga << endl;
    }
    cout << "========================================================" << endl;
}

void linearSearch(Hewan *arr, int n, string target)
{
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if ((arr + i)->nama == target)
        {
            cout << "=> Ditemukan: ID " << (arr + i)->id << " | Layanan: " << (arr + i)->jenisLayanan << " | Harga: Rp" << (arr + i)->harga << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Data dengan nama '" << target << "' tidak ditemukan." << endl;
}

void urutkanBerdasarkanID(Hewan *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((arr + j)->id > (arr + j + 1)->id)
            {
                swap((arr + j), (arr + j + 1));
            }
        }
    }
}

void fibonacciSearch(Hewan *arr, int n, int target)
{
    if (n == 0)
    {
        cout << "Data kosong!" << endl;
        return;
    }
    urutkanBerdasarkanID(arr, n);

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;
    while (fib < n)
    {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;
    int iterasi = 1;
    while (fib > 1)
    {
        int i = min(offset + fib2, n - 1);
        cout << "[Iterasi " << iterasi++ << "] Memeriksa indeks ke-" << i << " (Mencari ID: " << (arr + i)->id << ")" << endl;
        if ((arr + i)->id < target)
        {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else if ((arr + i)->id > target)
        {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
        else
        {
            cout << "Nama: " << (arr + i)->nama << " | Layanan: " << (arr + i)->jenisLayanan << " | Harga: Rp" << (arr + i)->harga << endl;
            return;
        }
    }

    if (fib1 == 1 && offset + 1 < n && (arr + offset + 1)->id == target)
    {
        cout << "[Iterasi " << iterasi << "] Memeriksa indeks ke-" << offset + 1 << " (Mencari ID: " << (arr + offset + 1)->id << ")" << endl;
        cout << "Nama: " << (arr + offset + 1)->nama << " | Layanan: " << (arr + offset + 1)->jenisLayanan << " | Harga: Rp" << (arr + offset + 1)->harga << endl;
        return;
    }

    cout << "ID " << target << " tidak ditemukan dalam sistem." << endl;
}

void bubbleSort(Hewan *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((arr + j)->nama > (arr + j + 1)->nama)
            {
                swap((arr + j), (arr + j + 1));
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan Nama Hewan (A-Z)." << endl;
}

void selectionSort(Hewan *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if ((arr + j)->harga < (arr + min_idx)->harga)
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap((arr + i), (arr + min_idx));
        }
    }
    cout << "Data berhasil diurutkan berdasarkan Harga Termurah." << endl;
}

int main()
{
    Hewan dataPawcare[100];
    int jumlahData = 0;
    int pilihan;

    do
    {
        cout << "=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tampil Semua Data Hewan" << endl;
        cout << "2. Tambah Data Baru" << endl;
        cout << "3. Cari Nama Hewan (Linear Search)" << endl;
        cout << "4. Cari ID Layanan (Fibonacci Search)" << endl;
        cout << "5. Urutkan Nama A-Z (Bubble Sort)" << endl;
        cout << "6. Urutkan Harga Termurah (Selection Sort)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            tampilData(dataPawcare, jumlahData);
        }
        else if (pilihan == 2)
        {
            tambahData(dataPawcare, &jumlahData);
        }
        else if (pilihan == 3)
        {
            string cariNama;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, cariNama);
            linearSearch(dataPawcare, jumlahData, cariNama);
        }
        else if (pilihan == 4)
        {
            int cariID;
            cout << "Masukkan ID: ";
            cin >> cariID;
            fibonacciSearch(dataPawcare, jumlahData, cariID);
        }
        else if (pilihan == 5)
        {
            bubbleSort(dataPawcare, jumlahData);
        }
        else if (pilihan == 6)
        {
            selectionSort(dataPawcare, jumlahData);
        }
        else if (pilihan != 0)
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
    return 0;
}