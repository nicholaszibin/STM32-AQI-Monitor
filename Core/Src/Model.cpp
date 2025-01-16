#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>


#ifndef SIMULATOR
#include "main.h"
#include <string.h>
#include <stdio.h>
extern "C"
{
	extern I2C_HandleTypeDef hi2c1;
	extern UART_HandleTypeDef huart2;

	void PMSA003I_Read(PMSA003I *aqi_data, I2C_HandleTypeDef *i2cHandle) {

		HAL_StatusTypeDef ret;      //Confirms whether I2C data transfer was successful
		uint8_t buf[32];			//Create a buffer with length of 32 as this matches the PMSA003I detached
		uint16_t buf_u16[15];
		buf[0] = PMSA003I_TEMP;

		ret = HAL_I2C_Master_Transmit(i2cHandle, PMSA003I_ADDR, buf, 1, HAL_MAX_DELAY);
		if ( ret != HAL_OK ) {
		  strcpy((char*)buf, "Error Tx\r\n");

		} else {
			ret = HAL_I2C_Master_Receive(i2cHandle, (0x12 << 1), buf, 32, HAL_MAX_DELAY);

	        if ( ret != HAL_OK || buf[0] != 0x42) {
			  strcpy((char*)buf, "Error Tx\r\n");

			} else {

				for (uint8_t i = 0; i < 15; i++) {
					//buf_u16[i] = (buf[2 + i * 2]);
					//buf_u16[i] += buf[2 + i * 2 + 1];
					buf_u16[i] = (buf[2 + i * 2] << 8) | buf[2 + i * 2 + 1];
				}

	            memcpy(aqi_data, buf_u16, sizeof(buf_u16));
			}
	  }
	  return;
	}





	float pm25[] = {0, 12.1, 35.5, 55.5, 150.5, 250.5, 500};
	float aqi25[] = {0, 50, 100, 150, 200, 300, 500};
	float aqi25_calc = 0;

	float pm10[] = {0, 55, 155, 255, 355, 425, 604};
	float aqi10[] = {0, 50, 100, 150, 200, 300, 500};
	float aqi10_calc = 0;

	PMSA003I aqi;

#endif



int n = 0;


}


Model::Model() : modelListener(0), aqi_val(0)
{

}

void Model::tick()
{

	if (n == 30) {

		#ifndef SIMULATOR

			PMSA003I_Read(&aqi, &hi2c1);

			char print_buffer[30];
			sprintf((char*)print_buffer, "PM2.5: %i ug_m3 \r\n", aqi.pm25_standard);

			HAL_UART_Transmit(&huart2, (uint8_t*)&print_buffer, strlen(print_buffer),1000);// Sending in normal mode (uint8_t*)&

			//char print2_buffer[30];
			//sprintf((char*)print2_buffer, "PM10: %i ug_m3 \r\n", aqi.pm10_standard);

			//HAL_UART_Transmit(&huart2, (uint8_t*)&print2_buffer, strlen(print2_buffer),1000);// Sending in normal mode (uint8_t*)&

			//Calculate PM2.5 AQI
		  int i = 1;
		  while (aqi.pm25_standard >= pm25[i]){
			i++;
		  }
		  aqi25_calc = (aqi25[i] - aqi25[i-1]) / (pm25[i] - pm25[i-1]) * (aqi.pm25_standard - pm25[i-1]) + aqi25[i-1];
		  aqi25_calc = aqi25_calc / 100 * 2; //Scale to max of 10

		  //Calculate PM10 AQI
		  i = 1;
		  while (aqi.pm10_standard >= pm10[i]){
			i++;
		  }
		  aqi10_calc = (aqi10[i] - aqi10[i-1]) / (pm10[i] - pm10[i-1]) * (aqi.pm10_standard - pm10[i-1]) + aqi10[i-1];
		  aqi10_calc = aqi10_calc / 100 * 2; //Scale to max of 10

		  aqi_val = aqi25_calc > aqi10_calc? aqi25_calc : aqi10_calc;

			char print2_buffer[30];
			sprintf((char*)print2_buffer, "AQI: %i.%i\r\n", (int)aqi_val, (int)(aqi_val * 10) % 10); //-u _printf_float not working...

			HAL_UART_Transmit(&huart2, (uint8_t*)&print2_buffer, strlen(print2_buffer),1000);// Sending in normal mode (uint8_t*)&
		#endif



	n = 0;
	}

	n++;


	modelListener->setAQI (aqi_val, aqi25_calc, aqi10_calc);

}
