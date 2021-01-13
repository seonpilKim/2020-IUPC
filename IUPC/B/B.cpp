#include <iostream>
#include <algorithm>

using namespace std;

int A[200001];

int main() {
    int N, M;
    int D, idx;

    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    sort(A, A + N);

    for (int i = 0; i < M; i++) {
        scanf("%d", &D);
        idx = lower_bound(A, A + N, D) - A;
        printf("%d\n", ((A[idx] == D && idx < N) ? idx : -1));
    }

    return 0;
}
