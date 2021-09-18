float test1(float* mat1, float* mat2,int N)
{
    int i, j, k;
    double res[N][N];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            res[i][j] = 0;
            for (k = 0; k < N; k++){
                res[i][j] += mat1[i*N + k] * mat2[k*N + j];
                // FP + (FP * FP)  2 FPops and 3 dram
            }
        }
    }
}

// CASCHE BLOCK SIZE 8

// line         FP ops          DRAM
//  10            2?             3
//  8 I          2*N           (RES) 1 + (MAT1) N/8 + (MAT2) N
// 6-12 J       2(N^2)         (RES) N/8 + (MAT1) N/8 + (MAT2) N*(N/8)           
// 5-13 K       2(N^3)         (RES) N * (N/8) + (MAT1) N*(N/8) + N*(N/8)


// line           DRAM
//  10            3
//  8 I          (RES) 1 + (MAT1) N/8 + (MAT2) N
// 6-12 J        (RES) N/8 + (MAT1) N/8 + (MAT2) N*(N/8)           
// 5-13 K        (RES) N * (N/8) + (MAT1) N*(N/8) + N*(N/8)

// res[i][j] += mat1[i*N + k] * mat2[k*N + j];
// Access res[] every i
// acess mat1 every i
//acess mat2 every K


// I  = W/Q
// IMAx = 3.8 G / 25.6 GB/s
// IMax = 0.1484375

// W = 2*(n^3)
// Q = 3((N^2)/8))
// I = 16N/3

// I = 3.8

