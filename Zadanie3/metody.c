#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 3.00000000000001

// rownanie dokladne
double f(double x) {
    return x*x+2;
}

// rownanie rozniczkowe
double fp(double x, double y) {
    return ((y-2)*y-x*x*x*x)/x;
}

// zmniejsza duza liczbe rozwiazan drukowanych na ekran
int mod(double h) {
    if (1/h <= 10) return 1;
    else return (int)((1/h)/10);
}

int main() {
    printf("Program rozwiazujacy zagadnienie rozniczkowe xy' = (y-2)y - x^4, y(1) = 3 na przedziale [1,3]\n");
    printf("metoda Eulera i Heuna oraz porownuje z rozwiazaniem dokladnym: y(x) = x^2 + 2. Najlepiej jest\n");
    printf("podac krok h mniejszy od 0.00001.\n\n");

    // uzytkownik podaje h
    int temp = 0;
    double h;
    do {
        if (temp) printf("h nieprawidlowe!\n");
        printf("Podaj krok h z zakresu (0,1): "); scanf("%lf",&h);
        temp = 1;
    } while (h <= 0.0 || h >= 1.0);

    int m = mod(h);

    double i;
    int j,k;

    // rozwiazania dokladne
    double x[21] = {};
    double normal[21] = {};
    for (i=1,j=0,k=0;i<=MAX;i+=h,j++) {
        if (j%m == 0) {
            x[k] = i;
            normal[k] = f(i);
            k++;
        }
    }
    int n = k;

    // rozwiazania przy pomocy Eulera
    double *euler = malloc(n*sizeof(double));
    double y = 3.0;
    euler[0] = y;
    for (i=1.0+h,j=1,k=1;i<=MAX;i+=h) {
        y = y + h*fp(i,y);
        if (j%m == 0) {
            euler[k] = y;
            k++;
        }
        j++;
    }

    // rozwiazania przy pomocy Heuna
    double *heun = malloc(n*sizeof(double));
    y = 3.0;
    heun[0] = y;
    for (i=1.0+h,j=1,k=1;i<=MAX;i+=h) {
        y = y + h*(fp(i,y)+fp(i+h,y+fp(i,y)*h))/2;
        if (j%m == 0) {
            heun[k] = y;
            k++;
        }
        j++;
    }

    // drukowanie na ekran
    printf("     x   | dokladny | metoda eulera |      blad | metoda heuna |      blad \n");
    printf("---------+----------+---------------+-----------+--------------+-----------\n");
    for (j=0;j<n;j++) {
        printf(" %.5lf | %8.5lf | %13.5lf | %9.5lf | %12.5lf | %9.5lf\n",x[j],normal[j],euler[j],fabs(normal[j]-euler[j]),heun[j],fabs(normal[j]-heun[j]));
    }

    return 0;
}
