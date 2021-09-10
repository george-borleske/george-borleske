#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dcdfile.h"

int testdcd(float ***dcd, char dcd_name[]) {
  //printf("entered testdcd \n");

  int i, j, k, l, m, nframes, natoms, fid, numlines, blocksize;
  float *x, *y, *z;
  char schar[4];
  DCDHeader dcd_header;
  FILE *dcdfile;

  //dcdfile = fopen("test2.dcd","rb");
  dcdfile = fopen(dcd_name,"rb");
  fid = fread(&i, sizeof(int),1,dcdfile);
  printf("opened dcd \n");

  dcd_header.fid = fid;
  if(i != 84) {
    printf(" wrong endianism. Stop! \n");
    exit(0);
  }

  fseek(dcdfile,0,SEEK_END);
  dcd_header.endoffile = ftell(dcdfile);
  fseek(dcdfile,4,SEEK_SET);

  fread(schar, sizeof(char),4,dcdfile);

  fread(&dcd_header.NSET, sizeof(int),1,dcdfile);

  fread(&dcd_header.ISTART, sizeof(int),1,dcdfile);
  
  fread(&dcd_header.NSAVC, sizeof(int),1,dcdfile);

  fseek(dcdfile,40,SEEK_SET);

  fread(&dcd_header.NAMNF, sizeof(int),1,dcdfile);

  fseek(dcdfile,84,SEEK_SET);

  fread(&i, sizeof(int),1,dcdfile);

  if(i==0) {
    dcd_header.charmm = 0;
  } else {
    dcd_header.charmm = 1; 
    dcd_header.charmm_extrablock = 0; 
    dcd_header.charmm_4dims = 0; 

    fseek(dcdfile,48,SEEK_SET);
    fread(&i, sizeof(int),1,dcdfile);
    if(i==1) dcd_header.charmm_extrablock = 1;

    fseek(dcdfile,52,SEEK_SET);
    fread(&i, sizeof(int),1,dcdfile);
    if(i==1) dcd_header.charmm_4dims = 1;
  }
  
  fseek(dcdfile,44,SEEK_SET);
  if(dcd_header.charmm==0)  fread(&dcd_header.DELTA, sizeof(double),1,dcdfile);
  else                      fread(&dcd_header.DELTA, sizeof(float), 1,dcdfile);
   
  fseek(dcdfile,92,SEEK_SET);
  
  fread(&i,  sizeof(int),1,dcdfile);
  fread(&numlines, sizeof(int),1,dcdfile);

  fseek(dcdfile,numlines*80,SEEK_CUR);
  fread(&i,  sizeof(int),1,dcdfile);

  fread(&i, sizeof(int),1,dcdfile);
  fread(&dcd_header.N, sizeof(int),1,dcdfile);
  fread(&i, sizeof(int),1,dcdfile);

  if(dcd_header.NAMNF != 0) {
    fread(&i, sizeof(int),1,dcdfile);
    fread(&dcd_header.FREEINDEXES, sizeof(int),dcd_header.N - dcd_header.NAMNF,dcdfile);
    fread(&i, sizeof(int),1,dcdfile);
  }

  nframes = dcd_header.NSET;
  natoms  = dcd_header.N;

  printf(" nframes = %d \n", nframes);
  printf(" natoms  = %d \n", natoms);
  //getchar();
  
  // allocate x, y, and z
  if( (x = (float *)malloc(sizeof(float) * natoms)) == NULL) {
     printf("ERROR: x malloc fails \n");
     return;
  }
  
  if( (y = (float *)malloc(sizeof(float) * natoms)) == NULL) {
     printf("ERROR: y malloc fails \n");
     return;
  }

  if( (z = (float *)malloc(sizeof(float) * natoms)) == NULL) {
     printf("ERROR: z malloc fails \n");
     return;
  }

  for(i=0; i<nframes; i++) {
    //printf("i = %d \n", i);
    if(dcd_header.charmm == 1 && dcd_header.charmm_extrablock==1) {
      fread(&blocksize, sizeof(int),1,dcdfile);
      fseek(dcdfile,blocksize,SEEK_CUR);
      fread(&blocksize, sizeof(int),1,dcdfile);
    }

    if(dcd_header.NAMNF==0) {
      fread(&blocksize, sizeof(int),1,dcdfile);
      fread(x, sizeof(float),blocksize/4,dcdfile);
      fread(&blocksize, sizeof(int),1,dcdfile);

      fread(&blocksize, sizeof(int),1,dcdfile);
      fread(y, sizeof(float),blocksize/4,dcdfile);
      fread(&blocksize, sizeof(int),1,dcdfile);

      fread(&blocksize, sizeof(int),1,dcdfile);
      fread(z, sizeof(float),blocksize/4,dcdfile);
      fread(&blocksize, sizeof(int),1,dcdfile);
    } 
    
    // Skip the 4th dimension, if present
    if(dcd_header.charmm ==1 && dcd_header.charmm_4dims==1) {
      fread(&blocksize, sizeof(int),1,dcdfile);
      fseek(dcdfile, blocksize, SEEK_CUR);
      fread(&blocksize, sizeof(int),1,dcdfile);
    }

    /*atom 1h8k
    if(i == nframes - 1) {
      printf("\n");
      for(j=natoms-10; j<natoms; j++) printf(" atom = %5d x = %12.4e y = %12.4e z = %12.4e \n", j+1, x[j], y[j], z[j]);
    }
    */
    //printf("test \n");
    //for(j=0; j<natoms; j++) printf(" atom = %5d x = %12.4e y = %12.4e z = %12.4e \n", j+1, x[j], y[j], z[j]);
    //getchar();
    for(j=0; j<natoms; j++){
      dcd[j][i][0] = x[j];
      dcd[j][i][1] = y[j];
      dcd[j][i][2] = z[j];
      //printf("j = %d \n",j);
      /*
      if(j == 30){
        printf("node 31 x coord on frame %d is %f \n",i+1,x[j]);
	getchar();
      }
      */
      
    }
    //printf("end of for loop \n");

    
  }
  fclose(dcdfile);
  return nframes;
}

