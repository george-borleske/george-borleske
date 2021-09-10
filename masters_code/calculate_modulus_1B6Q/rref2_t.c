#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>
//#include "dcdfile.h"

int rref2_t(float matrix[][5], float young[], float poisson[], int n, int res, int testnode){

  /* n is the number of rows */

  //printf("res = %d \n",res);

  int r;
  int c;
  int k;
  int i;
  int j;
  float v;
  int big; //stores which row has the biggest entry in the column we are looking at for pivoting w/in the rref
  float temp[n]; //temporary storage while rows are being swapped w/in pivoting

/*
if(p==23){
      printf("unsolved matrix at node %d is: \n",res+1);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n\n \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/

  /*
  ************************************************************************************************************
  * Convert matrix to an upper triangular form through Gaussian Elimination using pivoting
  ************************************************************************************************************
  */
  for(c=0;c<n-1;c++){
    /* find largest value in column */

/*
if(p==23){
    printf("Elastic Modulus: pre-pivoted matrix at node %d, c = %d is: \n",res+1,c);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n\n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/


    big=c; //begin w/ the biggest element of the column (including and below the diagonal) to be the diagonal element
    for(i=c+1;i<n;i++){
      
      if(fabs(matrix[big][c])<fabs(matrix[i][c])){ //compare elements in column below current biggest value and see if they are bigger
        big = i; //if they are bigger reset big to be this entry
     }
    }
    /* switch old top row with new top row */
    for(i=c;i<n+1;i++){
      temp[i] = matrix[c][i]; //temporarily store elements in the diagonal row of this column
      matrix[c][i] = matrix[big][i]; //replace w/ biggest row
      matrix[big][i] = temp[i]; //put old diagonal row in big row's place
      if(res==23){
        //printf("i is %d \n",i);
      }
    }
/*
if(p==23){
    printf("Elastic Modulus: mid-pivoted matrix at node %d, c = %d is: \n",res+1,c);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n\n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/

    /* upper triangular */
    for(r=c+1;r<n;r++){     
      v = matrix[r][c] / matrix[c][c];
      for(k=c;k<n+1;k++){
        matrix[r][k] = matrix[r][k] - v*matrix[c][k];
      }
    }
/*
if(p==23){
    printf("STRAIN: post-pivoted matrix at node %d, c = %d is: \n",res+1,c);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n \n\n\n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/
  }
    /*
    ************************************************************************************************************
    * Convert matrix to an upper triangular form through Gaussian Elimination
    ************************************************************************************************************
    */
/* old
    for(c=0;c<n-1;c++){
      for(r=c+1;r<n;r++){
        v=matrix[r][c]/matrix[c][c];
        for(k=c;k<n+1;k++){
          matrix[r][k]=matrix[r][k]-v*matrix[c][k];
        }
      }
    }


if(res==60){
      printf("\n uppertriangular matrix at node %d is: \n",res+1);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/

  /*
  ************************************************************************************************************
  * Make the first non-zero element of each row 1 (normalize)
  ************************************************************************************************************
  */	

  for(i=0;i<n;i++){
    for(j=n;j>=0;j--){
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

/*
if(p==23){
      printf("\n normalized matrix at node %d is: \n",p+1);
    printf("%f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
    printf("%f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
    printf("%f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
}
*/
  /*
  ************************************************************************************************************
  * Solve the matrix. Put the solution in the last column
  ************************************************************************************************************
  */
 
  for(i=n-2;i>=0;i--){
    for(k=n-1;k>i;k--){
      matrix[i][n] = matrix[i][n] - matrix[i][k] * matrix[k][n];
    }
  }

  /* We have four unkowns for transversely isotropic material */
  poisson[0] = matrix[0][4] / matrix[1][4]; // v = a / b = v/(1+v) / 1/(1+v)
  poisson[1] = matrix[2][4] / matrix[3][4]; // v' = c / d = v'/E' / 1/E'
  young[1]   = 1 / matrix[3][4];            // E' = 1 / d = 1 / (1/E')

  if(res==-testnode){
    printf("\n The solved matrix for node %d is:\n", res+1);
    printf("%f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4]);
    printf("%f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4]);
    printf("%f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4]);
    printf("%f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4]);
    printf("young[1] = %f poisson[1] = %f poisson[0] = %f \n", young[1], poisson[1], poisson[0]);
    //getchar();
  }

return 0;
}
