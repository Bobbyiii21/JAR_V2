#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontRight = motor(PORT17, gearSetting::ratio6_1, false);
motor MiddleRight = motor(PORT16, gearSetting::ratio6_1, false);
motor BackRight = motor(PORT15, gearSetting::ratio6_1, false);
//motor_group rightDrive = motor_group(FrontRight, MiddleRight, BackRight);
motor FrontLeft = motor(PORT18, gearSetting::ratio6_1, true);
motor MiddleLeft = motor(PORT19, gearSetting::ratio6_1, true);
motor BackLeft = motor(PORT20, gearSetting::ratio6_1, true);
//motor_group leftDrive = motor_group(FrontLeft, MiddleLeft, BackLeft);
motor cataMotor = motor(PORT14, gearSetting::ratio36_1, true);
motor intakeMotor = motor(PORT10, gearSetting::ratio18_1, true);
controller Controller1 = controller(primary);
digital_out intake_air = digital_out(Brain.ThreeWirePort.H);
digital_out rear_jack = digital_out(Brain.ThreeWirePort.G);
digital_out left_wing  = digital_out(Brain.ThreeWirePort.F);
digital_out right_wing = digital_out(Brain.ThreeWirePort.E);

// Vex Sensors
inertial Inertial = inertial(PORT12);
distance Distance = distance(PORT13);

// VEXcode generated functions
bool left_wing_toggle = false;
bool right_wing_toggle = false;
bool rear_jack_toggle  = false;
bool intake_toggle = false;

void ButtonY_Callback(){
      left_wing_toggle = !left_wing_toggle;
      left_wing.set(left_wing_toggle);
    }
void ButtonA_Callback(){
      right_wing_toggle = !right_wing_toggle;
      right_wing.set(right_wing_toggle);
    }
void ButtonB_Callback(){
      rear_jack_toggle = !rear_jack_toggle;
      rear_jack.set(rear_jack_toggle);
    }
void ButtonX_Callback(){
      intake_toggle = !intake_toggle;
      intake_air.set(intake_toggle);
    }
void ButtonUp_Callback(){
      right_wing_toggle = !right_wing_toggle;
      left_wing_toggle = right_wing_toggle;
      right_wing.set(right_wing_toggle);
      left_wing.set(left_wing_toggle);
    }

void wingValve(bool state) {
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

void intakeUntilObject()
{
	while (true)
	{
    intakeMotor.spin(directionType::fwd, 400, velocityUnits::rpm);
    if (Distance.objectDistance(distanceUnits::mm) < 100)
      intakeMotor.spin(directionType::fwd, 0, velocityUnits::rpm); break;
	}
}

vex::event intakeEvent(intakeUntilObject);

void phoneHome()
{
  while (true)
  {
      printf("X: %f    Y: %f    Theta: %f", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
      task::sleep(1000);
  }
}
vex::event telemetry(phoneHome);
 


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}