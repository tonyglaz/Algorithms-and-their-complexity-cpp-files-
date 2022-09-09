#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

vector<int> DecToBin(long long x) {
    vector<int> binX;
    while (x > 1) {
        binX.push_back(x % 2);
        x = x / 2;
    }
    binX.push_back(x);
    return binX;
}

long long BinaryMetod(long long intX, int pow, long long p) {
    bool first1 = false;
    long long y;
    vector<int> x = DecToBin(pow % p);
    y = intX % p;
    for (int i = x.size(); i > 0; i--) {
        if (first1 == false && x[i - 1] == 1) {
            first1 = true;
            continue;
        }
        y = (y * y) % p;
        if (x[i - 1] == 1) y = (y * intX) % p;
    }
    return y;
}

vector<long long> Divide(int x, int n, int m, long long p) {
    vector <long long> vectorA;
    const int power = m - 1;
    vectorA.push_back(p);
    for (int i = 0; i < power; i++) {
        vectorA.push_back(rand() % p);
    }
    vector <long long> vectorF;
    vectorF.push_back(p);
    for (int i = 1; i <= n; i++) {
        long long temp = 0;
        for (int j = 1; j <= power; j++) {
            temp = (temp + (vectorA[j] * BinaryMetod(i, power - j + 1, p)) % p) % p;
        }
        vectorF.push_back((temp + x) % p);
    }
    return vectorF;
}

long long ToModal(long long x, long long p) {
    long long result = 0;
    result = BinaryMetod(x, p - 2, p) % p;
    return result;
}

long long Lagrange(long long p, vector<pair<long long, int>> usedKeys) {
    long long f = 0;
    for (int j = 0; j < usedKeys.size(); j++) {
        long long l = 1;
        long long x = 1;
        for (int i = 0; i < usedKeys.size(); i++) {
            if (usedKeys[j].second == usedKeys[i].second) continue;
            x = x * (usedKeys[j].second - usedKeys[i].second) % p;
            if (x < 0) x = (x + p) % p;
            l = l * (-usedKeys[i].second + p) % p;
        }
        l = l * ToModal(x, p) % p;
        f = (f + l * usedKeys[j].first) % p;
    }
    return f;
}

int main() {
    srand(time(0));
    long long decX = 105;
    int n = 14;
    long long p = 1312;
    int x = 2034;
    int m = 4;
    vector<long long> keys = Divide(decX, n, m, p);
    vector<pair<long long, int>> usedKeys(m);
    usedKeys[0].first = keys[2];
    usedKeys[0].second = 2;
    usedKeys[1].first = keys[4];
    usedKeys[1].second = 4;
    usedKeys[2].first = keys[6];
    usedKeys[2].second = 6;
    usedKeys[3].first = keys[8];
    usedKeys[3].second = 8;
    cout << Lagrange(137, usedKeys);
    return 0;
}