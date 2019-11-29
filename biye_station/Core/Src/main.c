/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int button_pressed_count=0;
int button_pressed_count2=0;
void button_handler1(){
	button_pressed_count++;
	printNum(0, 0 , button_pressed_count, 0xffff, 0x0000);
}
void button_handler2(){
	button_pressed_count2++;
	printNum(60, 0, button_pressed_count2, 0xf800, 0x0000);
}

uint8_t rbuf[1024]={0};
uint8_t tbuf[1024]={0};

	FATFS fs[3];
	DIR dir;
	FIL fl;
	FILINFO finfo;

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
//  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();

  /* USER CODE BEGIN SysInit */

	JTAG_Set(1);
	RCC_INIT(9);
	sysTick_Set();

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

//  extern Word_Module WordTable[];
//  extern uint8_t CharTable[][17];

  LCD_Init();
  clearScreen(0x0000);
  TOUCH_GPIO_Init();
  delay_us(100);					//这条语句可以让delay_us这个函数被编译
//  void(*DELAY_US)(uint32_t)=delay_us;	//这条语句可以让delay_us这个函数被编译

//  void ButtonCreate(uint8_t *name, uint8_t id, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, void(*handle)(), uint16_t font_color, uint16_t back_color, uint16_t border_color){
//  ButtonCreate("Button1", 0, 80, 220, 160, 280, button_handler1, 0xffff, 0xf800, 0x001f);
//  ButtonCreate("Button2", 1, 80, 130, 160, 190, button_handler2, 0xf800, 0xffff, 0x07e0);

//  NRF24L01_Init();
//
//  while(NRF24L01_Check());
//
//  NRF24L01_TX_Mode();


  for(int i=0;i<1024;i++){
	  tbuf[i]=i%128;
  }

	my_mem_init(SRAMIN);		//初始化内部内存池

// 	while(SD_Init());//检测不到SD卡

// 	switch(SDCardInfo.CardType)
// 		{
// 			case SDIO_STD_CAPACITY_SD_CARD_V1_1://printf("Card Type:SDSC V1.1\r\n");break;
// 			case SDIO_STD_CAPACITY_SD_CARD_V2_0://printf("Card Type:SDSC V2.0\r\n");break;
// 			case SDIO_HIGH_CAPACITY_SD_CARD://printf("Card Type:SDHC V2.0\r\n");break;
// 			case SDIO_MULTIMEDIA_CARD://printf("Card Type:MMC Card\r\n");break;
// 		}

// 	printNum(0, 0, SDCardInfo.CardType, 0xf800, 0x0000);
//
// 	printNum(0, 20, SDCardInfo.CardCapacity>>20, 0xffff, 0x0000);
//
// 	printNum(0, 40, SDCardInfo.CardBlockSize, 0xffff, 0x0000);

// 	if(SD_WriteDisk(tbuf, 53, 1)==0){
// 		if(SD_ReadDisk(rbuf, 53, 1)==0){
// 			delay_ms(1000);
// 		}
// 	}




// 	exfuns_init();							//为fatfs相关变量申请内存
//
 	int res;

// 	res = f_mount(&(fs[1]),"1:",1); 					//挂载SD卡

 	MKFS_PARM mp;

//	uint8_t res = f_mkfs("1:", &mp, NULL, 4096);//格式化SDCard,1,盘符;1,不需要引导区,8个扇区为1个簇


// 	printMultiString(0, 120, "你好骚啊，Cal。", 0xffff, 0x0000);


 	delay_ms(100);


// 	Files_Handler("1:/NE001.txt", txt);



// 	while(1);

 	dir.dir="1:/";
// 	uint8_t res=0;
// 	while(res!=4 || res!=5 ){
//
// 		res = f_opendir(&dir, "1:/");
// 		int i=1;
// 		for(;i;){
// 			res = f_readdir(&dir, &finfo);
//
// 			delay_ms(100);
// 		}
//
// 		delay_ms(1000);
// 	}



// 	delay_ms(10000);

  GUI_Menu01_Create(menu01_handler, 0);

//  int32_t i=0;

  extern uint8_t menu_flag;
  menu_flag=1;

  uint8_t buf[32]={0};

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//	  clearScreen(0x001f);
//	  clearScreen(0x07e0);
//	  clearScreen(0xf800);
//	  printString(0, 0, CharTable, WordTable, "Hello, stm32!\nHello, Cal!\0", 0xf800, 0x0000);

//	  drawRect(40,40,100,90,0xffff);
//	  drawRectWithBorder(30,80,100,120,0x0000,5);
//	  drawLine(20,150,120,250,0xffff);

//	  printNum(80, 150, i, 0xffff, 0x0000);
//
//	  i++;

//	  ScreenScan();
//	  Button_dothings();
//	  GUI_Menu01_Scan();
	  Menu01_loop();
	  Menu02_loop();

	  NRF24L01_TxPacket(buf);

//	  delay_ms(1000);
//	  delay_us(1000000);

//	  uint16_t tx,ty;
//
//	  if(get_Pen_XY(&tx, &ty)){
//		  printNum(80, 200, tx, 0xffff, 0xf800);
//		  printNum(80, 230, ty, 0xffff, 0xf800);
//	  }
//
//	  delay_ms(1000);

	  /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
