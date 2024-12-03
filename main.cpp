/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       27kazi-zayyaan                                            */
/*    Created:      11/13/2024, 1:54:30 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here


#pragma region deviceConfiguration
motor leftMotor1 = motor(PORT11, ratio18_1, false);

motor leftMotor2 = motor(PORT12, ratio18_1, true);

motor leftMotor3 = motor(PORT18, ratio18_1, false);

motor rightMotor1 = motor(PORT14, ratio18_1, false);

motor rightMotor2 = motor(PORT15, ratio18_1, true);

motor rightMotor3 = motor(PORT16, ratio18_1, false);


motor_group leftside = motor_group(leftMotor1, leftMotor2, leftMotor3);

motor_group rightside = motor_group(rightMotor1, rightMotor2, rightMotor3);

controller Controller1 = controller(primary);
#pragma endregion deviceConfiguration



#pragma region Declarables


/*-----------Declarables Changelog-----------/
11/14/24
Started on basic declarables those being constants for both lateral movement and turning.
Also declared the events that will be used in the code


/-------------------------------------------*/


double TV = 5000.0/(3.14159 * 104.775) * 360; // Targeted Value


// Lateral constants
double Kp = 0.0101; // Proportion Constant
double Ki = 0.0001; // Integral Constant 
double Kd = 0.0001; // Derivative Constant

// Turning constants
double turnKp = 0.0001; // Turn Proportion Constant
double turnKi = 0.0001; // Turn Integral Constant
double turnKd = 0.0001; // Turn Derivative Constant

// Variables
double leftError = .1; //error is the distance left from the current position to the TV
double leftIntegral = 0.0;
double leftDerivative = 0.0;
double leftPrev_error = 0.0;


double rightError = .1;
double rightIntegral = 0.0;
double rightDerivative = 0.0;
double rightPrev_error = 0.0;


double leftlateralMotorPower = 0.0;
double rightlateralMotorPower = 0.0;

double AVGLMP = 0.0;
double AVGRMP = 0.0;
//Event Declaration.
event PidLoop = event(); // Multithreaded event that updates the variables for PID
event PidReset = event(); // Event called after every instruction that waits for the instruction to end before resetting all the variables


#pragma endregion Declarables



/*---------------------------Pre-Autonomous Functions--------------------------/
/ This is the brief changelog for the pre-auton functions.                     /
/
/ 11/13/24: wrote down the code to zero the motors.

/-----------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  rightside.setPosition(0, degrees);
  leftside.setPosition(0, degrees); 

}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  while (true){
    PidLoop.broadcast();
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    //printf(printToConsole_numberFormat(), static_cast<double>(turnError));
    Controller1.Screen.print(" ");
    Controller1.Screen.print(leftError);
  }

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//


void leftsideCalc(){
  AVGLMP = leftside.position(degrees);
  (TV != 0.0) ? leftError = TV - AVGLMP : leftError = 0.0;
  leftIntegral += leftError; // Updates the integral value
  leftPrev_error = leftError; // Updates the Previous error value
}



void rightsideCalc(){
  AVGRMP = rightside.position(degrees);
  (TV != 0.0 ) ? rightError = TV - AVGLMP : rightError = 0.0;

  rightIntegral += rightError;
  rightPrev_error = rightError; 
}

void finalCalc(){
  rightlateralMotorPower = ((Kp*rightError + Ki*rightIntegral + Kd * (rightError - rightPrev_error)));// Z@
  leftlateralMotorPower = ((Kp*leftError + Ki*leftIntegral + (Kd * (leftError - leftPrev_error))));// Z@
  leftside.spin(forward, leftlateralMotorPower, voltageUnits::volt);
  rightside.spin(reverse, rightlateralMotorPower, voltageUnits::volt);
  PidLoop.broadcast();
}
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  PidLoop(leftsideCalc);
  PidLoop(rightsideCalc);
  PidLoop(finalCalc);
  //



  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
