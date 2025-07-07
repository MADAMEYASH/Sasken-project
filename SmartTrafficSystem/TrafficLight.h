#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

enum LightState { RED, GREEN, YELLOW };

class TrafficLight {
public:
    LightState state;
    TrafficLight();
    void changeToGreen();
    void changeToRed();
    void changeToYellow();
};

#endif
