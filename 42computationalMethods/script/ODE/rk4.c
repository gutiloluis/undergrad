#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sigma 10.0
#define rho 28.0
#define beta 8.0/3.0

#define h 0.01
#define min_t 0.0
#define max_t 3.0

float func_x_prime(float t, float x, float y, float z);
float func_y_prime(float t, float x, float y, float z);
float func_z_prime(float t, float x, float y, float z);
void runge_kutta_4_step(float t_old, float x_old, float y_old, float z_old, float *t_new, float *x_new, float *y_new, float *z_new);
void runge_kutta_4(float t0, float x0, float y0, float z0, char *filename);

int main(){
  
  int i;
  for(i=0;i<10;i++){

    srand48(i);
    
    char filename[5];
    char c[5];
    sprintf(c, "%d", i);
    strcpy(filename,c);
    strcat(filename,".dat");
    
    float t0 = 0.0;
    float x0 = 20*drand48()-10;
    float y0 = 20*drand48()-10;
    float z0 = 20*drand48()-10;
 
    runge_kutta_4(t0, x0, y0, z0, filename);
  }
  
  return 0;
  
}


float func_x_prime(float t, float x, float y, float z){
  return sigma*(y-x);
}

float func_y_prime(float t, float x, float y, float z){
  return x*(rho-z)-y;
}

float func_z_prime(float t, float x, float y, float z){
  return x*y - beta*z;
}

void runge_kutta_4_step(float t_old, float x_old, float y_old, float z_old, float *t_new, float *x_new, float *y_new, float *z_new){
  
  float kx1 = func_x_prime(t_old, x_old, y_old, z_old);
  float ky1 = func_y_prime(t_old, x_old, y_old, z_old);
  float kz1 = func_z_prime(t_old, x_old, y_old, z_old);
  

  float t1 = t_old + h/2.0;
  float x1 = x_old + (h/2.0)*kx1;
  float y1 = y_old + (h/2.0)*ky1;
  float z1 = z_old + (h/2.0)*kz1;

  float kx2 = func_x_prime(t1, x1, y1, z1);
  float ky2 = func_y_prime(t1, x1, y1, z1);
  float kz2 = func_z_prime(t1, x1, y1, z1);


  float t2 = t_old + h/2.0;
  float x2 = x_old + (h/2.0)*kx2;
  float y2 = y_old + (h/2.0)*ky2;
  float z2 = z_old + (h/2.0)*kz2;

  float kx3 = func_x_prime(t2, x2, y2, z2);
  float ky3 = func_y_prime(t2, x2, y2, z2);
  float kz3 = func_z_prime(t2, x2, y2, z2);


  float t3 = t_old + h;
  float x3 = x_old + h*kx3;
  float y3 = y_old + h*ky3;
  float z3 = z_old + h*kz3;

  float kx4 = func_x_prime(t3, x3, y3, z3);
  float ky4 = func_y_prime(t3, x3, y3, z3);
  float kz4 = func_z_prime(t3, x3, y3, z3);

  
  float kx = (1.0/6.0)*(kx1 + 2.0*kx2 + 2.0*kx3 + kx4);
  float ky = (1.0/6.0)*(ky1 + 2.0*ky2 + 2.0*ky3 + ky4);
  float kz = (1.0/6.0)*(kz1 + 2.0*kz2 + 2.0*kz3 + kz4);

  *t_new = t_old + h;
  *x_new = x_old + h*kx;
  *y_new = y_old + h*ky;
  *z_new = z_old + h*kz;

}

void runge_kutta_4(float t0, float x0, float y0, float z0, char *filename){
  
  int n = (int) ((max_t - min_t)/h);
  
  float *t = malloc(sizeof(float)*n);
  float *x = malloc(sizeof(float)*n);
  float *y = malloc(sizeof(float)*n);
  float *z = malloc(sizeof(float)*n);
  
  float t_new;
  float x_new;
  float y_new;
  float z_new;

  t[0] = t0;
  x[0] = x0;
  y[0] = y0;
  z[0] = z0;

  FILE *out = fopen(filename, "w");
  
  fprintf(out, "%f %f %f %f\n", t0, x0, y0, z0);

  int i;

  for(i=1;i<n;i++){ 
    runge_kutta_4_step(t[i-1], x[i-1], y[i-1], z[i-1], &t_new, &x_new, &y_new, &z_new);
    t[i] = t_new;
    x[i] = x_new;
    y[i] = y_new;
    z[i] = z_new;
    fprintf(out, "%f %f %f %f\n", t_new, x_new, y_new, z_new);
  }
  fclose(out);
}
