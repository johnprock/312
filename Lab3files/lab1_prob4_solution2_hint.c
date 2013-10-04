/*
Lab-1, Problem-4, Sample soltion-2
Note: Only requirement 1,2,3,4 is covered 
modify this code to include requirement 5 also

Also add your own INPUT/OUTPUT code to test it.

*/


#include <stdio.h>
#include <time.h>
// Macro definitions to ensure portablity between both sun.cs and linux.cs

#if defined(sun)
    #define CLOCKNAME CLOCK_HIGHRES
        
#else
    #define CLOCKNAME CLOCK_PROCESS_CPUTIME_ID
#endif

unsigned int input;  

unsigned int output;  



//For input interface implementation
inline void read_inputs_from_ip_if(){
  printf("Input: ");
  scanf ("%d",&input);
}

//For output interface implementation
inline void write_output_to_op_if(){
   printf("Output: %d\n", output);
}


//The code segment which implements the decision logic
inline void control_action(){

	//Requirement 1, 2, 3, 4 only
	switch (input & 0xff) //Change to 0xff for all 5 requirements
	{
		case 5:
		case 7:
		case 13:
			output = 1;
		break;

		case 32:
		case 34:
		case 36:
		case 38:
		case 40:
		case 42:
		case 44:
		case 46:
		case 49:
		case 51:
			output = 2;
		break;

		case 53:
		case 55:
			output = 3;
		break;

		case 57:
		case 59:
			output = 2;
		break;

		case 61:
			output = 3;
		break;

		case 63:
			output = 2;
                break;

                case 192:
                        output = 4;
                break;

                case 64:
                        output = 0;                       
	
	}


}


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
	control_action();       // process the sensors
	clock_gettime(CLOCKNAME, &time2);   // get current time

	write_output_to_op_if();    // output the values of the actuators
	
	timeDiff = diff(time1,time2); // compute the time difference

	printf("Timer Resolution = %u nanoseconds \n ",timeres.tv_nsec);
	printf("Calibrartion time = %u seconds and %u nanoseconds \n ", calibrationTime.tv_sec, calibrationTime.tv_nsec);
    printf("The measured code took %u seconds and ", timeDiff.tv_sec - calibrationTime.tv_sec);
	printf(" %u nano seconds to run \n", timeDiff.tv_nsec - calibrationTime.tv_nsec);
	
	return 0;
}

