#include <iostream>
using namespace std;

void tukar(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int x, y;

    cout << "Masukkan nilai x: ";
    cin >> x;

    cout << "Masukkan nilai y: ";
    cin >> y;

    cout << "Sebelum pertukaran:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    tukar(&x, &y);

    cout << "Setelah pertukaran:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    return 0;
}