#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
/* Prints n_points of a function whose steps are Wiener processes */
int main(int argc, char **argv){

  int n_points = atoi(argv[1]);
  int i;
  srand48(n_points);

  double u1;
  double u2;
  double x;
  double y;

  double w=0.0;
  double t=0.0;
  double dt=0.01;
  double s = exp(t+w/2.0);
  double *W = malloc(n_points*sizeof(double));
  W[0] = w;
  /*printf("%f\n",w);*/
  printf("%f\n",s);
  
  for(i=1;i<n_points;i++){
    
    u1 = drand48();
    u2 = drand48();
    
    x = sqrt(-2*log(u2)) * cos(2*PI*u1);
    y = sqrt(-2*log(u2)) * sin(2*PI*u1);
    
    t+=dt;
    w = w+sqrt(dt)*x;
    s = exp(t+w/2.0);
    W[i] = w;
    /*printf("%f\n",w);*/
    printf("%f\n",s);
  }
  return 0;
}
