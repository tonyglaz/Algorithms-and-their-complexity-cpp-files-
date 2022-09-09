#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

vector<int> create(int n) {
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 2;
    }
    return x;
}

//int BinToDecimal(vector<int> x, int n) {
//    int result = 1;
//    for (int i = n - 1; i > 0; i--) {
//        if (x[i] == 0) continue;
//        result += x[i] * pow(2, i);
//    }
//    return result;
//}

double BinaryMetod(vector<int> x, int n) {
    double count = 0;
    bool first1 = false;
    // int intX = BinToDecimal(x, n);
   //  int y = intX;
    for (int i = 0; i < n; i++) {
        if (first1 == false && x[i] == 1) {
            first1 = true;
            continue;
        }
        //    y = pow(y, 2);
        count++;
        if (x[i] == 0)
            continue;
        //    y *= intX;
        count++;
    }
    return count;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    for (int n = 10; n <= 50; n++) {
        double count = 0.0;
        for (int i = 0; i < 10000; i++) {
            vector<int> x = create(n);
            count += BinaryMetod(x, n);
        }
        cout << "n = " << n << " /|\\   Cложность: " << count / 10000 << endl;
    }
}

