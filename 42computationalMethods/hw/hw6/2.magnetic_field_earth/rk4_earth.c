#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define q 1.60217657E-19
#define m 1.67262178E-27
#define B_0 3.0E-5
#define R_T 6378.1
#define c 2.99792458E8

#define A -q*B_0*pow(R_T,3)/m

#define h 1.0E-4
#define min_t 0.0
#define max_t 100


float func_x1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2);
float func_y1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2);
float func_z1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2);
float func_x2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma);
float func_y2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma);
float func_z2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma);
void runge_kutta_4_step(float t_old, float x1_old, float y1_old, float z1_old, float x2_old, float y2_old, float z2_old, float *t_new, float *x1_new, float *y1_new, float *z1_new, float *x2_new, float *y2_new, float *z2_new, float gamma);
void runge_kutta_4(float t0, float x10, float y10, float z10, float x20, float y20, float z20, char *filename, float gamma);

int main(int argc, char **argv){

  if(argc!=3){
    printf("2 arguments are needed, the kinetic energy and the pitch angle alpha\n");
    exit(1);
  }

  float t0 = 0.0;
  float kinetic_energy_MeV = atof(argv[1]);
  float alpha = atof(argv[2]);

  float kinetic_energy = kinetic_energy_MeV*1.602177E-13;
  float gamma = kinetic_energy/(m*pow(c,2)) + 1.0;
  
  float v = c*sqrt(1.0 - 1.0/pow(gamma,2));

  float x10 = 2*R_T;
  float y10 = 0.0;
  float z10 = 0.0;
  float x20 = 0;
  float y20 = v*sin(alpha);
  float z20 = v*cos(alpha);

  char filename[50] = "trayectoria_";
  strcat(filename, argv[1]);
  strcat(filename, "_");
  strcat(filename, argv[2]);
  strcat(filename, ".dat");

  runge_kutta_4(t0, x10, y10, z10, x20, y20, z20, filename, gamma);
  
  return 0;
}

float func_x1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2){
  return x2;
}

float func_y1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2){
  return y2;
}

float func_z1_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2){
  return z2;
}

float func_x2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma){
  float r = sqrt(pow(x1,2) + pow(y1,2) + pow(z1,2));
  float by = 3*y1*z1;
  float bz = 2*pow(z1,2)-pow(x1,2)-pow(y1,2);
  return A*(y2*bz - z2*by)/(gamma*pow(r,5));
}

float func_y2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma){
  float r = sqrt(pow(x1,2) + pow(y1,2) + pow(z1,2));
  float bx = 3*x1*z1;
  float bz = 2*pow(z1,2)-pow(x1,2)-pow(y1,2);
  return A*(z2*bx - x2*bz)/(gamma*pow(r,5));
}

float func_z2_prime(float t, float x1, float y1, float z1, float x2, float y2, float z2, float gamma){
  float r = sqrt(pow(x1,2) + pow(y1,2) + pow(z1,2));
  float bx = 3*x1*z1;
  float by = 3*y1*z1;
  return A*(x2*by - y2*bx)/(gamma*pow(r,5));
}

