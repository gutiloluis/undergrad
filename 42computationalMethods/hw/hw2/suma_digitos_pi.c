#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  
  int n;

  n = atoi(argv[1]);
  
  if(n<0){
    printf("ERROR: n cannot be less than 0\n");
    exit(EXIT_FAILURE);
  }
  else if(n>2500000){
    printf("ERROR: n cannot be greater than 2500000\n");
    exit(EXIT_FAILURE);
  }

  FILE *in;
  in = fopen("Pi_2500000.txt","r");
  if(!in){
    printf("problems opening the file\n");
    exit(1);
  }
  
  char *l;

  if(n<=1){
    l = malloc(n*sizeof(char));
    fgets(l,n+1,in);
    printf("The sum of the first %d digits of Pi is: %c\n", n, l[0]);

  }else{
    l = malloc(n*sizeof(char));
    fgets(l,n+2,in);
    int i;
    int suma = 0;

    for(i=0;i<n+1;i++){
      if(l[i] != '.'){
	suma += (l[i]-'0');
      }
    }
    printf("The sum of the first %d digits of Pi is: %d\n", n, suma);
  }
  return 0;
}
