// g++ -o main main.cpp -Wall

#include <iostream>
#include <cstdlib>
#define KMAX 5

using namespace std;

int main()
{
    int k = 0;
    do {
        if (k > KMAX) cout << "k wieksze niz KMAX. Podaj mniejsze k!" << endl;
        cout << "Podaj k: "; cin >> k;
    } while (k > KMAX);

    int n = 3*k;
    double *x = new double[n];
    double *A = new double[n];
    double *B = new double[k];

    for (int i=0;i<n;i++) {
        cout << "Podaj x" << i+1 << ": "; cin >> x[i];
    }

    for (int i=0;i<n;i++) {
        cout << "Podaj A" << i+1 << ": "; cin >> A[i];
    }

    for (int i=0;i<k;i++) {
        cout << "Podaj B" << i+1 << ": "; cin >> B[i];
    }

    for (int i=0;i<n;i++) {
        cout << "f(x" << i+1 << ") = " << A[i] << endl;
        if ((i+1)%3 == 0) cout << "f'(x" << i+1 << ") = " << B[i/3] << endl;
    }

    delete(x);
    delete(A);
    delete(B);

    return 0;
}
