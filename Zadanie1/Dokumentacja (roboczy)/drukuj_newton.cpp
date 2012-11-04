void drukuj_newton(double *wsp,double *x, int rozmiar) {
    cout << "W(x) = ";
    for (int i=0;i<rozmiar;i++)
        if (wsp[i] == 0.0f) continue;
        if (i == 0) cout << wsp[i];
        else 
            if (wsp[i] > 1.0f || wsp[i] < 1.0f)
                if (i>0 && wsp[i] < 0.0f) cout << -1*wsp[i];
                else cout << wsp[i];
        for (int j=0;j<i;j++)
            if ((j+1)%4 == 0) cout << "^2";
            else 
                if (x[j] < 0.0f) cout << "(x+" << -1*x[j] << ")";
                else if (x[j] == 0.0f) cout << "x";
                else cout << "(x-" << x[j] << ")";
        if (i+1 < rozmiar) 
            if (!same_zera(wsp,i+1,rozmiar)) 
                if (wsp[i+1] > 0.0f) cout << " + ";
                else cout << " - ";
    cout << endl;
}