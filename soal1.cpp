// hasil analisisnya ada di file penjelasan bang

#include <iostream>
using namespace std;

void FindMin(int A[], int n)
{
    int min = A[0];
    int index = 0;

    for (int i = 1; i < n; i++)
    {
        if (A[i] < min)
        {
            min = A[i];
            index = i;
        }
    }

    cout << "Nilai minimum: " << min << endl;
    cout << "Indeksnya: " << index << endl;
}

int main()
{
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};

    FindMin(A, 8);

    return 0;
}