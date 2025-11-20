#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>
using namespace std;
class Sensor {
    string id;
    
    string ts;
    string co;
    string humidity;
    string light;
    string lpg;
    string motion;
    string smoke;
    double temperature;
    bool celsius = true;

    public:
        Sensor(string id);
        void setData(string ts, string co, string humidity, string light, string lpg, string motion, string smoke, double temperature);
        void toCelsius();
        void toFahrenheit();
        string getId();
        string getValue(string header);
};

#endif