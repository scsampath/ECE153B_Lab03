/*
 * ECE 153B - Winter 2022
 *
 * Name(s):
 * Section:
 * Lab: 3A
 */

#include "stm32l476xx.h"
 
void PWM_Init() {
	// Enable GPIO Port A Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	// Enable TIM2 Clock
	RCC->APB1ENR1 |= 1UL<<0;
	
	// Configure PA5
		// Set the mode of PA5 to Alternative Function(10)
  GPIOA->MODER &= ~(3UL<<10); //clear mode bits
	GPIOA->MODER |= 2UL<<10; // Set mode to Alternative Function(10)
	
		// Set PA5 to Very High Output Speed(11)
	GPIOA->OSPEEDR &= ~(3UL<<10); //clear mode bits
	GPIOA->OSPEEDR |= 3UL<<10; //Set mode to Very High(11)
	
		// Set PA5 to No Pull-Up, No Pull-Down (00,reset)
	GPIOA->PUPDR &= ~(3UL<<10); //clear mode bits
	
		// Configure and Select Alternative Function for PA5
	GPIOA->AFR[0] &= ~(15UL<<20); //clear mode bits
		// AFSEL5 for pin 5, AF1 for PA5 TIM2_CH1
	GPIOA->AFR[0] |= 1UL<<20; //AF1 = 0001
	
	
	
	// Configure PWM Output for TIM2 CH 1
	TIM2->CR1 |= 0UL<<4; //DIR = 0 for upcounter
	
	TIM2->PSC |= 100UL; //Set the prescaler value
	
	TIM2->ARR |= 10UL; //Set the auto-reload value
	
	TIM2->CCMR1 &= ~(7UL<<4); //Clear output compare mode bits
	TIM2->CCMR1 |= 6UL<<4; //Set output compare mode bits to PWM mode 1 (0110)
	TIM2->CCMR1 |= 1UL<<3; //Output compare preload enable
	
	TIM2->CCER |= 0UL<<1;//Set the output polarity for compare 1 to active high (0)
	TIM2->CCER |= 1UL<<0;//Enable the channel 1 output
	
	TIM2->CCR1 |= 5UL; //Set the capture/compare value.
	
	TIM2->CR1 |= 1<<4; //CEN = 1 for Counter Enable
}
 
int main() {
	// Initialization - We will use the default 4 MHz clock
	PWM_Init();
	
	// Periodic Dimming
	int i;

	while(1) {
		for(i=0; i<1000; ++i); // Some Delay
	}
	
	return 0;
}
