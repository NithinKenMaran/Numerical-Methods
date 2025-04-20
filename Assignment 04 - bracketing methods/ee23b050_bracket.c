/*
name: Nithin Ken Maran
rollno: EE23B050
version: 1.0

*** description ***

input: ./<executablename> <option>

<option> = 1: bisection method
<option> = 2: false position method


output: calculated value of x (e = 10% for bisection, e=0.2% for false position)

***



*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float function(float);
float bisect();
float position();

int main(int argc, char* argv[]) {
    if (atoi(argv[1]) == 1) {
        bisect();
    }

    if (atoi(argv[1]) == 2) {
        position();
    }
    


   return 0;
}

float bisect() {
    int epsilon = 10;
    float error = 100;
    float xl = 0.5;
    float xu = 1.0;
    float xr = 0;
    float xrold;


    while (error >= epsilon) {

        xrold = xr;

        xr = (xl + xu)/2;
        if (function(xl)*function(xr)<0) {
            xu = xr;

        }

        if (function(xr)*function(xu)<0) {

            xl = xr;

        }
        if (xr!=0) {
            error = fabsf((xrold-xr)*100/xr);
        }

    }

    printf("%f",xr);
    return 0;
}

float function(float x) { 

    //-25 + 82x - 90 x^2 + 44 x^3 - 8 x^4 + 0.7 x^5
    
    return (float) (-25+(82*x)-90*pow(x, 2)+44*pow(x,3)-8*pow(x,4)+0.7*pow(x,5));

}

float position() {

    float epsilon = 0.2;
    float error = 100;
    float xl = 0.5;
    float xu = 1.0;
    float xr = 0;
    float xrold;


    while (error >= epsilon) {

        xrold = xr;
        //xr = xu - (f(xu))(xl-xu)/(f(xl) - f(xu))
        xr = xu - (function(xu))*(xl-xu)/(function(xl)-function(xu));
      
        if (function(xl)*function(xr)<0) {
            xu = xr;
            

        }

        if (function(xr)*function(xu)<0) {

            xl = xr;
            
        }

        if (xr!=0) {
            error = fabsf((xrold-xr)*100/xr);
           
        }

    }

    printf("%f",xr);
    return 0;

}