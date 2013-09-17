// CSCE312: Lab-1 Problem-3 framework

/* ***   README   **** */

/*
This example program sounds the bell when driver is on seat 
AND haven't closed the doors. Use the general framework and the function 
shells, replace the code inside  the control_action() function with your 
own code to do problems 3 and 4.

Note: This code is designed to run in an infinite loop to mimic a real control system. 
If you prefer to read the inputs from a file, modify the code appropriately to terminate the
loop when all the inputs have been processed.

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as : gcc filename.c -o executableName

*/


#include <stdio.h> //This is useful to do i/o to test the code 

// actuators
unsigned int bell;
unsigned int door_lock_actuator;
unsigned int brake_actuator;

// sensors
unsigned int driver_seat_belt_fastened;
unsigned int engine_running;
unsigned int driver_on_seat;
unsigned int doors_closed;
unsigned int key_in_car;
unsigned int door_lock_lever;
unsigned int brake_pedal;
unsigned int car_moving;


int convert(char c) {
  if(c == '1'){
    return 1;
  }
  else return 0;
}

void read_inputs_from_ip_if(){
  // read input from stdin 
  // input format is a sequence of '0' or '1' characters
  char c;
  c = getchar();
  driver_seat_belt_fastened = convert(c);
  
  c = getchar();
  engine_running = convert(c);

  c = getchar();
  driver_on_seat = convert(c);

  c = getchar();
  doors_closed = convert(c);

  c = getchar();
  key_in_car = convert(c);

  c = getchar();
  door_lock_lever = convert(c);

  c = getchar();
  brake_pedal = convert(c);

  c = getchar();
  car_moving = convert(c);


}

void write_output_to_op_if(){
  // sensor values printed for debugging purposes
  printf("driver_seat_belt_fastened: %d\n", driver_seat_belt_fastened);
  printf("engine_running: %d\n", engine_running);
  printf("driver_on_seat: %d\n", driver_on_seat);
  printf("doors_closed: %d\n", doors_closed);
  printf("key_in_car: %d\n", key_in_car);
  printf("door_lock_lever: %d\n", door_lock_lever);
  printf("brake_pedal: %d\n", brake_pedal);
  printf("car_moving: %d\n", car_moving);

  // actuators
  printf("bell: %d\ndoor_lock_actuator: %d\nbrake_actuator: %d\n", bell, door_lock_actuator, brake_actuator);
}


//The code segment which implements the decision logic
void control_action(){

  // bell logic
  if(engine_running && !driver_seat_belt_fastened) {
    bell = 1;
  }
  else if(engine_running && !doors_closed) {
    bell = 1;
  }
  else bell = 0;

  // door logic
  if (!driver_on_seat && key_in_car) {
    door_lock_actuator = 0;
  }
  else if(driver_on_seat && door_lock_lever) {
    door_lock_actuator = 1;
  }
  else door_lock_actuator = 0;

  // brake logic
  if(brake_pedal && car_moving) {
    brake_actuator = 1; 
  }
  else brake_actuator = 0;

}

/* ---     You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[])
{
	
	/*The main control loop which keeps the system alive and responsive for ever, 
	until the system is powered off */
	for (; ; )
	{
		read_inputs_from_ip_if();
		control_action();
		write_output_to_op_if();

	}
	
	return 0;
}
