#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

float *random_walks(int M, int N_max);
float random_walk(int N);

int main(void){
  
  int M = 100;
  int N_max = 1000;

  float *averages = random_walks(M, N_max);

  FILE *fileout;
  fileout = fopen("data.dat","w");
  int i;

  for(i=0;i<N_max;i++){
    fprintf(fileout, "%f\n", averages[i]);
  }

  return 0;

}

float random_walk(int N){

  int i;
  float x = 0;
  float y = 0;
  float dx, dy;
  for(i=0;i<N;i++){
    float theta = 2*PI*drand48();
    dx = cos(theta);
    dy = sin(theta);
    x+=dx;
    y+=dy;
  }
  return sqrt(pow(x,2)+pow(y,2));
}    

float *random_walks(int M, int N_max){
  
  float *averages = malloc(sizeof(float)*N_max);
  int i, j;

  for(i=0;i<N_max;i++){
    float average = 0.0;
    for(j=0;j<M;j++){
      srand48(i+M*j);
      average += random_walk(i+1);
    }
    averages[i] = average/M;
  }
  return averages;
}
