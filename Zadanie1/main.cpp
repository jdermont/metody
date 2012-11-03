// g++ -o main main.cpp tablica.cpp -Wall

#include <iostream>
#include <string>
#include "tablica.h"
#define KMAX 5 // z gory okreslone
#define ROZ 4*k

using namespace std;

// pomocnicza do postaci newtona
// sprawdza czy dalsze wspolczynniki to zera
bool same_zera(double *wsp,int teraz,int rozmiar) {
    for (int i=teraz;i<rozmiar;i++) {
        if (wsp[i] != 0.0) return false;
    }
    return true;
}

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

    t = 0;
    for (int i=0;i<n;i++) {
        cout << "Podaj A" << i+1 << ": "; cin >> A[i+t];
        if ((i+1)%3 == 0) {
            t++;
            A[i+t] = A[i+t-1];
        }
    }

    for (int i=0;i<k;i++) {
        cout << "Podaj B" << i+1 << ": "; cin >> B[i];
    }

    // tworzenie tablicy i wyciagniecie z niej wspolczynnikow
    double **tablica = roznice_dzielone(x,A,B,ROZ);
    double *wsp = wspolczynniki(tablica,ROZ);

    // postac newtona
    cout << "W(x) = ";
    for (int i=0;i<ROZ;i++) {
        if (wsp[i] == 0.0f) continue;
        if (i == 0) {
            cout << wsp[i];
        } else {
            if (wsp[i] > 1.0f || wsp[i] < 1.0f) {
                if (i>0 && wsp[i] < 0.0f) cout << -1*wsp[i];
                else cout << wsp[i];
            }
        }
        for (int j=0;j<i;j++) {
            if ((j+1)%4 == 0) {
                cout << "^2";
            } else {
                if (x[j] < 0.0f) cout << "(x+" << -1*x[j] << ")";
                else if (x[j] == 0.0f) cout << "x";
                else cout << "(x-" << x[j] << ")";
            }
        }
        if (i+1 < ROZ) {
            if (!same_zera(wsp,i+1,ROZ)) {
                if (wsp[i+1] > 0.0f) cout << " + ";
                else cout << " - ";
            }
        }
    }
    cout << endl;

	// POCZATEK POSTACI OGOLNEJ ( Last Update: Marcin Horoszko @12:43 3.11.2012 )
	
	// x maksymalnie 7 stopnia ( i = ROZ )
	// ROZ rozwiniec ( j = ROZ )
	// potem sumujemy kolumny
	// pierwsza jest wynikiem
	double tablicaOgolna[ROZ][ROZ];
	
	// tworzymy tablice startowa ( 1 kolumna to wspolczynniki, na koncu to beda wartosci przy danym stopniu )
	for( int i = 0 ; i < ROZ ; i++ )
	{
		for( int j = 0 ; j < ROZ ; j++ )
		{
			if( j == 0 ){ tablicaOgolna[i][j] = tablica[0][i]; }
			else{ tablicaOgolna[i][j] = 0; }
		}
	}
	
	// tworzymy tablice x'ow ( do mnozenia ) ( miejsc zerowych )
	double xValues[ROZ];
	
	for( int i = 0 ; i < ROZ ; i++ )
	{
		if( i == 0 ){ xValues[i] = 0; }
		
		if( i % 4 == 0 ){ xValues[i] = i == 0 ? 0 : x[i-2]; }
		else{ xValues[i] = x[i-1]; }
	}
	
	// liczymy kazdy wiersz ( dzialanie mnozenia wszystkich stopni )
	for( int i = 0 ; i < ROZ ; i++ )
	{
		// dla mnozenia ( 1 ) bedzie 0 iteracji, dla mnozenia ( 1 * (x-1) ) 1 iteracja, itp itd.
		for( int j = 0 ; j < i ; j++ )
		{
			// zapisanie aktualnej tablicy przed przesuwaniem by potem od tego mnozyc
			double currentOriginalTab[ROZ];
			for( int oT = 0 ; oT < ROZ; oT++ ){ currentOriginalTab[oT] = tablicaOgolna[i][oT]; }
			
			// przesuwamy wiersz glownej tablicy w prawo 
			for( int pT = ROZ - 1 ; pT > 0 ; pT-- )
			{
				tablicaOgolna[i][pT] = tablicaOgolna[i][pT-1];
			}
			tablicaOgolna[i][0] = 0;
			
			// mnozymy oryginalna tablice przez xValues i dodajemy do glownej
			for( int mT = 0 ; mT < ROZ ; mT++ )
			{
				tablicaOgolna[i][mT] = tablicaOgolna[i][mT] + ( currentOriginalTab[mT] * ( -1 * xValues[j+1] ) );
			}
		}
	}
	
	// zsumowanie kazdej kolumny
	for( int i = ROZ - 1 ; i > 0 ; i-- )
	{
		for( int j = 0 ; j < ROZ ; j++ )
		{
			tablicaOgolna[0][j] += tablicaOgolna[i][j];
		}
	}
	
	// wypisanie postaci ogolnej ( pierwszy wiersz jest wynikiem )
	cout << "W(x) = ";
	
	int farestNonZeroIndex = 0;
	
	for( int i = ROZ - 1 ; i > 0 ; i-- )
	{
		if( tablicaOgolna[0][i] != 0 )
		{
			farestNonZeroIndex = i;
			break;
		}
	}
	
	for( int i = 0 ; i < ROZ ; i++ )
	{
		if( tablicaOgolna[0][i] != 0 )
		{
			if( !(i > 0 && tablicaOgolna[0][i] == 1) ){ cout << tablicaOgolna[0][i]; }
			if( i == 1 ){ cout << "x"; }
			else if( i > 1 ){ cout << "x^" << i; }
			
			if( farestNonZeroIndex != i ){	cout << " + "; }
		}
	}
	
	cout << endl;
	// KONIEC POSTACI OGOLNEJ

    // czyszczenie pamieci, opcjonalne ale program wyglada profesjonalnie
    for (int i=0;i<ROZ;i++) delete [] tablica[i];
    delete [] tablica;

    delete [] wsp;

    return 0;
}
