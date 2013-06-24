//----------------------------------------------------------------------------
// C main line
//----------------------------------------------------------------------------

#include <m8c.h>        // part specific constants and macros
#include "PSoCAPI.h"    // PSoC API definitions for all User Modules

#define		LED_PORT		PRT0DR
		//Constant definition for the data port (Port 0) where the LED (LED1) resides.

#define		LED1_ON			0x01
#define		LED2_ON			0x02
#define		LED3_ON			0x04
#define		LED4_ON			0x08
		//Constant definition to OR with the LED1_PORT to turn on the LED (LED1).

#define		LED1_OFF		0xFE
#define		LED2_OFF		0xFD
#define		LED3_OFF		0xFB
#define		LED4_OFF		0xF8
		//Constant definition to AND with the LED1_PORT to turn off the LED (LED1).

unsigned char ucVR_ADCResult;
		//This global variable holds the converted output of the potentiometer (VR).

void main()
{
    M8C_EnableGInt;
	    //Enables the Global Interrupt

	VR_PGA_Start(VR_PGA_HIGHPOWER);
			//Performs all required initialization for the PGA User Module and sets the power level for the PGA
			//to high power (VR_PGA_HIGHPOWER).

	VR_ADC_Start(VR_ADC_HIGHPOWER);
			//Performs all required initialization for the VR_ADC User Module and sets the power level to high power.

	VR_ADC_GetSamples(0);
			//Sets the VR_ADC to run continuously by providing a 0 in the paramater list.


    while(1)
		//infinte loop.
	{
		if (VR_ADC_fIsDataAvailable() != 0)
				//This function checks the availability of sampled data.  The function returns a non-zero
				//value if data has been converted and is ready to read.
       	{
        	ucVR_ADCResult = VR_ADC_bClearFlagGetData();
				//This function clears the data ready flag and gets converted data as an unsigned char and
				//stores it in the variable ucVR_ADCResult.   This function also checks to see that data-flag
				//is still reset.   If not the data is retrieved again.   This makes sure that the ADC interrupt
				//routine did not update the answer while it was being collected.

			if (ucVR_ADCResult <= 64 )
				// Test to see if the potentiometer is less than 1/3 of the way up its 8-bit scale.
			{
					//Disabling the Interrupt for the Timer stops the blinking
				LED_PORT |= LED1_ON;
					// Turns the LED Off
			}	//end (ucVR_ADCResult <= 85)

			else if (ucVR_ADCResult <= 128)
				// Test to see if the potentiometer is less than 2/3 of the way up its 8-bit scale.
			{
				LED_PORT |= LED2_ON;
					//Flashes the LED
			} // end (ucVR_ADCResult <= 170)
			else if (ucVR_ADCResult <= 192)
				// Test to see if the potentiometer is less than 2/3 of the way up its 8-bit scale.
			{
				LED_PORT |= LED3_ON;
					//Flashes the LED
			} // end (ucVR_ADCResult <= 170)
			else
				// Don't need to test the top third.
			{
					//Disabling the Interrupt for the Timer stops the blinking
				LED_PORT |= LED4_ON;
					//Turn on LED1 by setting Bit 0 of Port 0 to high.
			} // end else
		} // end (VR_ADC_fIsDataAvailable() != 0)
	}

    //Read Port0 and XOR it with 0x01 to change the status from On to Off and vice-versa.
    PRT0DR ^= 0x01;
}
