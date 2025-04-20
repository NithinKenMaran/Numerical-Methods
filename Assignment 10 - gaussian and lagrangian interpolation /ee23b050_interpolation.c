/*
Name: Nithin Ken Maran
Roll Number: EE23B050
Version: 1.0

input: ./<program> <order> <xstart> <xend> <x0>
output: f(x0) calculated through newtonian interpolation

NOTE: newtonian interpolation samples from the legrangian interpolation as asked in the assignment, but this ends up giving the exact same result as if it sampled from f(x) itself, cuz the points sampled from legrangian are the exact same points given to the lagrng() function from f(x).

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int newtint(float*, float*, int, float, float*);
float lagrng(float*, float*, int, float);
float func(float);
int n;
float xstart, xend, x0;

int main(int argc, char* argv[]) {

    n = atoi(argv[1]);
    xstart = atof(argv[2]);
    xend = atof(argv[3]);
    x0 = atof(argv[4]);

    //float yint[n];
    float* yint = (float*)malloc(n*sizeof(float));
    //float y[n+1];
    float* y = (float*)malloc((n+1)*sizeof(float));
    //float ylegrange[n+1];
    float* ylegrange = (float*)malloc((n+1)*sizeof(float));

   //float x[n+1];
   float* x = (float*)malloc((n+1)*sizeof(float));

    

    for (int i = 0; i<n+1; i++){
        x[i] = xstart + i * (xend - xstart)/(n);
        y[i] = func(x[i]);
       
    }

    for (int i = 0; i<n+1; i++){
        ylegrange[i] = lagrng(x, y, n, x[i]);
    }
    
    newtint(x, ylegrange, n, x0, yint); //second argument is ylegrange, cuz newtint() is sampling from the legrangian interpolation.




    printf("%f", yint[n]);
free(yint);
free(y);
free(ylegrange);
free(x);
return 0;
}


int newtint(float* x, float* y, int n, float xi, float* yint) {
    float fdd[n+1][n+1];
    
   
    for (int i = 0; i <=n; i++) {
        fdd[i][0] = y[i];


    }

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= (n-j); i++) {
            fdd[i][j] = (fdd[i+1][j-1] - fdd[i][j-1])/(x[i+j]-x[i]);

        }
    }
    float xterm = 1.0;
    yint[0] = fdd[0][0];
    for (int order = 1; order <= n; order++) {
        xterm = xterm*(xi-x[order-1]);
        yint[2] = yint[order-1]+fdd[0][order]*xterm;
        yint[order] = yint[2];

    }

    return 0;
}

float lagrng(float* x, float* y, int n, float xx) {
    float sum = 0;
    for (int i = 0; i<=n; i++) {
        float product = y[i];
        for (int j = 0; j <= n; j++) {
            if (i != j) {
                product = product*(xx-x[j])/(x[i]-x[j]);

            }
        }
        sum = sum+product;
    }
    float lagrng = sum;
    return lagrng;
}

float func(float ex) {
    return (float) 1/(1+25*ex*ex);
}
