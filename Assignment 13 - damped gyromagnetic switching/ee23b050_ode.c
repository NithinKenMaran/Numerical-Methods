#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define gamma 1.76e+10
#define H 1e-10



int integrator_euler(float*, float*, float, float*, float, float*);
int integrator_rk45(float*, float*, float, float*, float, float*, float*, float*, float*, float*, float*);
int integrator_heun(float*, float*, float, float*, float, float*, float*);

int euler(float*, float*, float, float*, float*, float);
int heun(float*, float*, float, float*, float*, float*, float);
int rk45(float*, float*, float, float*, float*, float*, float);
int derivs_phi(float , float* , float* , float* , float );
int rk45_phi(float* , float* , float* , float , float* , float* , float* , float );


float rk45_dt;



int derivs(float, float*, float*, float);
float thetadot(float, float);


int main(int argc, char* argv[]) {
    rk45_dt = 0.001; //****************** defining rk45's delta_t ***********************//


    FILE* thetafile = fopen("theta.txt", "w");
    FILE* phifile = fopen("phi.txt", "w");
    FILE* coords_euler = fopen("coords_euler.txt", "w");
    FILE* coords_heun = fopen("coords_heun.txt", "w");

    float theta_start = atof(argv[1]);
    float theta_stop = atof(argv[2]);
    float alpha = atof(argv[3]);
    float delta_t = atof(argv[4]);

    int discard_n = (int)floor(delta_t/0.001); //cuz rk45 function'll have (discard_n) times the number of points as euler or heun

    float phi_start = 0.0;
    
    float phinew_rk45 = 0.0;
    float* phinew_rk45_ptr = &phinew_rk45;

    float ynew_euler = 0.0;
    float* ynew_euler_ptr = &ynew_euler;

    float ynew_heun = 0.0;
    float* ynew_heun_ptr = &ynew_heun;

    float ynew_rk45 = 0.0;
    float* ynew_rk45_ptr = &ynew_rk45;

    float ym = 0.0;
    float* ym_ptr = &ym;

    float ye = 0.0;
    float* ye_ptr = &ye;

    float ym_phi = 0.0;
    float* ym_phi_ptr = &ym_phi;

    float ye_phi = 0.0;
    float* ye_phi_ptr = &ye_phi;


    float dydx = 0.0;
    float* dydx_ptr = &dydx;

    float dydx_2 = 0.0;
    float* dydx_2_ptr = &dydx_2;

    float t = 0.0;
    float* t_ptr = &t;

    float t_rk45 = 0.0;
    float* t_rk45_ptr = &t_rk45;

    //phi 
    float phi = 0.0;
    float* phi_ptr = &phi;

    float ynew_phi = 0.0;
    float* ynew_phi_ptr = &ynew_phi;
    
    float theta_euler = 0.0;
    float* theta_euler_ptr = &theta_euler;

    float theta_heun = 0.0;
    float* theta_heun_ptr = &theta_heun;

    float theta_rk45 = 0.0;
    float* theta_rk45_ptr = &theta_rk45;

    double rss_euler = 0.0; /* r^2 calculation */
    double tss_euler = 0.0; /* r^2 calculation */
    double rss_heun = 0.0;
    double tss_heun = 0.0;

    float dt = delta_t;

    *(theta_euler_ptr) = theta_start;
    *(theta_heun_ptr) = theta_start;
    *(theta_rk45_ptr) = theta_start;

    double sum_euler = 0.0;
    double sum_heun = 0.0;
    double sum_rk45 = 0.0;
    int n_euler = 0;
    int n_heun = 0;
    int n_rk45 = 0;

    float count = 0;

    FILE* tempout = fopen("temp.txt", "w");

    /*running from theta_start to theta_stop once to calculate mean of euler and heun*/
    
    while (*theta_euler_ptr <= theta_stop && *theta_heun_ptr <= theta_stop && *theta_rk45_ptr <= theta_stop) {

        integrator_euler(t_ptr, theta_euler_ptr, dt, ynew_euler_ptr, alpha, dydx_ptr);
        integrator_heun(t_ptr, theta_heun_ptr, dt, ynew_heun_ptr, alpha, dydx_ptr, dydx_2_ptr);
        integrator_rk45(t_rk45_ptr, theta_rk45_ptr, dt, ynew_rk45_ptr, alpha, ym_ptr, ye_ptr, phi_ptr, ynew_phi_ptr, ym_phi_ptr, ye_phi_ptr);
        n_euler ++;
        n_heun ++;
        n_rk45 ++;

        sum_euler += *theta_euler_ptr;
        sum_heun += *theta_heun_ptr;
        sum_rk45 += *theta_rk45_ptr;

        *t_rk45_ptr += rk45_dt;

        //***** printing coordinates to file *******//

        fprintf(tempout, "%f %f\n", *t_rk45_ptr, *theta_rk45_ptr);
        fprintf(phifile, "%f\n", *phi_ptr);
        fprintf(thetafile, "%f\n", *theta_rk45_ptr);
        float theta_temp = *theta_euler_ptr;
        float phi_temp = *phi_ptr;
        fprintf(coords_euler, "%f %f %f\n", sin(theta_temp)*cos(phi_temp), sin(theta_temp)*sin(phi_temp), cos(theta_temp));
        float theta_temp = *theta_heun_ptr;
        float phi_temp = *phi_ptr;
        fprintf(coords_heun, "%f %f %f\n", sin(theta_temp)*cos(phi_temp), sin(theta_temp)*sin(phi_temp), cos(theta_temp));



        *t_ptr += dt;
        count ++;

        for (int i = 0; i < discard_n-1; i++) {
            integrator_rk45(t_rk45_ptr, theta_rk45_ptr, dt, ynew_rk45_ptr, alpha, ym_ptr, ye_ptr, phi_ptr, ynew_phi_ptr, ym_phi_ptr, ye_phi_ptr);
            *t_rk45_ptr += rk45_dt;
        }

    }


    double ybar_euler = sum_euler/n_euler;
    double ybar_heun = sum_heun/n_heun;
    double ybar_rk45 = sum_rk45/n_rk45;

    /*resetting euler, heun and rk45 pointers to theta_start, to calculate rsquared*/
    *(theta_euler_ptr) = theta_start;
    *(theta_heun_ptr) = theta_start;
    *(theta_rk45_ptr) = theta_start;

    *t_ptr = 0.0;
    *t_rk45_ptr = 0.0;

    while (*theta_euler_ptr <= theta_stop && *theta_heun_ptr <= theta_stop && *theta_rk45_ptr <= theta_stop) {
       float h = dt;
       integrator_euler(t_ptr, theta_euler_ptr, dt, ynew_euler_ptr, alpha, dydx_ptr);
       integrator_heun(t_ptr, theta_heun_ptr, dt, ynew_heun_ptr, alpha, dydx_ptr, dydx_2_ptr);
       integrator_rk45(t_rk45_ptr, theta_rk45_ptr, dt, ynew_rk45_ptr, alpha, ym_ptr, ye_ptr, phi_ptr, ynew_phi_ptr, ym_phi_ptr, ye_phi_ptr);

       *t_ptr += dt;
       *t_rk45_ptr += rk45_dt;

       



       rss_euler += pow(((*theta_euler_ptr)-(*theta_rk45_ptr)), 2);
       tss_euler += pow(((*theta_euler_ptr)-(ybar_euler)),2);

       rss_heun += pow(((*theta_heun_ptr)-(*theta_rk45_ptr)), 2);
       tss_heun += pow(((*theta_heun_ptr)-(ybar_heun)),2);

       for (int i = 0; i < discard_n-1; i++) {
            integrator_rk45(t_rk45_ptr, theta_rk45_ptr, dt, ynew_rk45_ptr, alpha, ym_ptr, ye_ptr, phi_ptr, ynew_phi_ptr, ym_phi_ptr, ye_phi_ptr);
            *t_rk45_ptr += rk45_dt;
        }

    }

    double rsq_euler = 1-(rss_euler/tss_euler);
    double rsq_heun = 1-(rss_heun/tss_heun);

    printf("%f %f %lf %lf", alpha, delta_t, fabs(rsq_euler), fabs(rsq_heun));

fclose(thetafile);
fclose(phifile);
fclose(tempout);
fclose(coords_heun);
fclose(coords_euler);


return 0;
}

