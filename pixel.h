#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>

class Pixel
{
private:
    int _minBrightness;
    int _maxBrightness;
    int _startingBrightness;
    int _currentBrightness;
    int _speed;
    int _direction;

public:
    Pixel(int minBrightness, int maxBrightness, int startingBrightness, int speed);
    
    void Tick();
    int GetBrightness();
};

#endif