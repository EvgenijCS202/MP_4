#include <random>
#include "gens.hpp"

const ull sampleSize = 67;
const ull sampleNumber = 10;

int main()
{
    setlocale(LC_ALL, "Russian");

    std::chrono::steady_clock::time_point start, end;

    Gen1 eng(module);

    fout << "Первый генератор:\n" << '\n';

    eng.setSeed(time(NULL));

    for (int i = 0; i < sampleNumber; ++i) {
        std::vector<double> v = eng.genRVector(sampleSize);
        writeInfo(v);
    }

    start = std::chrono::steady_clock::now();

    for (int i = 0; i < sizesNum; ++i) {
        //генерация с засечением времени
        for (int j = 0; j < sizes[i]; ++j)
            eng.gen();

        end = std::chrono::steady_clock::now();
        writeTime("На генерацию " + std::to_string(sizes[i]) + " значений ушло : ", start, end);
        start = end;
    }

    Gen2 eng2(module);

    eng2.setSeed(time(NULL));

    fout << "\nВторой генератор:\n" << '\n';

    for (int i = 0; i < sampleNumber; ++i) {
        std::vector<double> v = eng2.genRVector(sampleSize);
        writeInfo(v);
    }

    start = std::chrono::steady_clock::now();

    for (int i = 0; i < sizesNum; ++i) {
        //генерация с засечением времени
        for (int j = 0; j < sizes[i]; ++j)
            eng2.gen();

        end = std::chrono::steady_clock::now();
        writeTime("На генерацию " + std::to_string(sizes[i]) + " значений ушло : ", start, end);
        start = end;
    }

    fout << "\nСравнение с mt19937:\n" << '\n';

    std::mt19937 mt_rand(time(0));
    for (int l = 0; l < sampleNumber; ++l) {
        std::vector<double> vRand(sampleSize, 0);
        for (int i = 0; i < sampleSize; ++i)
            vRand[i] = (double)(mt_rand() % module) / module;
        writeInfo(vRand);
    }

    start = std::chrono::steady_clock::now();
    int num;
    for (int i = 0; i < sizesNum; ++i) {
        //генерация с засечением времени
        for (int j = 0; j < sizes[i]; ++j)
            num = mt_rand();

        end = std::chrono::steady_clock::now();
        writeTime("На генерацию " + std::to_string(sizes[i]) + " значений ушло : ", start, end);
        start = end;
    }
    num++;
    exit(0);
}
