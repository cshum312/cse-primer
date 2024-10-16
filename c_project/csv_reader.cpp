//
// Provided by CSE team.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
/*
 * @brief Writes a CSV file from a 2D Matrix
 */
void write_csv(std::string file_name, const std::vector<std::vector<double>> &data) {
  std::ofstream csv_file(file_name); // Opens the file and associates it with an OutputFileStream

  if (csv_file.is_open()) {
    for(const auto& row : data){
      // for the columns we use iterators, as it makes it easy to check if were already at the end of the column
      for(auto col_iterator = row.begin(); col_iterator!= row.end(); col_iterator++){
          // iterators are bascially some kind of pointers, so we *dereference them for their value
          csv_file << *col_iterator;
          // here we make sure, that we dont put an ugly ',' after the last column value
          if(col_iterator != row.end()-1){
            csv_file << ",";
          }
      }
      csv_file << "\n";
    }
  }
  // always close your resources
  csv_file.close();
}

/*
 * @brief Reads a CSV file and stores the contents to a 2D matrix
 */
std::vector<std::vector<double>> read_csv(std::string file_name) {
  std::vector<std::vector<double>> matrix{};
  std::ifstream csv_file(file_name); // Opens the file and associates it with an InputFilestream
  int row = 0;
  int col = 0;

  if (csv_file.is_open()) {
    std::string line;
    // Read the file line by line, till the end of file
    while (std::getline(csv_file, line)) {
      // now we have one line -> lets create stringstream
      std::istringstream lineStream(line);          // This will be the InputeString stream we read from
      std::string data;                             // This will be each data value from the line
      matrix.push_back(std::vector<double>());      // Introduce a new line to the 2D matrix
      // now iterate over the line, value by value
      while (std::getline(lineStream, data, ',')) { // Get a data value from the line, if available
        matrix[row].push_back(std::stod(data));     // Add this value to the matrix, as new element in the current row
        col++;                                      // Increase the columns counter
      }
      row++;
      col = 0;
    }
    csv_file.close();
    return matrix;
  }
  return std::vector<std::vector<double>>();
}