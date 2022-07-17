

/* 瑞仿电子	  ELH    enlighten  sunny
STM32 开发板 库函数部分	  */

// STM32串口1 PA9 PA10实验  串口会不停的自动发送出数据 到串口助手
//当接收到串口传来的数据 串口1进入中断 并将接收到的数据显示到串口助手上

// STM32C8系列 板上没有串口芯片  如果想做此实验 要用到串口模块

#include "delay.h"
#include "led.h"
#include "usart.h"
const u8 TEXT_TO_SEND[] = {"im you areyou"};
#define TEXT_LENTH sizeof(TEXT_TO_SEND) - 1 // TEXT_TO_SEND字符串长度(不包含结束符)
u8 SendBuff[10];
int main(void)
{
	int t, i;
	u8 len;
	u16 times = 0;
	delay_init();																		  //延时函数初始化
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);										  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);																	  //串口初始化为9600
	LED_Init();																			  //初始化与LED连接的硬件接口
	MYDMA_Config(DMA1_Channel4, (u32)&USART1->DR, (u32)TEXT_TO_SEND, 5); // DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
	
	USART1->CR3 = 1 << 7;		 //使能串口1的DMA发送
		MYDMA_Enable(DMA1_Channel4); //开始一次DMA传输！
		while (1)
		{
			if (DMA1->ISR & (1 << 13)) //等待通道4传输完成
			{
				DMA1->IFCR |= 1 << 13; //清除通道4传输完成标志
				break;
			}
		}
		delay_ms(2000);
	while (1)
	{
		MYDMA_Config(DMA1_Channel4, (u32)&USART1->DR, (u32)TEXT_TO_SEND,7); // DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
	
	USART1->CR3 = 1 << 7;		 //使能串口1的DMA发送
		MYDMA_Enable(DMA1_Channel4); //开始一次DMA传输！
		while (1)
		{
			if (DMA1->ISR & (1 << 13)) //等待通道4传输完成
			{
				DMA1->IFCR |= 1 << 13; //清除通道4传输完成标志
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
				break;
			}
		}
delay_ms(10000);
GPIO_SetBits(GPIOA,GPIO_Pin_1);
delay_ms(10000);
	}
}
