#ifndef FILES_H
#define FILES_H
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

std::string info = "info.txt";
std::string resultFile = "res.txt";

std::ofstream fout(resultFile);

int sizesNum = 7;

int sizes[7] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

void writeTime(std::string title, std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end, int divideBy = 1) {
    fout << title;

    fout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / divideBy << " [микросекунд]\n";
}

#endif // FILES_H
