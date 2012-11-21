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
    printf("Podaj liczbe a i b, takie ze 0 < a < b \n");
    do{
      if(tmp = 1) printf("Podaj inne a i b.");
      do{
        printf("Podaj a: ");
        scanf("%lf",&A);
      }while(A <= 0);
      do{
        printf("Podaj b: ");
        scanf("%lf",&B);
      }while(B <= A);
      tmp = 1;
    }while(f(a) * f(b) >= 0);
    double a,b;
    int i;
    while(1) {
        printf("Podaj epsilon, takie ze 0 < epsilon < 1\n");
        do{
          printf("Podaj epsilon: ");
          scanf("%lf",&e);
        }while(e <= 0 && e >= 1);

        // polowienia
        a = A;
        b = B;
        i = 0;
        while(fabs(a-b) > e) { // fabs - double wartosc bezwgledna
            c = (a+b)/2;
            if (f(a)*f(c) < 0) b = c;
            else a = c;
            i++;
        }
        printf("\nPolowienia:\n");
        printf("%.10lf\n",c);
        printf("%i krokow.\n",i);
	double C = c;
        // newton
        // c = x_k, d = x_{k+1}
        c = A;
        i = 0;
        while (1) {
            d = c-f(c)/fp(c);
            i++;
            if (fabs(c-d) <= e) break;
            c = d;
        }
        printf("\nMetoda Newtona:\n");
        if (fabs(d-C) > e) printf("(niestabilnosc metody newtona!) ");
        printf("%.10lf\n",d);
        printf("%i krokow.\n",i);
    }

    return 0;
}
