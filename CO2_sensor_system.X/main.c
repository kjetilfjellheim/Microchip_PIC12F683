
#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>
#include <pic12f683.h>        /* For true/false definition */
#include <math.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#define _XTAL_FREQ          32000000
#define ADC_BITS            10
#define VDD                 5
#define ZERO_POINT_VALUE    0.32
#define DC_GAIN             8.5

double getSensorMeasurement();
unsigned int getResultLed(double voltage);
void setResultLeds(unsigned int co2);
double getPowValue(double voltage);

void main(void) {
    /**
     * Configure oscillator.
     */
    ConfigureOscillator();
    /**
     * Initalize.
     */
    InitApp();

    /**
     * Main loop.
     */
    while (1) {
        /**
         * Wait one second.
         */
        __delay_ms(1000);
        /**
         * Get sensor measurement.
         */
        double sensorMeasurement = getSensorMeasurement();
        /**
         * Calculate ppm co2 value.
         */
        unsigned int leds = getResultLed(sensorMeasurement);
        /**
         * Set result LEDs based on ppm.
         */
        setResultLeds(leds);
    }
}

/**
 * 
 * @return 
 */
double getSensorMeasurement() {
    /**
     * Start temperature measurement.
     */
    ADCON0bits.GO = 1;
    /**
     * Wait until measurement is completed and ADGO is 0.
     */
    while (ADCON0bits.GO);
    unsigned char val = ADRESH;
    return (VDD * val) / ADC_BITS;
}

unsigned int getResultLed(double voltage) {
    if ((voltage / DC_GAIN) >= ZERO_POINT_VALUE) 
    {
        return 0;        
    } 
    else 
    {
        if (voltage > 3.3) { //Less than 150 ppm
            return 0b0000000000000000;
        } else if (voltage > 3.1) { // Less than 235 ppm
            return 0b1000000000000000;
        } else if (voltage > 2.9) { // Less than 337 ppm
            return 0b1100000000000000;
        } else if (voltage > 2.8) { // Less than 403 ppm
            return 0b1110000000000000;
        } else if (voltage > 2.7) { // Less than 482 ppm
            return 0b1111000000000000;
        } else if (voltage > 2.6) { // Less than 578 ppm
            return 0b1111100000000000;
        } else if (voltage > 2.5) { // Less than 691 ppm
            return 0b1111110000000000;
        } else if (voltage > 2.4) { // Less than 828 ppm
            return 0b1111111000000000;
        } else if (voltage > 2.2) { // Less than 1186 ppm
            return 0b1111111100000000;
        } else if (voltage > 2.0) { // Less than 1700 ppm
            return 0b1111111110000000;
        } else {
            return 0b1111111111000000;
        }
        
    }
}

void setResultLeds(unsigned int leds) {
    
}
