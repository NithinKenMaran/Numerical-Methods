/*
    Name: Nithin Ken Maran
    Roll Number: EE23B050
    version: 2.0


    NOTE: default values of xstart and xend are taken as -1.0 and 1.0 respectively, but if xstart and xend are to be specified, it should be done as: 

    ./<program> <order> <x0> <xstart> <xend>

    

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//adding function definitions here so that function definitions can be written after main() without creating errors.
void tridiag(float *x, float *y, int N, float *e, float*f, float*g, float*r);
void Gauss(float **a, float *r, int N, int*er, float tol,float*e, float*g, float*f); 
void Substitute(float **a, float *r, int N, float *d2x);
void pivot(float **a, float *r, int N, int row);
void Interpol(float*x, float*y, int N, float*d2x,float xu); 
float func(float);

int main(int argc, char* argv[]) {

    float xstart = 0.0;
    float xend = 0.0;
    int n = atoi(argv[1]);
    float xu = atof(argv[2]);
    float yu = 0.0;

    if (argc==5) {
     xstart = atof(argv[3]);
     xend = atof(argv[4]);
    }
    else {

         xstart = -1.0;
         xend = 1.0;

    }

    float* y = (float*)malloc((n+1)*sizeof(float));
    float* x = (float*)malloc((n+1)*sizeof(float));
    float dy, d2y;


    //dynamically allocating memory for all arrays together
    float* e = (float*)malloc((n+1)*sizeof(float));
    float* f = (float*)malloc((n+1)*sizeof(float));
    float* g = (float*)malloc((n+1)*sizeof(float));
    float* r = (float*)malloc((n+1)*sizeof(float));
    float* d2x = (float*)malloc((n+1)*sizeof(float));
    //using a[n][n] created segmentation fault; dynamic allocation works well even for 2d arrays apparently.
    float **a = malloc((n-1) * sizeof(float *));
    for(int i = 0; i < n-1; i++)
        a[i] = malloc((n) * sizeof(float));
        

    
    //fills x[] with values, and y[] with corresponding function values
    for (int i = 0; i<n+1; i++){
        x[i] = xstart + i * (xend - xstart)/(n);
        y[i] = func(x[i]);
       
    }
int*er = 0; // error indicator
float tol = 0.0000001; // tolerance

tridiag(x,y, n,e, f, g, r);
Gauss(a, r, n, er, tol,e, g, f);
Substitute(a, r, n, d2x);
Interpol(x, y, n, d2x,xu);

return 0;
}

float func(float ex) { /*function is 
                            1
                        -----------
                         1 + 25x^2
                        */

    return (float) 1/(1+25*ex*ex);
}

//this creates the tridiagonal matrix, which has coefficients of the system of equations for the spline's second derivatives.
void tridiag(float *x, float *y, int N, float *e, float*f, float*g, float*r){
int i= 1;

f[1] = 2 *(x[2]- x[0]);
g[1]= x[2]- x[1];
r[1]= 6/(x[2]- x[1])*(y[2]-y[1]);
r[1] = r[1] + 6/(x[1]-x[0])*(y[0]-y[1]);
   for(i= 2; i<=N-2 ; i++){
     e[i]= x[i]- x[i-1];
     f[i]= 2*(x[i+1] - x[i-1]);
     g[i]= x[i+1]- x[i];
     r[i]= 6/(x[i+1]- x[i])*(y[i+1]-y[i]);
     r[i]= r[i] + 6/(x[i] - x[i-1])*(y[i-1]-y[i]);
  }
e[N-1]= x[N-1]- x[N-2];
f[N-1]= 2*(x[i+1]- x[i-1]);
r[N-1]= 6/(x[N]- x[N-1])*(y[N]-y[N-1]);
r[N-1]= r[N-1] + 6/(x[N-1]- x[N-2]) * (y[N-2]- y[N-1]);
}

// gaussian elimination, just like the previous assignment
void Gauss(float **a, float *r, int N, int *er, float tol,float*e, float*g, float*f){
int i,j;
for(i = 1; i< N; i++){ 
      for (j = 1; j< N; j++){
        a[i-1][j-1]=0;
        }
      }
      
for(i= 1; i< N; i++){
   j = i;
     a[i-1][j-1]= f[i];
     }
    
for( i = 2; i < N; i++){
  j = i-1;
  a[i-1][j-1] = e[i];
  }
  
for ( i = 1; i< N-1; i ++){
 j = i+1;
 a[i-1][j-1]= g[1];
 }
 
 for (i = 0; i< N-1; i++) {
        pivot(a, r, N, i);
        for (j = i+1; j < N-1; j++) {
            float factor = a[j][i] / a[i][i];
            for (int k = i; k < N-1; k++) {
                a[j][k] -= factor * a[i][k];
            }
            r[j+1] -= factor * r[i+1];
        }
        if (fabs(a[i][i]) < tol) {
            *er = -1;
            printf("no solutions");
            return; 
        }
    }
}
void Substitute(float **a, float *r, int N, float *d2x) {
    for (int i = N - 2; i >= 0; i--) {
        float sum = 0;
        for (int j = i + 1; j < N-1; j++) {
            sum += a[i][j] * d2x[j+1];
        }
        d2x[i+1] = (r[i+1] - sum) / a[i][i];
    }
}

void pivot(float **a, float *r, int N, int row) {
    int p = row;
    for (int i = row+1; i < N-1; i++) {
        if (fabs(a[i][row]) > fabs(a[p][row])) {
            p = i;
        }
    }
    float *temp = a[row];
    a[row] = a[p];
    a[p] = temp;
    float temp_r = r[row+1];
    r[row+1] = r[p+1];
    r[p+1] = temp_r;
}
    
void Interpol(float*x, float*y, int N, float*d2x,float xu){
int flag = 0;
float yu=0.0;
int i = 1;
do {
 if (xu >= x[i-1] && xu<= x[i]){
   float c1= d2x[i-1]/6/(x[i]-x[i-1]);
   float c2= d2x[i]/6/(x[i]-x[i-1]);
   float c3= y[i-1]/(x[i]- x[i-1]) - (d2x[i-1]* (x[i]- x[i-1])/6);
   float c4= y[i]/(x[i]-x[i-1]) - (d2x[i]*(x[i]-x[i-1])/6);
   float t1 = c1* pow((x[i]- xu),3);
   float t2 = c2* pow((xu- x[i-1]),3);
   float t3= c3* (x[i]- xu);
   float t4= c4*(xu - x[i-1]);
   yu = t1+t2+t3+t4;
   flag = 1;
   }
  else{
  i = i+1;}
  }while( i!= N ||flag!= 1);
printf("%f",yu);
if (flag == 0){printf("outside range");}
}