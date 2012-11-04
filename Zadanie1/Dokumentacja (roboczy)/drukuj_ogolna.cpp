void drukuj_ogolna(double **tablica,double *x,int rozmiar) {
  double tablicaOgolna[rozmiar][rozmiar];
  // tworzymy tablice startowa ( 1 kolumna to wspolczynniki, na koncu to beda wartosci przy danym stopniu )
  for( int i = 0 ; i < rozmiar ; i++ )
    for( int j = 0 ; j < rozmiar ; j++ )
      if( j == 0 ){ tablicaOgolna[i][j] = tablica[0][i]; }
      else{ tablicaOgolna[i][j] = 0; }

  // tworzymy tablice x'ow ( do mnozenia ) ( miejsc zerowych )
  double xValues[rozmiar];
  for( int i = 0 ; i < rozmiar ; i++ )
    if( i == 0 ){ xValues[i] = 0; }
    if( i % 4 == 0 ){ xValues[i] = i == 0 ? 0 : x[i-2]; }
    else{ xValues[i] = x[i-1]; }

  // liczymy kazdy wiersz ( dzialanie mnozenia wszystkich stopni )
  for( int i = 0 ; i < rozmiar ; i++ )
    // dla mnozenia ( 1 ) bedzie 0 iteracji, dla mnozenia ( 1 * (x-1) ) 1 iteracja, itp itd.
    for( int j = 0 ; j < i ; j++ )
      // zapisanie aktualnej tablicy przed przesuwaniem by potem od tego mnozyc
      double currentOriginalTab[rozmiar];
      for( int oT = 0 ; oT < rozmiar; oT++ ){ currentOriginalTab[oT] = tablicaOgolna[i][oT]; }
      // przesuwamy wiersz glownej tablicy w prawo
      for( int pT = rozmiar - 1 ; pT > 0 ; pT-- )
	tablicaOgolna[i][pT] = tablicaOgolna[i][pT-1];
      tablicaOgolna[i][0] = 0;
      // mnozymy oryginalna tablice przez xValues i dodajemy do glownej
      for( int mT = 0 ; mT < rozmiar ; mT++ )
	tablicaOgolna[i][mT] = tablicaOgolna[i][mT] + ( currentOriginalTab[mT] * ( -1 * xValues[j+1] ) );

  // zsumowanie kazdej kolumny
  for( int i = rozmiar - 1 ; i > 0 ; i-- )
    for( int j = 0 ; j < rozmiar ; j++ )
      tablicaOgolna[0][j] += tablicaOgolna[i][j];

  // wypisanie postaci ogolnej ( pierwszy wiersz jest wynikiem )
  cout << "W(x) = ";
  int firstExp = 1;
  for( int i = rozmiar-1 ; i >= 0 ; i-- )
    if( tablicaOgolna[0][i] != 0 )
      if( !(i > 0 && tablicaOgolna[0][i] == 1) )
	if (!same_zera(tablicaOgolna[0],i+1,rozmiar))
	  if( tablicaOgolna[0][i] < 0 )
	    cout << " - ";
	    if (tablicaOgolna[0][i] != -1) cout << tablicaOgolna[0][i] * -1;
	  else
	    cout << " + ";
	    if (tablicaOgolna[0][i] != 1) cout << tablicaOgolna[0][i];
	else
	  if (tablicaOgolna[0][i] != -1 && tablicaOgolna[0][i] != 1) cout << tablicaOgolna[0][i];
	  if( i == 1 ){ if (tablicaOgolna[0][i]==-1) cout << "-x"; else cout << "x"; }
	  else if( i > 1 ){ if (tablicaOgolna[0][i]==-1) cout << "-x^"; else cout << "x^"; cout << i; }
      else if (firstExp == 1) 
	firstExp = 0;
      if (same_zera(tablicaOgolna[0],0,rozmiar)) cout << "0";
  cout << endl;