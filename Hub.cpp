#include "Hub.h"
#include <vector>      // for std::vector

using namespace std;

Hub::Hub(const string& inputPath) {
    // same as your old: Table* table = new Table("iot_telemetry_data.csv");
    table = new Table(inputPath);
}

Hub::~Hub() {
    // delete all Sensor pointers
    for (auto& pair : sensors) {
        delete pair.second;
    }
    sensors.clear();

    // delete the Table
    delete table;
}

void Hub::loadSensors() {
    // This is your first loop from main()
    for (const auto& row : table->rows) {
        string ts        = row[0];
        string id        = row[1];
        string co        = row[2];
        string humidity  = row[3];
        string light     = row[4];
        string lpg       = row[5];
        string motion    = row[6];
        string smoke     = row[7];
        double temperature = stod(row[8]);

        if (sensors.find(id) == sensors.end()) {
            sensors[id] = new Sensor(id);
        }

        sensors[id]->setData(ts, co, humidity, light, lpg, motion, smoke, temperature);

        // use whichever conversion your design expects:
        // if your data starts in Celsius and you want Fahrenheit, keep this:
        sensors[id]->toFahrenheit();
        // if instead the file is Fahrenheit and you want Celsius, use:
        // sensors[id]->toCelsius();
    }
}

void Hub::splitAndExport(const string& outDir) {
    // This is your second loop from main()
    for (const auto& header : table->headers) {
        if (header == "ts") {
            continue;
        }
        if (header == "device") {
            continue;
        }

        // create output table with ts, device, and the current header
        Table* outputTable = new Table(vector<string>{"ts", "device", header});

        for (const auto& row : table->rows) {
            string ts = row[0];
            string id = row[1];

            vector<string> outputRow;
            outputRow.push_back(ts);
            outputRow.push_back(id);
            outputRow.push_back(sensors[id]->getValue(header));

            outputTable->addRow(outputRow);
        }

        // outDir should be something like "out\\" on Windows or "out/" on Linux/Mac
        outputTable->save(outDir + header + "_data.csv");
        delete outputTable;
    }
}

void Hub::run(const string& outDir) {
    loadSensors();
    splitAndExport(outDir);
}
