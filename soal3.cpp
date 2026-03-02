#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "Sebelum dibalik:" << endl;
    int* ptr = prima;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *ptr << " -- Alamat: " << ptr << endl;
        ptr++;
    }

    reverseArray(prima, 7);

    cout << "Sesudah dibalik:" << endl;
    ptr = prima;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *ptr << " -- Alamat: " << ptr << endl;
        ptr++;
    }

    return 0;
}