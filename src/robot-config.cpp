#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor FrontRight = motor(PORT17, gearSetting::ratio6_1, false);
motor MiddleRight = motor(PORT16, gearSetting::ratio6_1, false);
motor BackRight = motor(PORT15, gearSetting::ratio6_1, false);
motor_group rightDrive = motor_group(FrontRight, MiddleRight, BackRight);
motor FrontLeft = motor(PORT18, gearSetting::ratio6_1, true);
motor MiddleLeft = motor(PORT19, gearSetting::ratio6_1, true);
motor BackLeft = motor(PORT20, gearSetting::ratio6_1, true);
motor_group leftDrive = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor cataMotor = motor(PORT14, gearSetting::ratio36_1, true);
motor intakeMotor = motor(PORT10, gearSetting::ratio18_1, false);
controller Controller1 = controller(primary);
digital_out intake_air = digital_out(Brain.ThreeWirePort.H);
digital_out rear_jack = digital_out(Brain.ThreeWirePort.D);
digital_out left_wing = digital_out(Brain.ThreeWirePort.F);
digital_out right_wing = digital_out(Brain.ThreeWirePort.E);
motor_group driveMotor(FrontLeft, MiddleLeft, BackLeft, FrontRight, MiddleRight, BackRight);

// Vex Sensors
inertial Inertial = inertial(PORT12);
distance Distance = distance(PORT13);
distance intakeDistance = distance(PORT9);

// VEXcode generated functions
bool left_wing_toggle = false;
bool right_wing_toggle = false;
bool rear_jack_toggle = false;
bool intake_toggle = false;

void ButtonY_Callback()
{
  left_wing_toggle = !(left_wing_toggle);
  left_wing.set(left_wing_toggle);
  printf("activated callback \n left wing toggle: %d \n", left_wing_toggle);
}
void ButtonA_Callback()
{
  right_wing_toggle = !(right_wing_toggle);
  right_wing.set(right_wing_toggle);
  printf("activated callback \n right wing toggle: %d \n", right_wing_toggle);
}
void ButtonB_Callback()
{
  rear_jack_toggle = !(rear_jack_toggle);
  rear_jack.set(rear_jack_toggle);
  printf("activated callback \n rear jack toggle: %d \n", rear_jack_toggle);
}
void ButtonX_Callback()
{
  intake_toggle = !(intake_toggle);
  intake_air.set(intake_toggle);
  printf("activated callback \n intake toggle: %d \n", intake_toggle);
}
void ButtonUp_Callback()
{
  right_wing_toggle = !(right_wing_toggle);
  left_wing_toggle = right_wing_toggle;
  right_wing.set(right_wing_toggle);
  left_wing.set(left_wing_toggle);
  printf("activated callback \n right wing toggle: %d \n left wing toggle: %d \n", right_wing_toggle, left_wing_toggle);
}

void wingValve(bool state)
{
  left_wing.set(state);
  right_wing.set(state);
}

// motor functions
void intake(bool state)
{
  if (state == true)
  {
    intakeMotor.spin(directionType::fwd, 400, velocityUnits::rpm);
  }
  else
  {
    intakeMotor.spin(directionType::fwd, 0, velocityUnits::rpm);
  }
}

void intakeReverse(bool state)
{
  if (state == true)
  {
    intakeMotor.spin(directionType::rev, 400, velocityUnits::rpm);
  }
  else
  {
    intakeMotor.spin(directionType::fwd, 0, velocityUnits::rpm);
  }
}

void intakeUntilObject()
{
  while (true)
  {
    intakeMotor.spin(directionType::fwd, 400, velocityUnits::rpm);
    if (intakeDistance.objectDistance(distanceUnits::mm) < 100)
    {
      intakeMotor.spin(directionType::fwd, 0, velocityUnits::rpm);
      task::sleep(5000);
    }
    task::sleep(20);
  }
}

event intakeEvent = event(intakeUntilObject);

void phoneHome()
{
  while (true)
  {
    printf("X: %f    Y: %f   Theta: %f\n", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
    task::sleep(1000);
  }
}
vex::event telemetry(phoneHome);

void cataReset(int target_dist)
{
  double Kp = .83;
  double Kd = 0.;
  double derivative;
  double prevError = 0;

  while (true)
  {

    double error = target_dist - Distance.objectDistance(distanceUnits::mm);
    if (fabs(error) < 10)
    {
      cataMotor.spin(directionType::rev, 0, velocityUnits::rpm);
      break;
    }

    derivative = error - prevError;

    double speed = (error * Kp) + (derivative * Kd);

    cataMotor.spin(directionType::rev, speed, velocityUnits::rpm);

    prevError = error;
    printf("error: %f \n", error);
    printf("distance: %f \n", Distance.objectDistance(distanceUnits::mm));
  }
}

void spinChassisMAX(int time)
{
  rightDrive.spin(directionType::fwd, 12, voltageUnits::volt);
  leftDrive.spin(directionType::fwd, 12, voltageUnits::volt);
  wait(time, timeUnits::msec);
  rightDrive.stop();
  leftDrive.stop();
}

void spinChassisReverseMAX(int time)
{
  rightDrive.spin(directionType::rev, 12, voltageUnits::volt);
  leftDrive.spin(directionType::rev, 12, voltageUnits::volt);
  wait(time, timeUnits::msec);
  rightDrive.stop();
  leftDrive.stop();
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}