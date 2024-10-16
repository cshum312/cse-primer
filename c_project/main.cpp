#include <iostream>
#include "csv_reader.hpp"

int main() {
    std::vector<std::vector<double>> v;
    v = read_csv("../sea_ice_concentration/data/1850/1.csv");

    for (auto vec : v) {
        for (auto row : vec) {
            std::cout << row << std::endl;
        }
    }

    return 0;
}
