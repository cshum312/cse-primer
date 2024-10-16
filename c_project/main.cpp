// use command "g++ main.cpp -o main -I/usr/include/python3.12 -I/usr/lib/python3/dist-packages/numpy/core/include -lpython3.12 -w" to compile with matplotlibcpp
#define _USE_MATH_DEFINES

#include <iostream>
#include "csv_reader.hpp"
#include <cmath>
#include <numeric>
#include <vector>
//#include "include/matplotlibcpp.h"
//namespace plt = matplotlibcpp;

double cell_area();
double ice_sum(std::vector<std::vector<double>> v);
void first_last_year_compare (std::vector<double> l850_sums, std::vector<double> l019_sums);
double hemi_sum(std::vector<std::vector<double>> v, std::string compass);
std::vector<std::vector<double>> matrix_convert(std::vector<double> sums);

int main() {
    std::vector<std::vector<double>> v;
    // outside vector is latitude
    // inside vector is longitude
    std::vector<int> months = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<int> years(170);
    std::iota(years.begin(), years.end(), 1850);

    std::vector<double> monthly_sums;

    std::vector<double> l850_sums;
    std::vector<double> l019_sums;

    std::vector<double> north_sums;
    std::vector<double> south_sums;

    for (int year : years) {
        for (int month : months) {
            std::string file_head = "../sea_ice_concentration/data/";
            std::string file_name = file_head + std::to_string(year) + "/" + std::to_string(month) + ".csv";

            v = read_csv(file_name);
            monthly_sums.push_back(ice_sum(v));
            north_sums.push_back(hemi_sum(v, "north"));
            south_sums.push_back(hemi_sum(v, "south"));

            if (year == 1850) {
                l850_sums.push_back(ice_sum(v));
            }

            if (year == 2019) {
                l019_sums.push_back(ice_sum(v));
            }
        }
    }

    // comparing 1850 and 2019 by months
    first_last_year_compare(l850_sums, l019_sums);

    // convert north and south to 2d matrix
    std::vector<std::vector<double>> north_matrix = matrix_convert(north_sums);
    std::vector<std::vector<double>> south_matrix = matrix_convert(south_sums);

    // write data to csv
    write_csv("north_matrix.csv", north_matrix);
    write_csv("south_matrix.csv", south_matrix);

    return 0;
}


std::vector<std::vector<double>> matrix_convert(std::vector<double> sums) {
    std::vector<std::vector<double>> matrix_sums{};
    int value_points = 0;
    int row_counter = 0;

    while (value_points < sums.size()) {
        matrix_sums.push_back(std::vector<double>()); // introduce new line vector
        for (int i = 0; i < 12; i++) {
            matrix_sums[row_counter].push_back(sums[value_points]);
            value_points++;
        }
        row_counter++;
    }

    return matrix_sums;
}

void first_last_year_compare (std::vector<double> l850_sums, std::vector<double> l019_sums) {
    std::ofstream monthly_diff;
    monthly_diff.open("month_diff.txt");
    monthly_diff << "Monthly differences in sea ice surface area between 1850 and 2019: \n";

    std::vector<std::string> month_names = {"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    std::vector<double> month_diff;

    for (int i = 0; i < 12; i++) {
        month_diff.push_back(l019_sums[i] - l850_sums[i]);
        monthly_diff << "Month:" << month_names[i] << " || Difference: " << month_diff[i] << '\n';
    }

    monthly_diff.close();
}

double ice_sum(std::vector<std::vector<double>> v) {
    double unit_area = cell_area();
    double sum = 0;

    for (auto vec : v) {
        for (auto ice_percent : vec) {
            if (ice_percent > 1) {
                ice_percent = 0;
            }

            sum += (ice_percent * unit_area);
        }
    }
    return sum;
}

double hemi_sum(std::vector<std::vector<double>> v, std::string compass) {
    double unit_area = cell_area();
    double sum = 0;
    int start;
    int end;

    if (compass == "north") {
        start = 0;
        end = v.size()/2;
    }
    else if (compass == "south") {
        start = v.size()/2 + 1;
        end = v.size();
    }

    for (int i = start; i < end; i++) {
        for (auto ice_percent : v[i]) {
            if (ice_percent > 1) {
                ice_percent = 0;
            }
            sum += (ice_percent * unit_area);
        }
    }

    return sum;
}

double cell_area() {
    // (sin(f1) - sin(f0)) * (l1 - l0) * R^2
    // https://gis.stackexchange.com/questions/29734/how-to-calculate-area-of-1-x-1-degree-cells-in-a-raster
    const double R = 6371.0072; // authalic Earth radius (km)
    double rad_unit = M_PI / 180.0; // 1 deg to rad
    double cell_area = (sin(rad_unit)) * rad_unit * R*R;

    return cell_area;
}





