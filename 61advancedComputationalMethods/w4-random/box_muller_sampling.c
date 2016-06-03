#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
int main(int argc, char **argv){

  int n_points = atoi(argv[1]);
  int i;
  srand48(n_points);

  double u1;
  double u2;
  double x;
  double y;
  
  for(i=0;i<n_points;i++){
    
    u1 = drand48();
    u2 = drand48();
    
    x = sqrt(-2*log(u2)) * cos(2*PI*u1);
    y = sqrt(-2*log(u2)) * sin(2*PI*u1);
    
    printf("%f\n%f\n",x,y);
  }
  return 0; 
}
