ECE382_Lab6
===========
#Prelab
See PreLab.doc
##Prelab Hardware Schematic
![alt tag](http://i47.photobucket.com/albums/f189/erik_thompson2/prelabschem_zps27bcf71a.jpg "TO-220 Config")

##Prelab Software Schematic
![alt tag](http://i47.photobucket.com/albums/f189/erik_thompson2/flowchart_zps4aa85f45.png "TO-220 Config")

# Required Functionality
  When I began to buil my robot for required functionality, I found that my prelab ideas were made without a complete unnderstading of how this assignment should be completed.  That being so, I scrapped by prelab hardware schematic in favor of emulating the schematic made by Dr.Coulston:
  ![alt tag](http://i47.photobucket.com/albums/f189/erik_thompson2/IMG_20141123_152548_212_zps3b576bb6.jpg "TO-220 Config").
Following this general idea, I was able to create a robot that would function correctly, demoing wheel movement with the example code provided online.

~~~
#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

    P1DIR &= ~BIT3;
    P1REN |= BIT3;

    P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
    P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

    P2DIR |= BIT4;							// P2.2 is associated with TA1CCR2
    P2SEL |= BIT4;							// P2.2 is associated with TA1CCTL2

	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
    TA1CCR0 = 0x0100;						// set signal period

    TA1CCR1 = 0x0020;
    TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

    TA1CCR2 = 0x0020;
    TA1CCTL2 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

    while (1) {

    	while((P1IN & BIT3) != 0);			// Wait for a button press
    	while((P1IN & BIT3) == 0);			// and release

        TA1CCR1 = (TA1CCR1 + 0x010) & 0xFF;	// increase duty cycle
        TA1CCR2 = (TA1CCR2 + 0x010) & 0xFF;	// decrease duty cycle

    } // end loop
} // end main
~~~

After I was certain that the hardware worked correctly, it appeared as follows (sans the IR Sensor):
  
  ![alt tag](http://i47.photobucket.com/albums/f189/erik_thompson2/IMG_20141202_072012_378_zpsea6a47e7.jpg
 "TO-220 Config").

I then began to implement my own software to accomplish the given task.  I ended up using a modular design exactly like that defined in my prelab, creating code to control forward and backward movement for each wheel then calling on this code for the tasks of moving forward and backward and rotating left and right.  The code appeared as follows:

~~~
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
~~~

To make sure that each of these fuctions worked, I made short list of commands that consisted of calling a "method," pausing, calling another one, etc.  Once each command was working well, I moved on to A Funcitonality.

#A Funcitonality
Implementing A Functinality took little effort.  For the hardware, all that needed to be done was include the IR sensor on the board, ensuring that it was grounded, recieved voltage from the regulator, and passed its information to XIN on the MSP430 just as in the previous lab.  Implementing it in the software just required that I copy and paste the code that intepreted packets from lab 5 into the main program of this lab, defined the buttons in the header file, and encapsulated each of the movement commands withing an if-else statement connected to a button press.  The code in the main appeared as follows:
~~~
while(1)  {

		//If there is a new packet detected, perform function, otherwise moveforward.
		if(newIRPacket){

			_disable_interrupt();

			if(packet == TWO){
				moveForward();
			}else if(packet == ZER){
				moveBackward();
			}else if(packet == THR ){
				rotateRight();
			}else if(packet == ONE){
				rotateLeft();
			}else if(packet == PWR){
				stop();

			}else{
				moveForward();
			}

			_enable_interrupt();

			initMSP430();
			newIRPacket= FALSE;
		}
	~~~
	After testing to ensure consistent performace of the button presses, I had completed the lab.  A video of A functionality appears below
	
#A Functionality Link
[URL=http://i47.photobucket.com/albums/f189/erik_thompson2/VID_20141123_231005_657_zpseqkpmksr.mp4][IMG]http://i47.photobucket.com/albums/f189/erik_thompson2/th_VID_20141123_231005_657_zpseqkpmksr.mp4[/IMG][/URL]

#Debugging
There was an extensive debugging process with my specific robot.  One issue I ran into was inconnsistency with the voltage rails, as sometimes the MSP would be supplied power while other times it would not.  To get a working program faster, I built my schematic and tested it upon C2C Jacob Lawson robot before transferring the design over to my own.  I've found that, after returning from break, I am still having issues with my robot and power, a problem which will have to be addressed before the next lab.  Another issue I ran into was shorting out the connection to the wheel through bad hardware connections, which was really just poor construction on my part.  Another wheel issue I encountered was the wheels turning too slowly or at different rates.  This was addressed by altering the duty cycle lengths until a satisfactory result was gained.  I also burned out one of the voltage regulators after plugging it into the 12V rail (though the tech doc says it should be able to withstand voltages in this range).  Smaller grievances include parts heating up, noise interfering with precision of control, and accidentally breakingn pins on the MSP430 when trying to operate it from the breadboard (eventually abandoned this idea and just worked with it while still plugged into its board).

#Documentation
-C2C Lawson allowed me to use his robot when mine was malfunctioning
-C2C Bollinger pointed me to the example code online and Dr.Coulston's schematic for one of the wheels
-Discussed various frustrations with C2C Terragnoli (not sure exactly what he helped me with, but we talked about the project often and it gave peace of mind)

