// C++ program to rotate a matrix
#include <string>
#include <bits/stdc++.h>
using namespace std;
void test1(double *, int);

void test1(double *a, int N)
{
    int i, j, k;
    for (i = 0; i < N; i = i + 1)
    {
        for (j = 0; j <= i; j = j + 1)
        {
            for (k = 0; k < j; k = k + 1)
                a[i * N + j] = a[i * N + j] - a[k * N + j];  // a[0 + 4]
            a[i * N + j] = a[i * N + j] / a[j * N + j];
        }
    }

    // 1 3     a[0]      a[0+1]      -> a[c*N + r]
    // 3 4     a[2+0]    a[2+1]
}
// A function to rotate an outter matrix mat[][]
void rotatematrix(int N, double * mat)
{
    int row = 0, col = 0;
    int prev, curr;

    int m,n = N;
    /*
    row - Staring row index
    m - ending row index
    col - starting column index
    n - ending column index
    i - iterator
    */
    while (row < m && col < n)
    {

        if (row + 1 == m || col + 1 == n)
            break;

        // Store the first element of next row, this
        // element will replace first element of current
        // row
        //prev = mat[row + 1][col];
        prev = mat[row*N + (col)];

        /* Move elements of first row from the remaining rows */
        for (int i = col; i < n; i++)
        {
            //curr = mat[row][i];
            //mat[row][i] = prev;
            curr = mat[row*N + i];
            mat[row*N + i] = prev;
            prev = curr;
        }
        row++;

        /* Move elements of last column from the remaining columns */
        for (int i = row; i < m; i++)
        {
            curr = mat[i*N + (n - 1)];
            mat[i*N + (n - 1)] = prev;
            prev = curr;
        }
        n--;

        /* Move elements of last row from the remaining rows */
        if (row < m)
        {
            for (int i = n - 1; i >= col; i--)
            {
                curr = mat[N*(m - 1) + i];
                mat[N*(m - 1) + i] = prev;
                prev = curr;
            }
        }
        m--;

        /* Move elements of first column from the remaining rows */
        if (col < n)
        {
            for (int i = m - 1; i >= row; i--)
            {
                curr = mat[i*N + col];
                mat[i*N + col] = prev;
                prev = curr;
            }
        }
        col++;
    }
}
