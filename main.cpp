#include "Hub.h"

int main() {
    Hub hub("iot_telemetry_data.csv");
    hub.run("out\\");   // or "out/" depending on your OS / folder
    return 0;
}
