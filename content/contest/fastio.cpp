int inline in() {    
    int N = 0;
    char C;
    C=getchar_unlocked();
    while (C < '0' || C>'9') C=getchar_unlocked();
    while (C >= '0' && C <= '9')
    {
        N = (N<<3) + (N<<1) + C - '0'; // 8*N + 2*N = 10*N
        C=getchar_unlocked();
    }
    return N;
}