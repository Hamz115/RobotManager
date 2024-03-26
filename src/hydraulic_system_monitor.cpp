#include <string>

class HydraulicSystemMonitor {
public:
    std::string hydraulic_oil_temperature;
    std::string hydraulic_oil_tank_fill_level;
    std::string hydraulic_oil_pressure;

    HydraulicSystemMonitor(const std::string& temp, const std::string& fill_level, const std::string& pressure)
    : hydraulic_oil_temperature(temp), hydraulic_oil_tank_fill_level(fill_level), hydraulic_oil_pressure(pressure) {}

    std::string getTemperature() const {
        return hydraulic_oil_temperature;
    }

    std::string getFillLevel() const {
        return hydraulic_oil_tank_fill_level;
    }

    std::string getPressure() const {
        return hydraulic_oil_pressure;
    }

    // Optionally, create a method to retrieve all attributes as a tuple or a custom struct
    void getAllMetrics(std::string& temp, std::string& fill_level, std::string& pressure) const {
        temp = hydraulic_oil_temperature;
        fill_level = hydraulic_oil_tank_fill_level;
        pressure = hydraulic_oil_pressure;
    }
};