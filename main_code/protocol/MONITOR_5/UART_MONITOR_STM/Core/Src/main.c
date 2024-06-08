/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "math.h"

#include "stdlib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DATA_OUT_SIZE 20
#define UART_TRANSMIT_THRESHOLD 15
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

char str1[50];
char buffer1[50]; // Định nghĩa một mảng char đủ lớn để chứa kết quả
int length1;

char str2[50];
char buffer2[50];
int length2;

char str3[50];
char buffer3[50];
int length3;

char str4[50];
char buffer4[50];
int length4;

char str5[50];
char buffer5[50];
int length5;

char str6[50];
char buffer6[50];
int length6;

float t = 0.0;
double a1,a2,a3,a4,a5,a6 ;
float b1,b2,b3,b4,b5,b6 ;
double a = 0.0;
int count;

float c1, c2, c3, c4;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */







/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_8)
	{
		count +=1;

	}
}


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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  float x_cir = c3*cos(t);
	  float y_cir = c3*sin(t);


	  if (count % 2 == 0) {
	     	  // Tạo dữ 2 dữ liệu cho chart1
    	     a1 = sin(t) + t ;
    	     // Giới hạn giá trị chỉ với 4 chữ số sau dấu chấm thập phân
    	     int integer_part1 = (int)a1;
    	     float decimal_part1 = a1 - integer_part1; // Lấy phần thập phân
    	     decimal_part1 *= 10000000; // Dịch chuyển phần thập phân sang trái 4 chữ số
    	     int truncated_decimal1 = (int)decimal_part1; // Chuyển phần thập phân đã dịch chuyển thành số nguyên
    	      b1 = integer_part1 + truncated_decimal1 / 10000000.0; // Kết hợp lại phần nguyên và phần thập phân đã cắt


     	     a2 = 10 + sin(t) + t ;
     	     int integer_part2 = (int)a2;
     	     float decimal_part2 = a2 - integer_part2;
     	     decimal_part2 *= 10000000;
     	     int truncated_decimal2 = (int)decimal_part2;
     	      b2 = integer_part2 + truncated_decimal2 / 10000000.0;

     	     a3 =10 + sin(t) + t + a ;
     	     int integer_part3 = (int)a3;
     	     float decimal_part3 = a3 - integer_part3;
     	     decimal_part3 *= 10000000;
     	     int truncated_decimal3 = (int)decimal_part3;
     	     b3 = integer_part3 + truncated_decimal3 / 10000000.0;

     	     a4 =  sin(t) + t ;
     	     int integer_part4 = (int)a4;
     	     float decimal_part4 = a4 - integer_part4;
     	     decimal_part4 *= 10000000;
     	     int truncated_decimal4 = (int)decimal_part4;
     	     b4 = integer_part4 + truncated_decimal4 / 10000000.0;


     	     a5 = x_cir ;
     	     int integer_part5 = (int)a5;
     	     float decimal_part5 = a5 - integer_part5;
     	     decimal_part5 *= 10000000;
     	     int truncated_decimal5 = (int)decimal_part5;
     	     b5 = integer_part5 + truncated_decimal5 / 10000000.0;
     	     //b5 = c1;

     	     a6 = y_cir   ;
     	     int integer_part6 = (int)a6;
     	     float decimal_part6 = a6 - integer_part6;
     	     decimal_part6 *= 10000000;
     	     int truncated_decimal6 = (int)decimal_part6;
     	     b6 = integer_part6 + truncated_decimal6 / 10000000.0;
     	     //b6 = c2;



    	     //Đếm size của mảng trước khi gán
	 		 sprintf(str1, "%.7f", b1);
	 		 sprintf(str2, "%.7f", b2);
	 		 int length1 = strlen(str1);
	 		 int length2 = strlen(str2);

	 		 sprintf(str3, "%.7f", b3);
	 		 sprintf(str4, "%.7f", b4);
	 		 int length3 = strlen(str3);
	 		 int length4 = strlen(str4);

	 		 sprintf(str5, "%.7f", b5);
	 		 sprintf(str6, "%.7f", b6);
	 		 int length5 = strlen(str5);
	 		 int length6 = strlen(str6);

	 		 // lấy length vừa tính được định dạng cho chuỗi
	     	 char str_a1[length1], str_a2[length2];
	     	 sprintf(str_a1, "%.7f", b1);
	     	 sprintf(str_a2, "%.7f", b2);

	     	 char str_a3[length3], str_a4[length4];
	     	 sprintf(str_a3, "%.7f", b3);
	     	 sprintf(str_a4, "%.7f", b4);

	     	 char str_a5[length5], str_a6[length6];
	     	 sprintf(str_a5, "%.7f", b5);
	     	 sprintf(str_a6, "%.7f", b6);

	     	 // tính tổng size cho mảng data_out
	     	 uint16_t size_data_out = sizeof(str_a1) + sizeof(str_a2)  + sizeof(str_a3) + sizeof(str_a4)+ sizeof(str_a5) + sizeof(str_a6) + 6;


	     	 // ghép lần lượt các chuỗi  vào dataout
	     	 char data_out[size_data_out];
	     	 strcpy(data_out, str_a1);
	     	 strcat(data_out, ";");
	     	 strcat(data_out, str_a2);
	     	 strcat(data_out, ";");

	     	 strcat(data_out, str_a3);
	     	 strcat(data_out, ";");
	     	 strcat(data_out, str_a4);
	     	 strcat(data_out, ";");

	     	 strcat(data_out, str_a5);
	     	 strcat(data_out, ";");
	     	 strcat(data_out, str_a6);
	     	 strcat(data_out, ";");
	     	 HAL_UART_Transmit(&huart1, data_out, size_data_out , 100);

	          t +=0.1;


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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
