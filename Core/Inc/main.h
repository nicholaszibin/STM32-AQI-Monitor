/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define PMSA003I_ADDR	(0x12 << 1)
#define PMSA003I_TEMP	0x00;

//Plantower PMSA003I Particulate Matter Monitor
// https://cdn-shop.adafruit.com/product-files/4632/4505_PMSA003I_series_data_manual_English_V2.6.pdf
// https://cdn-shop.adafruit.com/product-files/4632/4505_PMSA003I_series_data_manual_English_V2.6.pdf

typedef struct {
uint16_t framelen;       ///< How long this data chunk is
uint16_t pm10_standard,  ///< Standard PM1.0
  pm25_standard,       ///< Standard PM2.5
  pm100_standard;      ///< Standard PM10.0
uint16_t pm10_env,       ///< Environmental PM1.0
  pm25_env,            ///< Environmental PM2.5
  pm100_env;           ///< Environmental PM10.0
uint16_t particles_03um, ///< 0.3um Particle Count
  particles_05um,      ///< 0.5um Particle Count
  particles_10um,      ///< 1.0um Particle Count
  particles_25um,      ///< 2.5um Particle Count
  particles_50um,      ///< 5.0um Particle Count
  particles_100um;     ///< 10.0um Particle Count
uint16_t unused;         ///< Unused
uint16_t checksum;       ///< Packet checksum
} PMSA003I;

/*
typedef struct {
	int index;
	int pm25;
	int pm10
} AQI;
*/


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FRAME_RATE_Pin GPIO_PIN_11
#define FRAME_RATE_GPIO_Port GPIOG
#define MCU_ACTIVE_Pin GPIO_PIN_10
#define MCU_ACTIVE_GPIO_Port GPIOF
#define VSYNC_FREQ_Pin GPIO_PIN_0
#define VSYNC_FREQ_GPIO_Port GPIOC
#define RENDER_TIME_Pin GPIO_PIN_1
#define RENDER_TIME_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
