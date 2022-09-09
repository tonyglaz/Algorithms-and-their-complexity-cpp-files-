#include <vector>
#include <iostream>
#include <ctime>
#include <map>
using namespace std;

using Graph = vector<vector<bool>>;
using Permutation = vector<int>;

Graph generate(int n) {
	Graph result(n);
	for (int i = 0; i < n; i++)
		result[i].resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			bool b = rand() % 2 == 0;
			result[i][j] = b;
			result[j][i] = b;
		}
	}
	return result;
}

Graph apply(Graph g, Permutation p) {
	int n = g.size();
	Graph result(n);
	for (int i = 0; i < n; i++)
		result[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			result[p[i]][p[j]] = g[i][j];
	return result;
}

Permutation randomPermutation(int n) {
	Permutation result(n);
	for (int i = 0; i < n; i++) {
		int d = rand() % (i + 1);
		result[i] = result[d];
		result[d] = i;
	}
	return result;
}

void print(Graph g) {
	for (int i = 0; i < g.size(); i++) {
		for (int j = 0; j < g.size(); j++)
			cout << g[i][j];
		cout << endl;
	}
}

Permutation initPermutation(int n) {
	Permutation result(n);
	for (int i = 0; i < n; i++) result[i] = i;
	return result;
}

bool nextPermutation(Permutation& p) {
	int n = p.size();
	int k = n - 2;
	for (; k >= 0; k--)
		if (p[k] < p[k + 1])
			break;
	if (k == -1) return false;
	int l = n - 1;
	for (; l > k; l--)
		if (p[k] < p[l])
			break;
	swap(p[k], p[l]);
	reverse(p.begin() + k + 1, p.end());
	return true;
}

int edgeCount(const Graph& g) {
	int edge = 0;
	for (int i = 0; i < g.size(); i++)
		for (int j = 0; j < i; j++)
			if (g[i][j])
				edge++;
	return edge;
}

vector<int> degrees(const Graph& g) {
	vector<int> result(g.size());
	for (int i = 0; i < g.size(); i++) {
		int d = 0;
		for (int j = 0; j < g.size(); j++)
			if (g[i][j])
				d++;
		result[i] = d;
	}
	return result;
}

map<int, int> currentVertexDegrees(const vector<int>& deg) {
	map<int, int> result;
	for (int i = 0; i < deg.size(); i++) {
		int d = deg[i];
		if (!result.count(d)) result[d] = 1;
		else result[d]++;
	}
	return result;
}

map<int, int> neighborVertexDegrees(const Graph& g, const vector<int>& deg) {
	map<int, int> result;
	for (int i = 0; i < g.size(); i++) {
		int d = 0;
		for (int j = 0; j < g.size(); j++)
			if (g[i][j])
				d += deg[j];
		if (!result.count(d)) result[d] = 1;
		else result[d]++;
	}
	return result;
}

bool areEqual(const Graph& g1, const Graph& g2) {
	int n = g1.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (g1[i][j] != g2[i][j])
				return false;
	return true;
}

bool areIsomorphic(Graph g1, Graph g2) {
	if (edgeCount(g1) != edgeCount(g2)) return false;
	vector<int> deg1 = degrees(g1);
	vector<int> deg2 = degrees(g2);
	if (currentVertexDegrees(deg1) != currentVertexDegrees(deg2)) return false;
	if (neighborVertexDegrees(g1, deg1) != neighborVertexDegrees(g2, deg2)) return false;

	int n = g1.size();
	Permutation p = initPermutation(n);
	do {
		Graph g = apply(g2, p);
		if (areEqual(g1, g))
			return true;
	} while (nextPermutation(p));
	return false;
}

int main() {
	srand(time(NULL));
	int n = 100;
	Graph g1 = generate(n);
	Permutation p = randomPermutation(n);
	Graph g2 = apply(g1, p);
	print(g1);
	cout << endl;
	print(g2);
	int count = 0;
	//clock_t start = clock();
	const int K = 100;
	for (int i = 0; i < K; i++) {
		if (areIsomorphic(generate(n), generate(n)))
			count++;
	}
	clock_t finish = clock();
	/*cout << "TIME: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;*/
	cout <<"вероятность того,что рандомный граф изоморфный(из K графов)"<< count / K << endl;
}