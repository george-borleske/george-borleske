#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>
//#include "dcdfile.h"

int inverse(float cur_vec[][3], float inv_cur[][3], int res, int testnode){

  /* n is the number of rows */
  int n = 3;

  //printf("res = %d \n",res);

  int r;
  int c;
  int k;
  int i;
  int j;
  float v;
  int big; //stores which row has the biggest entry in the column we are looking at for pivoting w/in the rref
  float temp[n]; //temporary storage while rows are being swapped w/in pivoting
  float matrix[3][6];

  /* Concatinate cur_vec with identity matrix */
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      matrix[i][j] = cur_vec[i][j];
    }
  }
  
  matrix[0][3] = 1;
  matrix[0][4] = 0;
  matrix[0][5] = 0;

  matrix[1][3] = 0;
  matrix[1][4] = 1;
  matrix[1][5] = 0;

  matrix[2][3] = 0;
  matrix[2][4] = 0;
  matrix[2][5] = 1;

  /*
  ************************************************************************************************************
  * Convert matrix to an upper triangular form through Gaussian Elimination using pivoting
  ************************************************************************************************************
  */
  for(c=0;c<n-1;c++){
    /* find largest value in column */
    big=c; //begin w/ the biggest element of the column (including and below the diagonal) to be the diagonal element
    for(i=c+1;i<n;i++){
      
      if(fabs(matrix[big][c])<fabs(matrix[i][c])){ //compare elements in column below current biggest value and see if they are bigger
        big = i; //if they are bigger reset big to be this entry
     }
    }
    /* switch old top row with new top row */
    for(i=c;i<n+n;i++){
      temp[i] = matrix[c][i]; //temporarily store elements in the diagonal row of this column
      matrix[c][i] = matrix[big][i]; //replace w/ biggest row
      matrix[big][i] = temp[i]; //put old diagonal row in big row's place
      if(res==23){
        //printf("i is %d \n",i);
      }
    }

    /* upper triangular */
    for(r=c+1;r<n;r++){     
      v = matrix[r][c] / matrix[c][c];
      for(k=c;k<n+n;k++){
        matrix[r][k] = matrix[r][k] - v*matrix[c][k];
      }
    }
  }

  /*
  ************************************************************************************************************
  * Make the first non-zero element of each row 1 (normalize)
  ************************************************************************************************************
  */	
  for(i=0;i<n;i++){
    for(j=n+n;j>=0;j--){
      if(j>=i){
        if(i==2 && res==23){
          //printf("matrix[2][2] is %f,i=%d and j=%d \n",matrix[2][2],i,j);
        }
        matrix[i][j] = matrix[i][j] / matrix[i][i];
        if(i==2 && j==3 && res==23){
          //printf("martix[i][j] after is %f and matrix[i][i] is %f, i is %d \n",matrix[i][j],matrix[i][i],i);
        }
      }
    }
  }

  if(res == -testnode){
    printf("\n The upper trianglular matrix for node %d is:\n", res+1);
    printf("%f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5]);
    printf("%f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5]);
    printf("%f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5]);
    getchar();
  }

  /*
  ************************************************************************************************************
  * Convert matrix from upper triangular form to reduced row echelon
  ************************************************************************************************************
  */
  for(c=1;c<n;c++){
    for(r=c-1;r>-1;r--){     
      v = matrix[r][c];
      //if(res == testnode) printf("v = %f r = %d c = %d \n", v, r, c);
      for(k=c;k<n+n;k++){
        matrix[r][k] = matrix[r][k] - v * matrix[c][k];
      }
    }
  }

  if(res == -testnode){
    printf("\n The row reduced matrix for node %d is:\n", res+1);
    printf("%f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5]);
    printf("%f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5]);
    printf("%f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5]);
    getchar();
  }

  inv_cur[0][0] = matrix[0][3];
  inv_cur[0][1] = matrix[0][4];
  inv_cur[0][2] = matrix[0][5];

  inv_cur[1][0] = matrix[1][3];
  inv_cur[1][1] = matrix[1][4];
  inv_cur[1][2] = matrix[1][5];

  inv_cur[2][0] = matrix[2][3];
  inv_cur[2][1] = matrix[2][4];
  inv_cur[2][2] = matrix[2][5];

return 0;
}
