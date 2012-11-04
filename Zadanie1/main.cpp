// g++ -o main main.cpp tablica.cpp drukuj.cpp -Wall

#include <iostream>
#include <string>
#include "tablica.h"
#include "drukuj.h"
#define KMAX 5 // z gory okreslone
#define ROZ 4*k

using namespace std;

int main()
{
    // podawanie danych
    int k = 1;
    cout << "Podaj k z zakresu 1.." << KMAX << endl;
    do {
        if (k > KMAX || k < 1) cout << "k niepoprawne!" << endl;
        cout << "Podaj k: "; cin >> k;
    } while (k > KMAX || k < 1);

    int n = 3*k;
    double x[ROZ]; // x i A maja rozmiar 4*k (a nie n) poniewaz
    double A[ROZ]; // co trzeci element sie powtarza
    double B[k];
    int t = 0;
    double tmp_x;
    bool tmp;
    cout << "Podaj rozne wezly x." << endl;
    for (int i=0;i<n;i++) {
        tmp = false;
        cout << "Podaj x" << i+1 << ": "; cin >> tmp_x;
        for (int j=0; j<(i+t); j++) {
            if (tmp_x == x[j]) {
                cout << "Podaj inny x." << endl;
                tmp = true;
                break;
            }
        }

        if (tmp == true) {
            i--;
            continue;
        }

        x[i+t] = tmp_x;
        if ((i+1)%3 == 0) {
            t++;
            x[i+t] = x[i+t-1];
        }
	}

    cout << "Podaj komplet wartosci A." << endl;
    t = 0;
    for (int i=0;i<n;i++) {
        cout << "Podaj A" << i+1 << ": "; cin >> A[i+t];
        if ((i+1)%3 == 0) {
            t++;
            A[i+t] = A[i+t-1];
        }
    }

    cout << "Podaj komplet wartosci B." << endl;
    for (int i=0;i<k;i++) {
        cout << "Podaj B" << i+1 << ": "; cin >> B[i];
    }

    // tworzenie tablicy i wyciagniecie z niej wspolczynnikow
    double **tablica = roznice_dzielone(x,A,B,ROZ);
    double *wsp = wspolczynniki(tablica,ROZ);

    // postac newtona
    cout << endl << "Wielomian interpolacyjny w postaci Newtona:" << endl;
    drukuj_newton(wsp,x,ROZ);

    // postac ogolna
    cout << endl << "Wielomian interpolacyjny w postaci ogolnej:" << endl;
    drukuj_ogolna(tablica,x,ROZ);

    // czyszczenie pamieci
    for (int i=0;i<ROZ;i++) delete [] tablica[i];
    delete [] tablica;
    delete [] wsp;

    return 0;
}
