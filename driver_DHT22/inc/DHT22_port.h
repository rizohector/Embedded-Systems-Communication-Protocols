/* 

	DHT22 temperature sensor driver

*/


#include "DHT22.h"

// == function prototypes =======================================

void 	setDHTgpio(int gpio);

int getSignalLevel( int usTimeOut, bool state );
void setDirectionGpio (void);

