#ifndef SENSOR_H
#define SENSOR_H

#include <string>

namespace smartHome{
    class Sensor {
    public:
        Sensor(const std::string& type, const std::string& sensorId, double value, bool isFunctional);
        Sensor(const Sensor& other);
        Sensor& operator=(const Sensor& other);

        // Move constructor
        Sensor(Sensor&& other) noexcept;

        // Move assignment operator
        Sensor& operator=(Sensor&& other) noexcept;
        
        // Destructor
        virtual ~Sensor() = default;

        // Pure virtual function
        virtual void measure() = 0;
        
        //Getters & Setters
        const std::string& getType() const;
        const std::string& getID() const;
        double getValue() const;
        bool getIsFunctional() const;

        void setType(const std::string& newType);
        void setValue(double newValue);
        void setIsFunctional(bool newValue);

    private:
        std::string type;
        const std::string sensorId;
        double value;
        bool isFunctional;
    };
}
#endif // SENSOR_H