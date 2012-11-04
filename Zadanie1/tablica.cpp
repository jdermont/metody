#include "tablica.h"

double **roznice_dzielone(double *x, double *A, double *B, int rozmiar) {
    double **tablica = 0;
    tablica = new double*[rozmiar];

    for (int i=0;i<rozmiar;i++) {
        tablica[i] = new double[rozmiar];
        for (int j=0;j<rozmiar;j++) tablica[i][j] = 0;
    }

    for (int i=0;i<rozmiar;i++) {
       tablica[i][0] = A[i];
    }

    int t = 0;
    for (int i=0;i<rozmiar-1;i++) {
        double licznik = tablica[i+1][0] - tablica[i][0];
        double mianownik = x[i+1] - x[i];
        if (licznik == 0.0f && mianownik == 0.0f) {
            tablica[i][1] = B[(i-t)/3];
            t++;
            continue;
        }
        tablica[i][1] = licznik/mianownik;
    }

    for (int i=2;i<rozmiar;i++) {
        int z = i;
        for (int j=0;j<rozmiar-i;j++) {
            double licznik = tablica[j+1][i-1] - tablica[j][i-1];
            double mianownik = x[z]-x[j];
            z++;
            tablica[j][i] = licznik/mianownik;
        }
    }

    return tablica;
}

double *wspolczynniki(double **tablica,int rozmiar) {
    double *wsp = new double[rozmiar];

    for (int i=0;i<rozmiar;i++) wsp[i] = tablica[0][i];

    return wsp;
}
