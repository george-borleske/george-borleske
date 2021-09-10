#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rref2_i.c"


int least_sq_i(float mat[][2], float LHS[], float young[], float poisson[], int res, int testnode, int t, int ls_size) {

  /* Goal is to solve the least squares probelm (A^(T) * A) * x = A^(T) b */

  //printf("entered LS \n");

  int i,j;
  int m = ls_size * 3; // number of rows of the matrix mat
  int n = 2;
  int k;
  float sum = 0;
  float multiply1[n][n];  // multiply1 = matT * mat
  float multiply2[n];     // multiply2 = matT * strain where strain is though of as a vector w/ two identical components
  float matT[n][m];       // transpose of matrix mat.
  float aug[n][n+1];      // augmented matrix [multiply1 | multiply2]
                          // has 5 columns for passing to rref2.c. if n=2 then only use the first three columns
  int testframe = -t;     // frame to show output for transversely isotropic material
  if(t > 2000) {
    testframe = t;
  }

  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      matT[j][i] = mat[i][j];
    }
  }
  
  if(res==testnode && t == testframe){
  //if(res==testnode){
    printf("mat: \n");
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++)
        printf("%f\t", mat[i][j]);
 
      printf("\n");
    }
    printf("\n");
  }
  
    
  /* Compute A^(T) * A */
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < m; k++) {
        sum = sum + matT[i][k] * mat[k][j];
	//printf("sum = %f \n", sum);
      }
 
      multiply1[i][j] = sum;
      sum = 0;
    }
  }

  
  if(res==testnode && t == testframe){
  //if(res==testnode){
    printf("multiply1 = matT * mat: \n");
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++)
        printf("%f\t", multiply1[i][j]);

      printf("\n");
    }
    printf("\n");
  }
  

  /* Compute A^(T) * b */
  sum = 0;
  //printf("strain = %f \n", strain);
  for (i = 0; i < n; i++) {
    for (k = 0; k < m; k++) {
      if(res==testnode && k == 0 && i ==0 && t == testframe) printf("b =:\n");
      if(res==testnode && i == 0 && t == testframe) printf("%f \n", LHS[k]);
      //if(res==testnode && k == 0 && i ==0) printf("b =:\n");
      //if(res==testnode && i == 0) printf("%f \n", LHS[k]);
      sum = sum + matT[i][k] * LHS[k];
      //printf("sum = %f \n", sum);
    } 
    multiply2[i] = sum;
    sum = 0;
  }

  
  if(res==testnode && t == testframe){
  //if(res==testnode){
    printf("multiply2 = matT * strain: \n");
    for (i = 0; i < n; i++) {
      printf("%f\t", multiply2[i]);
      printf("\n");
    }
    printf("\n");
  }
  

  for(i=0;i<n;i++){
    for(j=0;j<n;j++) {
      aug[i][j] = multiply1[i][j];
    }
  }
  for(i=0;i<n;i++){
    aug[i][n] = multiply2[i];
  }
  
  if(res==testnode && t==testframe){
  //if(res==testnode){
    printf("aug = [multiply1 | multiply2] : \n");
    for (i = 0; i < n; i++) {
      for (j = 0; j < n + 1; j++)
        printf("%f\t", aug[i][j]);
 
      printf("\n");
    }
    getchar();
  }

  

  rref2_i(aug,young,poisson,n,res,testnode,testframe,t);


  return 0;
}
