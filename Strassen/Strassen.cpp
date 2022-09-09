#include <iostream>
#include <cmath>

using namespace std;
const int N = 1000000;
double add(long long n) {
    double counter = 0;
    counter += 3; // количество обращений к матрице
    counter *= (double)n * (double)n; // проходы по циклам
    return counter;
}

double multiply(long long n) {
    double counter = 0;
    counter = (double)n * (double)n; //проходы по циклам
    counter *= 2 * (double)n; // проход по циклу и обращение к двум матрицам
    counter += 1; //присваивание элементу исходной матрицы (обращение к ней) значения 
    return counter;
}

double strassen(long long n) {
    double counter = 0;
    if (n == 1) counter = 3;
    else counter = 18 * add(n/2) + 7 * strassen(n/2); // 18 сложений/вычитаний и 7 умножений
    return counter;
}

int main()
{
    int power = 2;
    bool better = false;
    bool worse = false;
    for (int n = 2; n < N; n++) {
        double usual = multiply(n);
        double strassenvalue = strassen(power);
        if (better==false && strassenvalue < usual) {
            better = true;
            cout << "Better: " << n << endl;
        }
        if (better==true && worse==false && strassenvalue > usual) {
            worse = true;
            cout << "Worse: " << n << endl;
            break;
        }
        if (n == power)
            power *= 2;
    }
    int newPow = 0; int i = 1;
    while (true) {
        double n = pow(2, i+1);
        if (strassen(n) < multiply(pow(2, i) + 1)) {
            newPow = i;
            break;
        }
        i++;
    }
    long long n = 1;
    for (int i = 0; i < newPow - 1; i++)
        n *= 2;
    cout << "Forever better: " << n << endl;
}