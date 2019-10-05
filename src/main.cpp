#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

 pros::Controller master(pros::E_CONTROLLER_MASTER);
 pros::Motor leftfront  (1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor leftback   (2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightfront (3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor rightback  (4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawleft   (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor clawright  (9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor lift       (10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
 pros::Motor stacker    (11, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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

	leftfront.move_velocity(100);
	leftback.move_velocity(100);
	rightfront.move_velocity(100);
	rightback.move_velocity(100);
	pros::delay(2000);

	clawleft.move_velocity(-100);
	clawright.move_velocity(-100);
	clawleft.move_velocity(0);
	clawright.move_velocity(0);
	pros::delay(1000);

	leftfront.move_velocity(-100);
	leftback.move_velocity(-100);
	rightfront.move_velocity(-100);
	rightback.move_velocity(-100);
	pros::delay(1200);

	leftfront.move_velocity(0);
	leftback.move_velocity(0);
	rightfront.move_velocity(0);
	rightback.move_velocity(0);
	pros::delay(1500);
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

   char mytext[64];

/*Create a screen*/
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
sprintf(mytext, "leftfront: %8.2f\n"
  "rightfront: %8.2f\n"
  "stacker: %8.2f\n"
  "arm: %8.2f",
     leftfront.get_position(),
     rightfront.get_position(),
  stacker.get_position(),
  lift.get_position()
   );
// print to screen
lv_label_set_text(txt, mytext);

		leftfront.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
  	leftback.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
		rightfront.set_brake_mode (pros::E_MOTOR_BRAKE_HOLD);
		rightback.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
		clawright.set_brake_mode  (pros::E_MOTOR_BRAKE_HOLD);
		clawleft.set_brake_mode   (pros::E_MOTOR_BRAKE_HOLD);
		lift.set_brake_mode       (pros::E_MOTOR_BRAKE_HOLD);
		stacker.set_brake_mode    (pros::E_MOTOR_BRAKE_HOLD);

		int y = master.get_analog (ANALOG_LEFT_Y);
		int x = master.get_analog (ANALOG_LEFT_X);
		int z = master.get_analog (ANALOG_RIGHT_X);

		// chasis
		leftfront.move  (y + x + z);
		leftback.move   (y - x + z);
		rightfront.move (y - x - z);
		rightback.move  (y + x - z);

		//lift
		if(master.get_digital(DIGITAL_L1) )
		{
      if (stacker.get_position()>-300.0) {
             stacker.move_velocity(-50);
             //pros::delay(20);
          } else {
            stacker.move_velocity(0);

				lift.move_velocity (100);
      }
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
		if(master.get_digital(DIGITAL_R2)  )
		{
				stacker.move_velocity (50);
		}
		else if(master.get_digital(DIGITAL_R1))
		{
				stacker.move_velocity (-50);
		}
		else if (master.get_digital(DIGITAL_L1)==0)
		{
			stacker.move_velocity (0);
		}

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		pros::delay(20);
	}
}
