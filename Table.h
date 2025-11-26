#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;
class Table {
    public:
        vector<vector<string>> rows;
        vector<string> headers;
        Table(string path);
        Table(vector<string> headers);
        void addRow(vector<string>& row);
        void save(string path);
        void write_to_csv(const std::string& filename, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& data);
};

#endif // TABLE_H