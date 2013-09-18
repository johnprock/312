//CSCE 312: Lab-1 Problem-5 framework
// This is version-2; bugfix for timediff
/* ***   README   **** */
/*This file is a framework: i.e. there is no actual code whose execution time will be
measured. You need to populate the appropriate functions with the code that you wrote 
for the previous problems in order to get useful data. 

Turning in this file without your code will result in zero points being awarded for this problem.

run this file as: gcc FileName.c -o ExecutableName -lrt 

*/




#include <stdio.h>
#include <time.h>

// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif

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



//The code segment which implements the decision logic
inline void control_action(){

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

inline void read_inputs_from_ip_if(){
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

inline void write_output_to_op_if(){
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


/* ---     You should not have to modify anything below this line ---------*/

/*timespec diff from
http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
*/
struct timespec diff(struct timespec start, struct timespec end)
 {
    struct timespec temp;
    //the if condition handles time stamp end being smaller than than 
    //time stamp start which could lead to negative time.

     if ((end.tv_nsec-start.tv_nsec)<0) {
          temp.tv_sec = end.tv_sec-start.tv_sec-1;
          temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
      } else {
          temp.tv_sec = end.tv_sec-start.tv_sec;
          temp.tv_nsec = end.tv_nsec-start.tv_nsec;
      }
  return temp;
 }

int main(int argc, char *argv[])
{
	unsigned int cpu_mhz;
	unsigned long long int begin_time, end_time;
	struct timespec timeDiff,timeres;
    struct timespec time1, time2, calibrationTime;
	
    clock_gettime(CLOCKNAME, &time1);
	clock_gettime(CLOCKNAME, &time2);
	calibrationTime = diff(time1,time2); //calibration for overhead of the function calls
    clock_getres(CLOCKNAME, &timeres);  // get the clock resolution data
	
    read_inputs_from_ip_if(); // get the sensor inputs
	
	clock_gettime(CLOCKNAME, &time1); // get current time
	control_action();                 // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}
