#include "main.h"
#include "config.hpp"
#include "gui.h"


 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightfront (16, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightback  (17, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawleft   (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawright  (9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor lift       (10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor stacker    (20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::delay(100);
  gui();
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

  redblue side=red;
  frontback isfront=front;

  // 1 red big
  // 2 blue big
  // 3 red small
  // 4 blue small
  // 5 skills 1
  // 6 none

  switch(auton_sel) // assign value to side and isfront based on the auto selection button pressed
  {
    case 1:
    {
      leftfront.move_velocity(100);      //front
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(2000);

      leftfront.move_velocity(-100);     //back
      leftback.move_velocity(-100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(1200);

      leftfront.move_velocity(0);      //stop
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(1500);
      break;
    }
    case 2:
    {
      leftfront.move_velocity(100);      //forwards
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(2000);

      leftfront.move_velocity(-100);     //backwards
      leftback.move_velocity(-100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(1200);

      leftfront.move_velocity(0);      //stop
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(1500);
      break;
    }
    case 3:
    {
      lift.move_velocity(100);           //lift up
      pros::delay(1000);

      lift.move_velocity(-100);          //lift down
      pros::delay(1000);

      clawleft.move_velocity(100);       //intake cubes
      clawright.move_velocity(100);
      pros::delay(5000);

      leftfront.move_velocity(100);      //move forwards
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(3000);

      leftfront.move_velocity(-100);     //backwards
      leftback.move_velocity(-100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(2000);

      leftfront.move_velocity(100);     //turn 145 right
      leftback.move_velocity(100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(750);

      leftfront.move_velocity(100);      //move forwards
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(1000);

      leftfront.move_velocity(0);     //stop moving
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(100);

      clawleft.move_velocity(-50);     //intake out
      clawright.move_velocity(-50);
      pros::delay(300);

      clawleft.move_velocity(0);      //intake stop
      clawright.move_velocity(0);
      pros::delay(50);

      stacker.move_velocity(100);     //stacker out
      pros::delay(1000);

      stacker.move_velocity(-100);    //stacker in
      pros::delay(1000);

      stacker.move_velocity(0);      //stacker stop
      pros::delay(50);

      leftfront.move_velocity(-100);     //move backwards
      leftback.move_velocity(-100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(500);

      leftfront.move_velocity(0);     //stop moving
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(50);
      break;
    }
    case 4:
    {
      leftfront.move_velocity(100);     //move forwards
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(4000);

      clawleft.move_velocity(100);      //intake cubes
      clawright.move_velocity(100);
      pros::delay(5000);

      leftfront.move_velocity(-100);      //turn 90 left
      leftback.move_velocity(-100);
      rightfront.move_velocity(100);
      rightback.move_velocity(100);
      pros::delay(750);

      leftfront.move_velocity(-100);      //stride left
      leftback.move_velocity(100);
      rightfront.move_velocity(100);
      rightback.move_velocity(-100);
      pros::delay(4000);

      leftfront.move_velocity(0);     //stop moving
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(100);

      clawleft.move_velocity(-50);      //intake out
      clawright.move_velocity(-50);
      pros::delay(500);

      clawleft.move_velocity(0);      //intake stop
      clawright.move_velocity(0);
      pros::delay(100);

      stacker.move_velocity(100);     //stacker out
      pros::delay(1000);

      stacker.move_velocity(-100);      //stacker in
      pros::delay(1000);

      stacker.move_velocity(0);     //stacker stop
      pros::delay(100);

      leftfront.move_velocity(-100);      //move backwards
      leftback.move_velocity(-100);
      rightfront.move_velocity(-100);
      rightback.move_velocity(-100);
      pros::delay(1000);

      leftfront.move_velocity(0);     //stop moving
      leftback.move_velocity(0);
      rightfront.move_velocity(0);
      rightback.move_velocity(0);
      pros::delay(100);
      break;
    }
    case 5:
    {
      break;
    }
    case 6:
    {
      break;
    }
    default:
    {
      break;
    }
  }}
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

   char mytext[64];       /*Create a screen*/
lv_obj_t * scr = lv_obj_create(NULL, NULL);
lv_scr_load(scr);                                  /*Load the screen*/
   lv_obj_clean(lv_scr_act());  // clean screen
  lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(title, "Debug");
  lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);  /*Align to the top*/

  /*Create a new label*/
  lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
  //lv_obj_set_style(txt, &style_txt);                    /*Set the created style*/
  lv_label_set_long_mode(txt, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
  lv_label_set_recolor(txt, true);                      /*Enable re-coloring by commands in the text*/
  lv_label_set_align(txt, LV_LABEL_ALIGN_LEFT);       /*Center aligned lines*/
  lv_label_set_text(txt, NULL);
  lv_obj_set_width(txt, 500);                           /*Set a width*/
  lv_obj_align(txt, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);      /*Align to center*/

	while (true) {
                                        // assign value to mytext
sprintf(mytext,
  "leftfront:  %8.2f\n"
  "rightfront: %8.2f\n"
  "stacker:    %d\n"
  "arm:        %8.2f",
     leftfront.get_position(),
     rightfront.get_position(),
     stacker.get_position(),
     lift.get_position()
   );                               // print to screen
lv_label_set_text(txt, mytext);

		leftfront.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
  	leftback.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
		rightfront.set_brake_mode (pros::E_MOTOR_BRAKE_HOLD);
		rightback.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
		clawright.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
		clawleft.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
		lift.set_brake_mode       (pros::E_MOTOR_BRAKE_HOLD);
		stacker.set_brake_mode    (pros::E_MOTOR_BRAKE_HOLD);

int forwardback = master.get_analog (ANALOG_LEFT_Y);
int stride      = master.get_analog (ANALOG_LEFT_X);
int turn        = master.get_analog (ANALOG_RIGHT_X);

		// chasis
	leftfront.move  (forwardback + turn + stride);
	leftback.move   (forwardback + turn - stride);
  rightfront.move (forwardback - turn - stride);
  rightback.move  (forwardback - turn + stride);


		//lift

  if(master.get_digital(DIGITAL_Y))
    {
      lift.move_absolute(430.20, 100);
    }
    else if(master.get_digital(DIGITAL_B))
      {
        lift.move_absolute(617.20, 100);
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
		if(master.get_digital(DIGITAL_R2))
		{
				stacker.move_velocity (100);
		}
		else if(master.get_digital(DIGITAL_R1))
		{
				stacker.move_velocity (-125);
		}
		else
		{
			stacker.move_velocity (0);
		}

		pros::delay(20);
	}
}
