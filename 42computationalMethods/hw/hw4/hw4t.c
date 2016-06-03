#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float *analyze_file(char *filename);
float *transpose(float *M, int rowM, int colM);
float *multiply(float *matrix_A, float *matrix_B, int rowA, int colA, int rowB, int colB, int *m, int *n);
float *cholesky(float *M, int dim);
float *forward_substitution(float *A,float *b,int dim);
float *back_substitution(float *A, float *b, int dim);

int main(void){
  
  FILE *in;
  in = fopen("names.dat", "r");
  if(!in){
    printf("Problems opening the file with the names\n");
    exit(1);
  }

  int i;
  char filename[50];
  
  char *theta;
  char *token;
  char *phi1;
  char *phi2;

  char line[2] = "_";
  char point[2] = ".";

  FILE *out;
  out = fopen("parameters.dat", "w");
  
  if(!out){
    printf("Problems opening the output file\n");
    exit(1);
  }

  for(i=0;i<1000;i++){

    fscanf(in, "%s\n", filename); 
    
    float *m = analyze_file(filename);

    strtok(filename, line);  
    strtok(NULL, line);
    
    theta = strtok(NULL, line);
    
    strtok(NULL, line);
    
    token = strtok(NULL, line);
    
    phi1 = strtok(token, point);
    
    phi2 = strtok(NULL, point);
    
    char phi[5];
    strcpy(phi, phi1);
    strcat(phi, ".");
    strcat(phi, phi2);
    
    if(m!=NULL){
      fprintf(out, "%s %s %f %f %f\n", theta, phi, m[0], m[1], m[2]);
    }

  }
  return 0;
}

float *analyze_file(char *filename){
  
  FILE *in;
  
  char Filename[50];
  strcpy(Filename, "Brahe-3141-f/");
  strcat(Filename, filename);

  in = fopen(Filename,"r");
  if(!in){
    printf("Problems opening the file %s\n", Filename);
    exit(1);
  }
  
  int rowG = 38;
  int colG = 3;
  
  float *d = malloc(sizeof(float)*rowG);
  float *t = malloc(sizeof(float)*rowG);
  float *G = malloc(sizeof(float)*rowG*colG);
  
  int i;
  float time, height;
  
  for(i=0;i<rowG;i++){
    fscanf(in, "%f %f\n", &time, &height);
    d[i] = height;
    t[i] = time;
    G[0 + colG*i] = 1.0;
    G[1 + colG*i] = time;
    G[2 + colG*i] = 0.5*time*time;
  }
  fclose(in);
  
  float *G_T;
  G_T = transpose(G,rowG,colG);  
  
  float *b;
  int rowb, colb;
  b = multiply(G_T, d, colG, rowG, rowG, 1, &rowb, &colb);

  float *A;
  int rowA, colA;
  A = multiply(G_T, G, colG, rowG, rowG, colG, &rowA, &colA);
  
  float *L = cholesky(A, rowA);
  
  float *y = forward_substitution(L, b, rowA);

  float *m = back_substitution(transpose(L, rowA, colA), y, rowA);

  float chi_squared = 0.0;
  for(i=0;i<rowG;i++){
    chi_squared += powf(d[i] - (m[0] + m[1]*t[i] + 0.5*m[2]*powf(t[i],2) ), 2);
  }

  if(chi_squared > 0.5){
    m = NULL;
  }
 
  return m;
}

float *transpose(float *M, int rowM, int colM){
  
  float *M_T = malloc(sizeof(float)*rowM*colM);

  int i, j;
  for(i=0;i<rowM;i++){
    for(j=0;j<colM;j++){
      M_T[i + j*rowM] = M[j + i*colM];
    }
  }
  return M_T;
}

float *multiply(float *matrix_A, float *matrix_B, int rowA, int colA, int rowB, int colB, int *m, int *n){
  
  if(colA!=rowB){
    fprintf(stderr, "Error: The given matrices cannot be multiplied\n");
    exit(1);
  }
  
  int rowC = rowA;
  int colC = colB;
  
  float *matrix_C = malloc(sizeof(double)*rowC*colC);

  int i, j, k;
  float entry;
  
  for(i=0;i<rowA;i++){
    for(j=0;j<colB;j++){
      entry = 0;
      for(k=0;k<colA;k++){
        entry += matrix_A[k+i*colA]*matrix_B[j+k*colB];
      }
      matrix_C[j + colC*i] = entry;
    }
  }
  *m = rowC;
  *n = colC;
  
  return matrix_C;
} 

float *cholesky(float *M, int dim){
  float *L = malloc(sizeof(float)*dim*dim);

  int i, j, k;
  float sum;
  for(i=0;i<dim;i++){
    for(j=0;j<=i;j++){
      
      sum = 0.0;
      
      if(j==i){
	for(k=0;k<j;k++){
	  sum += powf(L[k + i*dim],2);
	}
	L[j + i*dim] = sqrtf(M[j + i*dim] - sum);

      }else{
	
	for(k=0;k<j;k++){
	  sum += L[k + i*dim]*L[k + j*dim];
	}
	L[j + i*dim] = (M[j + i*dim] - sum)/L[j + j*dim];
      }   
    }
  }
  return L;
}

float *forward_substitution(float *A,float *b,int dim){
  
  float *x = malloc(sizeof(float)*dim);
  int i, j;
  float sum;
  for(i=0;i<dim;i++){
    sum = 0.0;
    for(j=0;j<i;j++){
      sum += A[j + dim*i]*x[j];
    }
    x[i] = (b[i] - sum)/A[i + dim*i];    
  }
  
  return x;
}
float *back_substitution(float *A, float *b, int dim){

  float *x = malloc(sizeof(float)*dim);
  int i, j;
  float sum;
  for(i=dim-1;i>=0;i--){
    sum = 0.0;
    for(j=i+1;j<dim;j++){
      sum += A[j + dim*i]*x[j];
    }
    x[i] = (b[i] - sum)/A[i + dim*i];
  }
  return x;
}
