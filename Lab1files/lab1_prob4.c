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
unsigned int actuator_outputs;

// sensors
unsigned int sensor_inputs;



void read_inputs_from_ip_if(){
  sensor_inputs = 0x3FF;
}

// returns the nth bit in input
unsigned int get_nth_bit(unsigned int input, unsigned int n) {
   if((input & (1 << n)) != 0) {
    return 1;
   }  
   return 0; 
}

// sets the nth bit in input to set
void set_nth_bit(unsigned int &input, unsigned int n, unsigned int set) {
  if (set) { // set nth bit to 1
    input = input | (1 << n);
  }
  else { // set nth bit to 0
    input = input & ~(1 << n);
  }
}

// sensors
unsigned int driver_on_seat() {
  return get_nth_bit(sensor_inputs, 0);
}
unsigned int driver_seat_belt_fastened() {
  return get_nth_bit(sensor_inputs, 1);
}
unsigned int engine_running() {
  return get_nth_bit(sensor_inputs, 2);
}
unsigned int doors_closed() {
  return get_nth_bit(sensor_inputs, 3);
}
unsigned int key_in_car() {
  return get_nth_bit(sensor_inputs, 4);
}
unsigned int door_lock_lever(){
  return get_nth_bit(sensor_inputs, 5);
}
unsigned int brake_pedal() {  
  return get_nth_bit(sensor_inputs, 6);
}
unsigned int car_moving() {
  return get_nth_bit(sensor_inputs, 7);
}

// actuators
unsigned int bell(unsigned int set) {
  set_nth_bit(actuator_outputs, 0, set);
}
unsigned int door_lock_actuator(unsigned int set) {
  set_nth_bit(actuator_outputs, 1, set);
}
unsigned int brake_actuator(unsigned int set) {
  set_nth_bit(actuator_outputs, 2, set);
}

unsigned int bell() {
  return get_nth_bit(actuator_outputs, 0);
}
unsigned int door_lock_actuator() {
  return get_nth_bit(actuator_outputs, 1);
}
unsigned int brake_actuator() {
  return get_nth_bit(actuator_outputs, 2);
}


//The code segment which implements the decision logic
void control_action(){

  if(engine_running() && !driver_seat_belt_fastened()) {
    bell(1);
  }
  else if(engine_running() && !doors_closed()) {
    bell(1);
  }
  else bell(0);

  // door logic
  if (!driver_on_seat() && key_in_car()) {
    door_lock_actuator(0);
  }
  else if(driver_on_seat() && door_lock_lever()) {
    door_lock_actuator(1);
  }
  else door_lock_actuator(0);

  // brake logic
  if(brake_pedal() && car_moving()) {
    brake_actuator(1); 
  }
  else brake_actuator(0);

}

void write_output_to_op_if(){
  printf("bell: %d\ndoor_lock_actuator: %d\nbrake_actuator: %d\n", bell(), door_lock_actuator(), brake_actuator());
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
