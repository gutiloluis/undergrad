#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double function(double x){
  return pow(x,-1.0/3.0) + x/10.0;
}

void integrate(int n_points, double *f){
  double integral;
  double x;
  int i;
  for(i=0;i<n_points;i++){
    x = drand48();
    f[i] = function(x);
    integral+=f[i];
  }
  integral/=n_points;
  printf("%.5e\n",integral);
}
    
		 
int main(int argc, char **argv){

  int M = atoi(argv[1]);
  int n_points = atoi(argv[2]);
  double x;
  double *f = malloc(n_points*sizeof(double));
  double integral=0;
  int i;
  
  for(i=0;i<M;i++){
    
    srand48(i);
    integrate(n_points,f);
  }
  return 0;
}
