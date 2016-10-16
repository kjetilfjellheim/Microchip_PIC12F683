
#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic12f683.h>        /* For true/false definition */

#include "user.h"

void InitApp(void)
{
    /*
     * GP4 will be used as input from the sensor.
     */
    TRISIObits.TRISIO4 = 1;
    /*
     * ADC setup for channel AN3.
     */
    ADCON0bits.CHS = 0b11;
    /*
     * Turn on analog digital conversion.
     */
    ADCON0bits.ADON = 1;
    /*
     * GP0, GP1 and GP2 are output LEDs. 
     * RED = GP0
     * YELLOW = GP1
     * GREEN = GP2
     */
    TRISIObits.TRISIO0 = 0;
    TRISIObits.TRISIO1 = 0;
    TRISIObits.TRISIO2 = 0;
    
}

