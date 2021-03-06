/****Drive Methods****/

void sync_arcade(){
	int leftSpeed = (DEADBAND(vexRT[JOY_AXIS_LEFT]) + DEADBAND(vexRT[JOY_AXIS_TURN])) * SLOW; // Get the normal left speed
	int rightSpeed = (DEADBAND(vexRT[JOY_AXIS_LEFT]) - DEADBAND(vexRT[JOY_AXIS_TURN])) * SLOW;// Get the normal right speed
	motor[leftMotor] = IS_REVERSED ? (rightSpeed * -1) : leftSpeed;	// Set the left motor to the right speed if it is reversed
	motor[rightMotor] = IS_REVERSED ? (leftSpeed * -1) : rightSpeed; // Set the right motor to the left speed if it is reversed
}

// This method moves each wheel independently, taking input from the respective joysticks
void tank_drive(){
	int leftSpeed = DEADBAND(vexRT[JOY_AXIS_LEFT]) * SLOW;					// Get the normal left speed
	int rightSpeed = DEADBAND(vexRT[JOY_AXIS_RIGHT]) * SLOW;				// Get the normal right speed
	motor[leftMotor] = IS_REVERSED ? (rightSpeed * -1) : leftSpeed;	// Set the left motor to the right speed if it is reversed
	motor[rightMotor] = IS_REVERSED ? (leftSpeed * -1) : rightSpeed;// Set the right motor to the left speed if it is reversed
}

// Takes input from the driver to move the robot
// This task operates concurrently with the main method
task drive(){
	// The loop repeats forever (or until the robot is turned off)
	while(true){
		// Take input to toggle arcade mode
		if(vexRT[ARCADE_BTN]){
			arcade = !arcade; // Toggle arcade mode
			motor[servoFlagDrive] = (arcade ? arcadeFlagPos : tankFlagPos);
			while(vexRT[ARCADE_BTN]){} // Don't test again (or do anything) until the button is released
		}

		if(arcade){
			// If arcade mode is activated, we want to move both wheels together
			sync_arcade();
		}else{
			// If arcade mode is not activated, we want to move each wheel independently
			tank_drive();
		}
	}
}

/****Miscellaneous Methods****/

// Moves the lift based on input from two buttons
task dust_pan(){
	while(true){
		// The lift is controlled by the up or down buttons on both sides of the controller
		int power = (vexRT[DUST_UP] - vexRT[DUST_DOWN]) * BTN_SPEED * 0.8;// Totals both inputs for up and down
		motor[dustPan] = ((power == 0) ? (BTN_SPEED * 0.2) : power);			// Sets the dust pan motor's speed, and applies consistant speed if there is no input from the controller
	}
}

// Runs the start-up stuffs
void init(){
	arcade = false;				// Set the default drive mode to tank_drive
	motor[servoFlagDrive] = tankFlagPos;
}
