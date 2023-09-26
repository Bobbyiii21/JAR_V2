#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test(){
  chassis.turn_to_angle(5);
  vex::task::sleep(1000);
  chassis.turn_to_angle(30);
    vex::task::sleep(1000);
  chassis.turn_to_angle(90);
    vex::task::sleep(1000);
  chassis.turn_to_angle(225);
    vex::task::sleep(1000);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

void red_Right(){
  odom_constants();
  chassis.set_coordinates(0, 0, -15);
  telemetry.broadcast();
  //Time for the fun stuff

  //Dash to the first triball
  intakeEvent.broadcast();
  chassis.drive_distance(52,-15);
  wait(200, msec);
  // chassis.drive_distance(-10);
  // wait(700, msec);
  chassis.turn_to_angle(90);
  wait(200,msec);
  chassis.drive_distance(1);
  wait(100, msec);
  intake_air.set(true);
  intakeMotor.spinFor(forward, -6, turns, 400, velocityUnits::rpm, false);
  chassis.drive_distance(15);
  wait(100, msec);
  chassis.drive_distance(-8);
  wait(100, msec);
  // chassis.turn_to_angle(-65);
  chassis.left_swing_to_angle(-45);
  intake_air.set(false);
  wait(100, msec);
  //intakeEvent.broadcast();
  chassis.drive_distance(16);
  wait(100, msec);
  chassis.turn_to_angle(90);
  wait(200,msec);
  chassis.drive_distance(25);
  intake_air.set(true);
  wait(100, msec);

  
  
  // wait(2000, msec);
  // chassis.left_swing_to_angle(-90);
  // wait(700, msec);
  // chassis.drive_distance(10); 
  // wait(700, msec);

  
  
}