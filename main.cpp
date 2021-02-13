#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

const int size = std::pow(10, 9);

double med(double a, double b, double c)
{
    if (a > b) {
        if (c > a)
            return a;
        return (b > c) ? b : c;
    }

    if (c > b)
        return b;
    return (a > c) ? a : c;
}

template <typename FUNC_T>
void qsort(double* left, double* right, FUNC_T cmp) {

    if (right - left <= 1)
        return;

    double supElem = med(*left, *(left + (right - left) / 2), *(right - 1));
    double* tmpLeft = left;
    double* tmpRight = right - 1;

    while (tmpLeft <= tmpRight) {
        while (cmp(*tmpLeft, supElem))
            tmpLeft++;

        while (cmp(supElem, *tmpRight))
            tmpRight--;

        if (tmpLeft <= tmpRight) {
            std::swap(*tmpLeft, *tmpRight);
            tmpLeft++;
            tmpRight--;
        }
    }

    if (left < tmpRight)
        qsort(left, tmpRight + 1, cmp);

    if (tmpLeft < right)
        qsort(tmpLeft, right, cmp);
}

int main() {
    double lowerBound = 0;
    double upperBound = std::pow(10, 4);
    std::uniform_real_distribution<double> unif(lowerBound, upperBound);
    std::default_random_engine re;
    re.seed(std::chrono::steady_clock::now().time_since_epoch().count());


    auto* arr = static_cast<double*>(malloc(size * sizeof(double)));
    for (int i = 0; i < size; ++i)
        arr[i] = unif(re);

 /*   for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n\nAfter sort:\n";*/

    const double EPSILON = std::pow(10, -4);
    auto cmp = [EPSILON](double a, double b) { return (std::fabs(a - b) < EPSILON) ? 0 : a < b; };

    auto start = std::chrono::system_clock::now();
    qsort(arr, arr + size, cmp);
    auto end = std::chrono::system_clock::now();
/*
    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";*/

    std::cout << "\n\nSort time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds" << std::endl;

    return 0;
}
