#include "main.h"
#include "config.hpp"
#include "gui.h"
#include "MiniPID.h"

 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightfront (16, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightback  (17, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawleft   (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawright  (9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor lift   	(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor stacker	(20, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::ADIPotentiometer ADIstacker (1);

 void basePID(double target, double speedmax) {
   MiniPID pid=MiniPID(0.35,0.002,0.1);

   pid.setOutputLimits(-speedmax,speedmax);
   pid.setOutputRampRate(5);
   double start=leftfront.get_position();
   double ticks = (target*360)/(4*M_PI)+start;
   while (fabs(leftfront.get_position()-ticks)>10) {
 	double output=pid.getOutput(leftfront.get_position(),
     	ticks);
 	leftback.move(output);
 	leftfront.move(output);
 	rightback.move(output);
 	rightfront.move(output);
  pros::delay(20);
  if (leftfront.get_actual_velocity()==0 && rightfront.get_actual_velocity()==0)
  break;
   }
}

void liftPID(double target) {
  MiniPID pid=MiniPID(0.3,0,0.1);

  pid.setOutputLimits(-80,80);
  pid.setOutputRampRate(5);
  double start=lift.get_position();
  double ticks = (target)+start;
  while (fabs(lift.get_position()-ticks)>10) {
	double output=pid.getOutput(lift.get_position(),
    	ticks);
	lift.move(output);
  }
}

void stackerP(double target) {
	double start=lift.get_position();
	double ticks = (target)+start;
	while (fabs(lift.get_position()-ticks)>10) {
	double error=ticks-stacker.get_position();
  	lift.move(error*0.3);
	}
}

void Tdisplay (void*) {
  char displaytext[100];
  while (1) {
    sprintf(displaytext,
            "tray: %8.2f,\n"
            "leftfront:%8.2f @: %5.1f rightfront:%8.2f @: %5.1f\n",
            lift.get_position(),
            leftfront.get_position(), leftfront.get_actual_velocity(), rightfront.get_position(),  rightfront.get_actual_velocity()
    );
    lv_label_set_text(label, displaytext);
    pros::delay(100);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::delay(100);
 lv_ex_tabview_1();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // 1 red big
  // 2 blue big
  // 3 red small
  // 4 blue small
  // 5 skills 1
  // 6 none
  lv_tabview_set_tab_act(tabview, 1, LV_ANIM_NONE);
  pros::Task T_display(Tdisplay);

  switch(auton_sel) // assign value to side and isfront based on the auto selection button pressed
  {
	case 1:
	{
  	leftfront.move_velocity(100);  	//front
  	leftback.move_velocity(100);
  	rightfront.move_velocity(100);
  	rightback.move_velocity(100);
  	pros::delay(2000);

  	leftfront.move_velocity(-100); 	//back
  	leftback.move_velocity(-100);
  	rightfront.move_velocity(-100);
  	rightback.move_velocity(-100);
  	pros::delay(1200);

  	leftfront.move_velocity(0);  	//stop
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(1500);
  	break;
	}
	case 2:
	{
  	leftfront.move_velocity(100);  	//forwards
  	leftback.move_velocity(100);
  	rightfront.move_velocity(100);
  	rightback.move_velocity(100);
  	pros::delay(2000);

  	leftfront.move_velocity(-100); 	//backwards
  	leftback.move_velocity(-100);
  	rightfront.move_velocity(-100);
  	rightback.move_velocity(-100);
  	pros::delay(1200);

  	leftfront.move_velocity(0);  	//stop
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(1500);
  	break;
	}
	case 3:
	{
    lift.move_velocity(100);       	//lift up
  	pros::delay(750);

  	lift.move_velocity(-100);      	//lift down
    clawleft.move_velocity(-100);   	//intake cubes
    clawright.move_velocity(-100);
    pros::delay(750);

  	lift.move_velocity(0);      	//lift stop
  	pros::delay(10);

  	clawleft.move_velocity(100);   	//intake cubes
  	clawright.move_velocity(100);
  	basePID(46,50);                   	//move forwards
  	pros::delay(1500);

  	clawleft.move_velocity(0);   	//stop intake
  	clawright.move_velocity(0);
  	pros::delay(20);

  	basePID(-30,75);                  	//backwards

    leftfront.move_relative(613.60, 50);  	//turn 145 left
  	leftback.move_relative(537.20, 50);
  	rightfront.move_relative(-626.00, 50);
  	rightback.move_relative(-582.00, 50);
  	pros::delay(1400);

  	basePID(16,50);                	//move forwards

  	leftfront.move_velocity(0); 	//stop moving
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(10);

  	clawleft.move_velocity(-75); 	//intake out
  	clawright.move_velocity(-75);
  	pros::delay(250);

  	clawleft.move_velocity(0);  	//intake stop
  	clawright.move_velocity(0);
  	pros::delay(10);

  	stacker.move_relative(-1850,50); 	//stacker out
  	pros::delay(2000);

  	stacker.move_velocity(0);  	//stacker stop
  	pros::delay(10);

    basePID(5,75);

  	basePID(-10,75);                	//move backwards

  	leftfront.move_velocity(0);	//stop moving
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(25);

  	stacker.move_relative(861.00, 75);   //stacker in
  	pros::delay(1000);

  	stacker.move_velocity(0);  	//stacker stop
  	pros::delay(10);

  	break;
	}
	case 4:
	{
    lift.move_velocity(100);       	//lift up
  	pros::delay(750);

  	lift.move_velocity(-100);      	//lift down
    clawleft.move_velocity(-100);   	//intake cubes
    clawright.move_velocity(-100);
  	pros::delay(750);

  	lift.move_velocity(0);      	//lift stop
  	pros::delay(20);

  	clawleft.move_velocity(100);   	//intake cubes
  	clawright.move_velocity(100);
  	basePID(46,50);                   	//move forwards
  	pros::delay(1400);

  	clawleft.move_velocity(0);   	//stop intake
  	clawright.move_velocity(0);
  	pros::delay(10);

  	basePID(-34,75);                  	//backwards

  	leftfront.move_relative(-604.50, 50);  	//turn 145 left
  	leftback.move_relative(-663.70, 50);
  	rightfront.move_relative(688.10, 50);
  	rightback.move_relative(580.90, 50);
  	pros::delay(2000);

  	basePID(15,75);                	//move forwards

  	leftfront.move_velocity(0); 	//stop moving
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(10);

  	clawleft.move_velocity(-75); 	//intake out
  	clawright.move_velocity(-75);
  	pros::delay(250);

  	clawleft.move_velocity(0);  	//intake stop
  	clawright.move_velocity(0);
  	pros::delay(10);

  	stacker.move_relative(-861,75); 	//stacker out
  	pros::delay(3000);

  	stacker.move_velocity(0);  	//stacker stop
  	pros::delay(10);

    basePID(3,50);

  	basePID(-10,75);                	//move backwards

  	leftfront.move_velocity(0);	//stop moving
  	leftback.move_velocity(0);
  	rightfront.move_velocity(0);
  	rightback.move_velocity(0);
  	pros::delay(10);

  	stacker.move_relative(861.00, 75);   //stacker in
  	pros::delay(1000);

  	stacker.move_velocity(0);  	//stacker stop
  	pros::delay(10);
  	break;
	}
	case 5:
	{
  	break;
	}
	case 6:
	{

    basePID(46,50);

    basePID(-30,75);

    leftfront.move_relative(613.60, 50);  	//turn 145 left
  	leftback.move_relative(537.20, 50);
  	rightfront.move_relative(-626.00, 50);
  	rightback.move_relative(-582.00, 50);
  	pros::delay(1400);
  	break;
	}
	default:
	{
  	break;
	}
  }
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void opcontrol() {

   leftfront.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
   leftback.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
   rightfront.set_brake_mode (pros::E_MOTOR_BRAKE_HOLD);
   rightback.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
   clawright.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
   clawleft.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
   lift.set_brake_mode   	(pros::E_MOTOR_BRAKE_HOLD);
   stacker.set_brake_mode	(pros::E_MOTOR_BRAKE_HOLD);
   lv_tabview_set_tab_act(tabview, 2, LV_ANIM_NONE);
   char mytext[64];

   while (true) {
                                    	// assign value to mytext
    sprintf(mytext,
    "leftfront:  %8.2f\n"
    "leftback:  %8.2f\n"
    "rightfront: %8.2f\n"
    "rightback:  %8.2f\n"
    "stacker:	%8.2f\n"
    "ADIstacker:	%d\n"
    "arm:    	%8.2f",
   	leftfront.get_position(),
   	leftback.get_position(),
   	rightfront.get_position(),
   	rightback.get_position(),
   	stacker.get_position(),
    ADIstacker.get_value(),
   	lift.get_position()
     );                           	// print to screen
     lv_label_set_text(txt, mytext);

  int forwardback = master.get_analog (ANALOG_LEFT_Y);
  int stride  	= master.get_analog (ANALOG_LEFT_X);
  int turn    	= master.get_analog (ANALOG_RIGHT_X);

  // chasis
  leftfront.move  (forwardback + turn + stride);
  leftback.move   (forwardback + turn - stride);
  rightfront.move (forwardback - turn - stride);
  rightback.move  (forwardback - turn + stride);


  //lift

  if(master.get_digital(DIGITAL_Y))
	{
  	lift.move_absolute(450.00, 100);
	}
	else if(master.get_digital(DIGITAL_B))
  	{
    	lift.move_absolute(679.20, 100);
  	}
  else if(master.get_digital(DIGITAL_L1))
  {
    lift.move_velocity (100);
  }
  else if(master.get_digital(DIGITAL_L2))
  {
    lift.move_velocity (-100);
  }
  else
  {
   lift.move_velocity (0);
  }

  //clawintake
  if(master.get_digital(DIGITAL_X))
  {
    clawleft.move_velocity (150);
    clawright.move_velocity (150);
  }
  else if(master.get_digital(DIGITAL_A))
  {
    clawleft.move_velocity (-150);
    clawright.move_velocity (-150);
  }
  else
  {
   clawleft.move_velocity (0);
   clawright.move_velocity (0);
  }

  //stacker
  if(master.get_digital(DIGITAL_R2) && ADIstacker.get_value()>10)
  {
    stacker.move_velocity (75);
  }
  else if(master.get_digital(DIGITAL_R1) && ADIstacker.get_value()<2100)
  {
    stacker.move_velocity (-25);
  }
  else
  {
   stacker.move_velocity (0);
  }

  pros::delay(20);
 }
}