/**************integrator functions*******************/

int integrator_euler(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float alpha, float* dydx_ptr){

    euler(t_ptr, theta_ptr, dt, ynew_ptr, dydx_ptr, alpha);
    *theta_ptr = *ynew_ptr; //y updated


    return 0;
}

int integrator_heun(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float alpha, float* dydx_ptr, float* dydx_2_ptr){

    heun(t_ptr, theta_ptr, dt, ynew_ptr, dydx_ptr, dydx_2_ptr, alpha);
    *theta_ptr = *ynew_ptr; //y updated


    return 0;
}

int integrator_rk45(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float alpha, float* ym_ptr, float* ye_ptr, float* phi_ptr, float* ynew_phi_ptr, float* ym_phi_ptr, float* ye_phi_ptr){

    rk45(t_ptr, theta_ptr, rk45_dt, ynew_ptr, ym_ptr, ye_ptr, alpha);
    *theta_ptr = *ynew_ptr; //y updated

    rk45_phi(t_ptr, phi_ptr, theta_ptr, dt, ynew_phi_ptr, ym_phi_ptr, ye_phi_ptr, alpha);
    *phi_ptr = *ynew_phi_ptr;



return 0;
}

/**************integrators****************/

/*********** euler, heun and rk45 functions *********/

int euler(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float* dydx_ptr, float alpha) {

    derivs((*t_ptr), theta_ptr, dydx_ptr, alpha);
    *ynew_ptr = *theta_ptr + (*dydx_ptr)*dt;
    

return 0;
}

