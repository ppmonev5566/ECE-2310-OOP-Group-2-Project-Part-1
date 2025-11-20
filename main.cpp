#include "sensor.h"
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

void write_to_csv(const std::string& filename, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& data) {
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

struct Table {
    vector<vector<string>> rows;
    vector<string> headers;
    Table(string path) {
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
    }
    Table(vector<string> headers) {
        this->headers = headers;
    }
    void addRow(vector<string>& row) {
        rows.push_back(row);
    }
    void save(string path) {
        write_to_csv(path, headers, rows);
    }
};

int main(){
    Table* table = new Table("iot_telemetry_data.csv");
    
    map<string, Sensor*> sensors;
    for (const auto& row : table->rows){
        string ts = row[0];
        string id = row[1];
        string co = row[2];
        string humidity = row[3];
        string light = row[4];
        string lpg = row[5];
        string motion = row[6];
        string smoke = row[7];
        double temperature = stod(row[8]);
        if(sensors.find(id) == sensors.end()){
            sensors[id] = new Sensor(id);
        }
        sensors[id]->setData(ts, co, humidity, light, lpg, motion, smoke, temperature);
        sensors[id]->toFahrenheit();
    }

    for (const auto& header : table->headers){
        if (header == "ts"){
            continue;
        }
        if (header == "device"){
            continue;
        }
        Table* outputTable = new Table(vector<string>{"ts", "device", header});
        for (const auto& row : table->rows){
            string ts = row[0];
            string id = row[1];
            vector<string> outputRow;
            outputRow.push_back(ts);
            outputRow.push_back(id);
            outputRow.push_back(sensors[id]->getValue(header));
            outputTable->addRow(outputRow);
        }
        outputTable->save("out\\" + header + "_data.csv");
        delete outputTable;
    }

    return 0;
}
