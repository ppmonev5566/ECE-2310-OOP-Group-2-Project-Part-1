#include "Table.h"
using namespace std;
Table::Table(string path) {
    ifstream file(path);
    string line;

    if (!file.is_open()) {
        cout << "Error: Couldn't open file\n";
        return;
    }

    if (std::getline(file, line)) {
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            if (!cell.empty() && cell.front() == '"' && cell.back() == '"') {
                cell = cell.substr(1, cell.size() - 2);
            }
            headers.push_back(cell);
        }
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (std::getline(ss, cell, ',')) {
            if (!cell.empty() && cell.front() == '"' && cell.back() == '"') {
                cell = cell.substr(1, cell.size() - 2);
            }
            row.push_back(cell);
        }

        rows.push_back(row);
    }
};
Table::Table(vector<string> headers) {
    this->headers = headers;
};
void Table::addRow(vector<string>& row) {
    rows.push_back(row);
}
void Table::save(string path) {
    write_to_csv(path, headers, rows);
}
void Table::write_to_csv(const std::string& filename, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& data) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < headers.size(); ++i) {
        outputFile << '"' << headers[i] << '"';
        if (i < headers.size() - 1) {
            outputFile << ",";
        }
    }
    outputFile << std::endl;

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << '"' << row[i] << '"';
            if (i < row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << std::endl;
    }

    outputFile.close();
}