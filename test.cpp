#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <chrono>
#include <numeric>
#include "sort_parallel.cpp"

using namespace templates;

struct S {
    int n1, n2;
};

int Compare(const S* l, const S* r) {
    int diff = r->n1 - l->n1;
    if (diff == 0) {
        return r->n2 - l->n2;
    }
    return diff;
}

TEST_CASE("merge") {
    std::vector<double> res;
    for (int k = 0; k < 50; k++) {
        const int n = 1000000;
        std::vector<S *> v(n);

        std::vector<S> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = {i % 17 + i % 8, i % 5};
        }
        for (int i = 0; i < n; ++i) {
            v[i] = data.data() + i;
        }
        std::cout << "до сортировки: " << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort<S>(v.data(), n, Compare);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "после сортировки: " << elapsed.count() << std::endl;
        res.push_back(elapsed.count());
        for (int i = 0; i + 1 < n; ++i) {
            CHECK(Compare(v[i], v[i + 1]) >= 0);
        }
    }

    double sum = std::accumulate(res.begin(), res.end(), 0.0);

    // Нахождение среднего значения
    double average = sum / res.size();

    std::cout << "Среднее значение: " << average << std::endl;
}

TEST_CASE("quick") {
    std::vector<double> res;
    for (int k = 0; k < 50; k++) {
        const int n = 100000;
        std::vector<S *> v(n);

        std::vector<S> data(n);
        for (int i = 0; i < n; ++i) {
            data[i] = {i % 17 + i % 8, i % 5};
        }
        for (int i = 0; i < n; ++i) {
            v[i] = data.data() + i;
        }
        auto start = std::chrono::high_resolution_clock::now();
        quickSort<S>(v.data(), n, Compare);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "после сортировки: " << elapsed.count() << std::endl;
        res.push_back(elapsed.count());
        for (int i = 0; i + 1 < n; ++i) {
            CHECK(Compare(v[i], v[i + 1]) >= 0);
        }
    }

    double sum = std::accumulate(res.begin(), res.end(), 0.0);

    // Нахождение среднего значения
    double average = sum / res.size();

    std::cout << "Среднее значение: " << average << std::endl;
}
