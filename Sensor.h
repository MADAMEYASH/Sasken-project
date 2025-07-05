class Sensor {
private:
    int laneId;

public:
    Sensor(int id);
    int detectVehicles();
    bool detectEmergency(); 
};
