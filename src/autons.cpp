#include "vex.h"

void default_constants()
{
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 2000);
}

void odom_constants()
{
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test()
{
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test()
{
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

void swing_test()
{
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test()
{
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test()
{
  chassis.set_coordinates(0, 0, 0);
  while (1)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0, 70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0, 90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0, 110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0, 130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24, 24);
  chassis.drive_to_point(0, 0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test()
{
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

void farSide()
{
  rear_jack.set(false);
  intake_air.set(false);
  odom_constants();
  chassis.set_coordinates(0, 0, -15);
  telemetry.broadcast();
  // Time for the fun stuff

  // Dash to the first triball
  intakeEvent.broadcast();
  chassis.drive_distance(52, -15);
  wait(200, msec);
  // chassis.drive_distance(-10);
  // wait(700, msec);
  chassis.turn_to_angle(90);
  wait(200, msec);
  // chassis.drive_distance(1);
  // wait(100, msec);
  intake_air.set(true);
  intakeMotor.spinFor(forward, -6, turns, 400, velocityUnits::rpm, false);
  wait(50, msec);

  chassis.drive_distance(17);
  wait(100, msec);
  chassis.drive_distance(-8);
  wait(100, msec);
  // chassis.turn_to_angle(-65);
  chassis.left_swing_to_angle(-45);
  intake_air.set(false);
  wait(100, msec);
  // intakeEvent.broadcast();
  chassis.drive_distance(16);
  wait(100, msec);
  chassis.turn_to_angle(90);
  wait(200, msec);
  intake_air.set(true);
  intakeMotor.spinFor(forward, -6, turns, 400, velocityUnits::rpm, false);
  chassis.drive_distance(30);
  wait(100, msec);
  chassis.drive_distance(-3);
  wait(100, msec);
  chassis.turn_to_angle(225);
  wait(200, msec);
  chassis.drive_distance(15);
  wait(100, msec);
  intake_air.set(false);
  chassis.drive_to_point(-20, 19);
  wait(100, msec);
  driveMotor.spinFor(forward, 4, turns, 600, velocityUnits::rpm, true);
  ButtonA_Callback();

  // wait(2000, msec);
  // chassis.left_swing_to_angle(-90);
  // wait(700, msec);
  // chassis.drive_distance(10);
  // wait(700, msec);
}

void oldSkills()
{
  // Goal of this Autonomus is to score as many points as possible by shooting many balls across the field then scoring them by going across the field
  rear_jack.set(false);
  intake_air.set(false);
  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, -145);
  telemetry.broadcast();
  // Time for the fun stuff
  //  wait(2000,msec);
  //  cataMotor.spinFor(forward, 15, turns, 600, velocityUnits::rpm, true);
  //  wait(200,msec);
  //  cataReset(100);
  // turn
  chassis.turn_to_angle(-90);
  wait(200, msec);
  // drive to other side of field
  chassis.drive_distance(-15, -90);
  wait(200, msec);
  chassis.turn_to_angle(-125);
  chassis.drive_distance(-85);
  intake_air.set(true);
  chassis.left_swing_to_angle(-210);
  wait(100, msec);
  right_wing.set(true);
  chassis.drive_distance(-24);
  wait(100, msec);
  chassis.drive_distance(24);
  wait(100, msec);
  chassis.turn_to_angle(-245);
  wait(100, msec);
  chassis.drive_distance(-28);
  wait(100, msec);
  chassis.right_swing_to_angle(-125);
  wait(100, msec);
  chassis.turn_to_angle(-125);
  wait(100, msec);
  chassis.drive_distance(-15);
  wait(100, msec);
  chassis.drive_distance(17);
  wait(100, msec);
  chassis.turn_to_angle(-210);
  wait(100, msec);
  chassis.drive_distance(-10);
  wait(100, msec);
  chassis.right_swing_to_angle(-125);
  wait(100, msec);
  chassis.turn_to_angle(-125);
  wait(100, msec);
  chassis.drive_distance(-15);
  wait(100, msec);
  chassis.drive_distance(17);
  wait(100, msec);

  // right swing to face goal
  //  chassis.right_swing_to_angle(-180);
  //  wait(200,msec);
  //  //deploy wings and run into goal
  //  wingValve(true);
  //  chassis.drive_distance(-20);
  //  wait(200,msec);
  //  chassis.drive_distance(20);
  //  wait(200,msec);
  //  //turn tangent to goal
  //  chassis.turn_to_angle(-235);
  //  wait(200,msec);
  //  //drive then swing around goal
  //  chassis.drive_distance(-15);
  //  wait(200,msec);
  //  chassis.left_swing_to_angle(-90);
  //  wait(200,msec);
}

void skills()
{

  // rear_jack.set(false);
  intake_air.set(false);
  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, -108);
  telemetry.broadcast();
  wait(1, timeUnits::sec);
  // cataMotor.spinFor(forward, 70, rotationUnits::rev, 600, velocityUnits::rpm, true);
  // cataMotor.spinFor(forward, 60, rotationUnits::rev, 600, velocityUnits::rpm, true);
  wait(200, timeUnits::msec);
  cataReset(100);
  rear_jack.set(false);
  wait(300, timeUnits::msec);
  chassis.drive_distance(-12, -108);
  wait(1, timeUnits::msec);
  chassis.turn_to_angle(10);
  wait(1, timeUnits::msec);
  // chassis.drive_distance(70);
  spinChassisMAX(900);
  wait(1, timeUnits::msec);
  chassis.turn_to_angle(100);
  wait(1, timeUnits::msec);
  chassis.drive_distance(65,
                        chassis.desired_heading,
                        12,
                        chassis.heading_max_voltage,
                        chassis.drive_settle_error,
                        chassis.drive_settle_time,
                        chassis.drive_timeout
                        );
  wait(1, timeUnits::msec);
  chassis.turn_to_angle(-90);
  intakeReverse(true);
  wait(1, timeUnits::msec);
  wingValve(true);
  wait(1, timeUnits::msec);
  // chassis.drive_distance(-30);
  spinChassisReverseMAX(900);
  wait(1, timeUnits::msec);
  wingValve(false);
  chassis.drive_distance(30);
  wait(1, timeUnits::msec);
  chassis.turn_to_angle(-100);
  wait(1, timeUnits::msec);
  wingValve(true);
  // chassis.drive_distance(-30);
  spinChassisReverseMAX(900);
  wait(1, timeUnits::msec);
}

void closeSide()
{
  rear_jack.set(false);
  
  rightDrive.setStopping(brake);
  leftDrive.setStopping(brake);
  rightDrive.stop();
  leftDrive.stop();
  odom_constants();
  chassis.set_coordinates(0, 0, -45);
  telemetry.broadcast();
  wait(1, timeUnits::sec);

  // Time for the fun stuff
  ButtonY_Callback();
  chassis.drive_distance(15, -45);
  wait(1, timeUnits::msec);
  ButtonY_Callback();
  chassis.right_swing_to_angle(0);
  // intake_air.set(false);
  chassis.turn_to_angle(135);
  wait(1,msec);
  chassis.drive_distance(10);
  wait(1,msec);
  chassis.turn_to_angle(90);
  wait(1,msec);
  chassis.drive_distance(40);
  wait(1,msec);



}