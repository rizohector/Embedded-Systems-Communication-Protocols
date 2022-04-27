/*

	DHT22 sensor reading implemetation

    Embedded-Systems-Communication-Protocols Project (CESE 16)

	Abril 2022: RIZO Héctor


*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "DHT22.h"
#include <DHT22_port.h>

extern int DHTgpio;

void DHT_task(void *pvParameter)
{
	setDHTgpio( DHTgpio );
	printf( "Starting DHT Task\n\n");

	while(1) {
	
		printf("=== Reading Sensor DHT ===\n" );
		int ret = readDHT();
		
		errorHandler(ret);

		printf( "Humidity    = %.1f\n", getHumidity() );
		printf( "Temperature = %.1f\n", getTemperature() );
		
		// -- wait at least 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 5000 / portTICK_RATE_MS );
	}
}

void app_main()
{
	nvs_flash_init();
	vTaskDelay( 1000 / portTICK_RATE_MS );
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );
}
