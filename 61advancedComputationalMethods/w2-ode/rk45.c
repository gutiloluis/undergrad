#include <stdio.h>
#include <math.h>

double y_prime(double t, double y);
void step(double eps, double *h, double t, double y, double *t_step, double *y_step);
int main(void){
  
  double T = 10.0;
  double eps = 1.0e-5;
  double h = 0.2;
  double t;
  double y;
  
  double h_new;
  double t_step;
  double y_step;

  t = 0.0;
  y = 5.0;
  
  int i;
  while(t <= T){
    
    printf("%f %.15e\n", t, y);
    step(eps, &h, t, y, &t_step, &y_step);
    t += t_step;
    y += y_step;
    i++;
  }
  
  return 0;
}

double y_prime(double t, double y){
  return -y;
}

void step(double eps, double *h, double t, double y, double *t_step, double *y_step){
  
  double k1 = *h*y_prime(t,y);
  double k2 = *h*y_prime(t + 1.0/4.0**h, y + 1.0/4.0*k1);
  double k3 = *h*y_prime(t + 3.0/8.0**h, y + 3.0/32.0*k1 + 9.0/32.0*k2);
  double k4 = *h*y_prime(t + 12.0/13.0**h, y + 1932.0/2197.0*k1 - 7200.0/2197.0*k2 + 7296.0/2197.0*k3);
  double k5 = *h*y_prime(t + *h, y + 439.0/216.0*k1 - 8.0*k2 + 3680.0/513.0*k3 - 845.0/4104.0*k4);
  double k6 = *h*y_prime(t + 1.0/2.0**h, y - 8.0/27.0*k1 + 2.0*k2 - 3544.0/2565.0*k3 + 1859.0/4104.0*k4 - 11.0/40.0*k5);
  
  double y4_step = 25.0/216.0*k1 + 1408.0/2565.0*k3 + 2197.0/4104.0*k4 - 1.0/5.0*k5;
  double y5_step = 16.0/135.0*k1 + 6656.0/12825.0*k3 + 28561.0/56430.0*k4 - 9.0/50.0*k5 + 2.0/55.0*k6;
  
  double R = fabs(y4_step - y5_step)/(*h);
  double delta = pow(1.0/2.0*eps/R, 1.0/4.0);
  *h = delta**h;
  
  if(R <= eps){
    *t_step = *h;
    *y_step = y4_step;
  } else {
    *t_step = 0.0;
    *y_step = 0.0;
  }
}
