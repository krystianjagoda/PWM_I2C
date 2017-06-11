/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC12F1840
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

char dutyValueH = 0;  
char dutyValueL = 0;
int dutyValue = 0;


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

   writeEEPROMvalue(0x00, DATAEE_ReadByte(0x00));
   writeEEPROMvalue(0x01, DATAEE_ReadByte(0x01));
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        dutyValueH = returnEEPROMvalue(0);
        dutyValueL = returnEEPROMvalue(1);
        
        if(returnEEPROMvalue(2) == 0x01){
            DATAEE_WriteByte(0x00, dutyValueH);
            DATAEE_WriteByte(0x01, dutyValueL);
            writeEEPROMvalue(2, 0x00);
        }      

        dutyValue = (dutyValueH << 8) | (dutyValueL & 0xff);
        
       if(dutyValue == 0){
           IO_RA4_SetLow();
           EPWM_LoadDutyValue(0);   
       } 
       else{
           IO_RA4_SetHigh();
           EPWM_LoadDutyValue(dutyValue);   
       }      
        
        __delay_ms(10);               
    }
}
/**
 End of File
*/