//****************************************//
/* Developer: Nithin Ken Maran            */
/* Version: 1.0                           */
/* input: floats: x0, y0, r0              */
/* Function: plots fibonacci spiral       */
//****************************************//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int hem(int);

#define PI 3.14159265

float a = 2.0;
float b = 1.0;
float r;
float theta;
int hem(int);


int main(int argc, char* argv[]){
    float a = 2.0;
    float b = 1.0;

    FILE* graph = fopen("graph.txt", "w");
    float x0 = atof(argv[1]);
    float y0 = atof(argv[2]);
    float x0_old = x0;
    float y0_old = y0;
    float r = atof(argv[3]);
    float r_old = r;
    float theta = 0.0;
    while(r<r_old+5.0){
    //plots half-circles with radii following fibonacci series, thus forming a spiral

    //100 points per semi-circle
    for (float i = 0; i <= 1000.0; i+=1.0) {

        theta = theta + i*PI/15;
        float x = x0 + r*cos(theta);
        float y = y0 + r*sin(theta);
        fprintf(graph, "%f %f\n", x, y);

       
    }
    
    x0 = x0 + x0_old;
    r = r_old + r;

    }

    FILE* script = fopen("script.txt", "w");
    //writing all gnuplot commands to one script file to execute together with one "system()" call
    fprintf(script, "set ytics -3, 2\n");
    fprintf(script, "set xlabel \"x axis\"\n");
    fprintf(script, "set ylabel \"y axis\"\n");
    fprintf(script, "plot 'graph.txt'\n");

    fclose(script);

    system("gnuplot -p script.txt");




return 0;
}

