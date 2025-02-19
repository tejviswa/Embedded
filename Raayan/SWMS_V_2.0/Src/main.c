/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
//#include "16x2_LCD.h"
#include "USART6.h"
#include "fonts.h"
#include "st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/*FOR TASK 2 temperature*/
int lm35_data;
int lm35_flag;
char temp[10];


int internet_status;

char str2[4];
char str3[4];
char str4[4];

char str5[8];
char str6[8];
char str7[8];
//uint8_t pData={0x10,0x56,0x15,0x05,0x07,0x02,0x25};

/*FOR TASK 5 configuration*/
unsigned char sec=0,min=0,hour=0,day=0,date=0,month=0,year=0;
unsigned char buff[10];
char str[10];
int config_flag;
unsigned char pData[]={0x10,0x14,0x17,0x05,0x07,0x02,0x25};

unsigned char rec[8];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void Task1_ReadRTC_WriteLCD_1Sec(void);
void Task2_ReadLM35_WriteLCD_5Sec(void);
void Task3_Check_InternetStatus(void);
void Task4_Wi_Fi_Tx(void);
void Task5_SWMS_Config(void);
int DECIMAL_TO_BCD(unsigned int x);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART6_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_WriteString(0, 30, "Initialalizing     Wi-Fi...", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  sendcmds_wifi_init();
  ST7735_FillScreen(ST7735_BLACK);
  /*KM_LCD_Init();
  KM_LCD_Write_Cmd(0x81);
  KM_LCD_Write_Str(" Initialalizing     Wi-Fi...");

  //Wifi_Init();
  //sendcmds_wifi_init();

  //Task1_ReadRTC_WriteLCD_1Sec();
  KM_LCD_Write_Cmd(0x01);*/

 // HAL_I2C_Mem_Write(&hi2c1, 0x68 << 1, 0x00, 1,(uint8_t *) pData, 7, 100);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	 Task1_ReadRTC_WriteLCD_1Sec();
	 Task2_ReadLM35_WriteLCD_5Sec();
	 Task3_Check_InternetStatus();

	 if(lm35_flag && internet_status)   //checking if both the lm35data and internet status is OK
	 {
		 lm35_flag=internet_status=0;
		 Task4_Wi_Fi_Tx();
	 }
	 if(config_flag)
	 {
		 config_flag=0;
		 Task5_SWMS_Config();
	 }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_144CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI1_D_C_Pin|SPI1_RST_Pin|SPI1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|BUZZER_Pin
                          |LCD_D7_Pin|LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED_LED_Pin|GREEN_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : SPI1_D_C_Pin SPI1_RST_Pin SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_D_C_Pin|SPI1_RST_Pin|SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin BUZZER_Pin
                           RED_LED_Pin GREEN_LED_Pin LCD_D7_Pin LCD_RS_Pin
                           LCD_RW_Pin LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|BUZZER_Pin
                          |RED_LED_Pin|GREEN_LED_Pin|LCD_D7_Pin|LCD_RS_Pin
                          |LCD_RW_Pin|LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_UP_Pin SW_DN_Pin */
  GPIO_InitStruct.Pin = SW_UP_Pin|SW_DN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_ENT_Pin */
  GPIO_InitStruct.Pin = SW_ENT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_ENT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Task1_ReadRTC_WriteLCD_1Sec(void)
{

	HAL_I2C_Mem_Read(&hi2c1, 0x68 << 1, 0x00, 1, rec, 7, 100);

	sprintf(str2,"%2X",rec[2]);
	str2[2]=':';
	ST7735_WriteString(0, 30,str2, Font_11x18, ST7735_WHITE, ST7735_BLACK);

	sprintf(str3,"%2X",rec[1]);
	str3[2]=':';
	ST7735_WriteString(32, 30,str3, Font_11x18, ST7735_WHITE, ST7735_BLACK);

	sprintf(str4,"%2X",rec[0]);
	ST7735_WriteString(64, 30,str4, Font_11x18, ST7735_WHITE, ST7735_BLACK);


	sprintf(str5,"%2X",rec[4]);
    str5[2]=':';
	ST7735_WriteString(0, 60,str5, Font_11x18, ST7735_WHITE, ST7735_BLACK);

	sprintf(str6,"%2X",rec[5]);
	str6[2]=':';
	ST7735_WriteString(32, 60,str6, Font_11x18, ST7735_WHITE, ST7735_BLACK);

	sprintf(str7,"%2X",rec[6]);
	ST7735_WriteString(64, 60,str7, Font_11x18, ST7735_WHITE, ST7735_BLACK);




			/*KM_LCD_Write_Cmd(0x81);
			KM_LCD_Write_Data(((rec[2]>>4)&0x01)+ 48);
			KM_LCD_Write_Data(((rec[2])&0x0F) +48);

			KM_LCD_Write_Cmd(0x83);
			KM_LCD_Write_Str(":");


			KM_LCD_Write_Cmd(0x84);
			KM_LCD_Write_Data((rec[1]>>4)+ 48);
			KM_LCD_Write_Data(((rec[1])&0x0F) +48);

			KM_LCD_Write_Cmd(0x86);
			KM_LCD_Write_Str(":");

			KM_LCD_Write_Cmd(0x87);
			KM_LCD_Write_Data((rec[0]>>4)+ 48);
			KM_LCD_Write_Data(((rec[0])&0x0F) +48);

			KM_LCD_Write_Cmd(0xC1);
			KM_LCD_Write_Data((rec[4]>>4)+ 48);
			KM_LCD_Write_Data(((rec[4])&0x0F) +48);

			KM_LCD_Write_Cmd(0xC3);
			KM_LCD_Write_Str("/");

			KM_LCD_Write_Cmd(0xC4);
			KM_LCD_Write_Data((rec[5]>>4)+ 48);
			KM_LCD_Write_Data(((rec[5])&0x0F) +48);

			KM_LCD_Write_Cmd(0xC6);
			KM_LCD_Write_Str("/");

			KM_LCD_Write_Cmd(0xC7);
			KM_LCD_Write_Data((rec[6]>>4)+ 48);
			KM_LCD_Write_Data(((rec[6])&0x0F) +48);
			*/

}

void Task2_ReadLM35_WriteLCD_5Sec(void)
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 20);
	lm35_data = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	//lm35_data=((lm35_data*330)/4096);
	sprintf(temp,"%d",lm35_data);
	ST7735_WriteString(60, 90,temp, Font_11x18, ST7735_WHITE, ST7735_BLACK);

	//itoa(temp,lm35_data);

	lm35_flag=1;