int heun(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float* dydx_ptr, float* dydx_2_ptr, float alpha){

    derivs(*t_ptr, theta_ptr, dydx_ptr, alpha);
    float ye = *theta_ptr + (*dydx_ptr)*dt;
    float* ye_ptr = &ye;

    derivs((*t_ptr)+dt, ye_ptr, dydx_2_ptr, alpha);

    float slope = ((*dydx_ptr)+(*dydx_2_ptr))/2;
    *ynew_ptr = *theta_ptr + slope*dt;


return 0;
}

int rk45(float* t_ptr, float* theta_ptr, float dt, float* ynew_ptr, float* ym_ptr, float* ye_ptr, float alpha){

    FILE* phi = fopen("phi.txt", "w");

    float k1 = 0.0;
    float* k1_ptr = &k1;

    float k2 = 0.0;
    float* k2_ptr = &k2;

    float k3 = 0.0;
    float* k3_ptr = &k3;

    float k4 = 0.0;
    float* k4_ptr = &k4;


    

    derivs(*t_ptr, theta_ptr, k1_ptr, alpha);
    
    *(ym_ptr) = *theta_ptr + (*k1_ptr)*dt/2;

    derivs(*t_ptr, theta_ptr, k2_ptr, alpha);

    *(ym_ptr) = *theta_ptr + (*k2_ptr)*dt/2;

    derivs(*t_ptr, theta_ptr, k3_ptr, alpha);

    *(ye_ptr) = *(theta_ptr) + (*k3_ptr)*dt/2;

    derivs((*t_ptr)+dt, ye_ptr, k4_ptr, alpha);

    float slope = (*k1_ptr + 2*((*k2_ptr) + (*k3_ptr)) + *k4_ptr)/6;

    *ynew_ptr = *theta_ptr + slope*dt;

    

return 0;
}

int rk45_phi(float* t_ptr, float* phi_ptr, float* theta_ptr, float dt, float* ynew_phi_ptr, float* ym_phi_ptr, float* ye_phi_ptr, float alpha){

    FILE* phi = fopen("phi.txt", "w");

    float k1_phi = 0.0;
    float* k1_phi_ptr = &k1_phi;

    float k2_phi = 0.0;
    float* k2_phi_ptr = &k2_phi;

    float k3_phi = 0.0;
    float* k3_phi_ptr = &k3_phi;

    float k4_phi = 0.0;
    float* k4_phi_ptr = &k4_phi;


    

    derivs_phi(*t_ptr, phi_ptr, theta_ptr, k1_phi_ptr, alpha);
    
    *(ym_phi_ptr) = *theta_ptr + (*k1_phi_ptr)*dt/2;

    derivs_phi(*t_ptr, phi_ptr, theta_ptr, k2_phi_ptr, alpha);

    *(ym_phi_ptr) = *theta_ptr + (*k2_phi_ptr)*dt/2;

    derivs_phi(*t_ptr, phi_ptr, theta_ptr, k3_phi_ptr, alpha);

    *(ye_phi_ptr) = *(theta_ptr) + (*k3_phi_ptr)*dt/2;

    derivs_phi((*t_ptr)+dt, ye_phi_ptr, theta_ptr, k4_phi_ptr, alpha);

    float slope = (*k1_phi_ptr + 2*((*k2_phi_ptr) + (*k3_phi_ptr)) + *k4_phi_ptr)/6;

    *ynew_phi_ptr = *phi_ptr + slope*dt;

    

return 0;
}

/*********************************/

//derivs() uses equation 8 from mallinson's paper for d(theta)/dt

int derivs(float t_val, float* theta_ptr, float* dydx_ptr, float alpha){

    *dydx_ptr = gamma*alpha*(H*sin(t_val))/(alpha*alpha + 1);

return 0;
}

int derivs_phi(float t_val, float* phi_ptr, float* theta_ptr, float* dydx_phi_ptr, float alpha) {

    *dydx_phi_ptr = (-1)*gamma*alpha*(H*sin(t_val))/((alpha*alpha + 1)*alpha*sin(*theta_ptr));

return 0;
}


