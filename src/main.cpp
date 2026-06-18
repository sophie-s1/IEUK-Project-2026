// Engineering Sector Skills Project
// Created by Sophie Smeeton for IEUK 2026
// Revision 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>

int main() {
    // Input file
    std::string file_path = "telemetry_data(in).csv";
    std::ifstream file(file_path);

    // Current line of csv
    std::string line;

    // Set of turbine IDs with vibration spikes over 15.0 mm/s
    std::set<std::string> high_vibration_turbines;
    // Set of turbine IDs with average temperature over 85.0 °C
    std::set<std::string> high_temp_turbines;
    // Map of accumulated temperature data: {turbine_id: {sum_of_temperatures, count}}
    std::map<std::string, std::pair<double, int>> temp_stats;

    // Read and discard the first line (header)
    std::getline(file, line);

    // Read the file line by line
    while (std::getline(file, line)) {
        // Convert line to stream for parsing
        // TODO: take data from stdin for real-time processing?
        std::stringstream line_stream(line);

        // Variables to hold parsed values
        std::string timestamp, turbine_id, temp_str, vib_str, rpm_str;

        // Parse fields separated by commas
        std::getline(line_stream, timestamp, ',');
        std::getline(line_stream, turbine_id, ',');
        std::getline(line_stream, temp_str, ',');
        std::getline(line_stream, vib_str, ',');
        std::getline(line_stream, rpm_str, ',');

        // TODO: identify and handle corrupted rows/missing data

        try {
            // Convert temperature and vibration to floats
            float temperature_c = std::stof(temp_str);
            float vibration_mm_s = std::stof(vib_str);

            // 1. Check for vibration spikes over 15.0
            if (vibration_mm_s > 15.0) {
                high_vibration_turbines.insert(turbine_id);
            }

            // 2. Accumulate temperature data
            temp_stats[turbine_id].first += temperature_c; // add to sum
            temp_stats[turbine_id].second += 1;            // increment count

        } catch (const std::invalid_argument& e) {
            // TODO: log rows where conversion to double fails (e.g., corrupted data)
            continue;
        }
    }

    // Calculate and check average temperature of each turbine
    for (const auto& pair : temp_stats) {
        const std::string& t_id = pair.first;
        double sum = pair.second.first;
        int count = pair.second.second;
        double avg_temp = sum / count;

        if (avg_temp > 85.0) {
            high_temp_turbines.insert(t_id);
        }
    }

    // Output the results
    std::cout << "=== Turbine Analysis Results ===" << std::endl;

    std::cout << "Turbines with vibration spikes over 15.0 mm/s: [";
    bool first = true;
    for (const auto& id : high_vibration_turbines) {
        if (!first) std::cout << ", "; // Add a comma and space if not the first element
        std::cout << "'" << id << "'"; // Print turbine ID
        first = false; // Update first to false after the first element
    }
    std::cout << "]" << std::endl;

    std::cout << "Turbines with an average temperature > 85.0 °C: [";
    first = true;
    for (const auto& id : high_temp_turbines) {
        if (!first) std::cout << ", "; // Add a comma and space if not the first element
        std::cout << "'" << id << "'"; // Print turbine ID
        first = false; // Update first to false after the first element
    }
    std::cout << "]" << std::endl;

    return 0;
}
