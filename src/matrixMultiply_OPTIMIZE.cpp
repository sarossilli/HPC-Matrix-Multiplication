float multOptimize(float* mat1, float* mat2,int N)
{
    int i, j, k;
    double res[N][N];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            res[i][j] = 0;
            for (k = 0; k < N; k++)
                res[i][j] += mat1[i*N + k]* mat2[k*N + j];
        }
    }
}