void runge_kutta_4_step(float t_old, float x1_old, float y1_old, float z1_old, float x2_old, float y2_old, float z2_old, float *t_new, float *x1_new, float *y1_new, float *z1_new, float *x2_new, float *y2_new, float *z2_new, float gamma){
  
  float kx1_1 = func_x1_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old);
  float ky1_1 = func_y1_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old);
  float kz1_1 = func_z1_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old);
  float kx2_1 = func_x2_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old, gamma);
  float ky2_1 = func_y2_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old, gamma);
  float kz2_1 = func_z2_prime(t_old, x1_old, y1_old, z1_old, x2_old, y2_old, z2_old, gamma);
  

  float t_1 = t_old + h/2.0;
  float x1_1 = x1_old + (h/2.0)*kx1_1;
  float y1_1 = y1_old + (h/2.0)*ky1_1;
  float z1_1 = z1_old + (h/2.0)*kz1_1;
  float x2_1 = x2_old + (h/2.0)*kx2_1;
  float y2_1 = y2_old + (h/2.0)*ky2_1;
  float z2_1 = z2_old + (h/2.0)*kz2_1;

  float kx1_2 = func_x1_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1);
  float ky1_2 = func_y1_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1);
  float kz1_2 = func_z1_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1);
  float kx2_2 = func_x2_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1, gamma);
  float ky2_2 = func_y2_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1, gamma);
  float kz2_2 = func_z2_prime(t_1, x1_1, y1_1, z1_1, x2_1, y2_1, z2_1, gamma);
  
  
  float t_2 = t_old + h/2.0;
  float x1_2 = x1_old + (h/2.0)*kx1_2;
  float y1_2 = y1_old + (h/2.0)*ky1_2;
  float z1_2 = z1_old + (h/2.0)*kz1_2;
  float x2_2 = x2_old + (h/2.0)*kx2_2;
  float y2_2 = y2_old + (h/2.0)*ky2_2;
  float z2_2 = z2_old + (h/2.0)*kz2_2;

  float kx1_3 = func_x1_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2);
  float ky1_3 = func_y1_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2);
  float kz1_3 = func_z1_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2);
  float kx2_3 = func_x2_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2, gamma);
  float ky2_3 = func_y2_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2, gamma);
  float kz2_3 = func_z2_prime(t_2, x1_2, y1_2, z1_2, x2_2, y2_2, z2_2, gamma);
  
  
  float t_3 = t_old + h;
  float x1_3 = x1_old + h*kx1_3;
  float y1_3 = y1_old + h*ky1_3;
  float z1_3 = z1_old + h*kz1_3;
  float x2_3 = x2_old + h*kx2_3;
  float y2_3 = y2_old + h*ky2_3;
  float z2_3 = z2_old + h*kz2_3;

  float kx1_4 = func_x1_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3);
  float ky1_4 = func_y1_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3);
  float kz1_4 = func_z1_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3);
  float kx2_4 = func_x2_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3, gamma);
  float ky2_4 = func_y2_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3, gamma);
  float kz2_4 = func_z2_prime(t_3, x1_3, y1_3, z1_3, x2_3, y2_3, z2_3, gamma);

  
  float kx1 = (1.0/6.0)*(kx1_1 + 2.0*kx1_2 + 2.0*kx1_3 + kx1_4);
  float ky1 = (1.0/6.0)*(ky1_1 + 2.0*ky1_2 + 2.0*ky1_3 + ky1_4);
  float kz1 = (1.0/6.0)*(kz1_1 + 2.0*kz1_2 + 2.0*kz1_3 + kz1_4);
  float kx2 = (1.0/6.0)*(kx2_1 + 2.0*kx2_2 + 2.0*kx2_3 + kx2_4);
  float ky2 = (1.0/6.0)*(ky2_1 + 2.0*ky2_2 + 2.0*ky2_3 + ky2_4);
  float kz2 = (1.0/6.0)*(kz2_1 + 2.0*kz2_2 + 2.0*kz2_3 + kz2_4);

  *t_new = t_old + h;
  *x1_new = x1_old + h*kx1;
  *y1_new = y1_old + h*ky1;
  *z1_new = z1_old + h*kz1;
  *x2_new = x2_old + h*kx2;
  *y2_new = y2_old + h*ky2;
  *z2_new = z2_old + h*kz2;
}

void runge_kutta_4(float t0, float x10, float y10, float z10, float x20, float y20, float z20, char *filename, float gamma){
  int n = (int) ((max_t - min_t)/h);
  
  float *t = malloc(sizeof(float)*n);
  float *x1 = malloc(sizeof(float)*n);
  float *y1 = malloc(sizeof(float)*n);
  float *z1 = malloc(sizeof(float)*n);
  float *x2 = malloc(sizeof(float)*n);
  float *y2 = malloc(sizeof(float)*n);
  float *z2 = malloc(sizeof(float)*n);

  float t_new, x1_new, y1_new, z1_new, x2_new, y2_new, z2_new;

  t[0] = t0;
  x1[0] = x10;
  y1[0] = y10;
  z1[0] = z10;
  x2[0] = x20;
  y2[0] = y20;
  z2[0] = z20;

  FILE *out = fopen(filename, "w");
  fprintf(out, "%f %f %f %f\n", t0, x10, y10, z10);
  
  int i;

  for(i=1;i<n;i++){
    runge_kutta_4_step(t[i-1], x1[i-1], y1[i-1], z1[i-1], x2[i-1], y2[i-1], z2[i-1], &t_new, &x1_new, &y1_new, &z1_new, &x2_new, &y2_new, &z2_new, gamma);
    t[i] = t_new;
    x1[i] = x1_new;
    y1[i] = y1_new;
    z1[i] = z1_new;
    x2[i] = x2_new;
    y2[i] = y2_new;
    z2[i] = z2_new;
    
    fprintf(out, "%f %f %f %f\n", t_new, x1_new, y1_new, z1_new);
  }
  fclose(out);
}
