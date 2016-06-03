#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_math.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_blas.h>
#include<gsl/gsl_cblas.h>
#include<gsl/gsl_linalg.h>
#include<gsl/gsl_eigen.h>

int main (int argc, char **argv){
  
  //Archivo de datos que se va a aproximar
  FILE *file;
  file=fopen(argv[1], "r");
  
  //Cuenta el numero de filas
  int n_dimensions;
  n_dimensions=3;

  int n_measurements;
  n_measurements=count_lines(argv[1]);

  //Genera la matriz de datos
  gsl_matrix *data=gsl_matrix_alloc (n_measurements, n_dimensions);
  gsl_matrix_fscanf (file, data);

  //Genera la matriz de covarianza
  gsl_matrix *covariance_matrix=gsl_matrix_alloc(n_dimensions,n_dimensions);
  fill_covariance_matrix(n_dimensions,n_measurements,data,covariance_matrix);

  //Encuentra los vectores propios
  gsl_matrix *eigenvectors=gsl_matrix_alloc(n_dimensions, n_dimensions);
  find_eigenvectors(n_dimensions, covariance_matrix, eigenvectors);

  //Exporta al archivo
  export(eigenvectors);

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

double find_average(int n_measurements, gsl_vector *dimension){

  int k;
  double sum;
  sum=0;
  for(k=0;k<n_measurements;k++){
    sum+=gsl_vector_get(dimension,k);
  }
  return sum/n_measurements;
}

double find_sum_term(int k, int n_measurements, gsl_vector *dimension_i, gsl_vector *dimension_j){

  double factor_i;
  factor_i=gsl_vector_get(dimension_i,k)-find_average(n_measurements, dimension_i);
  double factor_j;
  factor_j=gsl_vector_get(dimension_j,k)-find_average(n_measurements, dimension_j);

  return factor_i*factor_j;

}

double find_element(int n_measurements, int i, int j, gsl_matrix *data){

  gsl_vector *dimension_i=gsl_vector_alloc(n_measurements);
  gsl_matrix_get_col(dimension_i, data, i);

  gsl_vector *dimension_j=gsl_vector_alloc(n_measurements);
  gsl_matrix_get_col(dimension_j, data, j);

  int k;
  double sum;
  sum=0;
  for(k=0;k<n_measurements;k++){    
    sum+=find_sum_term(k, n_measurements, dimension_i, dimension_j);
  }
  return sum/(n_measurements-1);
}

int fill_covariance_matrix(int n_dimensions, int n_measurements, gsl_matrix *data, gsl_matrix *covariance_matrix){

  int i;
  int j;

  for(i=0;i<n_dimensions;i++){
    for(j=0;j<n_dimensions;j++){

      gsl_matrix_set(covariance_matrix, i, j, find_element( n_measurements, i, j, data));
    }
  }
  return 0;
}

int find_eigenvectors(int n_dimensions, gsl_matrix *covariance_matrix, gsl_matrix *eigenvectors){

  gsl_eigen_symmv_workspace *workspace=gsl_eigen_symmv_alloc(n_dimensions);
  gsl_vector *eigenvalues=gsl_vector_alloc(n_dimensions);

  gsl_eigen_symmv(covariance_matrix, eigenvalues, eigenvectors, workspace);

  gsl_eigen_symmv_sort (eigenvalues, eigenvectors, GSL_EIGEN_SORT_VAL_DESC);

  return 0;
}

int export(gsl_matrix *eigenvectors){
  
  FILE *out;
  out=fopen("autovectores_3D_data.dat","w");
  
  fprintf(out,"%f %f %f \n %f %f %f \n %f %f %f",gsl_matrix_get(eigenvectors, 0, 0), gsl_matrix_get(eigenvectors, 1, 0), gsl_matrix_get(eigenvectors, 2, 0), gsl_matrix_get(eigenvectors, 0, 1), gsl_matrix_get(eigenvectors, 1, 1), gsl_matrix_get(eigenvectors, 2, 1), gsl_matrix_get(eigenvectors, 0, 2), gsl_matrix_get(eigenvectors, 1, 2), gsl_matrix_get(eigenvectors, 2, 2));

  fclose(out);
 
  return 0;
}

