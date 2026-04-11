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

void linearSearch(Hewan* arr, int n, string target) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        cout << "[Iterasi " << i + 1 << "] Mengecek: " << (arr + i)->nama << endl;
        if ((arr + i)->nama == target) {
            cout << ">> Ditemukan! Melakukan swap ke posisi depan (indeks 0)...\n";
            swap((arr + i), (arr + 0));
            found = true;
            break;
        }
    }
    if (!found) cout << "Data tidak ditemukan.\n";
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
        cout << "[Iterasi " << iterasi++ << "] Indeks: " << i << " (ID: " << (arr + i)->id << ")\n";

        // kondisi jika data langsung ditemukan di indeks i
        if ((arr + i)->id == target)
        {
            swap((arr + i), (arr + 0));
            return 0;
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
                min_idx = j;
        }
        if (min_idx != i)
            swap((arr + i), (arr + min_idx));
    }
    cout << "Data berhasil diurutkan berdasarkan Harga Termurah." << endl;
}

void push(Hewan *stackArr, int *top, Hewan data)
{
    if (*top >= MAX - 1)
    {
        cout << "[Stack Overflow] Riwayat penuh, tidak bisa mencatat lagi!" << endl;
        return;
    }
    (*top)++;
    *(stackArr + *top) = data;
}

void pop(Hewan *stackArr, int *top)
{
    if (*top < 0)
    {
        cout << "[Stack Underflow] Riwayat kosong, tidak ada yang bisa dibatalkan." << endl;
        return;
    }
    cout << "=> Tindakan untuk pasien " << (stackArr + *top)->nama << " telah dibatalkan." << endl;
    (*top)--;
}

void enqueue(Hewan *queueArr, int *front, int *rear, Hewan data)
{
    if ((*rear + 1) % MAX == *front)
    {
        cout << "[Queue Overflow] Antrian sudah penuh!" << endl;
        return;
    }

    if (*front == -1)
    {
        *front = 0;
    }

    *rear = (*rear + 1) % MAX;
    *(queueArr + *rear) = data;
    cout << "Pasien " << data.nama << " (ID: " << data.id << ") masuk ke antrian." << endl;
}

void dequeue(Hewan *queueArr, int *front, int *rear, Hewan *stackArr, int *top)
{
    if (*front == -1)
    {
        cout << "[Queue Underflow] Tidak ada antrian pasien saat ini." << endl;
        return;
    }

    Hewan pasienDipanggil = *(queueArr + *front);
    cout << "=> Memanggil Pasien: " << pasienDipanggil.nama << " (ID: " << pasienDipanggil.id << ") untuk diperiksa." << endl;

    push(stackArr, top, pasienDipanggil);
    cout << "=> Pemeriksaan selesai. Data masuk ke riwayat medis." << endl;

    if (*front == *rear)
    {
        *front = -1;
        *rear = -1;
    }
    else
    {
        *front = (*front + 1) % MAX;
    }
}

void peek(Hewan *queueArr, int front, Hewan *stackArr, int top)
{
    cout << "\n=== STATUS SAAT INI ===" << endl;
    if (front == -1)
    {
        cout << "Antrian Terdepan : Kosong" << endl;
    }
    else
    {
        cout << "Antrian Terdepan : " << (queueArr + front)->nama << " (ID: " << (queueArr + front)->id << ")" << endl;
    }

    if (top < 0)
    {
        cout << "Riwayat Terakhir : Kosong" << endl;
    }
    else
    {
        cout << "Riwayat Terakhir : " << (stackArr + top)->nama << " (ID: " << (stackArr + top)->id << ") - " << (stackArr + top)->jenisLayanan << endl;
    }
    cout << "=======================" << endl;
}

void tampilAntrian(Hewan *queueArr, int front, int rear)
{
    if (front == -1)
    {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "--- Daftar Antrian Pemeriksaan ---" << endl;
    int i = front;
    int nomor = 1;
    while (true)
    {
        cout << nomor++ << ". ID: " << (queueArr + i)->id << " | Nama: " << (queueArr + i)->nama << " | Layanan: " << (queueArr + i)->jenisLayanan << endl;
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
}

void tampilRiwayat(Hewan *stackArr, int top)
{
    if (top < 0)
    {
        cout << "Belum ada riwayat pemeriksaan!" << endl;
        return;
    }
    cout << "--- Riwayat Pemeriksaan Medis (Terbaru -> Terdahulu) ---" << endl;
    for (int i = top; i >= 0; i--)
    {
        cout << "- ID: " << (stackArr + i)->id << " | Nama: " << (stackArr + i)->nama << " | Layanan: " << (stackArr + i)->jenisLayanan << endl;
    }
}

int main()
{
    Hewan dataPawcare[MAX];
    int jumlahData = 0;

    Hewan queueAntrian[MAX];
    int frontQueue = -1;
    int rearQueue = -1;

    Hewan stackRiwayat[MAX];
    int topStack = -1;

    int pilihan;

    do
    {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tampil Semua Data Database" << endl;
        cout << "2. Tambah Data Baru ke Database" << endl;
        cout << "3. Cari Nama Hewan" << endl;
        cout << "4. Cari ID Layanan" << endl;
        cout << "5. Urutkan Nama A-Z" << endl;
        cout << "6. Urutkan Harga Termurah" << endl;
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
                cout << "Database kosong! Tambahkan data ke database (Menu 2) terlebih dahulu." << endl;
                break;
            }
            int idDaftar;
            cout << "Masukkan ID hewan yang masuk antrian: ";
            cin >> idDaftar;

            bool found = false;
            for (int i = 0; i < jumlahData; i++)
            {
                if ((dataPawcare + i)->id == idDaftar)
                {
                    enqueue(queueAntrian, &frontQueue, &rearQueue, *(dataPawcare + i));
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "ID tidak ditemukan di database." << endl;
            break;
        }
        case 8:
            dequeue(queueAntrian, &frontQueue, &rearQueue, stackRiwayat, &topStack);
            break;
        case 9:
            pop(stackRiwayat, &topStack);
            break;
        case 10:
            peek(queueAntrian, frontQueue, stackRiwayat, topStack);
            break;
        case 11:
            tampilAntrian(queueAntrian, frontQueue, rearQueue);
            break;
        case 12:
            tampilRiwayat(stackRiwayat, topStack);
            break;
        case 0:
            cout << "Terima kasih!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (pilihan != 0);
    return 0;
}