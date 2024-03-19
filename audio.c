#include "address_map_arm.h"
#include <math.h>

#define TWOPI 6.28318531
#define SAMPLE_RATE 8000
#define BUF_SIZE 2400
#define BUF_THRESHOLD 1800

int main(void){
    volatile int * audio_ptr = (int *) AUDIO_BASE;
    //list of frequencies
    double freqs[] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228,
                      369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
    int buffer[BUF_SIZE];
    int nth_sample, sample, buf_index;
    int vol = 0x7FFFFFFF;
    
    sample = 0;
    //loops through all frequencies to play a chromatic scale
    for (sample = 0; sample < 13; sample++) {
       	buf_index = 0; //reset index to 0
    	for(nth_sample = 0; nth_sample < BUF_SIZE ; nth_sample++){ //2400 = 0.3 * SAMPLE_RATE
    	    //places sine waves into a buffer
            buffer[nth_sample] = vol * sin(nth_sample * (TWOPI*freqs[sample]/SAMPLE_RATE));
    	}
        while(buf_index<BUF_SIZE){
        	//send buffer to left and right
        	*(audio_ptr+2) = buffer[buf_index];
        	*(audio_ptr+3) = buffer[buf_index];
        	buf_index++;
        }
	}
    printf("done"); //test to see if finished
}
