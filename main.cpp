#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<double>;
using vii = vector<pii>;
using vll = vector<pll>;
using vs = vector<string>;

using vvb = vector<vb>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvd = vector<vd>;

ll n;
ll max_j;
vl A;
vvl table;
ll ans;

void BuildTable() {
  for (auto i = 0; i < n; ++i) {
    table[i][0] = i;
  }

  for (auto j = 1; j < max_j; ++j) {
    const auto& w = 1 << (j - 1);
    for (auto i = 0; i + w < n; ++i) {
      const auto& k = i + w;

      const auto& x = table[i][j - 1];
      const auto& y = table[k][j - 1];

      if (-1 == x || -1 == y) {
        table[i][j] = -1;
        continue;
      }

      if (A[x] < A[y]) {
        table[i][j] = x;
      } else {
        table[i][j] = y;
      }
    }
  }
}

ll Query(ll b, ll e) {
  if (b == e) {
    return table[b][0];
  }

  auto j = 0LL;
  auto w = 1LL;
  while (b + 2 * w <= e) {
    ++j;
    w *= 2;
  }

  const auto& k = e - w + 1;

  if (-1 == table[k][j]) {
    return table[b][j];
  }

  if (A[table[b][j]] < A[table[k][j]]) {
    return table[b][j];
  }

  return table[k][j];
}

void Solve(ll b, ll e) {
  if (e < b) {
    return;
  }

  if (b == e) {
    ans = max(ans, A[b]);
    return;
  }

  const auto& mid = Query(b, e);
  ans = max(ans, A[mid] * (e - b + 1));

  Solve(b, mid - 1);
  Solve(mid + 1, e);
}

void Print() {
  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < max_j; ++j) {
      if (-1 == table[i][j]) {
        cout << "* ";
        continue;
      }

      cout << table[i][j] << ' ';
    }
    cout << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n;
  while (0 < n) {
    A = vl(n);
    for (auto&& x : A) {
      cin >> x;
    }

    max_j = 0;
    auto b = 1;
    while (b <= n) {
      ++max_j;
      b *= 2;
    }

    table = vvl(n, vl(max_j, -1));
    BuildTable();
    // Print();

    ans = 0;
    Solve(0, n - 1);
    cout << ans << '\n';

    cin >> n;
  }

  return 0;
}