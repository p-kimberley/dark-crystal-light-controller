#include "Arduino.h"
#include "pixel.h"

Pixel::Pixel(int minBrightness, int maxBrightness, int startingBrightness, int speed)
{
    _minBrightness = minBrightness;
    _maxBrightness = maxBrightness;
    _startingBrightness = startingBrightness;
    _currentBrightness = 1;
    _speed = speed;
    _direction = 1;
}

void Pixel::Tick()
{
    _currentBrightness += _speed * _direction;
    if (_currentBrightness > _maxBrightness)
    {
        _currentBrightness = _maxBrightness;
        _direction *= -1;
    }
    else if (_currentBrightness < _minBrightness)
    {
        _currentBrightness = _minBrightness;
        _direction *= -1;
    }
}

int Pixel::GetBrightness()
{
    return _currentBrightness;
}