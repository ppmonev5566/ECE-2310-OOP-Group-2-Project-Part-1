#include "sensor.h"
#include "table.h"
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

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