/*
	KM_LCD_Write_Cmd(0x8E);
	KM_LCD_Write_Data(0xDF);
	KM_LCD_Write_Data('C');
	KM_LCD_Write_Cmd(0x8C);
	KM_LCD_Write_Str(temp);
*/

	}

void Task3_Check_InternetStatus(void)
{
	int res;
		HAL_UART_Transmit(&huart6, (uint8_t *)"AT+CIPSTATUS\r\n", 16, 1000);

			res=(Check_Wifi_Response());
			if((res==SUCCESS))
			{
				//connect_wifi();
				internet_status=1;
			//	KM_LCD_Write_Cmd(0xCB);
			//	KM_LCD_Write_Str("IPOK");
				ST7735_WriteString(100, 52,"IPOK", Font_11x18, ST7735_WHITE, ST7735_BLACK);

				HAL_Delay(500);
				ST7735_WriteString(100, 52,"    ", Font_11x18, ST7735_WHITE, ST7735_BLACK);
			//	KM_LCD_Write_Cmd(0xCB);
			//	KM_LCD_Write_Str("    ");

			}
			/*else
			{
				KM_LCD_Write_Cmd(0xCB);
				KM_LCD_Write_Str("FAIL");
			}*/
			HAL_Delay(50);
	}

void Task4_Wi_Fi_Tx(void)
{
	Wifi_Transmit();
	}

