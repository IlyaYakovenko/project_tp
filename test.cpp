#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <random>
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

std::vector<S> generateRandomVector(int size, int minValue, int maxValue) {
    std::vector<S> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minValue, maxValue);

    for (auto& element : vec) {
        element.n1 = dis(gen);
        element.n2 = dis(gen);
    }

    return vec;
}

TEST_CASE("merge") {
    for (int n = 1000; n < 100000000; n *= 10) {
        std::cout << "Размер массива: " << n << "\n";
        std::vector<S *> v(n);
        std::vector<S> data = generateRandomVector(n, 1, 1000);
        for (int i = 0; i < n; ++i) {
            v[i] = data.data() + i;
        }
        std::cout << "Массив создан, начинаю сортировку слиянием" << "\n";
        mergeSort<S>(v.data(), n, Compare);
        for (int i = 0; i + 1 < n; ++i) {
            CHECK(Compare(v[i], v[i + 1]) >= 0);
        }
        std::cout << "Массив отсортирован!" << "\n";
    }
}

TEST_CASE("quick") {
    for (int n = 1000; n < 100000000; n *= 10) {
        std::cout << "Размер массива: " << n << "\n";
        std::vector<S *> v(n);
        std::vector<S> data = generateRandomVector(n, 1, 1000);
        for (int i = 0; i < n; ++i) {
            v[i] = data.data() + i;
        }
        std::cout << "Массив создан, начинаю быструю сортировку" << "\n";
        quickSort<S>(v.data(), n, Compare);
        for (int i = 0; i + 1 < n; ++i) {
            CHECK(Compare(v[i], v[i + 1]) >= 0);
        }
        std::cout << "Массив отсортирован!" << "\n";
    }
}
