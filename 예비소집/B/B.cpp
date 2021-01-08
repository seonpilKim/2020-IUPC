#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int N, M;
	double* x;
	int max;

	cin >> N;
	cin >> M;
	x = new double[M];
	for (int i = 0; i < M; i++) {
		cin >> x[i];
	}

	max = x[0];
	for (int i = 1; i < M; i++) {
		if (max < ceil((x[i] - x[i - 1]) / 2)) max = ceil((x[i] - x[i - 1]) / 2);
	}
	if (max < N - x[M - 1]) max = N - x[M - 1];

	cout << max;

	return 0;
}