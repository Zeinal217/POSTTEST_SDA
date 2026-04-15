#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct Hewan
{
    int id;
    string nama;
    string jenisLayanan;
    int harga;
};

struct Node
{
    Hewan data;
    Node *next;
};

void swap(Hewan *a, Hewan *b)
{
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

void swapNode(Node *node1, Node *node2)
{
    swap(&(node1->data), &(node2->data));
}

void tambahData(Node *&head, int &lastID)
{
    Node *nodeBaru = new Node();
    lastID++;
    nodeBaru->data.id = lastID;

    cout << "ID                : " << nodeBaru->data.id << endl;
    cout << "Nama              : ";
    cin.ignore();
    getline(cin, nodeBaru->data.nama);
    cout << "Layanan/Tindakan  : ";
    getline(cin, nodeBaru->data.jenisLayanan);
    cout << "Harga (Rp)        : ";
    cin >> nodeBaru->data.harga;
    nodeBaru->next = nullptr;

    if (head == nullptr)
    {
        head = nodeBaru;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
    cout << "Data berhasil ditambahkan ke database!" << endl;
}

void tampilData(Node *head)
{
    if (head == nullptr)
    {
        cout << "Database kosong!" << endl;
        return;
    }
    cout << "========================================================" << endl;
    cout << "ID\tNama      \tLayanan\t\t\tHarga" << endl;
    cout << "========================================================" << endl;
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data.id << "\t"
             << temp->data.nama << "\t\t"
             << temp->data.jenisLayanan << "\t\t\tRp "
             << temp->data.harga << endl;
        temp = temp->next;
    }
    cout << "========================================================" << endl;
}

void linearSearch(Node *head, string target)
{
    if (head == nullptr)
    {
        cout << "Data kosong.\n";
        return;
    }
    Node *temp = head;
    int iterasi = 1;
    bool found = false;

    while (temp != nullptr)
    {
        cout << "[Iterasi " << iterasi++ << "] Mengecek: " << temp->data.nama << endl;
        if (temp->data.nama == target)
        {
            cout << ">> Ditemukan! Melakukan swap ke posisi depan (Head)...\n";
            swapNode(temp, head);
            found = true;
            break;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "Data tidak ditemukan.\n";
}

void bubbleSort(Node *head)
{
    if (head == nullptr || head->next == nullptr)
        return;

    bool ditukar;
    Node *current;
    Node *lptr = nullptr;

    do
    {
        ditukar = false;
        current = head;
        while (current->next != lptr)
        {
            if (current->data.nama > current->next->data.nama)
            {
                swapNode(current, current->next);
                ditukar = true;
            }
            current = current->next;
        }
        lptr = current;
    } while (ditukar);
    cout << "Data berhasil diurutkan berdasarkan Nama Hewan (A-Z)." << endl;
}

void selectionSort(Node *head)
{
    if (head == nullptr)
        return;

    Node *temp = head;
    while (temp != nullptr)
    {
        Node *minNode = temp;
        Node *r = temp->next;

        while (r != nullptr)
        {
            if (r->data.harga < minNode->data.harga)
            {
                minNode = r;
            }
            r = r->next;
        }
        if (minNode != temp)
        {
            swapNode(temp, minNode);
        }
        temp = temp->next;
    }
    cout << "Data berhasil diurutkan berdasarkan Harga Termurah." << endl;
}

void push(Node *&top, Hewan dataPasien)
{
    Node *nodeBaru = new Node();
    nodeBaru->data = dataPasien;
    nodeBaru->next = top;
    top = nodeBaru;
}

void pop(Node *&top)
{
    if (top == nullptr)
    {
        cout << "(Underflow) Riwayat kosong, tidak ada yang bisa dibatalkan." << endl;
        return;
    }
    Node *temp = top;
    cout << "=> Tindakan untuk pasien " << temp->data.nama << " telah dibatalkan." << endl;
    top = top->next;
    delete temp;
}

void enqueue(Node *&front, Node *&rear, Hewan dataPasien)
{
    Node *nodeBaru = new Node();
    nodeBaru->data = dataPasien;
    nodeBaru->next = nullptr;

    if (front == nullptr)
    {
        front = rear = nodeBaru;
    }
    else
    {
        rear->next = nodeBaru;
        rear = nodeBaru;
    }
    cout << "Pasien " << dataPasien.nama << " (ID: " << dataPasien.id << ") masuk ke antrian." << endl;
}

void dequeue(Node *&front, Node *&rear, Node *&top)
{
    if (front == nullptr)
    {
        cout << "(Underflow) Tidak ada antrian pasien saat ini." << endl;
        return;
    }

    Node *temp = front;
    Hewan pasienDipanggil = temp->data;
    cout << "=> Memanggil Pasien: " << pasienDipanggil.nama << " (ID: " << pasienDipanggil.id << ") untuk diperiksa." << endl;

    push(top, pasienDipanggil);
    cout << "=> Pemeriksaan selesai. Data masuk ke riwayat medis." << endl;

    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
}

void peek(Node *front, Node *top)
{
    cout << "\n=== STATUS SAAT INI ===" << endl;
    if (front == nullptr)
    {
        cout << "Antrian Terdepan : Kosong (Underflow)" << endl;
    }
    else
    {
        cout << "Antrian Terdepan : " << front->data.nama << " (ID: " << front->data.id << ")" << endl;
    }

    if (top == nullptr)
    {
        cout << "Riwayat Terakhir : Kosong (Underflow)" << endl;
    }
    else
    {
        cout << "Riwayat Terakhir : " << top->data.nama << " (ID: " << top->data.id << ") - " << top->data.jenisLayanan << endl;
    }
    cout << "=======================" << endl;
}

void tampilAntrian(Node *front)
{
    if (front == nullptr)
    {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "--- Daftar Antrian Pemeriksaan ---" << endl;
    int nomor = 1;
    Node *temp = front;
    while (temp != nullptr)
    {
        cout << nomor++ << ". ID: " << temp->data.id << " | Nama: " << temp->data.nama << " | Layanan: " << temp->data.jenisLayanan << endl;
        temp = temp->next;
    }
}

void tampilRiwayat(Node *top)
{
    if (top == nullptr)
    {
        cout << "Belum ada riwayat pemeriksaan!" << endl;
        return;
    }
    cout << "--- Riwayat Pemeriksaan Medis (Terbaru -> Terdahulu) ---" << endl;
    Node *temp = top;
    while (temp != nullptr)
    {
        cout << "- ID: " << temp->data.id << " | Nama: " << temp->data.nama << " | Layanan: " << temp->data.jenisLayanan << endl;
    }
}

int main()
{
    Node *headDB = nullptr;
    Node *frontQueue = nullptr;
    Node *rearQueue = nullptr;
    Node *topStack = nullptr;

    int lastID = 0;
    int pilihan;

    do
    {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tampil Semua Data Database" << endl;
        cout << "2. Tambah Data Baru ke Database" << endl;
        cout << "3. Cari Nama Hewan" << endl;
        cout << "4. Urutkan Nama A-Z" << endl;
        cout << "5. Urutkan Harga Termurah" << endl;
        cout << "6. Daftarkan Pasien ke Antrian (Enqueue)" << endl;
        cout << "7. Panggil Pasien & Catat Riwayat (Dequeue & Push)" << endl;
        cout << "8. Batalkan Riwayat Terakhir (Pop)" << endl;
        cout << "9. Lihat Pasien Terdepan & Riwayat Terakhir (Peek)" << endl;
        cout << "10. Tampil Semua Antrian" << endl;
        cout << "11. Tampil Semua Riwayat" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tampilData(headDB);
            break;
        case 2:
            tambahData(headDB, lastID);
            break;
        case 3:
        {
            string cariNama;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, cariNama);
            linearSearch(headDB, cariNama);
            break;
        }
        case 4:
        {
            bubbleSort(headDB);
            break;
        }
        case 5:
            selectionSort(headDB);
            break;
        case 6:
        {
            if (headDB == nullptr)
            {
                cout << "Database kosong! Tambahkan data ke database (Menu 2) terlebih dahulu." << endl;
                break;
            }
            int idDaftar;
            cout << "Masukkan ID hewan yang masuk antrian: ";
            cin >> idDaftar;

            bool found = false;
            Node *temp = headDB;
            while (temp != nullptr)
            {
                if (temp->data.id == idDaftar)
                {
                    enqueue(frontQueue, rearQueue, temp->data);
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            if (!found)
                cout << "ID tidak ditemukan di database." << endl;
            break;
        }
        case 7:
        {
            dequeue(frontQueue, rearQueue, topStack);
            break;
        }
        case 8:
            pop(topStack);
            break;
        case 9:
            peek(frontQueue, topStack);
            break;
        case 10:
            tampilAntrian(frontQueue);
            break;
        case 11:
            tampilRiwayat(topStack);
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