void Task5_SWMS_Config(void)
{
	int t=0;

			/*	KM_LCD_Write_Cmd(0x01);
				KM_LCD_Write_Cmd(0x81);
				KM_LCD_Write_Str("SS:MM:HH");*/
				ST7735_FillScreen(ST7735_BLUE);
				ST7735_WriteString(30, 30,"SS:MM:HH", Font_11x18, ST7735_WHITE, ST7735_BLACK);

			/*	KM_LCD_Write_Cmd(0xC1);
				KM_LCD_Write_Str("00");*/
				ST7735_WriteString(30, 50,"00", Font_11x18, ST7735_WHITE, ST7735_BLACK);

		//CONFIGURATION BEGINS HERE
				while(t<8)
				{
				switch(t)
				{
					case 0:while(1)
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))                        //FOR SEC
								{
									HAL_Delay(250);
									sec=sec+1;
									if(sec>=0 && sec<60)
									{
								//	KM_LCD_Write_Cmd(0xC1);
									sprintf(str,"%02d",sec);
								//	KM_LCD_Write_Str(str);
									ST7735_WriteString(30, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
									}
									else
									{
										sec=0;
								//		KM_LCD_Write_Cmd(0xC1);
										sprintf(str,"%02d",sec);
										ST7735_WriteString(30, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
								//		KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									sec = sec-1;
									if(sec>=0 && sec<60)
									{
								//	KM_LCD_Write_Cmd(0xC1);
									sprintf(str,"%02d",sec);
									ST7735_WriteString(30, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
								//	KM_LCD_Write_Str(str);
									}
									else
									{
										sec=59;
								//		KM_LCD_Write_Cmd(0xC1);
										sprintf(str,"%02d",sec);
										ST7735_WriteString(30, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
								//		KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=1;
									HAL_Delay(250);
									break;
								}

							}
						break;


					case 1:
						//KM_LCD_Write_Cmd(0xC3);                               //FOR MIN
							//	KM_LCD_Write_Str(":00");
								ST7735_WriteString(55, 50,":00", Font_11x18, ST7735_WHITE, ST7735_BLACK);
						while(1)
							{
								if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									min=min+1;
									if(min>=0 && min<60)
									{
								//	KM_LCD_Write_Cmd(0xC4);
									sprintf(str,"%02d",min);
									ST7735_WriteString(64, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
								//	KM_LCD_Write_Str(str);
									}
									else
									{
										min=0;
							//			KM_LCD_Write_Cmd(0xC4);
										sprintf(str,"%02d",min);
										ST7735_WriteString(64, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
								//		KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									min = min-1;
									if(min>=0 && min<60)
									{
						//			KM_LCD_Write_Cmd(0xC4);
									sprintf(str,"%02d",min);
									ST7735_WriteString(64, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										min=59;
							//			KM_LCD_Write_Cmd(0xC4);
										sprintf(str,"%02d",min);
										ST7735_WriteString(64, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//			KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=2;
									HAL_Delay(250);
									break;
								}

							}
						break;


					case 2:
							//	KM_LCD_Write_Cmd(0xC6);
							//	KM_LCD_Write_Str(":00");
								ST7735_WriteString(90, 50,":00", Font_11x18, ST7735_WHITE, ST7735_BLACK);
						while(1)                                                  //FOR HOURS
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									hour=hour+1;
									if(hour>=0 && hour<25)
									{
							//		KM_LCD_Write_Cmd(0xC7);
									sprintf(str,"%02d",hour);
									ST7735_WriteString(100, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										hour=0;
							//			KM_LCD_Write_Cmd(0xC7);
										sprintf(str,"%02d",hour);
										ST7735_WriteString(100, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//			KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									hour = hour-1;
									if(hour>=0 && hour<60)
									{
							//		KM_LCD_Write_Cmd(0xC7);
									sprintf(str,"%02d",hour);
									ST7735_WriteString(100, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										hour=23;
							//			KM_LCD_Write_Cmd(0xC7);
										sprintf(str,"%02d",hour);
										ST7735_WriteString(100, 50,str, Font_11x18, ST7735_WHITE, ST7735_BLACK);
							//			KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=3;
									HAL_Delay(250);
									break;
								}

							}
						break;

					case 3:                                                    //FOR DAY
						/*		KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0x81);
								KM_LCD_Write_Str("DAY:DD:MM:YY");
								KM_LCD_Write_Cmd(0xC2);
								KM_LCD_Write_Str("00");*/
						while(1)
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									day=day+1;
									if(day>=0 && day<8)
									{
							//		KM_LCD_Write_Cmd(0xC2);
									sprintf(str,"%02d",day);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										day=0;
							//			KM_LCD_Write_Cmd(0xC2);
										sprintf(str,"%02d",day);
							//			KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									day = day-1;
									if(day>=0 && day<8)
									{
						//			KM_LCD_Write_Cmd(0xC2);
									sprintf(str,"%02d",day);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										day=7;
						//				KM_LCD_Write_Cmd(0xC2);
										sprintf(str,"%02d",day);
							//			KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=4;
									HAL_Delay(250);
									break;
								}

							}
						break;

					case 4:                                                     //FOR DATE
						//		KM_LCD_Write_Cmd(0xC4);
						//		KM_LCD_Write_Str(":00");
						while(1)
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									date=date+1;
									if(date>=1 && date<32)
									{
						//			KM_LCD_Write_Cmd(0xC5);
									sprintf(str,"%02d",date);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										date=1;
							//			KM_LCD_Write_Cmd(0xC5);
										sprintf(str,"%02d",date);
							//			KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									date = date-1;
									if(date>=1 && date<32)
									{
							//		KM_LCD_Write_Cmd(0xC5);
									sprintf(str,"%02d",date);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										date=31;
							//			KM_LCD_Write_Cmd(0xC5);
										sprintf(str,"%02d",date);
							//			KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=5;
									HAL_Delay(250);
									break;
								}

							}
						break;

					case 5:                                             //FOR MONTH
							//	KM_LCD_Write_Cmd(0xC7);
							//	KM_LCD_Write_Str(":00");
						while(1)
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									month=month+1;
									if(month>=1 && month<13)
									{
						//			KM_LCD_Write_Cmd(0xC8);
									sprintf(str,"%02d",month);
							//		KM_LCD_Write_Str(str);
									}
									else
									{
										month=1;
						//				KM_LCD_Write_Cmd(0xC8);
										sprintf(str,"%02d",month);
							//			KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									month = month-1;
									if(month>=1 && month<13)
									{
					//				KM_LCD_Write_Cmd(0xC8);
									sprintf(str,"%02d",month);
						//			KM_LCD_Write_Str(str);
									}
									else
									{
										month=12;
						//				KM_LCD_Write_Cmd(0xC8);
										sprintf(str,"%02d",month);
						//				KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=6;
									HAL_Delay(250);
									break;
								}
							}

						break;

					case 6:                                              //FOR YEAR
					//		KM_LCD_Write_Cmd(0xCA);
						//		KM_LCD_Write_Str(":00");
						while(1)
							{
							if(!HAL_GPIO_ReadPin(SW_UP_GPIO_Port, SW_UP_Pin))
								{
									HAL_Delay(250);
									year=year+1;
									if(year>=0 && year<100)
									{
					//				KM_LCD_Write_Cmd(0xCB);
									sprintf(str,"%02d",year);
					//				KM_LCD_Write_Str(str);
									}
									else
									{
										year=0;
					//					KM_LCD_Write_Cmd(0xCB);
										sprintf(str,"%02d",year);
						//				KM_LCD_Write_Str(str);
									}

								}
								if(!HAL_GPIO_ReadPin(SW_DN_GPIO_Port, SW_DN_Pin))
								{
									HAL_Delay(250);
									year = year-1;
									if(year>=0 && year<100)
									{
					//				KM_LCD_Write_Cmd(0xCB);
									sprintf(str,"%02d",year);
					//				KM_LCD_Write_Str(str);
									}
									else
									{
										year=99;
					//					KM_LCD_Write_Cmd(0xCB);
										sprintf(str,"%02d",year);
						//				KM_LCD_Write_Str(str);
									}
								}
								if(!(HAL_GPIO_ReadPin(SW_ENT_GPIO_Port, SW_ENT_Pin)))
								{
									t=7;
									HAL_Delay(250);
									break;
								}
							}
						break;
								                           //COVERTING TO BCD AND STORING IN BUFFER ARRAY
					case 7:
						buff[0]=DECIMAL_TO_BCD(sec);buff[1]=DECIMAL_TO_BCD(min);buff[2]=DECIMAL_TO_BCD(hour);
						buff[3]=DECIMAL_TO_BCD(day);buff[4]=DECIMAL_TO_BCD(date);buff[5]=DECIMAL_TO_BCD(month);buff[6]=DECIMAL_TO_BCD(year);
						t=8;

						EXTI->IMR |= (0x01<<10);                   //ENABLING  THE SW_ENT INTERRUPT
						break;

				}      //switch case end

			} //main while end

			HAL_I2C_Mem_Write(&hi2c1, 0x68<<1, 0x00, 1, buff, 7, 100);           //WRITING TIME TO RTC

		//		KM_LCD_Write_Cmd(0x01);
			}


int DECIMAL_TO_BCD(unsigned int x)
{
	int res,res1,res2;
	res1=x%10;
	res2=x/10;
	res=res1|(res2<<4);

	return res;
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
