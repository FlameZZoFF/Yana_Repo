#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void matrixf();
void matrixm();

int main() {
    setlocale(LC_ALL, "RUS");
    std::cout << "1. Матрица из файла \n";
    std::cout << "2. Ввод матрицы \n";
    int a;
    std::cin >> a;
    switch (a) {
    case 1: matrixf();
       
    case 2: matrixm();
      
    }
    return 0;
}

double sign(double x) {
    if (x == 0.0) return 0;
    if (x > 0.0) return 1;
    else return -1;
}

void matrixf() {

        const int n = 3;
        int m;
        ifstream f("matrix.txt");
        m = n + 1;
        double** A = new double* [n + 1];
        for (int i = 1; i <= n; i++)
            A[i] = new double[m + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                f >> A[i][j];
            }
        }
        f.close();

        std::cout << "Матрица A: " << std::endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (j == m) std::cout << "|";
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        double S[n + 1][n + 1];
        double D[n + 1][n + 1];

        S[1][1] = sqrt(abs(A[1][1]));
        D[1][1] = sign(A[1][1]);
        for (int j = 2; j <= n; ++j) {
            S[1][j] = A[1][j] / (S[1][1] * D[1][1]);
        }

        for (int i = 2; i <= n; ++i) {
            double sum = 0;
            for (int l = 1; l <= i - 1; ++l)
                sum = sum + S[l][i] * S[l][i] * D[l][l];
            S[i][i] = sqrt(abs(A[i][i] - sum));
            D[i][i] = sign(A[i][i] - sum);
            for (int j = i + 1; j <= n; ++j) {
                sum = 0;
                for (int l = 1; l <= i - 1; l++) {
                    sum = sum + S[l][i] * S[l][j] * D[l][l];
                }
                S[i][j] = (A[i][j] - sum) / (S[i][i] * D[i][i]);
            }
        }
 
        std::cout << "Главная диагональ матрицы D:" << std::endl;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (abs(S[i][j]) < 0.000001) S[i][j] = 0;

        for (int i = 1; i <= n; i++) {
            std::cout << D[i][i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Полученная матрица S:" << std::endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                std::cout << S[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;

        double y[n + 1];
        y[1] = A[1][m] / S[1][1] * D[1][1];
        for (int i = 2; i <= n; ++i) {
            double sum = 0;
            for (int l = 1; l <= i - 1; ++l)
                sum = sum + S[l][i] * y[l] * D[l][l];
            y[i] = (A[i][m] - sum) / (S[i][i] * D[i][i]);
        }
        std::cout << "Вектор y:" << std::endl;
        for (int i = 1; i <= n; ++i) {
            std::cout << y[i] << ' ';
        }
        std::cout << std::endl;

        double x[n + 1];
        x[n] = y[n] / S[n][n];
        for (int i = n - 1; i >= 1; --i) {
            double sum = 0;
            for (int l = i + 1; l <= n; ++l)
                sum = sum + S[i][l] * x[l];
            x[i] = (y[i] - sum) / S[i][i];
        }
 
        ofstream out("answer.txt");
        std::cout << std::endl << "Ответ" << std::endl;
        for (int i = 1; i <= n; i++) {
            std::cout << x[i] << " ";
            out << x[i] << ' ';
        }
        std::cout << "\n";
        out.close();
        delete[] A;
        main();
}

void matrixm() {

    float A[10][10];
    float U[10][10];
    float b[10], x[10], y[10];
    int n, k;
    int i, j;
    float temp;
    cout << "Введите размерность матрицы" << endl;
    cin >> n;
label:
    cout << "Введите элементы симметричной матрицы" << n << "x" << n << endl;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            U[i][j] = 0;
        }
 
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (A[i][j] != A[j][i])
            {
                cout << "Матрица не симметрична" << endl;
                goto label;
            }
        }
    cout << "Введите элементы вектора b" << n << "x" << n << endl;
    for (i = 0; i < n; i++)
    {
        cin >> b[i];
    }

    for (int i = 0; i < n; i++)
    {
        temp = 0;
        for (int k = 0; k < i; k++)
            temp = temp + U[k][i] * U[k][i];
        U[i][i] = sqrt(A[i][i] - temp);
        for (j = i; j < n; j++)
        {
            temp = 0;
            for (k = 0; k < i; k++)
                temp = temp + U[k][i] * U[k][j];
            U[i][j] = (A[i][j] - temp) / U[i][i];
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }
    for (i = 0; i < n; i++)
    {
        temp = 0;
        for (int k = 0; k < i; k++)
            temp = temp + U[k][i] * y[k];
        y[i] = (b[i] - temp) / U[i][i];
    }
    for (i = n - 1; i >= 0; i--)
    {
        temp = 0;
        for (int k = i + 1; k < n; k++)
            temp = temp + U[i][k] * x[k];
        x[i] = (y[i] - temp) / U[i][i];
    }
    for (i = 0; i < n; i++)
        cout << "x" << i << "= " << x[i] << endl;
    system("pause");

}