/*
 * robot.c
 *
 *  Created on: Nov 23, 2014
 *      Author: C16Erik.Thompson
 */

#include <msp430.h>
#include "robot.h"

//----------------------------------------------------
// Movement Functions
//----------------------------------------------------

/*
 * Move forward
 */
void moveForward(){
	leftForward();
	rightForward();
}


/*
 * Move Backward
 */
void moveBackward(){
	leftReverse();
	rightReverse();
}

/*
 * Rotate Robot Right
 */
void rotateRight(){
    leftForward();
    rightReverse();
    __delay_cycles(TIME2);
}


/*
 * Rotate Robot Left.
 */
void rotateLeft(){
	rightForward();
	leftReverse();
    __delay_cycles(TIME2);
}

/*
 * Stops the robot, whatever direction it is moving.
 */
void stop(){
	rightStop();
	leftStop();
}
//==================================================
// Wheel Control
//==================================================



/*
 * Stops the right wheen until further notice.
 */
void rightStop(){
    //forward
	P2DIR &= ~BIT4;
    P2SEL &= ~BIT4;
    //backward
	P2DIR &= ~BIT5;
	P2SEL &= ~BIT5;
}



/*
 * Stops the left wheel until further notice.
 */
void leftStop(){
    //forward
	P2DIR &= ~BIT2;
    P2SEL &= ~BIT2;
    //backward
    P2DIR &= ~BIT1;
    P2SEL &= ~BIT1;
}


/*
 * Starts the right wheel until further notice.
 */
void rightForward(){
    P2DIR |= BIT4;
    P2SEL |= BIT4;
}


/*
 * Starts the left wheel until further notice.
 */
void leftForward(){
    P2DIR |= BIT2;
    P2SEL |= BIT2;
}

/*
 * Makes the left wheel turn backwards.
 */
void leftReverse(){
	P2DIR |=BIT1;
	P2SEL |=BIT1;
}

/*
 * Makes the right wheel turn backwards.
 */
void rightReverse(){
	P2DIR |=BIT5;
	P2SEL |=BIT5;
}
