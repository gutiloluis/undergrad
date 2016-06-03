#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

  double theta_1;
  theta_1 = atoi(argv[1]);
  double phi_1;
  phi_1 = atoi(argv[2]);
  double theta_2;
  theta_2 = atoi(argv[3]);
  double phi_2;
  phi_2 = atoi(argv[4]);

  if(theta_1 < 0 || theta_1 > 180 || theta_2 < 0 || theta_2 > 180 || phi_1 < 0 || phi_1 > 360 || phi_2 < 0 || phi_2 > 360){
    
    printf("ERROR: The angles are outside the expected range\n");
    exit(EXIT_FAILURE);
  }
 
  printf("%f %f %f %f\n",theta_1, phi_1, theta_2, phi_2);

  return 0;
}
