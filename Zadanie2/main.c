// gcc -Wall -o idea idea.c -O2 -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// rownanie
double f(double x) {
    return log(x)+x-5;
}

// pochodna rownania
double fp(double x) {
    return (1/x)+1;
}

int main() {
    double A,B,c,d,e,tmp=0;
    double x0,x1;
    printf("--- Program rozwiazujacy rownanie ln(x) + x - 5 = 0. ---\n\n");
    printf("Podaj liczbe a i b, takie ze 0 < a < b \n");
    do{
      if(tmp == 1) printf("Nie ma rozwiaznia. Podaj inne a i b.\n");
      do{
        printf("Podaj a: ");
        scanf("%lf",&A);
      }while(A <= 0);
      do{
        printf("Podaj b: ");
        scanf("%lf",&B);
      }while(B <= A);
      tmp = 1;
    } while(f(A) * f(B) >= 0);

    double a,b;
    int i,j;
    while(1) {
        printf("Podaj epsilon, takie ze 0 < epsilon < 1\n");
        do{
          printf("Podaj epsilon: ");
          scanf("%lf",&e);
        } while(e <= 0 || e >= 1);

        // metdoa polowien
        a = A;
        b = B;
        i = 0;
        while(fabs(a-b) > e) {
            c = (a+b)/2;
            if (f(a)*f(c) < 0) b = c;
            else a = c;
            i++;
        }
        printf("\nMetoda polowien:\n");
        printf("%.10lf\n",c);
        printf("Ilosc krokow: %i.\n",i);

        // metoda newtona
        x0 = A;
        j = 0;
        while (1) {
            x1 = x0-f(x0)/fp(x0);
            j++;
            if (fabs(x0-x1) <= e && fabs(c-x1) < 1) break;
            if (j == 100) break;
            x0 = x1;
        }
        printf("\nMetoda Newtona:\n");
        if (j == 100) printf("(wynik nieprawidlowy, metoda Newtona rozbiezna!) ");
        printf("%.10lf\n",x1);
        printf("Ilosc krokow: %i.\n\n",j);
    }
    return 0;
}
