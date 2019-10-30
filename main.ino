#include <Adafruit_NeoPixel.h>
#include "pixel.h"

// PUSH-BUTTON

#define PUSH_BUTTON_LED_PIN_OUT 5
#define PUSH_BUTTON_SW_PIN_OUT 4
#define PUSH_BUTTON_SW_PIN_INT 2
#define PUSH_BUTTON_DEBOUNCE_INTERVAL 500 // Block keypresses occurring more frequently than this
volatile byte pushButtonState = LOW;
volatile unsigned long lastPressedTime;

// CRYSTAL LIGHTS

Pixel crystalLights[] = {
    Pixel(50, 255, 0, 4),
    Pixel(50, 255, 0, 6)};

const unsigned int crystalLightCount = sizeof(crystalLights) / sizeof(Pixel);

#define CRYSTAL_PIXEL_PIN 6
#define CRYSTAL_PIXEL_COUNT 2
Adafruit_NeoPixel crystalPixels(CRYSTAL_PIXEL_COUNT, CRYSTAL_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// STEM LIGHTS

Pixel stemLights[] = {
    Pixel(20, 60, 0, 10),  // Yellow
    Pixel(150, 255, 0, 5)   // Red
};

const unsigned int stemLightCount = sizeof(stemLights) / sizeof(Pixel);

#define STEM_PIXEL_PIN 8
#define STEM_PIXEL_COUNT 2
Adafruit_NeoPixel stemPixels(STEM_PIXEL_COUNT, STEM_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    lastPressedTime = millis();
    crystalPixels.begin();
    stemPixels.begin();

    pinMode(PUSH_BUTTON_LED_PIN_OUT, OUTPUT);
    pinMode(PUSH_BUTTON_SW_PIN_OUT, OUTPUT);
    digitalWrite(PUSH_BUTTON_SW_PIN_OUT, HIGH);
    pinMode(PUSH_BUTTON_SW_PIN_INT, INPUT_PULLUP);

    updatePushButtonLightState();
    attachInterrupt(digitalPinToInterrupt(PUSH_BUTTON_SW_PIN_INT), switchPressed, CHANGE);
}

void loop()
{
    crystalPixels.clear();
    stemPixels.clear();

    if (pushButtonState)
    {
        Pixel& crystalLight1 = crystalLights[0];
        int brightness = crystalLight1.GetBrightness();
        crystalPixels.setPixelColor(0, crystalPixels.Color(brightness, 0, brightness / 2));
        crystalLight1.Tick();

        Pixel& crystalLight2 = crystalLights[1];
        brightness = crystalLight2.GetBrightness();
        crystalPixels.setPixelColor(1, crystalPixels.Color(brightness, 0, brightness));
        crystalLight2.Tick();
    
        crystalPixels.show();

        Pixel& stemLight1 = stemLights[0];
        brightness = stemLight1.GetBrightness();
        stemPixels.setPixelColor(0, stemPixels.Color(brightness, brightness / 4, 0));
        stemLight1.Tick();

        Pixel& stemLight2 = stemLights[1];
        brightness = stemLight2.GetBrightness();
        stemPixels.setPixelColor(1, stemPixels.Color(brightness, 0, brightness / 50));
        stemLight2.Tick();
    
        stemPixels.show();
    }
    else
    {
        crystalPixels.show();
        stemPixels.show();
    }

    updatePushButtonLightState();

    delay(20);
}

void switchPressed()
{
    if (digitalRead(PUSH_BUTTON_SW_PIN_INT) == LOW)
    {
        unsigned long now = millis();
        if (now - lastPressedTime > PUSH_BUTTON_DEBOUNCE_INTERVAL)
        {
            pushButtonState = !pushButtonState;
            lastPressedTime = now;
        }
    }
}

void updatePushButtonLightState()
{
    digitalWrite(PUSH_BUTTON_LED_PIN_OUT, !pushButtonState);
}
