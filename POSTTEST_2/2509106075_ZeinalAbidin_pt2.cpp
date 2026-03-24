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

int fibonacciSearch(Hewan *arr, int n, int target)
{
    // menyiapkan 3 deret Fibonacci awal untuk menentukan rentang pembagian.
    int fib2 = 0; // F(k-2)
    int fib1 = 1; // F(k-1)
    int fib = 1; //F(k)

    // looping ini mencari bilangan Fibonacci terkecil yang lebih besar atau sama dengan jumlah elemen, dengan tujuan agar tahu ukuran blok data yang akan dibagi.
    while (fib < n)
    {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    // membuat offset untuk menandai batas indeks array bagian kiri yang sudah dibuang.
    int offset = -1;
    int iterasi = 1;

    // membelah array berdasarkan deret Fibonacci selama ukuran rentang (fib) lebih besar dari 1.
    while (fib > 1)
    {
        // menentukan indeks yang akan dicek, didapat dari offset + F(k-2). fungsi min() mencegah indeks melebihi batas array.
        int i = min(offset + fib2, n - 1);

        // kondisi jika data langsung ditemukan di indeks i
        if ((arr + i)->id == target)
        {
            return i;
        }
        // kondisi jika target lebih besar dari nilai di indeks i, berarti target ada di bagian KANAN array. Kita buang bagian KIRI dengan menggeser offset ke i.lalu deret Fibonacci mundur 1 langkah (dari F(k) menjadi F(k-1)).
        else if ((arr + i)->id < target)
        {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        // kondisi jika target lebih kecil dari nilai di indeks i, berarti target ada di bagian KIRI array. Offset tetap, tapi area pencarian dipersempit, lalu deret Fibonacci mundur 2 langkah (dari F(k) menjadi F(k-2)).
        else
        {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
    }
    // jika loop selesai tapi masih ada 1 elemen tersisa (fib1 == 1), kita cek elemen yang berada persis setelah batas offset terakhir.
    if (fib1 == 1 && (arr + offset + 1)->id == target)
        return offset + 1;

    // Return -1 menandakan pencarian selesai dan ID target tidak ditemukan
    return -1;
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

        switch (pilihan)
        {
        case 1:
            tampilData(dataPawcare, jumlahData);
            break;
        case 2:
            tambahData(dataPawcare, &jumlahData);
            break;
        case 3:
        {
            string cariNama;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, cariNama);
            linearSearch(dataPawcare, jumlahData, cariNama);
            break;
        }
        case 4:
        {
            int cariID;
            cout << "Masukkan ID yang dicari: ";
            cin >> cariID;

            urutkanBerdasarkanID(dataPawcare, jumlahData);

            int hasil = fibonacciSearch(dataPawcare, jumlahData, cariID);

            if (hasil != -1)
            {
                cout << "Data Ditemukan!\n";
                cout << "Nama: " << (dataPawcare + hasil)->nama << "\n";
                cout << "Harga: " << (dataPawcare + hasil)->harga << "\n";
            }
            else
            {
                cout << "ID tidak ditemukan.\n";
            }
            break;
        }
        case 5:
            bubbleSort(dataPawcare, jumlahData);
            break;
        case 6:
            selectionSort(dataPawcare, jumlahData);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan layanan Pawcare!\n";
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (pilihan != 0);
    return 0;
}