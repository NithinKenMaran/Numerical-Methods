/*
Name: Nithin Ken Maran
Roll number: EE23B050
version: 2.0

input: ./<program_name> <N> <sigma_n>
output: <sigma_n> <A> <sigma_g> <R^2>

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//x ranges from -2 to 2, 
//N (input) datapoints in the curve.

float randomee() { //box-muller transform
//NOTE: stdev of these numbers is 1
    float u1 = random()/(RAND_MAX + 1.0);
    float u2 = random()/(RAND_MAX + 1.0);
    float z0 = sqrt((-2)*log(u1))*cos(2*M_PI*u2);

    return z0;

}

float lorentz(float x) { //lorentzian function

    return (float)1/(1+25*pow(x,2)); 

}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    float sigma_n = atof(argv[2]);
    

    float* baseline = (float*)malloc(N*sizeof(float));
    float* lor_noiseless = (float*)malloc(N*sizeof(float));
    float* lor_noisy = (float*)malloc(N*sizeof(float));
    float* gauss_fit = (float*)malloc(N*sizeof(float));

    FILE* fout = fopen("noisy.txt", "w");
    float sum_squares = 0.0;
    float sum = 0.0;
    float sum_r = 0.0;


    for (int i = 0; i < N; i++) {
        baseline[i] = (float)randomee()*sigma_n;
         //baseline noise; mean'll be 0 and stdev will be sigma_n (noise goes from -3sigma_n to +3sigma_n).
        lor_noiseless[i] = lorentz((-2.0*N + 4.0*i)/N); 
        //x = -2 + 4i/N (goes from -2 to 2)
        lor_noisy[i] = baseline[i] + lor_noiseless[i];
         //noisy curve with lorentzian + baseline noise
        float bloop = (-2.0*N + 4.0*i)/N;
        fprintf(fout, "%f %f\n", bloop, lor_noisy[i]);
        
        
    }
    fclose(fout);

    FILE* script = fopen("script.txt", "w"); 
    //writing all commands to a text file to execute together with one system() call
    fprintf(script, "set fit quiet\n");
    fprintf(script, "mean(x)=m\n");
    
    fprintf(script,"g(x) = A * exp(-(x**2)/(2*(s**2)))\n");
    fprintf(script,"fit g(x) 'noisy.txt' via A, s\n");
    
    fprintf(script, "set print 'A.txt'\n");
    fprintf(script,"print A\n");

    fprintf(script, "set print 's.txt'\n");
    fprintf(script, "print s\n");

    fclose(script);
    system("gnuplot script.txt"); 
    //calling the script file

    FILE* Afile = fopen("A.txt", "r");
    FILE* sfile = fopen("s.txt", "r");

    double A,s,R;

    fscanf(Afile, "%lf", &A);
    fscanf(sfile, "%lf", &s);
    
    fclose(Afile);
    fclose(sfile);

    for (int i = 0; i < N; i++) { 
        //calculating R^2
        sum += lor_noisy[i];
        gauss_fit[i] = A*exp(-pow(((-2.0*N + 4.0*i)/N),2)/2*pow(s,2));
        sum_r += pow((lor_noisy[i]-gauss_fit[i]),2);



    }
    float mean = sum/N;
    for (int i = 0; i < N; i++) {
        sum_squares += pow((mean - lor_noisy[i]),2);
    }

    R = 1-(sum_r/sum_squares);

    printf("%f %lf %lf %lf", sigma_n, A, s, fabs(R));

free(baseline);
free(lor_noiseless);
free(lor_noisy);

return 0;
}