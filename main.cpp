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
motor leftMotor1 = motor(PORT8, ratio18_1, false);

motor leftMotor2 = motor(PORT9, ratio18_1, true);

motor leftMotor3 = motor(PORT10, ratio18_1, false);

motor rightMotor1 = motor(PORT3, ratio18_1, false);

motor rightMotor2 = motor(PORT5, ratio18_1, true);

motor rightMotor3 = motor(PORT4, ratio18_1, false);

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

#pragma region Constants
// Lateral constants
double Kp = 0.0001; // Proportion Constant
double Ki = 0.0001; // Integral Constant 
double Kd = 0.0001; // Derivative Constant

double turnKp = 0.0001; // Turn Proportion Constant
double turnKi = 0.0001; // Turn Integral Constant
double turnKd = 0.0001; // Turn Derivative Constant
#pragma endregion Constants

#pragma endregion Declarables



/*---------------------------Pre-Autonomous Functions--------------------------/
/ This is the brief changelog for the pre-auton functions.                     /
/
/ 11/13/24: wrote down the code to zero the motors.

/-----------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

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
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
