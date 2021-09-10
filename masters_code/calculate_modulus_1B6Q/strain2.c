#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int strain2(float matrix[][7], float s[], int n, int p){

/* first entry of node 723 strain value is 0 causing the results to be nan */

  int r; //row
  int c; //column
  int k;
  int i;
  int j;
  float v;
  int big; //stores which row has the biggest entry in the column we are looking at for pivoting w/in the rref
  float temp[6]; //temporary storage while rows are being swapped w/in pivoting

/*
  if(p==23){
    printf("STRAIN: unsolved matrix at node %d is: \n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n\n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);
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
    printf("STRAIN: pre-pivoted matrix at node %d is: \n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n \n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);
*/

    big=c;
    for(i=c+1;i<6;i++){
      
      if(fabs(matrix[big][c])<fabs(matrix[i][c])){
        big=i;
      }
    }
    /* switch old top row with new top row */
    for(i=c;i<7;i++){
      temp[i]=matrix[c][i];
      matrix[c][i]=matrix[big][i];
      matrix[big][i]=temp[i];
    }
/*
    printf("STRAIN: pivoted matrix at node %d is: \n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n \n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);

    /* upper triangular */
    for(r=c+1;r<n;r++){     
      v=matrix[r][c]/matrix[c][c];
      for(k=c;k<n+1;k++){
        matrix[r][k]=matrix[r][k]-v*matrix[c][k];
      }
    }
  }
/*
  if(p==369 || p==10 || p==722 || p==117){
      printf("\n STRAIN:  uppertriangular matrix at node %d is: \n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);
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
        matrix[i][j]=matrix[i][j]/matrix[i][i];
      }
    }
  }
/*
  if(p==369 || p==10 || p==722 || p==117){
      printf("\n STRAIN:  normalized matrix at node %d is: \n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);
  }
*/
  /*
  ************************************************************************************************************
  * Solve the matrix. Put the solution in the last column
  ************************************************************************************************************
  */
  for(i=(n-2);i>=0;i--){
    for(k=n-1;k>i;k--){
      matrix[i][n]=matrix[i][n]-matrix[i][k]*matrix[k][n];
    }

    /* store the strain components in 's' */
    s[i]=matrix[i][n];
  }
  s[n-1]=matrix[n-1][n];

/*
  if(p==23){
    printf("STRAIN (with pivoting): The solved matrix of node %d is:\n",p+1);
    printf("%f %f %f %f %f %f %f \n",matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3],matrix[0][4],matrix[0][5],matrix[0][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3],matrix[1][4],matrix[1][5],matrix[1][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3],matrix[2][4],matrix[2][5],matrix[2][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3],matrix[3][4],matrix[3][5],matrix[3][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[4][0],matrix[4][1],matrix[4][2],matrix[4][3],matrix[4][4],matrix[4][5],matrix[4][6]);
    printf("%f %f %f %f %f %f %f \n",matrix[5][0],matrix[5][1],matrix[5][2],matrix[5][3],matrix[5][4],matrix[5][5],matrix[5][6]);

    printf("strain is %f %f %f %f %f %f \n \n \n \n",s[0],s[1],s[2],s[3],s[4],s[5]);
  }
*/

return 0;
}
