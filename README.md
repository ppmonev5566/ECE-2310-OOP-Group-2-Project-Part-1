This project is a C++ application that processes IoT telemetry data stored in a CSV file. It loads the raw dataset, organizes readings by device, converts temperature units, and exports clean, split datasets—one output CSV per 
sensor type (CO, humidity, light, LPG, motion, smoke, temperature, etc.).

The system emphasizes modular design with clear separation of concerns between data loading (Table), device modeling (Sensor), and orchestration (Hub).

CSV ingestion using a custom Table class

Automatic Sensor object creation per device ID

Temperature conversion (Celsius ↔ Fahrenheit)

Data cleanup + normalization

Automatic CSV splitting (one file per attribute/column)

Memory-safe design using explicit cleanup in destructors
------------------------------------------------------

1. Loading the CSV

Table opens the provided CSV and stores:

headers (first row)

rows (vector of string vectors)

2. Building Sensor Objects

The Hub iterates through all rows:

Creates a Sensor object for each unique device ID

Updates the sensor's fields with the row’s data

Converts temperature (based on current configuration)

3. Splitting Data into Multiple CSVs

For each header except ts and device, the program:

Creates a new output Table

Writes rows containing:
timestamp, device ID, that column’s value

Saves the file to the output directory
ts, device, co, humidity, light, lpg, motion, smoke, temperature



