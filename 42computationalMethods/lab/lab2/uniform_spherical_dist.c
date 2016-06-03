#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

int main(int argc, char **argv){

  int n;

  double *x;
  double *y;
  double *z;

  n = atoi(argv[1]);

  x = malloc(n*sizeof(double));
  y = malloc(n*sizeof(double));
  z = malloc(n*sizeof(double));

  int i;
  for(i=0;i<n;i++){

    double phi = 2.0*PI*drand48();
    double cos_theta = 2.0*drand48()-1.0;
    double theta = acos(cos_theta);
    
    double x_n = sin(theta)*cos(phi);
    double y_n = sin(theta)*sin(phi);
    double z_n = cos(theta);
    
    x[i]=x_n;
    y[i]=y_n;
    z[i]=z_n;

  }

  FILE *fileout;
  fileout = fopen("uniform_dist_data.dat","w");
  for(i=0;i<n;i++){
    fprintf(fileout, "%f\t%f\t%f\n", x[i], y[i], z[i]);
  }
  fclose(fileout);

  return 0;
}
