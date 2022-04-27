/*------------------------------------------------------------------------------

	DHT22 temperature & humidity sensor AM2302 (DHT22) driver_port for ESP32

    Embedded-Systems-Communication-Protocols Project (CESE 16)

    Abril 2022:	RIZO Héctor, new for DHT22  	


---------------------------------------------------------------------------------*/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include "DHT22.h"
#include "DHT22_port.h"

// == global defines =============================================

//static const char* TAG = "DHT";

int DHTgpio = 4;				// DHT pin = 4




/*-------------------------------------------------------------------------------
;
;	 *  @brief Function set the DHT used pin
      
     *  @details   This function configures the GPIO port to use.
     *   	
     *
	 *  @param		The GPIO number.
	 *  @return     None.

;--------------------------------------------------------------------------------*/
void setDHTgpio( int gpio )
{
	DHTgpio = gpio;
}



/*-------------------------------------------------------------------------------
;
;	 *  @brief Function get signal level 
      
     *  @details   Function to check if the time and signal level is the indicated one
     *   	
     *
	 *  @param		Determines the action to be taken with the pin connected to the DHT.
	 *  @return     State time.

;--------------------------------------------------------------------------------*/

int getSignalLevel( int usTimeOut, bool state )
{

	int uSec = 0;
	while( gpio_get_level(DHTgpio)==state ) {

		if( uSec > usTimeOut ) 
			return -1;
		
		++uSec;
		ets_delay_us(1);		// uSec delay
	}
	
	return uSec;
}




/*-------------------------------------------------------------------------------
;
;	 *  @brief Function set direction gpio 
      
     *  @details   Function that configures the GPIO port as output or input according to the necessary case
     *   	
     *
	 *  @param		None.
	 *  @return     None.

;--------------------------------------------------------------------------------*/

void setDirectionGpio (void)
{
	// == Send start signal to DHT sensor ===========

	gpio_set_direction( DHTgpio, GPIO_MODE_OUTPUT );

	// pull down for 3 ms
	gpio_set_level( DHTgpio, 0 );
	ets_delay_us( 3000 );			

	// pull up for 25 us asking for data
	gpio_set_level( DHTgpio, 1 );
	ets_delay_us( 25 );

	gpio_set_direction( DHTgpio, GPIO_MODE_INPUT );		// change to input mode
} 
	