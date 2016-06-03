#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159264

double gauss(double x){
  return 1/(sqrt(2*PI))*exp(-pow(x,2)/2);
}
/*Another implementation is on the repository of the course*/
int main(int argc, char **argv){
   
  int n_points = atoi(argv[1]);
  srand48(n_points);
  
  double x = 0.0;
  double x_prime;

  int i;
  double beta;
  printf("%f\n",x);
  
  for(i=1;i<n_points;i++){
    
    x_prime = x + (drand48()-0.5)*0.1;
    beta = gauss(x_prime)/gauss(x);
    
    if(beta>1){
      x = x_prime;
    } else  if(drand48() < beta){
      x = x_prime;
    }
    printf("%f\n",x);
  }
  return 0;
}
