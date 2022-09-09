// CM4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
using namespace std;

const int N = 5000;
using Vector = double[N];
using Matrix = double[N][N];

default_random_engine eng(time(NULL));

void randomMatrix(Matrix& a) {
    uniform_real_distribution<double> distr(-1, 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = distr(eng);
        }
    }
}

void randomDiagonalDominantMatrix(Matrix& a) {//матрица у котроой на диагонали в каждой строчке стоит элемент=сумме всех остальных элементов в строчке
    randomMatrix(a);
    for (int i = 0; i < N; i++) {
        double sum = 0;
        for (int j = 0; j < N; j++) {
            sum += abs(a[i][j]);
            if (a[i][i] > 0)
                a[i][i] = sum;
            else
                a[i][i] = -sum;
        }
    }
}

void randomVector(Vector& v) {
    uniform_real_distribution<double> distr(-10, 10);
    for (int i = 0; i < N; i++) {
        v[i] = distr(eng);
    }
}

void multiply(const Matrix& a, const Vector& f, Vector& out) {
    for (int i = 0; i < N; i++) {
        out[i] = 0;
        for (int j = 0; j < N; j++) {
            out[i] += a[i][j] * f[j];
        }
    }
}

double diff(const Vector& a, const Vector& b) {
    double result = 0;
    for (int i = 0; i < N; i++) {
        result += abs(a[i] - b[i]);
    }
    return result;
}

void Jacobi(const Matrix& a, const Vector& f, Vector& out) {
    int k = 0;//счетчик
    const double epsilon = 1e-15;
    for (int i = 0; i < N; i++)
        out[i] = f[i] / a[i][i];
    Vector outNext;
    bool equal = false;
    while (!equal && k <= 50) {
        for (int i = 0; i < N; i++) {
            double s = 0;
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                s += a[i][j] * out[j];
            }
            outNext[i] = (f[i] - s) / a[i][i];
        }
        for (int i = 0; i < N; i++)
            if (abs(out[i] - outNext[i]) > epsilon) {
                equal = false;
                break;
            }
        for (int i = 0; i < N; i++)
            out[i] = outNext[i];
        k++;
    }
    cout << " k = " << k << "; ";
}

void Seidel(const Matrix& a, const Vector& f, Vector& out) {
    int k = 0;
    const double epsilon = 1e-15;
    for (int i = 0; i < N; i++)
        out[i] = f[i] / a[i][i];
    Vector outPrev;
    bool equal = false;
    while (!equal && k <= 50) {
        for (int i = 0; i < N; i++)
            outPrev[i] = out[i];
        for (int i = 0; i < N; i++) {
            double s = 0;
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                s += a[i][j] * out[j];
            }
            out[i] = (f[i] - s) / a[i][i];
        }
        equal = true;
        for (int i = 0; i < N; i++)
            if (abs(out[i] - outPrev[i]) > epsilon) {
                equal = false;
                break;
            }
        k++;
    }
    cout << " k = " << k << "; ";
}

void getdiffByF() {
    Matrix* a = (Matrix*)new double[N * N];
    Vector f, x, f1;

    randomDiagonalDominantMatrix(*a);
    randomVector(f);

    Jacobi(*a, f, x);
    multiply(*a, x, f1);
    cout << "Погрешность вычисления при решении методом Якоби при зарандомленном векторе f : " << diff(f, f1) << endl;

    Seidel(*a, f, x);
    multiply(*a, x, f1);
    cout << "Погрешность вычисления при решении методом Зейделя при зарандомленном векторе f: " << diff(f, f1) << endl;

    cout << endl;
    delete[] a;
}

void getdiffByX() {
    Matrix* a = (Matrix*)new double[N * N];
    Vector f, x, x1;
    randomDiagonalDominantMatrix(*a);
    randomVector(x);

    Jacobi(*a, f, x1);
    cout << "Погрешность вычисления при решении методом Якоби при зарандомленном векторе Х: " << diff(x, x1) << endl;

    Seidel(*a, f, x1);
    cout << "Погрешность вычисления при решении методом Зейделя при зарандомленном векторе Х: " << diff(x, x1) << endl;

    cout << endl;
    delete[] a;
}

int main() {
    setlocale(LC_ALL, "");
    getdiffByF();
    getdiffByX();
}