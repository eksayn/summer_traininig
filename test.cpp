#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M, N;
vector<int> fav;

bool canPlace(int mid) {
    vector<int> seats(M, 0);
    for (int i = 0; i < mid; ++i) {
        int row = fav[i] - 1;
        if (seats[row] < N) {
            seats[row]++;
        } else {
            int nextRow = (row + 1) % M;
            if (seats[nextRow] < N) {
                seats[nextRow]++;
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int X;
    cin >> X >> M >> N;
    fav.resize(X);
    for (int i = 0; i < X; ++i)
        cin >> fav[i];

    int low = 0, high = X, ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canPlace(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << X - ans << endl; // Кол-во неудовлетворённых
    return 0;
}

