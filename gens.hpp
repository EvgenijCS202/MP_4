#ifndef GENS_HPP
#define GENS_HPP
#include <vector>
#include <deque>
#include "files.hpp"
#define ull unsigned long long

const ull module = 1 << 20;

class Gen1 {
    ull m;
    ull a = 1234123421;
    ull c = 754342159;
    ull k = 7;
    ull seed = 0;
public:
    Gen1(ull module) {
        m=module;
    }
    void setSeed(ull seed) {
        this->seed = seed;
    }
    ull gen() {
        seed = (a^k * seed + (a^k - 1) / (a - 1) * c) % m;
        return seed;
    }
    double genR() {
        return (double)gen() / m;
    }
    std::vector<ull> genVector(int count) {
        std::vector<ull> res(count);
        for(int i = 0; i < count; ++i)
            res[i] = this->gen();
        return res;
    }
    std::vector<double> genRVector(int count) {
        std::vector<double> res(count);
        for(int i = 0; i < count; ++i)
            res[i] = this->genR();
        return res;
    }
};

class Gen2 {
    int r;
    int l;
    std::deque<ull> nums;
    ull m;
public:
    Gen2(ull module) {
        r=55;
        l=24;
        m=module;
        nums.clear();
        Gen1 eng(module);
        std::vector<ull> temp = eng.genVector(r);
        for(int i = 0; i < r; ++i)
            nums.push_back(temp[i]);
    }
    void setSeed(ull seed) {
        nums.clear();
        Gen1 eng(m);
        eng.setSeed(seed);
        std::vector<ull> temp = eng.genVector(r);
        for(int i = 0; i < r; ++i)
            nums.push_back(temp[i]);
    }
    ull gen() {
        ull newNumber = (nums[r - 1] * 41 + nums[l - 1] * 37) % m;
        nums.push_front(newNumber);
        nums.pop_back();
        return newNumber;
    }
    double genR() {
        return (double)gen() / m;
    }
    std::vector<ull> genVector(int count) {
        std::vector<ull> res(count);
        for(int i = 0; i < count; ++i)
            res[i] = this->gen();
        return res;
    }
    std::vector<double> genRVector(int count) {
        std::vector<double> res(count);
        for(int i = 0; i < count; ++i)
            res[i] = this->genR();
        return res;
    }
};

double M(std::vector<double>& v) {
    double sum = 0;

    for (auto& n : v)
        sum += n;

    return sum / (double)(v.size());
}

double D(double mean, std::vector<double>& v) {
    double sum = 0;

    for (auto& n : v)
        sum += (n - mean) * (n - mean);

    return sqrt(sum / v.size());
}

double varC(double deviation, double mean) {
    return deviation / mean;
}

double chiSquare(std::vector<double>& v) {
    const double n = v.size();
    const double k = 10;
    const double p = 1 / k;

    std::vector<double> n_i(k, 0);
    for (auto& el : v)
        for (int j = 0; j < k; ++j)
            if (p * j <= el && el < p * (j + 1))
                ++n_i[j];

    double chi = 0;
    for (auto& u : n_i)
        chi += u*u/p;
    return chi / n - n;
}

bool testChi(double chi) {
    return 5.899 <= chi && chi <= 11.39;
}

void writeInfo(std::vector<double>& vec) {
    double m = M(vec);
    double d = D(m, vec);
    double vc = varC(d, m);
    double chi = chiSquare(vec);

    fout << "Среднее: " << m << "\nОтклонение: " << d << "\nКоэффициент вариации: " << vc
        << "\nКритерий хи-квадрат: " << chi << "\nИдеальное значение критерия: "
        << 8.343 << "\nКритерий " << (testChi(chi) ? "пройден" : "не пройден") << "\n\n";
}


#endif // GENS_HPP
