#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define ll long long

template <typename T>
using V = vector<T>;
template <typename T>
using VV = vector<vector<T>>;
using vi = vector<int>;
using vl = vector<long long>;
using vd = V<double>;
using vs = V<string>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;

// 最後の引数を出力するためのテンプレート関数
template <typename T>
void print_impl_endl(T &&arg) {
    std::cout << arg << std::endl;
}
// 複数の引数を出力するためのテンプレート関数
template <typename T, typename... Args>
void print_impl_endl(T &&first, Args &&...args) {
    std::cout << first << " ";
    print_impl_endl(std::forward<Args>(args)...);
}
// メインのprint関数（改行あり）
template <typename... Args>
void print(Args &&...args) {
    print_impl_endl(std::forward<Args>(args)...);
}

// 最後の引数を出力するためのテンプレート関数
template <typename T>
void print_impl_end(T &&arg) {
    std::cout << arg;
}
// 複数の引数を出力するためのテンプレート関数
template <typename T, typename... Args>
void print_impl_end(T &&first, Args &&...args) {
    std::cout << first << " ";
    print_impl_end(std::forward<Args>(args)...);
}
// メインのprint関数（改行無し）
template <typename... Args>
void printf_cpp(Args &&...args) {
    print_impl_end(std::forward<Args>(args)...);
}

template <typename T, typename U>
struct P : pair<T, U> {
    template <typename... Args>
    P(Args... args) : pair<T, U>(args...) {}

    using pair<T, U>::first;
    using pair<T, U>::second;

    P &operator+=(const P &r) {
        first += r.first;
        second += r.second;
        return *this;
    }
    P &operator-=(const P &r) {
        first -= r.first;
        second -= r.second;
        return *this;
    }
    P &operator*=(const P &r) {
        first *= r.first;
        second *= r.second;
        return *this;
    }
    template <typename S>
    P &operator*=(const S &r) {
        first *= r, second *= r;
        return *this;
    }
    P operator+(const P &r) const { return P(*this) += r; }
    P operator-(const P &r) const { return P(*this) -= r; }
    P operator*(const P &r) const { return P(*this) *= r; }
    template <typename S>
    P operator*(const S &r) const {
        return P(*this) *= r;
    }
    P operator-() const { return P{-first, -second}; }
};
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
using pl = P<long long, long long>;
using pi = P<int, int>;
using vp = V<pl>;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), v.rend()
#define each(i, v) for (auto i : v)
#define each2(x, y, v) for (auto [x, y] : v)
#define rep(i, N) for (long long i = 0; i < (long long)(N); i++)
#define repr(i, N) for (long long i = (long long)(N) - 1; i >= 0; i--)
#define rep1(i, N) for (long long i = 1; i <= (long long)(N); i++)
#define repr1(i, N) for (long long i = (N); (long long)(i) > 0; i--)
#define reg(i, a, b) for (long long i = (a); i < (b); i++)
#define regr(i, a, b) for (long long i = (b) - 1; i >= (a); i--)
// #define fi first
// #define se second

#define input(a) cin >> a
constexpr int INF = 0x3f3f3f3f;
constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;
constexpr double EPS = 1e-8;
constexpr int MOD = 998244353;
// constexpr int MOD = 1000000007;
#define pb push_back
#define mod(a, b) (a % b + b) % b // 出力が正整数になるmod計算


int main() {




    ll N, M, K;
    cin >> N >> M >> K;

    vs Rm(M);
    vl Cm(M);
    vl A(M, 0);
    rep(i, M){
        cin >> Cm[i];
        // cout << "Cm = " << Cm[i] << endl;
        ll Aij;
        rep(j, Cm[i]){
            cin >> Aij;
            // cout << "--" << (ll)pow(2, (Aij-1)) << endl;
            A[i] += (ll)pow(2, (Aij-1)); // (tmp[j]-1)は鍵id
        }
        cin >> Rm[i];
    }


    vl count_1((ll)pow(2, N));
    // 十進数を二進数にしたときの1の個数を数える
    rep(ptn_i, (ll)pow(2, N)){
        count_1[ptn_i] = __buildtin_popcount((uint32_t)ptn_i);
        
        /*
        rep(j, N){
            if ((ptn_i >> j) % 2 == 1) count_1[ptn_i] += 1;
        }
        */
    }

    ll ans_n = 0;
    // 鍵のoxパターンを全部試す
    ll ans_bit, ok_or_ng;
    rep(ptn_i, (ll)pow(2, N)){
        // cout << "ptn = " << ptn_i << endl;
        ok_or_ng = 1;
        rep(i, M){
            ans_bit = (ptn_i & A[i]);
            // cout << ptn_i << " & " << A[i] << " = " << ans_bit << endl;
            if(!( (K <= count_1[ans_bit] && Rm[i] == "o") || (count_1[ans_bit] < K && Rm[i] == "x")) ){
                ok_or_ng &= 0;
                // cout << "NG!!!!  " << count_1[ans_bit] << " " << ans_bit << endl;
            }
        }
        // cout << ok_or_ng << endl;
        ans_n += ok_or_ng; // ok=1 , ng=0 なのでその分足せばいい
    }

    cout << ans_n << endl;


    return 0;
}
