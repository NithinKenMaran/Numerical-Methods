//Roll no.: ee23b050
//Date: 18 aug 2023
//Version: 1.0
/*Description:
calculates sin value of user-inputted number to the required accuracy using maclaurin's expansion, and also calculates error from actual value.
*/

//Inputs: number of terms to calculate sin upto, and value of x to calculate sin for

//Outputs: calculated sin value and error from actual value

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int factorial(int);



int main(int argc, char* argv[]) {

    float mysin=0.0;

    if (argc>3){ //checking number of arguments
        printf("%s", "too many arguments, please enter only 2");
    }

    int numarg = atoi(argv[1]); //number of terms to calculate
    float x = atof(argv[2]); //value to calculate sin for

    for (int i=1; i<=numarg; i++){

        mysin += (pow(-1, i+1) * pow(x,((2*i)-1)))/factorial((2*i)-1);
        //cuz sinx = x^1/1! - x^3/3! + x^5/5!...
        //thus general term is (-1)^(r+1) * x^(2r-1) / (2r-1)!

    }


    printf("%.3f,%.3f", mysin, (sin(x)-mysin));

    return 0;

}

int factorial(int z){


    int factorial1 = 1;


    for (int i=1; i<=z; i++) {
        factorial1 *= i;
    }
    return factorial1;

}