#include <stdio.h>
#include <stdlib.h>

void update_u(double *u_new, double *u_past, int n_points, double delta_x, double delta_t, double c){
  int i;
  for(i=1;i<=n_points-1;i++){
    u_new[i] = u_past[i] - c*delta_t/delta_x*(u_past[i]-u_past[i-1]);
  }
}

void copy(double *u_new, double *u_past, int n_points){
  int i;
  for(i=0;i<n_points;i++){
    u_past[i] = u_new[i];
  }
}

void print_u(double *u, int n_points){
  int i;
  for(i=0;i<n_points;i++){
    printf("%.5e\n", u[i]);
  }
}

void initial_condition(double *u, int n_points, double delta_x){
  int i;
  double x;
  for(i=0;i<n_points;i++){
    x=i*delta_x;
    if(x<5.0){
      u[i]=1.0;
    } else {
      u[i]=0.0;
    }
  }
}

int main(){
  
  double delta_x=0.01;
  int n_x = (int)(10.0/delta_x);
  double delta_t = 1E-4;
  int n_t = (int)(0.0/delta_t);
  double c = 1.0;
  int i;

  double *u_past = malloc(n_x*sizeof(double));
  double *u_present = malloc(n_x*sizeof(double));

  initial_condition(u_past, n_x, delta_x);

  for(i=0;i<n_t;i++){
    update_u(u_present, u_past, n_x, delta_x, delta_t, c);
    copy(u_present, u_past, n_x);
  }

  print_u(u_past, n_x);
  return 0;
}
