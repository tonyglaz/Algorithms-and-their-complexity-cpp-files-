#include <iostream>
#include <vector>
using namespace std;
const long long N = 1000000;
//сойдется к n=1 при любом n 0<n<1000000 точно(дальше не доказано,но полагают)

long long mas[N];
long long newMas[N];

long long Kollatz(long long n)
{
	long long count = 0;
	while (n != 1) {
		if (n % 2 == 0) n /= 2;
		else n = n * 3 + 1;
		count++;
	}
	return  count;
}
int main()
{
	long long prevMax = 0; long long nextMax = 0; long long localMax;
	for (long long i = 2; i < N; i++) {
		localMax = Kollatz(i);
		mas[i] = Kollatz(i);
		if (localMax<prevMax && prevMax > nextMax)
		{
			cout << i - 1 << " \t" << prevMax << endl;
			nextMax = prevMax;
		}
		prevMax = localMax;
	}
	for (long long i = 0; i < N; i++)
		newMas[i] = 0;
	for (long long i = 0; i < N; i++)
		newMas[mas[i]]++;
	for (long long i = 0; i < N; i++)
		if (newMas[i] != 0)
			cout << i << "\t" << newMas[i] << endl;
	return 0;
}

