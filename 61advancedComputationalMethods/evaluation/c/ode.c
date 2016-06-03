#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define h 0.001
#define min_t 0
#define max_t 2*3.141592

float func_x2_prime(float t, float x1, float x2);
float func_x1_prime(float t, float x1, float x2);
void euler_step(float t_old, float x1_old, float x2_old, float *t_new, float *x1_new, float *x2_new);
void euler(float t0, float x10, float x20);

int main(){
  euler(0.0,1.0,0.0);
  return 0;
}

float func_x2_prime(float t, float x1, float x2){
  return -x1;
}

float func_x1_prime(float t, float x1, float x2){
  return x2;
}

void euler_step(float t_old, float x1_old, float x2_old, float *t_new, float *x1_new, float *x2_new){
  
  *t_new = t_old + h;
  *x1_new = x1_old + h*func_x1_prime(t_old, x1_old, x2_old);
  *x2_new = x2_old + h*func_x2_prime(t_old, x1_old, x2_old);

}

void euler(float t0, float x10, float x20){

  int n = (int) ((max_t - min_t)/h);

  float *t = malloc(sizeof(float)*n);
  float *x1 = malloc(sizeof(float)*n);
  float *x2 = malloc(sizeof(float)*n);

  float t_new;
  float x1_new;
  float x2_new;

  t[0] = t0;
  x1[0] = x10;
  x2[0] = x20;

  FILE *out = fopen("a.dat", "w");

  int i;

  /*printf("%f %f\n", t0, x10);*/
  fprintf(out,"%f %f\n", t0, x10);

  for(i=1;i<n;i++){
    euler_step(t[i-1], x1[i-1], x2[i-1], &t_new, &x1_new, &x2_new);
    t[i] = t_new;
    x1[i] = x1_new;
    x2[i] = x2_new;
    /*printf("%f %f\n", t_new, x1_new);*/
    fprintf(out,"%f %f\n", t_new, x1_new);
  }
  fclose(out);
}
