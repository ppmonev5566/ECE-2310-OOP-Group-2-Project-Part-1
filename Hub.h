#ifndef HUB_H
#define HUB_H

#include <map>
#include <string>

#include "sensor.h"
#include "Table.h"   // match your current filename/casing

class Hub {
private:
    Table* table;                          // holds full CSV
    std::map<std::string, Sensor*> sensors; // one Sensor per device id

public:
    // load CSV into the Table
    Hub(const std::string& inputPath);

    // clean up dynamic memory
    ~Hub();

    // build Sensor objects from table->rows and convert temperature
    void loadSensors();

    // create one output file per header (co, humidity, light, etc.)
    void splitAndExport(const std::string& outDir);

    // convenience function to run the whole pipeline
    void run(const std::string& outDir);
};

#endif // HUB_H
