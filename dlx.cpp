struct DLX{
    int n, m, cnt;
    int L[maxnode], R[maxnode], U[maxnode], D[maxnode], row[maxnode], col[maxnode];
    int S[MAXC], H[MAXR], o[MAXR];
    void init( int _n, int _m ){
        n = _n; m = _m;
        for( int i = 0; i <= m; ++i ){
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1; R[i] = i + 1;
        }
        R[m] = 0; L[0] = m;
        cnt = m;
        for( int i = 1; i <= n; ++i ) H[i] = -1;
    }
    void link( int r, int  c ){
        S[c]++;
        col[++cnt] = c; row[cnt] = r;
        D[cnt] = D[c];  U[D[c]] = cnt;
        U[cnt] = c; D[c] = cnt;
        if( H[r] < 0 ) H[r] = L[cnt] = R[cnt] = cnt;
        else{
            R[cnt] = R[H[r]];
            L[R[H[r]]] = cnt;
            L[cnt] = H[r];
            R[H[r]] = cnt;
        }
    }
    void remove( int c ){
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for( int i = D[c]; i != c; i = D[i] )
            for( int j = R[i]; j != i; j = R[j] ){
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[col[j]];
            }
    }
    void resume( int c ){
        for( int i = U[c]; i != c; i = U[i] )
            for( int j = L[i]; j != i; j = L[j] ){
                U[D[j]] = D[U[j]] = j;
                ++S[col[j]];
            }
        L[R[c]] = R[L[c]] = c;
    }
    bool dancing( int d ){
        if( R[0] == 0 )
            return true;
        int c = R[0];
        for( int i = R[0]; i != 0; i = R[i] )
            if( S[i] < S[c] ) 
                c = i;
        remove(c);
        for( int i = D[c]; i != c; i = D[i] ){
            o[d] = row[i];
            for( int j = R[i] ; j != i; j = R[j] ) remove( col[j] );
            if( dancing( d + 1 ) ) return true;
            for( int j = L[i] ; j != i; j = L[j] ) resume( col[j] );
        }
        resume(c);
        return false;
    }
}dlx;
