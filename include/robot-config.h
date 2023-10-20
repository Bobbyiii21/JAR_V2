using namespace vex;

extern brain Brain;



// VEXcode devices
extern motor FrontRight;
extern motor MiddleRight;
extern motor BackRight;
extern motor_group rightDrive;
extern motor FrontLeft;
extern motor MiddleLeft;
extern motor BackLeft;
extern motor_group leftDrive;
extern motor cataMotor;
extern motor intakeMotor;
extern controller Controller1;
extern digital_out intake_air;
extern digital_out rear_jack;
extern digital_out left_wing;
extern digital_out right_wing;
extern inertial Inertial;
extern distance Distance;
extern distance intakeDistance;
extern motor_group driveMotor;

extern bool left_wing_toggle;
extern bool right_wing_toggle;
extern bool rear_jack_toggle;
extern bool intake_toggle;

extern void ButtonY_Callback();
extern void ButtonA_Callback();
extern void ButtonB_Callback();
extern void ButtonX_Callback();
extern void ButtonUp_Callback();
extern void wingValve(bool state);
extern void intake(bool state);
extern void intakeReverse(bool state);
extern void intakeUntilObject();
extern void cataReset(int target_dist);
extern void spinChassisMAX(int time);
extern void spinChassisReverseMAX(int time);


extern vex::event intakeEvent;
extern vex::event telemetry;



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );