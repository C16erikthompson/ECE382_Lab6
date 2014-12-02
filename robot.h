/*
 * robot.h
 *
 *  Created on: Nov 23, 2014
 *      Author: C16Erik.Thompson
 */



typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0



//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//	Bit = 0: The PxIFGx flag is set with a low-to-high transition
//	Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6


#define		averageLogic0Pulse	590
#define		averageLogic1Pulse	1626
#define		averageStartPulse	4411

#define		marginOfError		150
#define 	packetLength		33
#define		otherData			0xFF

#define		minLogic0Pulse		averageLogic0Pulse - marginOfError
#define		maxLogic0Pulse		averageLogic0Pulse + marginOfError
#define		minLogic1Pulse		averageLogic1Pulse - marginOfError
#define		maxLogic1Pulse		averageLogic1Pulse + marginOfError
#define		minStartPulse		averageStartPulse - marginOfError
#define		maxStartPulse		averageStartPulse + marginOfError




//all of the buttons specific to remote #3.
#define		PWR		0x20DF10EF
#define		ONE		0x20DF8877
#define		TWO		0x20DF48B7
#define		THR		0x20DFC837
#define		ZER		0x20DF08F7

#define		VOL_UP	0x20DF40BF
#define		VOL_DW	0x20DFC03F
#define		CH_UP	0x20DF00FF
#define		CH_DW	0x20DF807F


#define TIME 1000000
#define TIME2 (TIME*0.5)

#ifndef ROBOT_H_
#define ROBOT_H_



#endif /* ROBOT_H_ */
