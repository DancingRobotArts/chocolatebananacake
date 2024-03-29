#include "main.h"

#ifndef CONFIG_H
#define CONFIG_H

extern pros::Controller master;
extern pros::Motor leftfront  ;
extern pros::Motor leftback   ;
extern pros::Motor rightfront ;
extern pros::Motor rightback  ;
extern pros::Motor lift       ;
extern pros::Motor claw1      ;
extern pros::Motor claw2      ;
extern pros::Motor stacker    ;
extern pros::ADIPotentiometer ADISstacker;

enum redblue {red=1, blue=-1};
enum frontback {front=1, back=-1};

#endif
