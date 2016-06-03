#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>

int main (int argc, char **argv){

  //Archivo de datos que se va a aproximar
  FILE *file;
  file=fopen(argv[1], "r");

  //Numero de filas y numero de columnas
  int n_rows;
  int n_columns;
  int i;

  //Asigna el numero de columnas y cuenta el de lineas
  n_columns=2;
  n_rows=count_lines(argv[1]);
 
  //Inicializa la matriz con los datos
  gsl_matrix *data=gsl_matrix_alloc (n_rows, n_columns);

  //Genera la matriz data con columna 1 de tiempos, columna 2 de distancia
  gsl_matrix_fscanf (file, data);

  //Generar el vector distance, con las distancias y el vector time con los tiempos separando la matriz data
  gsl_vector *distance=gsl_vector_alloc(n_rows);
  gsl_matrix_get_col(distance,data,1);
  gsl_vector *time=gsl_vector_alloc(n_rows);
  gsl_matrix_get_col(time,data,0);
  
  //Generar la matriz G con la primera columna de 1, la segunda t y la tercera t^2
  gsl_matrix *g=gsl_matrix_alloc(n_rows,3);
  fill_g(g,n_rows,time);
  
  //Calcula la transpuesta de g y la multiplica por g
  gsl_matrix *g_transposed_g=gsl_matrix_alloc(3,3);
  gsl_blas_dgemm(CblasTrans ,CblasNoTrans, 1.0, g, g, 0.0, g_transposed_g);
  
  //Calcula la inversa de la anterior
  gsl_matrix *inverse_of_g_transposed_g=gsl_matrix_alloc(3,3);
  invert(g_transposed_g,inverse_of_g_transposed_g);
  
  //Calcula G transpuesta y la multiplica por d
  gsl_vector *g_transposed_d=gsl_vector_alloc(3);
  gsl_blas_dgemv(CblasTrans,1.0, g, distance, 0.0, g_transposed_d);;
  
  //Calcula m, el vector con los parametros
  gsl_vector *m=gsl_vector_alloc(3);
  gsl_blas_dgemv(CblasNoTrans, 1.0, inverse_of_g_transposed_g, g_transposed_d, 0.0, m);
    
  //Exporta al archivo
  export(m);

  return 0;
}

int count_lines(char *filename)
{
  FILE *in;
 int n_rows;
 int c;
 if(!(in=fopen(filename, "r"))){
   printf("problem opening file %s\n", filename);
    exit(1);
 }
 n_rows=0;
 
 do{
   c=fgetc(in);
   if(c=='\n')
     n_rows++;
   
 }while(c!=EOF);
 
 fclose(in);
 return n_rows;
}

int fill_g(gsl_matrix *g,int size, gsl_vector *t){

  gsl_vector *column1=gsl_vector_alloc(size);
  gsl_vector *column3=gsl_vector_alloc(size);
  
  gsl_vector_set_all(column1,1);
  
  gsl_vector_memcpy(column3,t);
  gsl_vector_mul(column3,t);
  
  gsl_matrix_set_col(g,0,column1);
  gsl_matrix_set_col(g,1,t);
  gsl_matrix_set_col(g,2,column3);
  
  return 0;
  
}

int invert(gsl_matrix *matrix, gsl_matrix *inverse ){
  
  int s;
  gsl_permutation * perm = gsl_permutation_alloc (3);
  gsl_linalg_LU_decomp (matrix, perm, &s);
  gsl_linalg_LU_invert (matrix, perm, inverse);

  return 0;
}

int export(gsl_vector *m){

  FILE *out;
  out=fopen("parametros_movimiento.dat","w");
  fprintf(out,"%f %f %f",gsl_vector_get(m,0),gsl_vector_get(m,1),gsl_vector_get(m,2));
  fclose(out);

  return 0;
}
