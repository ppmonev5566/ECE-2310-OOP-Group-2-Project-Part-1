#include "sensor.h"
#include <string>

Sensor::Sensor(string id){
    this->id = id;
}

void Sensor::setData(string ts, string co, string humidity, string light, string lpg, string motion, string smoke, double temperature){
    this->ts = ts;
    this->co = co;
    this->humidity = humidity;
    this->light = light;
    this->lpg = lpg;
    this->motion = motion;
    this->smoke = smoke;
    this->temperature = temperature;
}

void Sensor::toCelsius(){
    if(!celsius){
        temperature = (temperature - 32) * 5.0/9.0;
        celsius = true;
    }
}

void Sensor::toFahrenheit(){
    if(celsius){
        temperature = (temperature * 9.0/5.0) + 32;
        celsius = false;
    }
}

string Sensor::getId(){
    return id;
}

string Sensor::getValue(string header){
    if(header == "co"){
        return co;
    } else if(header == "ts"){
        return ts;
    } else if(header == "humidity"){
        return humidity;
    } else if(header == "light"){
        return light;
    } else if(header == "lpg"){
        return lpg;
    } else if(header == "motion"){
        return motion;
    } else if(header == "smoke"){
        return smoke;
    } else if(header == "temp"){
        return to_string(temperature);
    }
    return "";
}