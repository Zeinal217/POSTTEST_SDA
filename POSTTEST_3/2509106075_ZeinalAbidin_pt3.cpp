#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX = 100;

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
    if (*n >= MAX)
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
    cout << "Data berhasil ditambahkan ke database!" << endl;
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
    int fib2 = 0;
    int fib1 = 1;
    int fib = 1;

    while (fib < n)
    {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;
    while (fib > 1)
    {
        int i = min(offset + fib2, n - 1);
        if ((arr + i)->id == target)
            return i;
        else if ((arr + i)->id < target)
        {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }
        else
        {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
    }
    if (fib1 == 1 && (arr + offset + 1)->id == target)
        return offset + 1;

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

void pushRiwayat(Hewan *stackArr, int *top, Hewan data)
{
    if (*top >= MAX - 1)
    {
        cout << "[Stack Overflow] Riwayat penuh, tidak bisa mencatat lagi!" << endl;
        return;
    }
    (*top)++;
    *(stackArr + *top) = data;
}

void enqueue(Hewan *queueArr, int *rear, Hewan data)
{
    if (*rear >= MAX - 1)
    {
        cout << "[Queue Overflow] Antrian sudah penuh!" << endl;
        return;
    }
    (*rear)++;
    *(queueArr + *rear) = data;
    cout << "Pasien " << data.nama << " (ID: " << data.id << ") masuk ke antrian." << endl;
}

void dequeueDanPeriksa(Hewan *queueArr, int *rear, Hewan *stackArr, int *top)
{
    if (*rear == -1)
    {
        cout << "[Queue Underflow] Tidak ada antrian pasien saat ini." << endl;
        return;
    }

    Hewan pasienDipanggil = *(queueArr + 0);
    cout << "Memanggil Pasien: " << pasienDipanggil.nama << " (ID: " << pasienDipanggil.id << ") untuk diperiksa." << endl;

    pushRiwayat(stackArr, top, pasienDipanggil);
    cout << "Pemeriksaan selesai. Data masuk ke riwayat medis." << endl;

    for (int i = 0; i < *rear; i++)
    {
        *(queueArr + i) = *(queueArr + i + 1);
    }
    (*rear)--;
}

void popRiwayat(Hewan *stackArr, int *top)
{
    if (*top == -1)
    {
        cout << "[Stack Underflow] Riwayat kosong, tidak ada yang bisa dibatalkan." << endl;
        return;
    }
    cout << "=> Tindakan untuk pasien " << (stackArr + *top)->nama << " (ID: " << (stackArr + *top)->id << ") telah dibatalkan/dihapus dari riwayat." << endl;
    (*top)--;
}

void peek(Hewan *queueArr, int rear, Hewan *stackArr, int top)
{
    cout << "\n=== STATUS SAAT INI ===" << endl;
    if (rear == -1)
    {
        cout << "Antrian Terdepan : Kosong" << endl;
    }
    else
    {
        cout << "Antrian Terdepan : " << (queueArr + 0)->nama << " (ID: " << (queueArr + 0)->id << ")" << endl;
    }

    if (top == -1)
    {
        cout << "Riwayat Terakhir : Kosong" << endl;
    }
    else
    {
        cout << "Riwayat Terakhir : " << (stackArr + top)->nama << " (ID: " << (stackArr + top)->id << ") - " << (stackArr + top)->jenisLayanan << endl;
    }
    cout << "=======================" << endl;
}

void tampilAntrian(Hewan *queueArr, int rear)
{
    if (rear == -1)
    {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "--- Daftar Antrian Pemeriksaan (Front -> Rear) ---" << endl;
    for (int i = 0; i <= rear; i++)
    {
        cout << i + 1 << "ID: " << (queueArr + i)->id << " | Nama: " << (queueArr + i)->nama << " | Layanan: " << (queueArr + i)->jenisLayanan << endl;
    }
}

void tampilRiwayat(Hewan *stackArr, int top)
{
    if (top == -1)
    {
        cout << "Belum ada riwayat pemeriksaan!" << endl;
        return;
    }
    cout << "--- Riwayat Pemeriksaan Medis (Terbaru -> Terdahulu) ---" << endl;
    for (int i = top; i >= 0; i--)
    {
        cout << "ID: " << (stackArr + i)->id << " | Nama: " << (stackArr + i)->nama << " | Layanan: " << (stackArr + i)->jenisLayanan << endl;
    }
}

int main()
{
    Hewan dataPawcare[MAX];
    int jumlahData = 0;

    Hewan queueAntrian[MAX];
    int rearQueue = -1;

    Hewan stackRiwayat[MAX];
    int topStack = -1;

    int pilihan;

    do
    {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tampil Semua Data" << endl;
        cout << "2. Tambah Data Baru" << endl;
        cout << "3. Cari Nama Hewan (Linear Search)" << endl;
        cout << "4. Cari ID Layanan (Fibonacci Search)" << endl;
        cout << "5. Urutkan Nama A-Z (Bubble Sort)" << endl;
        cout << "6. Urutkan Harga Termurah (Selection Sort)" << endl;
        cout << "7. Daftarkan Pasien ke Antrian (Enqueue)" << endl;
        cout << "8. Panggil Pasien & Catat Riwayat (Dequeue & Push)" << endl;
        cout << "9. Batalkan Riwayat Terakhir (Pop)" << endl;
        cout << "10. Lihat Pasien Terdepan & Riwayat Terakhir (Peek)" << endl;
        cout << "11. Tampil Semua Antrian" << endl;
        cout << "12. Tampil Semua Riwayat" << endl;
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
                cout << "Data Ditemukan!\nNama: " << (dataPawcare + hasil)->nama << "\nHarga: " << (dataPawcare + hasil)->harga << "\n";
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
        case 7:
        {
            if (jumlahData == 0)
            {
                cout << "Data kosong! Tambahkan data terlebih dahulu." << endl;
                break;
            }
            int idDaftar;
            cout << "Masukkan ID hewan yang ingin didaftarkan ke antrian: ";
            cin >> idDaftar;

            bool found = false;
            for (int i = 0; i < jumlahData; i++)
            {
                if ((dataPawcare + i)->id == idDaftar)
                {
                    enqueue(queueAntrian, &rearQueue, *(dataPawcare + i));
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "ID tidak ditemukan." << endl;
            break;
        }
        case 8:
            dequeueDanPeriksa(queueAntrian, &rearQueue, stackRiwayat, &topStack);
            break;
        case 9:
            popRiwayat(stackRiwayat, &topStack);
            break;
        case 10:
            peek(queueAntrian, rearQueue, stackRiwayat, topStack);
            break;
        case 11:
            tampilAntrian(queueAntrian, rearQueue);
            break;
        case 12:
            tampilRiwayat(stackRiwayat, topStack);
            break;
        case 0:
            cout << "Terima kasih telah menggunakan layanan Pawcare!\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n"
                 << endl;
            break;
        }
    } while (pilihan != 0);
    return 0;
}