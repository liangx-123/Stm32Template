

/* ��µ���	  ELH    enlighten  sunny
STM32 ������ �⺯������	  */

// STM32����1 PA9 PA10ʵ��  ���ڻ᲻ͣ���Զ����ͳ����� ����������
//�����յ����ڴ��������� ����1�����ж� �������յ���������ʾ������������

// STM32C8ϵ�� ����û�д���оƬ  ���������ʵ�� Ҫ�õ�����ģ��

#include "delay.h"
#include "led.h"
#include "usart.h"
u8 TEXT_TO_SEND[8] = {"aaaaa"};
u8 TEXT_TO_SEND1[8] = {"bbbb"};
char data11[8];
#define TEXT_LENTH sizeof(TEXT_TO_SEND) - 1 // TEXT_TO_SEND�ַ�������(������������)
u8 SendBuff[10];
int main(void)
{

	int t, i, xx = 0;
	u8 len;
	u16 times = 0;
	delay_init();	 //��ʱ������ʼ��
					 //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);										  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600); //���ڳ�ʼ��Ϊ9600
	LED_Init();		 //��ʼ����LED���ӵ�Ӳ���ӿ�

	delay_ms(2000);
MYDMA_Config1(DMA1_Channel5, (u32)&USART1->DR, (u32)TEXT_TO_SEND, 2);
			USART1->CR3 = 1 << 6;		 //ʹ�ܴ���1��DMA����
			MYDMA_Enable(DMA1_Channel5); //��ʼһ��DMA���䣡
			while (1)
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				if (DMA1->ISR & (1 << 17)) //�ȴ�ͨ��4�������
				{
					DMA1->IFCR |= 1 << 17; //���ͨ��4������ɱ�־
					GPIO_ResetBits(GPIOA, GPIO_Pin_1);
					break;
				}
				delay_ms(10000);
			}
			
			delay_ms(10000);
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			delay_ms(10000);


			USART1->CR3  &=~(1<<6);       //关闭DMA传输 
				MYDMA_Enable1(DMA1_Channel5);	
												 //��ʼһ��DMA���䣡
			MYDMA_Config(DMA1_Channel4, (u32)&USART1->DR, (u32)TEXT_TO_SEND, 8); // DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,��(TEXT_LENTH+2)*100.

			USART1->CR3 = 1 << 7;		 //ʹ�ܴ���1��DMA����
			MYDMA_Enable(DMA1_Channel4); //��ʼһ��DMA���䣡
			xx++;
			while (1)
			{
				if (DMA1->ISR & (1 << 13)) //�ȴ�ͨ��4�������
				{
					DMA1->IFCR |= 1 << 13; //���ͨ��4������ɱ�־

					break;
				}
			}
			MYDMA_Enable1(DMA1_Channel4); //��ʼһ��DMA���䣡
			USART1->CR3  &=~(1<<7);       //关闭DMA传输 
	while (1)
	{
		while (1)
		{

			



			MYDMA_Config1(DMA1_Channel5, (u32)&USART1->DR, (u32)TEXT_TO_SEND1, 3);
			USART1->CR3 = 1 << 6;		 //ʹ�ܴ���1��DMA����
		
			MYDMA_Enable(DMA1_Channel5); //��ʼһ��DMA���䣡
			while (1)
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
				if (DMA1->ISR & (1 << 17)) //�ȴ�ͨ��4�������
				{
					DMA1->IFCR |= 1 << 17; //���ͨ��4������ɱ�־
					GPIO_ResetBits(GPIOA, GPIO_Pin_1);
					break;
				}
				delay_ms(100);
			}
	MYDMA_Enable1(DMA1_Channel5); //��ʼһ��DMA���䣡
			USART1->CR3  &=~(1<<6);       //关闭DMA传输  
			delay_ms(100);
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			delay_ms(100);
			
			
			
						 //��ʼһ��DMA���䣡
			MYDMA_Config(DMA1_Channel4, (u32)&USART1->DR, (u32)TEXT_TO_SEND1, 3); // DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,��(TEXT_LENTH+2)*100.
	MYDMA_Enable(DMA1_Channel4);
			USART1->CR3 = 1 << 7;		 //ʹ�ܴ���1��DMA����
			
			xx++;
			while (1)
			{
				if (DMA1->ISR & (1 << 13)) //�ȴ�ͨ��4�������
				{
					DMA1->IFCR |= 1 << 13; //���ͨ��4������ɱ�־

					break;
				}
			}
				USART1->CR3  &=~(1<<7);       //关闭DMA传输 
				MYDMA_Enable1(DMA1_Channel4);
		}
	}
}
