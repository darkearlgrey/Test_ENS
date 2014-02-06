#include <msp430.h> 

/*
 * main.c
 */
int i, second;
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P4DIR |= 0x04;	//LED3
	P4DIR |= 0x02;	//LED1

	//Setup RTC Timer
	RTCCTL01 = RTCTEVIE + RTCSSEL_2 + RTCTEV_0; // Counter Mode, RTC1PS, 8-bit ovf
	// overflow interrupt enable
	RTCPS0CTL = RT0PSDIV_2;						// ACLK, /8, start timer
	RTCPS1CTL = RT1SSEL_2 + RT1PSDIV_3;		// out from RT0PS, /16, start timer

	__bis_SR_register(LPM3_bits + GIE);

	return 0;
}
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void) {
	switch (__even_in_range(RTCIV, 16)) {
	case 0:
		break;	// No interrupts
	case 2:
		break;	// RTCRDYIFG
	case 4:

		P4OUT |= 0x02;
		for (i = 0; i < 10000; i++)
			;
		P4OUT &= ~0x02;
		for (i = 0; i < 10000; i++)
			;

		P4OUT |= 0x04;
		for (i = 0; i < 10000; i++)
			;
		P4OUT &= ~0x04;
		for (i = 0; i < 10000; i++)
			;
		break;
	case 6:
		break;                          // RTCAIFG
	case 8:
		break;                          // RT0PSIFG
	case 10:
		break;                         // RT1PSIFG
	case 12:
		break;                         // Reserved
	case 14:
		break;                         // Reserved
	case 16:
		break;                         // Reserved
	default:
		break;
	}

}

