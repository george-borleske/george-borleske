#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int initial_positions(float xyz0[][4], char initial_name[]) {

  char *str1;
  str1 = (char *) malloc(10);
  char *str2;
  str2 = (char *) malloc(10);
  char *str3;
  str3 = (char *) malloc(10);
  char *str4;
  str4 = (char *) malloc(10);
  char *str5;
  str5 = (char *) malloc(10);
  char *str6;
  str6 = (char *) malloc(10);

  float num1, num2, num3, num4, num5, num6, num7;
  int a=1; 
  int b=1;
  int i=0;
  int temp;
  char str[100];
  int pos; /* position in the file being read */

  /*
  ************************************************************************************************************
  * Open pdb file
  ************************************************************************************************************
  */
  FILE *fp;
  //fp = fopen("1MV4_trans.pdb", "r");
  fp = fopen(initial_name, "r");
  if (fp == NULL) {
    printf("Can't open input file of initial positions!\n");
    exit(1);
  }

  while(a==1) {
    fgets(str, 100, fp);
    if(strstr(str, "CRYST1")) {
      a=0;
      while (b==1) {
	pos = ftell(fp);
        //printf("position is %d \n", pos);
        temp = fscanf(fp, "%s %f %s %s %s %f %f %f %f %f %f %s", str1, &num1, str2, str3, str4, &num2, &num3, &num4, &num5, &num6, &num7, str5);
	//printf("temp is %d, i is %d \n", temp, i);
        //printf("position after scan is %d \n", ftell(fp));

	if(12 == temp) {
          xyz0[i][0] = num1; // Node
	  xyz0[i][1] = num3; // x-position
	  xyz0[i][2] = num4; // y-position
	  xyz0[i][3] = num5; // z-position
	  i = i + 1;
	  //printf("\n");
	} else if(strstr(str1, "END")) {
          b = 0;
	  i = i - 1;
	} else if(1 == temp){
		/*
	  //fseek(fp, pos, SEEK_SET);
	  pos = ftell(fp);
	  printf("position after moving back is %d \n", pos);
          temp = fscanf(fp, "%s %f %s %s %s %f %f %f %f %f %f %s", str1, &num1, str2, str3, str4, &num2, &num3, &num4, &num5, &num6, &num7, str5);
          xyz0[i][0] = num1; // Node
	  xyz0[i][1] = num3; // x-position
	  xyz0[i][2] = num4; // y-position
	  xyz0[i][3] = num5; // z-position
	  i = i + 1;
	  printf("position after moving back then rescanning %d \n\n", ftell(fp));
	  */
	} else {
	  printf("problem reading initial positions \n");
	  exit(1);
	}
      }
    }
  }
  return 0;
}
