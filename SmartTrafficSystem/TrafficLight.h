#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

enum LightState {
    RED,
    GREEN,
    YELLOW
};

class TrafficLight {
private:
    LightState state;

public:
    TrafficLight();

    void changeToGreen();
    void changeToRed();
    void changeToYellow();

    LightState getState() const;
};

#endif
