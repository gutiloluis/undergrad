#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592

double *make_complete_walks(char *M);

int main(int argc, char **argv){

  char *M = argv[1];
  double *N = make_complete_walks(M);
  int *D = malloc(50*sizeof(int));

  FILE *fileout;
  char filename[50];
  strcpy(filename, "final_stats_3D_");
  strcat(filename, M);
  strcat(filename, ".dat");
  fileout = fopen(filename, "w");

  int i = 0;
  for(i=0;i<50;i++){
    int d = (i+1)*10;
    D[i] = d;
    fprintf(fileout, "%d\t%f\n", D[i], N[i]);
  }
  
  fclose(fileout);
  
  return 0;
}

double *make_complete_walks(char *M){
  
  int m = atoi(M);
  double *N = malloc(50*sizeof(double));
  int i;
  for(i=0;i<m;i++){
    
    srand48(i);
    int n_threshold = 0;
    int threshold = (n_threshold+1)*10;
    
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double D = 0.0;
    int n = 0;
  
    while(1){
    
      double phi = 2.0*PI*drand48();
      double cos_theta = 2.0*drand48()-1.0;
      double theta = acos(cos_theta);
      
      double dx = sin(theta)*cos(phi);
      double dy = sin(theta)*sin(phi);
      double dz = cos(theta);
      
      x = x+dx;
      y = y+dy;
      z = z+dz;
      D = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
      n++;
      
      if(D>=threshold){
	N[n_threshold] += n*1.0/(m*1.0);
	n_threshold++;
	threshold = (n_threshold+1)*10;
      }
      
      if(threshold > 500){
	break;
      }
    }
  }
  return N;
}
