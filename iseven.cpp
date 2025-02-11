#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

// Make 31 left shifts and check the sign bit, O(1)
bool iseven_1(int n)
{
    for(int i=0; i<8*sizeof(n)-1; i++) n<<=1;
    return !(n<0);
}

// Improvement over the previous method for even numbers, still O(1).
bool iseven_1_5(int n)
{
    int c=0;
    while (n) {
        n <<= 1;
        c++;
    }
    return (c <= 8*sizeof(n)-1);
}

// (-1)^n, O(n)
bool iseven_2(int n)
{
    int c = -1;
    for(;n>0; --n) c *= -1;
    return c == 1;
}

// recursive, O(n)
bool iseven_3(unsigned int n )
{
    if (n<=1) return !(bool)n;
    return iseven_3(n-2);
}

// Optimal but slightly obfuscated
bool iseven_4(int n)
{
    return !(n&1);
}

// Poor tree search, O(n)
bool iseven_5(int n)
{
    std::queue<std::pair<int, bool> > queue;
    std::pair<int, bool> top = std::make_pair(0, true);
    queue.push(top);
    while (top.first != n) {
        top = queue.front();
        queue.push(std::make_pair(top.first+1, !top.second));
        queue.push(std::make_pair(2*top.first, true));
        queue.pop();
    }
    return top.second;
}

template<typename T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

// The same but with Dijkstra
// requires --std=c++11
bool iseven_6(int n)
{
    min_heap<std::tuple<int, int, bool> > heap;
    std::tuple<int, int, bool> top = std::make_tuple(-n, 0, true);
    int k, d=n;
    bool b = true;
    heap.push(top);
    while (d != 0) {
        top = heap.top();
        heap.pop();
        std::tie(d, k, b) = top;
        heap.push(std::make_tuple(std::abs(k+1 - n), k+1, !b));
        heap.push(std::make_tuple(std::abs(2*k - n), 2*k, true));
    }
    return b;
}

// Wrong but efficient
bool iseven_7(int n)
{
    int *p = (int*) n;
    return (bool)(*p); // Segfault 
}

// Compute Bernouilli(n), O(horrible) with a law against return cast
bool iseven_8(int n)
{
    long double res = 0;
    for (long k=1; k<=n; k++) {
        long int binom = 1;
        long int binom_loop = 0;
        for (int i=1; i<=k; i++) {
            binom = (binom * (k - i + 1)) / i;
            binom_loop += binom * pow(-1, i) * pow(i, n);
        }
        res += (long double) binom_loop / (k + 1);
    }
    return res;
}