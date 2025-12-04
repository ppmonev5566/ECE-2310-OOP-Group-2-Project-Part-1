#include <iostream>
#include <cassert>
#include <fstream>

#include "sensor.h"
#include "Table.h"
#include "Hub.h"

using namespace std;

// ---- Test 1: temperature conversion logic in Sensor ----
void testSensorTemperatureConversion() {
    Sensor s("dev1");

    // Your Sensor starts with celsius = true
    s.setData("ts", "1.0", "2.0", "3.0", "4.0", "0", "0", 25.0); // 25°C

    // Convert to Fahrenheit (Hub currently calls toFahrenheit())
    s.toFahrenheit();
    string tempF = s.getValue("temp");
    double tF = stod(tempF);

    cout << "Sensor temp (F) = " << tF << endl;
    // 25°C -> 77°F
    assert(tF > 76.9 && tF < 77.1);

    // Convert back to Celsius
    s.toCelsius();
    string tempC = s.getValue("temp");
    double tC = stod(tempC);

    cout << "Sensor temp (C) = " << tC << endl;
    assert(tC > 24.9 && tC < 25.1);

    cout << "[PASS] testSensorTemperatureConversion\n";
}

// ---- Test 2: getValue() returns the correct strings ----
void testSensorGetValue() {
    Sensor s("dev42");
    s.setData("2024-01-01 12:00", "0.5", "40", "100", "0.1", "1", "0", 20.0);

    assert(s.getValue("co") == "0.5");
    assert(s.getValue("humidity") == "40");
    assert(s.getValue("light") == "100");
    assert(s.getValue("lpg") == "0.1");
    assert(s.getValue("motion") == "1");
    assert(s.getValue("smoke") == "0");

    cout << "[PASS] testSensorGetValue\n";
}

// ---- Test 3: small end-to-end run through Hub ----
void testHubPipeline() {
    // 1) Create a small test CSV that matches your Hub indexing
    const string testFile = "test_iot.csv";
    ofstream out(testFile);
    out << "\"ts\",\"device\",\"co\",\"humidity\",\"light\",\"lpg\",\"motion\",\"smoke\",\"temperature\"\n";
    out << "\"2024-01-01 12:00\",\"devA\",\"0.3\",\"50\",\"200\",\"0.01\",\"0\",\"0\",\"25\"\n";
    out << "\"2024-01-01 12:05\",\"devB\",\"0.4\",\"55\",\"250\",\"0.02\",\"1\",\"1\",\"30\"\n";
    out.close();

    // 2) Run Hub on this small file
    // Use "test_out\\" on Windows or "test_out/" on Linux/Mac
    Hub hub(testFile);
    hub.run("test_out/");

    cout << "[INFO] Hub.run() executed on " << testFile << endl;
    cout << "[MANUAL CHECK] Look at files in test_out/ (co_data.csv, humidity_data.csv, etc.)\n";
    cout << "[PASS] testHubPipeline (basic run)\n";
}

int main() {
    cout << "Running test bench...\n";

    testSensorTemperatureConversion();
    testSensorGetValue();
    testHubPipeline();

    cout << "All tests completed.\n";
    return 0;
}
