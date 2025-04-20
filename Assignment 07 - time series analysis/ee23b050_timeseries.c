/*
    Name: Nithin Ken Maran
    Roll number: EE23B050
    version: 3.0

    input: M, T, a, <choice>
    output: avg(T) avg(a) stdev(T) stdev(a)

    NOTE: as given in assignment, <choice> should have the first letter capitalized ("Gaussian" or "Lorentzian")
    
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define W 100 // (1/size_of_interval)
#define scale 0.05 //scales noise to these many times the value it's being added to

// lorentzian function:
//      a^2
//  --------------
//  a^2 + (t-mT)^2



// gaussian function:
//       (t-mT)^2
//     - -------
//         2a^2
//  e^^

float T;

struct allpeaks {

    float amplitude;
    float location;
    float width;

};

float randomee() {

    float u1 = random()/(RAND_MAX + 1.0);
    float u2 = random()/(RAND_MAX + 1.0);
    float z0 = sqrt((-2)*log(u1))*cos(2*M_PI*u2);

    return z0;

}

float lorentz(float a, float t, float m) {

    float numerator = pow(a,2);
    float denominator = pow(a,2) + pow((t-(m*T)),2);
    return (float) (numerator/denominator);

}

float gauss(float a, float t, float m) {
    float numerator = (-1)*pow((t-(m*T)),2);
    float denominator = 2*pow(a,2);
    return (float) exp(numerator/denominator);

}


int main(int argc, char* argv[]) {
    
    //initializing things:
        int M = atoi(argv[1]);
        T = atof(argv[2]);
        float a = atof(argv[3]);
        int num_datapoints = (int)ceil(W*T);
        char* choice = (char*)malloc(20*sizeof(char));
        if (argv[4]!=NULL) {
            choice = argv[4];
        }

        else {
            choice = "Lorentzian";
        }

        double signal[M][num_datapoints];
        struct allpeaks* peaks = (struct allpeaks*)malloc(M*sizeof(struct allpeaks));


    float t = (float) T/2; //first peak: T/2 to 3T/2. 
                           //second peak: 3T/2 to 5T/2
                           //third peak: 5T/2 to 7T/2
                           //...
    

    for (int i = 0; i < M; i++) { //drawing lorentzian curve
        
        for (int j = 0; j < num_datapoints; j++) {
            

            if (!strcmp(choice, "Gaussian")) {

                signal[i][j] = gauss((a+(((scale)*randomee())*a)), t, ((i+1)+(scale)*randomee())); //i+1 goes from 1 to M

            }
            
            else {

                signal[i][j] = lorentz((a+(((scale)*randomee())*a)), t, ((i+1)+(scale)*randomee())); //i+1 goes from 1 to M
            }
            t += (float) T/num_datapoints;
        }

    }

    
    
    float t1 = (float) T/2;
    int halfpoint = (int)floor((num_datapoints)/2);
    float interval = T/num_datapoints; //step size of "t" (on the x axis)
    int jleft,jright,jcentre;

    //jleft: half-max point to the left of the peak
    //jright: half-max point to the right of the peak

    //initializing more things
        float a_sum = 0.0;
        float a_sum_squares = 0.0;
        float T_sum = 0.0;
        float T_sum_squares = 0.0;


    for (int i = 0; i < M; i++){
        float peakstart = ((2*i)+1)*T/2; //each i'th peak starts with this value of t
        for (int j1 = 0; j1 < halfpoint; j1++) {

            if (signal[i][j1] < 0.5) continue;
            jleft = j1;
            break;

        }

        for (int j2 = halfpoint; j2 < num_datapoints; j2++) {
            
            if (signal[i][j2] > 0.5) continue;
            jright = j2;
            break;

        }

        jcentre = (int)floor((jleft+jright)/2);


        peaks[i].width = (jright-jleft)*interval/2;
        a_sum += peaks[i].width/2;
        a_sum_squares += pow(((peaks[i].width)/2),2);

        peaks[i].location = peakstart + (jcentre*interval);
        if (i>1) { 
            T_sum += peaks[i].location - peaks[i-1].location;
            T_sum_squares += pow((peaks[i].location - peaks[i-1].location),2); 
                
           }

        peaks[i].amplitude = signal[i][jcentre];
    }

    float a_avg = a_sum/(M);
    float T_avg = T_sum/(M-2);
    
    float a_avg_squares = a_sum_squares/(M);
    float T_avg_squares = T_sum_squares/(M-2);

    float a_stdev = sqrt(a_avg_squares - pow(a_avg,2));
    float T_stdev = sqrt(T_avg_squares - pow(T_avg,2));

    printf("%f %f %f %f", T_avg, a_avg, T_stdev, a_stdev );


    return 0;
}

