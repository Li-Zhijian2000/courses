// #define local
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 1e6;
int A[maxn], T[maxn];
long res = 0;

// long merge(int lo, int mi, int hi)
// {
//     vector<int> left(v.begin() + lo, v.begin() + mi);
//     vector<int> right(v.begin() + mi, v.begin() + hi);

//     for (int i = 0, j = 0; i < left.size() || j < right.size(); ) {
//         if (i < left.size() && (j == right.size() || left[i] <= right[j]))  {
//             v[lo++] = left[i++];
//         }
//         if (j < right.size() && (i == left.size() || left[i] > right[j])) {
//             v[lo++] = right[j++];
//             res += left.size() - i;
//         }
//     }
// }
void MergeSort(int* A, int lo, int hi, int* T)
{
    if (hi - lo < 2) return;

    int mi = (lo + hi) / 2;
    MergeSort(A, lo, mi, T), MergeSort(A, mi, hi, T);

    int p = lo, q = mi, r = hi, i = lo;
    while (p < mi || q < hi) {
        if (q >= hi || p < mi && A[p] <= A[q])  T[i++] = A[p++];
        else { T[i++] = A[q++]; res += mi - p; }
    }
    for (int i = lo; i < hi; i++) A[i] = T[i];
}

int main()
{
#ifdef local
    freopen("e.txt", "r", stdin);
#endif
    int n; 
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    MergeSort(A, 0, n, T);
    cout << res << endl;
    return 0;    
}