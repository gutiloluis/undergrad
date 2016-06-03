#include <stdio.h>
#include <stdlib.h>

float *load_matrix(char *filename, int *n, int *m);
float *multiply(float *matrix_A, float *matrix_B, int row, int col);
void print_matrix(float *matrix, int row, int col);
float *sc_multiply(float *M, float s, int row, int col);
float *sum(float *A, float *B, int row, int col);
float *sum_id(float *M, int row, int col);
float *exponential(float *M, int row, int col);

int main(int argc, char **argv){

  float *M;
  int row, col;

  M = load_matrix(argv[1], &row, &col);
  printf("M\n");
  print_matrix(M,row,col);

  printf("exp(M)\n");
  print_matrix(exponential(M,row,col), row, col);

  return 0;
}
  
float *load_matrix(char *filename, int *n, int *m){
  float *matrix;
  FILE *in;
  int n_row, n_col;
  int i, j;
  
  if(!(in = fopen(filename, "r"))){
    fprintf(stderr, "Problem opening the file %s\n", filename);
    exit(1);
  }

  fscanf(in, "%d %d\n", &n_row, &n_col);
  printf("%d %d\n", n_row, n_col);

  matrix = malloc(sizeof(float)*n_row*n_col);
  
  for(i=0;i<n_row;i++){
    for(j=0;j<n_col;j++){
      fscanf(in, "%f", &matrix[i*n_col + j]);
    }
  }

  *n = n_row;
  *m = n_col;

  return matrix;
}
  
float *multiply(float *matrix_A, float *matrix_B, int row, int col){
    
  float *matrix_C = malloc(sizeof(double)*row*col);

  int i, j, k;
  float entry;

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      entry = 0;
      for(k=0;k<col;k++){
	entry += matrix_A[k+i*col]*matrix_B[j+k*col];
      }
      matrix_C[j + col*i] = entry;
    }
  }
  return matrix_C;
} 
void print_matrix(float *matrix, int row, int col){

  int i,j,pos;

  printf("\n");

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      pos = j + i*col;
      printf("%f ",matrix[pos]);
    }
    printf("\n");
  }
  printf("\n");
}

float *sum(float *A, float *B, int row, int col){
  int i, j;
  float *C = malloc(sizeof(float)*row*col);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      C[j+col*i] = A[j+col*i] + B[j+col*i];
    }
  }
  return C;
}

float *sc_multiply(float *M, float s, int row, int col){
  int i, j;
  float *C = malloc(sizeof(float)*row*col);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      C[j+col*i] = s*M[j+col*i];
    }
  }
  return C;
}

float *sum_id(float *M, int row, int col){
  int i, j;
  int pos;
  float *C = malloc(sizeof(float)*row*col);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      pos = j + col*i;
      if(i==j){
	C[pos]=1.0+M[pos];
      }else{
	C[pos]=M[pos];
      }
    }
  }
  return C;
}
  
float *exponential(float *M, int row, int col){

  float *E = malloc(sizeof(float)*row*col);
 
  E = sum_id(M,row,col);
  
  float *prev = M;
  float prevsc = 1.0;

  float *now;
  float nowsc;

  int n;
  float *summand;
  
  for(n=2;n<=20;n++){
    
    now = multiply(prev,M,row,col);
    nowsc = n*prevsc;
    
    summand = sc_multiply(now,1.0/nowsc,row,col);
    
    E = sum(E,summand,row,col);
    
    prev = now;
    prevsc = nowsc;
  }
  return E;
}

