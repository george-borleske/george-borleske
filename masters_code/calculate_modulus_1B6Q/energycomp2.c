#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* x_(i,j) = x_i - x_j */

int energycomp2(float En[][9],float xyz[][4],int bond_nodes[][2], double bond_para[][2],int angle_nodes[][3],double angle_para[][2],int dihedral_nodes[][4],double dihedral_para[][2],char des2[][10],float charge2[],int num_nodes,float xyz0[][4], int testnode, int t, char rep2[][10], int num_tot_bd){

  /*
  ************************************************************************************************************
  * Compute the energy between bonded nodes, units of this potential energy will be KJ/mol
  ************************************************************************************************************
  */
  int i=0, loop=1, w=0;
  int j;
  float x1, y1, z1, force_const, norm, conv, x1_0, y1_0, z1_0;
  float bond_eng       = 0.0;
  float angle_eng      = 0.0;
  float dihedral_eng   = 0.0, dieng_this;
  float Coulomb_engr   = 0.0;
  float Coulomb_engs   = 0.0;
  float Coulomb_engs2  = 0.0;
  float Coulomb_engd   = 0.0;
  float Coulomb_this   = 0.0;
  float Coulomb_raw    = 0.0;
  float Coulomb_shift  = 0.0;
  float Coulomb_shift2 = 0.0;
  float Coulomb_dd     = 0.0;
  float total_eng      = 0.0;
  FILE  *fp;
  char  title[100];            /* title of text output */
  int   bonded;                /* output of check_bonds program telling if nodes i and j are bonded */
  int   npair;                 /* counts how many Coulombic interactions there are. This is double the true value */
  int   ncharge;               /* counts how many nodes have a charge */
  int   neg = 1;               /* neg should be 1. F_x,ij = force_const * x1 =  -F_x,ji and r_0,ij = -r_0,ji */

  while(loop==1){
    if (bond_nodes[i][0] > num_nodes || bond_nodes[i][1] > num_nodes || bond_nodes[i][0] == '\0') {
      loop=0;
      i= i-1;
    } else {
      x1           = xyz[bond_nodes[i][0]-1][1]  - xyz[bond_nodes[i][1]-1][1];  /* x-component of the distance between nodes */
      y1           = xyz[bond_nodes[i][0]-1][2]  - xyz[bond_nodes[i][1]-1][2];  /* y-component of the distance between nodes */
      z1           = xyz[bond_nodes[i][0]-1][3]  - xyz[bond_nodes[i][1]-1][3];  /* z-component of the distance between nodes */
      x1_0         = xyz0[bond_nodes[i][0]-1][1] - xyz0[bond_nodes[i][1]-1][1]; /* x-component of the initial distance between nodes */
      y1_0         = xyz0[bond_nodes[i][0]-1][2] - xyz0[bond_nodes[i][1]-1][2]; /* y-component of the initial distance between nodes */
      z1_0         = xyz0[bond_nodes[i][0]-1][3] - xyz0[bond_nodes[i][1]-1][3]; /* z-component of the initial distance between nodes */
      norm         = sqrtf(powf(x1,2) + powf(y1,2) + powf(z1,2));               /* distance between nodes */
      force_const  = bond_para[i][0] * (1-bond_para[i][1]/norm);                /* part of the Force (derivative of energy) that will remain constant no matter what the component is */
     
      total_eng += 0.5*bond_para[i][0]*powf(norm - bond_para[i][1],2);

      /*
      if(bond_nodes[i][0]==93) { 
        printf("first node (%s) = %d second node (%s) = %d \n", des2[bond_nodes[i][0]-1], bond_nodes[i][0], des2[bond_nodes[i][1]-1], bond_nodes[i][1]); 
        printf("have bond_const = %12.5e equlibrium dist = %12.5e force_const = %12.5e \n\n", bond_para[i][0], bond_para[i][1], force_const);
        getchar(); 
      }
      */
       
      /*
      if(bond_nodes[i][0] == 9000003 || bond_nodes[i][1] == 90000003){
	//printf("i is %d \n", i);
	printf("BOND ENERGY \n");
	printf("bonds are %d (%s) and %d (%s) \n", bond_nodes[i][0], des2[bond_nodes[i][0]-1], bond_nodes[i][1], des2[bond_nodes[i][1]-1]);
        printf("k_b is %12.5e \n",bond_para[i][0]);
        printf("equilibrium distance = %12.5e \n", bond_para[i][1]);
        printf("magnitude of vector length (norm) is %12.5e \n", norm);
        printf("equib dist/norm is %12.5e \n",bond_para[i][1]/norm);
        printf("bond constant is %12.5e at node %d \n",force_const,i+1);
        printf("x1 = %12.5e x1_0 = %12.5e \n", x1, x1_0);
        printf("Energy contribution to x-component = %12.5e \n\n", force_const * x1 * x1_0);
      }
      */

      if(strstr(des2[bond_nodes[i][0]-1], "BAS") != NULL && strstr(des2[bond_nodes[i][1]-1], "BAS") != NULL){      

        /* Derivative of energy wrt first backbone node (ith) */
        En[bond_nodes[i][0]-1][0] += force_const * x1 * x1_0 * 1; /* energy from F_x * r_0,x */
        En[bond_nodes[i][0]-1][1] += force_const * y1 * y1_0 * 1; /* energy from F_y * r_0,y */
        En[bond_nodes[i][0]-1][2] += force_const * z1 * z1_0 * 1; /* energy from F_z * r_0,z */

        En[bond_nodes[i][0]-1][3] += force_const * z1 * y1_0 * 1; /* energy from F_z * r_0,y */
        En[bond_nodes[i][0]-1][6] += force_const * y1 * z1_0 * 1; /* energy from F_y * r_0,z */

        En[bond_nodes[i][0]-1][4] += force_const * z1 * x1_0 * 1; /* energy from F_z * r_0,x */
        En[bond_nodes[i][0]-1][7] += force_const * x1 * z1_0 * 1; /* energy from F_x * r_0,z */

        En[bond_nodes[i][0]-1][5] += force_const * y1 * x1_0 * 1; /* energy from F_y * r_0,x */
        En[bond_nodes[i][0]-1][8] += force_const * x1 * y1_0 * 1; /* energy from F_x * r_0,y */


        /* Derivative of energy wrt second backbone node (jth) */
        /* neg should be 1. F_x,ij = force_const * x1 =  -F_x,ji and r_0,ij = -r_0,ji */
        En[bond_nodes[i][1]-1][0] += force_const * x1 * x1_0 * neg; /* energy from F_x * r_0,x */
        En[bond_nodes[i][1]-1][1] += force_const * y1 * y1_0 * neg; /* energy from F_y * r_0,y */
        En[bond_nodes[i][1]-1][2] += force_const * z1 * z1_0 * neg; /* energy from F_z * r_0,z */

        En[bond_nodes[i][1]-1][3] += force_const * z1 * y1_0 * neg; /* energy from F_z * r_0,y */
        En[bond_nodes[i][1]-1][6] += force_const * y1 * z1_0 * neg; /* energy from F_y * r_0,z */

        En[bond_nodes[i][1]-1][4] += force_const * z1 * x1_0 * neg; /* energy from F_z * r_0,x */
        En[bond_nodes[i][1]-1][7] += force_const * x1 * z1_0 * neg; /* energy from F_x * r_0,z */

        En[bond_nodes[i][1]-1][5] += force_const * y1 * x1_0 * neg; /* energy from F_y * r_0,x */
        En[bond_nodes[i][1]-1][8] += force_const * x1 * y1_0 * neg; /* energy from F_x * r_0,y */

      } else if(strstr(des2[bond_nodes[i][0]-1], "BAS") != NULL && strstr(des2[bond_nodes[i][1]-1], "SI") != NULL){

        /* Derivative of energy wrt first backbone node (ith) */
        En[bond_nodes[i][0]-1][0] += force_const * x1 * x1_0 * 1; /* energy from F_x * r_0,x */
        En[bond_nodes[i][0]-1][1] += force_const * y1 * y1_0 * 1; /* energy from F_y * r_0,y */
        En[bond_nodes[i][0]-1][2] += force_const * z1 * z1_0 * 1; /* energy from F_z * r_0,z */

        En[bond_nodes[i][0]-1][3] += force_const * z1 * y1_0 * 1; /* energy from F_z * r_0,y */
        En[bond_nodes[i][0]-1][6] += force_const * y1 * z1_0 * 1; /* energy from F_y * r_0,z */

        En[bond_nodes[i][0]-1][4] += force_const * z1 * x1_0 * 1; /* energy from F_z * r_0,x */
        En[bond_nodes[i][0]-1][7] += force_const * x1 * z1_0 * 1; /* energy from F_x * r_0,z */

        En[bond_nodes[i][0]-1][5] += force_const * y1 * x1_0 * 1; /* energy from F_y * r_0,x */
        En[bond_nodes[i][0]-1][8] += force_const * x1 * y1_0 * 1; /* energy from F_x * r_0,y */


      } else if(strstr(des2[bond_nodes[i][0]-1], "SI") != NULL && strstr(des2[bond_nodes[i][1]-1], "SI") != NULL){
        /* The partial derivivate of energy between side chain nodes wrt backbone node = 0 */
        /*
        } else {
          printf("problem occured between SI nodes \n");
        }
        */
      } else{
        /* @@@@@@@@@@@@@@@@@@@@@@ Problem with possible memory leak @@@@@@@@@@@@@@@@@@@@@
        printf("problem occured between nodes %d and %d \n",bond_nodes[i][0],bond_nodes[i][1]);
	printf("des are %s and %s \n", des2[bond_nodes[i][0]-1], des2[bond_nodes[i][1]-1]);
	printf("i = %d \n", i);
	*/
      }
    }
    i=i+1;
    
  }

  bond_eng = total_eng;
  //if(t==0) { printf(" t = %5d bond_eng = %12.4e \n", t, bond_eng); getchar(); }
  //angle_eng = bond_eng;

  /*
  for(i=90;i<100;i++){
    if(strstr(des2[i], "BAS") != NULL){
      printf("energy after bond at node %d is %f %f %f \n %f %f %f \n\n",i+1,En[i][0],En[i][1],En[i][2],En[i][3],En[i][4],En[i][5]);
    }
  } 
  getchar();
  */

  /*
  *********************************************************************************************************************
  * Output Energy after bond energy is added
  *********************************************************************************************************************
  */
  sprintf(title, "Energy_after_bond_%d.txt", testnode + 1);
  if( t == 0) {
    fp = fopen(title, "w");
  } else {
    fp = fopen(title, "a");
  }
  if (fp == NULL) {
    printf("can't open output file for energy of testnode after bond! \n");
  } else {
    // Angstroms
    fprintf(fp, "%d %f %f %f %f %f %f \n", t , En[testnode][0], En[testnode][1], En[testnode][2], En[testnode][3], En[testnode][4], En[testnode][5]);
  }
  fclose(fp);
  

  /*
  ************************************************************************************************************
  * Compute the energy between nodes that form an angle
  ************************************************************************************************************
  */
  loop=1;
  i=0;
  float x2,y2,z2,n1,n2,theta,ctheta,x2_0,y2_0,z2_0,stheta;
  float cross[3];
  float cross_leng;
  float testnode_c_ang[3][4];
  int testcount = 0;
  while(loop==1){
    if(angle_nodes[i][0] > num_nodes || angle_nodes[i][1] > num_nodes || angle_nodes[i][2] > num_nodes || angle_nodes[i][0] == '\0'){
      //printf("all done w/ angle energy \n");
      //printf("i is %d\n",i);
      loop = 0;
    } else {
      x1          = xyz[angle_nodes[i][0]-1][1] - xyz[angle_nodes[i][1]-1][1];   /* x-component of the distance between the first nodes 1 and 2; vector 1 */
      x2          = xyz[angle_nodes[i][2]-1][1] - xyz[angle_nodes[i][1]-1][1];   /* x-component of the distance between the first nodes 2 and 3; vector 1 */

      y1          = xyz[angle_nodes[i][0]-1][2] - xyz[angle_nodes[i][1]-1][2];   /* y-component of the distance between the first nodes 1 and 2; vector 1 */
      y2          = xyz[angle_nodes[i][2]-1][2] - xyz[angle_nodes[i][1]-1][2];   /* y-component of the distance between the first nodes 2 and 3; vector 2 */

      z1          = xyz[angle_nodes[i][0]-1][3] - xyz[angle_nodes[i][1]-1][3];   /* z-component of the distance between the first nodes 1 and 2; vector 2 */
      z2          = xyz[angle_nodes[i][2]-1][3] - xyz[angle_nodes[i][1]-1][3];   /* z-component of the distance between the first nodes 2 and 3; vector 2 */

      x1_0        = xyz0[angle_nodes[i][0]-1][1] - xyz0[angle_nodes[i][1]-1][1]; /* x-component of the initial distance between the first nodes 1 and 2; vec 1 */
      x2_0        = xyz0[angle_nodes[i][2]-1][1] - xyz0[angle_nodes[i][1]-1][1]; /* x-component of the initial distance between the first nodes 2 and 3; vec 1 */

      y1_0        = xyz0[angle_nodes[i][0]-1][2] - xyz0[angle_nodes[i][1]-1][2]; /* y-component of the initial distance between the first nodes 1 and 2; vec 1 */
      y2_0        = xyz0[angle_nodes[i][2]-1][2] - xyz0[angle_nodes[i][1]-1][2]; /* y-component of the initial distance between the first nodes 2 and 3; vec 2 */

      z1_0        = xyz0[angle_nodes[i][0]-1][3] - xyz0[angle_nodes[i][1]-1][3]; /* z-component of the initial distance between the first nodes 1 and 2; vec 2 */
      z2_0        = xyz0[angle_nodes[i][2]-1][3] - xyz0[angle_nodes[i][1]-1][3]; /* z-component of the initial distance between the first nodes 2 and 3; vec 2 */

      n1          = sqrtf(powf(x1,2) + powf(y1,2) + powf(z1,2));               /* distance between nodes 1 and 2 */
      n2          = sqrtf(powf(x2,2) + powf(y2,2) + powf(z2,2));               /* distance between nodes 2 and 3 */
      ctheta      = (x1 * x2 + y1 * y2 + z1 * z2) / (n1 * n2);                 /* This is equal is the angle between the three nodes/two vectors, from the dot product */
      cross[0]    = y1 * z2 - z1 * y2;                                         /* Fist component of the cross product */
      cross[1]    = -(x1 * z2 - z1 * x2);                                      /* Second component of the cross product */
      cross[2]    = x1 * y2 - y1 * x2;                                         /* Third component of the cross product */
      cross_leng  = sqrtf(powf(cross[0],2) + powf(cross[1],2) + powf(cross[2],2));   /* magnitude of the cross product */
      stheta      = cross_leng / (n1 * n2);                                    /* Sine Theta of the angle between the vectors */
      force_const = -angle_para[i][1] * (ctheta - cos(angle_para[i][0] * M_PI / 180)) * (-stheta) * (-1 / sqrtf(1 - powf((x1*x2 + y1*y2 + z1*z2)/ (n1 * n2),2))) / (n1 * n2);  /* part of the Force (derivative of energy) that will remain constant no matter which component of the force is taken. Extra negative is added since a negative is lostwhen computing cross_leng. */
      /*
      printf(" u = [%f %f %f ], v = [%f %f %f] \n", x1, y1, z1, x2, y2, z2);
      printf("cross product = [%f %f %f] \n", cross[0], cross[1], cross[2]);
      printf("stheta = %f \n", stheta);
      getchar();
      */
      angle_eng += .5 * angle_para[i][1] * powf(ctheta - cos(angle_para[i][0] * M_PI/180),2);  
      
      /*
      if(angle_nodes[i][0] == 65 || angle_nodes[i][1] == 65 || angle_nodes[i][2] == 65){
        //printf("i is %d\n", i+1);
        printf("t = %d \n", t);
	printf("ANGLE ENERGY \n");
	printf("nodes are %d, %d, %d \n", angle_nodes[i][0], angle_nodes[i][1], angle_nodes[i][2]);
        printf("n1 and n2 are %f and %f \n",n1,n2);
        printf("ctheta is %f \n", ctheta);
        printf("cos subtraction is %f \n",ctheta-cos(angle_para[i][0]*M_PI/180));
        printf("n1*n2 is %f \n", n1*n2);
        printf("equlibrium angle = %12.5e k_theta = %12.5e \n", angle_para[i][0], angle_para[i][1]);
        printf("x1 = %12.5e x1_0 = %12.5e \n", x1, x1_0);
        printf("x2 = %12.5e \n", x2);	
        printf("force constant is %12.5e at nodes %d, %d, %d \n",force_const,angle_nodes[i][0]+1,angle_nodes[i][1]+1,angle_nodes[i][2]+1);
        printf("energy contribution to x component = %12.5e \n\n", force_const * x1 * x1_0);
        getchar();	
      }
      */

      if(angle_nodes[i][0] == testnode+1 || angle_nodes[i][1] == testnode+1 || angle_nodes[i][2] == testnode+1){
        testnode_c_ang[testcount][0] = angle_nodes[i][0];
        testnode_c_ang[testcount][1] = angle_nodes[i][1];
        testnode_c_ang[testcount][2] = angle_nodes[i][2];
        testnode_c_ang[testcount][3] = ctheta;
        testcount = testcount + 1;
      }

      /* angles formed between backbone nodes */
      if(strstr(des2[angle_nodes[i][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[i][1]-1], "BAS") != NULL && strstr(des2[angle_nodes[i][2]-1], "BAS") != NULL){

        /* derivative of vector 1 wrt node 1 */
        En[angle_nodes[i][0]-1][0] += force_const * x1 * x1_0 * 1; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][0]-1][1] += force_const * y1 * y1_0 * 1; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][0]-1][2] += force_const * z1 * z1_0 * 1; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][0]-1][3] += force_const * z1 * y1_0 * 1; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][0]-1][6] += force_const * y1 * z1_0 * 1; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][0]-1][4] += force_const * z1 * x1_0 * 1; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][0]-1][7] += force_const * x1 * z1_0 * 1; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][0]-1][5] += force_const * y1 * x1_0 * 1; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][0]-1][8] += force_const * x1 * y1_0 * 1; /* Energy from F_x r_0,y vector 1 */


        /* derivative of vector 1 wrt node 2 */
        En[angle_nodes[i][1]-1][0] += force_const * x1 * x1_0 * neg; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][1]-1][1] += force_const * y1 * y1_0 * neg; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][1]-1][2] += force_const * z1 * z1_0 * neg; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][1]-1][3] += force_const * z1 * y1_0 * neg; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][1]-1][6] += force_const * y1 * z1_0 * neg; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][1]-1][4] += force_const * z1 * x1_0 * neg; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][1]-1][7] += force_const * x1 * z1_0 * neg; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][1]-1][5] += force_const * y1 * x1_0 * neg; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][1]-1][8] += force_const * x1 * y1_0 * neg; /* Energy from F_x r_0,y vector 1 */


        /* derivative of vector 2 wrt node 2 */
        En[angle_nodes[i][1]-1][0] += force_const * x2 * x2_0 * neg; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][1]-1][1] += force_const * y2 * y2_0 * neg; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][1]-1][2] += force_const * z2 * z2_0 * neg; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][1]-1][3] += force_const * z2 * y2_0 * neg; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][1]-1][6] += force_const * y2 * z2_0 * neg; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][1]-1][4] += force_const * z2 * x2_0 * neg; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][1]-1][7] += force_const * x2 * z2_0 * neg; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][1]-1][5] += force_const * y2 * x2_0 * neg; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][1]-1][8] += force_const * x2 * y2_0 * neg; /* Energy from F_x r_0,y vector 1 */


        /* derivative of vector 2 wrt node 3 */
        En[angle_nodes[i][2]-1][0] += force_const * x2 * x2_0 * 1; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][2]-1][1] += force_const * y2 * y2_0 * 1; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][2]-1][2] += force_const * z2 * z2_0 * 1; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][2]-1][3] += force_const * z2 * y2_0 * 1; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][2]-1][6] += force_const * y2 * z2_0 * 1; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][2]-1][4] += force_const * z2 * x2_0 * 1; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][2]-1][7] += force_const * x2 * z2_0 * 1; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][2]-1][5] += force_const * y2 * x2_0 * 1; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][2]-1][8] += force_const * x2 * y2_0 * 1; /* Energy from F_x r_0,y vector 1 */


      /* angles formed between 2 backbone nodes and 1 sidechain node */
      } else if(strstr(des2[angle_nodes[i][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[i][1]-1], "BAS") != NULL && strstr(des2[angle_nodes[i][2]-1], "SI") != NULL){

        /* derivative of vector 1 wrt node 1 */
        En[angle_nodes[i][0]-1][0] += force_const * x1 * x1_0 * 1; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][0]-1][1] += force_const * y1 * y1_0 * 1; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][0]-1][2] += force_const * z1 * z1_0 * 1; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][0]-1][3] += force_const * z1 * y1_0 * 1; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][0]-1][6] += force_const * y1 * z1_0 * 1; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][0]-1][4] += force_const * z1 * x1_0 * 1; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][0]-1][7] += force_const * x1 * z1_0 * 1; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][0]-1][5] += force_const * y1 * x1_0 * 1; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][0]-1][8] += force_const * x1 * y1_0 * 1; /* Energy from F_x r_0,y vector 1 */


        /* derivative of vector 1 wrt node 2 */
        En[angle_nodes[i][1]-1][0] += force_const * x1 * x1_0 * neg; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][1]-1][1] += force_const * y1 * y1_0 * neg; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][1]-1][2] += force_const * z1 * z1_0 * neg; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][1]-1][3] += force_const * z1 * y1_0 * neg; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][1]-1][6] += force_const * y1 * z1_0 * neg; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][1]-1][4] += force_const * z1 * x1_0 * neg; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][1]-1][7] += force_const * x1 * z1_0 * neg; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][1]-1][5] += force_const * y1 * x1_0 * neg; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][1]-1][8] += force_const * x1 * y1_0 * neg; /* Energy from F_x r_0,y vector 1 */


        /* derivative of vector 2 wrt node 2 */
        En[angle_nodes[i][1]-1][0] += force_const * x2 * x2_0 * neg; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][1]-1][1] += force_const * y2 * y2_0 * neg; /* Energy from F_y r_0,y vector 1 */
        En[angle_nodes[i][1]-1][2] += force_const * z2 * z2_0 * neg; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][1]-1][3] += force_const * z2 * y2_0 * neg; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][1]-1][6] += force_const * y2 * z2_0 * neg; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][1]-1][4] += force_const * z2 * x2_0 * neg; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][1]-1][7] += force_const * x2 * z2_0 * neg; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][1]-1][5] += force_const * y2 * x2_0 * neg; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][1]-1][8] += force_const * x2 * y2_0 * neg; /* Energy from F_x r_0,y vector 1 */


      /* angles formed between 1 backbone node and 2 sidechain nodes */
      } else if(strstr(des2[angle_nodes[i][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[i][1]-1], "SI") != NULL && strstr(des2[angle_nodes[i][2]-1], "SI") != NULL){

        /* derivative of vector 1 wrt node 1 */
        En[angle_nodes[i][0]-1][0] += force_const * x1 * x1_0 * 1; /* Energy from F_x r_0,x vector 1 */
        En[angle_nodes[i][0]-1][1] += force_const * y1 * y1_0 * 1; /* Energy from F_y r_0,y vector 1 */   
        En[angle_nodes[i][0]-1][2] += force_const * z1 * z1_0 * 1; /* Energy from F_z r_0,z vector 1 */

        En[angle_nodes[i][0]-1][3] += force_const * z1 * y1_0 * 1; /* Energy from F_z r_0,y vector 1 */
        En[angle_nodes[i][0]-1][6] += force_const * y1 * z1_0 * 1; /* Energy from F_y r_0,z vector 1 */

        En[angle_nodes[i][0]-1][4] += force_const * z1 * x1_0 * 1; /* Energy from F_z r_0,x vector 1 */
        En[angle_nodes[i][0]-1][7] += force_const * x1 * z1_0 * 1; /* Energy from F_x r_0,z vector 1 */

        En[angle_nodes[i][0]-1][5] += force_const * y1 * x1_0 * 1; /* Energy from F_y r_0,x vector 1 */
        En[angle_nodes[i][0]-1][8] += force_const * x1 * y1_0 * 1; /* Energy from F_x r_0,y vector 1 */
      } else {
        printf("something went wrong with angle energy \n");
      }
    }
    i=i+1;
  }

  sprintf(title, "Angle_of_testnode_%d.txt", testnode + 1);
  if( t == 0) {
    fp = fopen(title, "w");
  } else {
    fp = fopen(title, "a");
  }
  if (fp == NULL) {
    printf("can't open output file for angles! \n");
    getchar();
  } else {
    fprintf(fp, "%d %f %f %f %f %f %f %f %f %f %f %f %f \n", t, testnode_c_ang[0][0], testnode_c_ang[0][1], testnode_c_ang[0][2], testnode_c_ang[0][3],
                                              testnode_c_ang[1][0], testnode_c_ang[1][1], testnode_c_ang[1][2], testnode_c_ang[1][3],
                                              testnode_c_ang[2][0], testnode_c_ang[2][1], testnode_c_ang[2][2], testnode_c_ang[2][3]);
  }
  fclose(fp);

  //total_eng = angle_eng + bond_eng;
  /*
  if(t==0) { 
    printf(" angle energy computed w/ first set of angle parameters \n");
    printf(" t = %5d angle_eng = %12.4e \n\n", t, angle_eng); 
    getchar(); 
  }
  */


  /*
  *********************************************************************************************************************
  * Output Energy after angle energy is added
  *********************************************************************************************************************
  */
  sprintf(title, "Energy_after_angle_%d.txt", testnode + 1);
  if( t == 0) {
    fp = fopen(title, "w");
  } else {
    fp = fopen(title, "a");
  }
  if (fp == NULL) {
    printf("can't open output file for energy of testnode after bond! \n");
  } else {
    // Angstroms
    fprintf(fp, "%d %f %f %f %f %f %f \n", t , En[testnode][0], En[testnode][1], En[testnode][2], En[testnode][3], En[testnode][4], En[testnode][5]);
  }
  fclose(fp);


  /*
  ************************************************************************************************************
  * Compute the energy between nodes that form a dihedral angle
  ************************************************************************************************************
  */
  loop=1;
  i=0;
  float x01[3],x12[3],x32[3],x21[3],v[3],u[3],d1[3],d2[3],d3[3],normnormal[2];
  float x01_0[3], x12_0[3], x32_0[3], x21_0[3];
  while (loop == 1) {
    if (dihedral_nodes[i][0] > num_nodes || dihedral_nodes[i][1] > num_nodes || dihedral_nodes[i][2] > num_nodes || dihedral_nodes[i][3] > num_nodes || dihedral_nodes[i][0] == '\0') {
      loop = 0;
      //printf("done w/ dihedrals \n");
    } else {

    /* dihedral angle formed between 4 backbone nodes */
      if(strstr(des2[dihedral_nodes[i][0]-1], "BAS") != NULL && strstr(des2[dihedral_nodes[i][1]-1], "BAS") != NULL && strstr(des2[dihedral_nodes[i][2]-1], "BAS") != NULL && strstr(des2[dihedral_nodes[i][3]-1], "BAS") != NULL){

        /* vector 0 between nodes 0 and 1 */
        x01[0] = xyz[dihedral_nodes[i][0]-1][1] - xyz[dihedral_nodes[i][1]-1][1];
        x01[1] = xyz[dihedral_nodes[i][0]-1][2] - xyz[dihedral_nodes[i][1]-1][2];
        x01[2] = xyz[dihedral_nodes[i][0]-1][3] - xyz[dihedral_nodes[i][1]-1][3];

        /* vector -1 between nodes 1 and 2 */
        x21[0] = xyz[dihedral_nodes[i][2]-1][1] - xyz[dihedral_nodes[i][1]-1][1];
        x21[1] = xyz[dihedral_nodes[i][2]-1][2] - xyz[dihedral_nodes[i][1]-1][2];
        x21[2] = xyz[dihedral_nodes[i][2]-1][3] - xyz[dihedral_nodes[i][1]-1][3];

        /* vector 2 between nodes 2 and 3 */
        x32[0] = xyz[dihedral_nodes[i][3]-1][1] - xyz[dihedral_nodes[i][2]-1][1];
        x32[1] = xyz[dihedral_nodes[i][3]-1][2] - xyz[dihedral_nodes[i][2]-1][2];
        x32[2] = xyz[dihedral_nodes[i][3]-1][3] - xyz[dihedral_nodes[i][2]-1][3];

        /* vector 1 between nodes 1 and 2, but in oppoiste direction (used for second plane, not first plane) */
        x12[0] = xyz[dihedral_nodes[i][1]-1][1] - xyz[dihedral_nodes[i][2]-1][1];
        x12[1] = xyz[dihedral_nodes[i][1]-1][2] - xyz[dihedral_nodes[i][2]-1][2];
        x12[2] = xyz[dihedral_nodes[i][1]-1][3] - xyz[dihedral_nodes[i][2]-1][3];
	
        /* Initial vector 0 between nodes 0 and 1 */
        x01_0[0] = xyz0[dihedral_nodes[i][0]-1][1] - xyz0[dihedral_nodes[i][1]-1][1];
        x01_0[1] = xyz0[dihedral_nodes[i][0]-1][2] - xyz0[dihedral_nodes[i][1]-1][2];
        x01_0[2] = xyz0[dihedral_nodes[i][0]-1][3] - xyz0[dihedral_nodes[i][1]-1][3];

        /* Initial vector -1 between nodes 1 and 2 */
        x21_0[0] = xyz0[dihedral_nodes[i][2]-1][1] - xyz0[dihedral_nodes[i][1]-1][1];
        x21_0[1] = xyz0[dihedral_nodes[i][2]-1][2] - xyz0[dihedral_nodes[i][1]-1][2];
        x21_0[2] = xyz0[dihedral_nodes[i][2]-1][3] - xyz0[dihedral_nodes[i][1]-1][3];

        /* Initial vector 2 between nodes 2 and 3 */
        x32_0[0] = xyz0[dihedral_nodes[i][3]-1][1] - xyz0[dihedral_nodes[i][2]-1][1];
        x32_0[1] = xyz0[dihedral_nodes[i][3]-1][2] - xyz0[dihedral_nodes[i][2]-1][2];
        x32_0[2] = xyz0[dihedral_nodes[i][3]-1][3] - xyz0[dihedral_nodes[i][2]-1][3];	

	/* vector 1 between nodes 1 and 2, but in oppoiste direction (used for second plane, not first plane) */
        x12_0[0] = xyz0[dihedral_nodes[i][1]-1][1] - xyz0[dihedral_nodes[i][2]-1][1];
        x12_0[1] = xyz0[dihedral_nodes[i][1]-1][2] - xyz0[dihedral_nodes[i][2]-1][2];
        x12_0[2] = xyz0[dihedral_nodes[i][1]-1][3] - xyz0[dihedral_nodes[i][2]-1][3];  
	
        /* cross product of first two vectors, which is the vector normal to the first plane: v = x01 X x12 */
        v[0] = x01[1] * x21[2] - x01[2] * x21[1];
        v[1] = x01[2] * x21[0] - x01[0] * x21[2];
        v[2] = x01[0] * x21[1] - x01[1] * x21[0];
	
	/* test x23 X x12 */
	/*
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
        */

        /* cross product of last two vectors, which is the vector normal to the second plane: u = x32 X x21 */
        u[0] = x12[2] * x32[1] - x12[1] * x32[2]; //u is the vector normal to the second plane
        u[1] = x12[0] * x32[2] - x12[2] * x32[0];
        u[2] = x12[1] * x32[0] - x12[0] * x32[1];

        /* test x21 X x32 */        
	u[0] = -u[0];
	u[1] = -u[1];
	u[2] = -u[2];
        

        normnormal[0] = sqrtf(powf(v[0],2) + powf(v[1],2) + powf(v[2],2));                                 /* norm of u */
        normnormal[1] = sqrtf(powf(u[0],2) + powf(u[1],2) + powf(u[2],2));                                 /* norm of v */
        theta         = acos((v[0] * u[0] + v[1] * u[1] + v[2] * u[2]) / (normnormal[0] * normnormal[1])); /* the angle between u,v, ie angle between the two planes */

        /* derivative of theta */
        d1[0] = -x21[2] * u[1] + x21[1] * u[2]; /* with respect to x01[0] */
        d1[1] =  x21[2] * u[0] - x21[0] * u[2]; /* wrt x01[1] */
        d1[2] = -x21[1] * u[0] + x21[0] * u[1]; /* wrt x01[2] */

        d2[0] = -1 * ( x01[2] * u[1] - x01[1] * u[2]) + ( x32[2] * v[1] - x32[1] * v[2]); /* wrt x12[0], negative wrt x21[0], so first part is multiplied by -1 */
        d2[1] = -1 * (-x01[2] * u[0] + x01[0] * u[2]) + (-x32[2] * v[0] + x32[0] * v[2]); /* wrt x12[1] */
        d2[2] = -1 * ( x01[1] * u[0] - x01[0] * u[1]) + ( x32[1] * v[0] - x32[0] * v[1]); /* wrt x12[2] */

        d3[0] = (-x12[2] * v[1] + x12[1] * v[2]) * -1; /* wrt x32[0] */
        d3[1] = ( x12[2] * v[0] - x12[0] * v[2]) * -1; /* wrt x32[1] */
        d3[2] = (-x12[1] * v[0] + x12[0] * v[1]) * -1; /* wrt x32[2] */
      
        /* part of the Force (derivative of energy) that will remain constant no matter what the component is */
        force_const = dihedral_para[i][1] * sin(1 * theta - dihedral_para[i][0] * M_PI/180) * 1 * (-1 / sqrtf(1 - powf(cos(theta),2)));
        dieng_this = dihedral_para[i][1] * (1 + cos(1 * theta - dihedral_para[i][0] * M_PI/180));
        dihedral_eng += dieng_this;

        /*
	if(t==0) {

        printf(" v01 = %12.4e %12.4e %12.4e \n",  x01[0], x01[1], x01[2]);
        printf(" v21 = %12.4e %12.4e %12.4e \n",  x21[0], x21[1], x21[2]);
        printf(" v12 = %12.4e %12.4e %12.4e \n",  x12[0], x12[1], x12[2]);
        printf(" v32 = %12.4e %12.4e %12.4e \n\n",  x32[0], x32[1], x32[2]);

        printf("   v = %12.4e %12.4e %12.4e \n",  v[0], v[1], v[2]);
        printf("   u = %12.4e %12.4e %12.4e \n",  u[0], u[1], u[2]);

          printf("dihedral force constant is %12.5e at nodes %d (%s), %d (%s), %d (%s), %d (%s) \n",force_const,
	    dihedral_nodes[i][0],des2[dihedral_nodes[i][0]-1],dihedral_nodes[i][1],des2[dihedral_nodes[i][1]-1],
	    dihedral_nodes[i][2],des2[dihedral_nodes[i][2]-1],dihedral_nodes[i][3],des2[dihedral_nodes[i][3]-1]);
          printf("with repesentaions as %d (%s), %d (%s), %d (%s), %d (%s) \n",
            dihedral_nodes[i][0],rep2[dihedral_nodes[i][0]-1],dihedral_nodes[i][1],rep2[dihedral_nodes[i][1]-1],
	    dihedral_nodes[i][2],rep2[dihedral_nodes[i][2]-1],dihedral_nodes[i][3],rep2[dihedral_nodes[i][3]-1]);
          //printf("x01[2] = %12.5e x21[0] = %12.5e x01[0] = %12.5e x21[2] = %12.5e \n", x01[2], x21[0], x01[0], x21[2]);
          printf("k value: dihedral_para[i][1] = %12.5e  angle equilibrium: dihedral_para[i][0] = %12.5e \n", dihedral_para[i][1], dihedral_para[i][0]);
          printf("u[0] = %12.5e u[1] = %12.5e u[2] = %12.5e \n", u[0], u[1], u[2]);
          printf("v[0] = %12.5e v[1] = %12.5e v[2] = %12.5e \n", v[0], v[1], v[2]);
          printf("dot product between normals is %12.5e |v| = %12.5e |u| = %12.5e \n", v[0] * u[0] + v[1] * u[1] + v[2] * u[2], normnormal[0], normnormal[1]);
          printf("|n1| * |n2| = %12.5e \n", normnormal[0] * normnormal[1]);
          printf("cos(angle) = %12.5e \n", (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]) / (normnormal[0] * normnormal[1]));
          printf("angle in radions = %12.5e in degrees = %12.5e \n", theta, theta * 180/M_PI);
          printf("what i'm taking cos of for dihedral energy = %12.5e, in degrees = %12.5e \n", 1 * theta - dihedral_para[i][0] * M_PI/180, (1 * theta - dihedral_para[i][0] * M_PI/180) * 180/M_PI);
          printf("energy from this angle is = %12.5e \n\n",  dihedral_para[i][1] * (1 + cos(1 * theta - dihedral_para[i][0] * M_PI/180)));
          //getchar();
        }
	*/
      
        /* energy from vector 0 wrt to node 0 */
        En[dihedral_nodes[i][0]-1][0] += force_const * d1[0] * x01_0[0]; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][0]-1][1] += force_const * d1[1] * x01_0[1]; /* Energy from F_y * r_0,y */
        En[dihedral_nodes[i][0]-1][2] += force_const * d1[2] * x01_0[2]; /* Energy from F_z * r_0,z */

        /* take average of fx * ry and fy * rx since theoretically they should be equal */
        En[dihedral_nodes[i][0]-1][3] += .5 * force_const * d1[2] * x01_0[1]; /* Energy from F_z * r_0,y */
        En[dihedral_nodes[i][0]-1][3] += .5 * force_const * d1[1] * x01_0[2]; /* Energy from F_y * r_0,z */

        En[dihedral_nodes[i][0]-1][4] += .5 * force_const * d1[2] * x01_0[0]; /* Energy from F_z * r_0,x */
        En[dihedral_nodes[i][0]-1][4] += .5 * force_const * d1[0] * x01_0[2]; /* Energy from F_x * r_0,z */

        En[dihedral_nodes[i][0]-1][5] += .5 * force_const * d1[1] * x01_0[0]; /* Energy from F_y * r_0,x */
        En[dihedral_nodes[i][0]-1][5] += .5 * force_const * d1[0] * x01_0[1]; /* Energy from F_x * r_0,y */


        /* energy from vector 0 wrt node 1 */
        En[dihedral_nodes[i][1]-1][0] += force_const * d1[0] * x01_0[0] * neg; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][1]-1][1] += force_const * d1[1] * x01_0[1] * neg; /* Energy from F_y * r_0,y */
        En[dihedral_nodes[i][1]-1][2] += force_const * d1[2] * x01_0[2] * neg; /* Energy from F_z * r_0,z */

        En[dihedral_nodes[i][1]-1][3] += force_const * d1[2] * x01_0[1] * neg; /* Energy from F_z * r_0,y */
        En[dihedral_nodes[i][1]-1][6] += force_const * d1[1] * x01_0[2] * neg; /* Energy from F_y * r_0,z */

        En[dihedral_nodes[i][1]-1][4] += force_const * d1[2] * x01_0[0] * neg; /* Energy from F_z * r_0,x */
        En[dihedral_nodes[i][1]-1][7] += force_const * d1[0] * x01_0[2] * neg; /* Energy from F_x * r_0,z */

        En[dihedral_nodes[i][1]-1][5] += force_const * d1[1] * x01_0[0] * neg; /* Energy from F_y * r_0,x */
        En[dihedral_nodes[i][1]-1][8] += force_const * d1[0] * x01_0[1] * neg; /* Energy from F_0 * r_0,y */


        /* energy from vector 1 wrt node 1 */
        En[dihedral_nodes[i][1]-1][0] += force_const * d2[0] * x12_0[0]; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][1]-1][1] += force_const * d2[1] * x12_0[1]; /* Energy from F_y * r_0,y */ 
        En[dihedral_nodes[i][1]-1][2] += force_const * d2[2] * x12_0[2]; /* Energy from F_z * r_0,z */ 

        En[dihedral_nodes[i][1]-1][3] += force_const * d2[2] * x12_0[1]; /* Energy from F_z * r_0,y */ 
        En[dihedral_nodes[i][1]-1][6] += force_const * d2[1] * x12_0[2]; /* Energy from F_y * r_0,z */ 

        En[dihedral_nodes[i][1]-1][4] += force_const * d2[2] * x12_0[0]; /* Energy from F_z * r_0,x */ 
        En[dihedral_nodes[i][1]-1][7] += force_const * d2[0] * x12_0[2]; /* Energy from F_x * r_0,z */ 

        En[dihedral_nodes[i][1]-1][5] += force_const * d2[1] * x12_0[0]; /* Energy from F_y * r_0,x */ 
        En[dihedral_nodes[i][1]-1][8] += force_const * d2[0] * x12_0[1]; /* Energy from F_0 * r_0,y */ 


        /* energy from vector 1 wrt node 2 */
        En[dihedral_nodes[i][1]-1][0] += force_const * d2[0] * x12_0[0] * neg; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][1]-1][1] += force_const * d2[1] * x12_0[1] * neg; /* Energy from F_y * r_0,y */ 
        En[dihedral_nodes[i][1]-1][2] += force_const * d2[2] * x12_0[2] * neg; /* Energy from F_z * r_0,z */ 

        En[dihedral_nodes[i][1]-1][3] += force_const * d2[2] * x12_0[1] * neg; /* Energy from F_z * r_0,y */ 
        En[dihedral_nodes[i][1]-1][6] += force_const * d2[1] * x12_0[2] * neg; /* Energy from F_y * r_0,z */ 

        En[dihedral_nodes[i][1]-1][4] += force_const * d2[2] * x12_0[0] * neg; /* Energy from F_z * r_0,x */ 
        En[dihedral_nodes[i][1]-1][7] += force_const * d2[0] * x12_0[2] * neg; /* Energy from F_x * r_0,z */ 

        En[dihedral_nodes[i][1]-1][5] += force_const * d2[1] * x12_0[0] * neg; /* Energy from F_y * r_0,x */ 
        En[dihedral_nodes[i][1]-1][8] += force_const * d2[0] * x12_0[1] * neg; /* Energy from F_x * r_0,y */ 


        /* energy from vector 2 wrt node 2 */
        En[dihedral_nodes[i][2]-1][0] += force_const * d2[0] * x32_0[0] * neg; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][2]-1][1] += force_const * d2[1] * x32_0[1] * neg; /* Energy from F_y * r_0,y */ 
        En[dihedral_nodes[i][2]-1][2] += force_const * d2[2] * x32_0[2] * neg; /* Energy from F_z * r_0,z */ 

        En[dihedral_nodes[i][2]-1][3] += force_const * d2[2] * x32_0[1] * neg; /* Energy from F_z * r_0,y */ 
        En[dihedral_nodes[i][2]-1][6] += force_const * d2[1] * x32_0[2] * neg; /* Energy from F_y * r_0,z */ 

        En[dihedral_nodes[i][2]-1][4] += force_const * d2[2] * x32_0[0] * neg; /* Energy from F_z * r_0,x */ 
        En[dihedral_nodes[i][2]-1][7] += force_const * d2[0] * x32_0[2] * neg; /* Energy from F_x * r_0,z */ 

        En[dihedral_nodes[i][2]-1][5] += force_const * d2[1] * x32_0[0] * neg; /* Energy from F_y * r_0,x */ 
        En[dihedral_nodes[i][2]-1][8] += force_const * d2[0] * x32_0[1] * neg; /* Energy from F_x * r_0,y */ 


	/* energy from vector 2 wrt node 3 */
        En[dihedral_nodes[i][3]-1][0] += force_const * d2[0] * x32_0[0]; /* Energy from F_x * r_0,x */ 
        En[dihedral_nodes[i][3]-1][1] += force_const * d2[1] * x32_0[1]; /* Energy from F_y * r_0,y */ 
        En[dihedral_nodes[i][3]-1][2] += force_const * d2[2] * x32_0[2]; /* Energy from F_z * r_0,z */ 

        En[dihedral_nodes[i][3]-1][3] += force_const * d2[2] * x32_0[1]; /* Energy from F_z * r_0,y */ 
        En[dihedral_nodes[i][3]-1][6] += force_const * d2[1] * x32_0[2]; /* Energy from F_y * r_0,z */ 

        En[dihedral_nodes[i][3]-1][4] += force_const * d2[2] * x32_0[0]; /* Energy from F_z * r_0,x */ 
        En[dihedral_nodes[i][3]-1][7] += force_const * d2[0] * x32_0[2]; /* Energy from F_x * r_0,z */ 

        En[dihedral_nodes[i][3]-1][5] += force_const * d2[1] * x32_0[0]; /* Energy from F_y * r_0,x */ 
        En[dihedral_nodes[i][3]-1][8] += force_const * d2[0] * x32_0[1]; /* Energy from F_x * r_0,y */ 
      }
    }
    i=i+1;
  }

  /*
  *********************************************************************************************************************
  * Output Energy after dihedral energy is added
  *********************************************************************************************************************
  */
  sprintf(title, "Energy_after_dihedral_%d.txt", testnode + 1);
  if( t == 0) {
    fp = fopen(title, "w");
  } else {
    fp = fopen(title, "a");
  }
  if (fp == NULL) {
    printf("can't open output file for energy of testnode after bond! \n");
  } else {
    // Angstroms
    fprintf(fp, "%d %f %f %f %f %f %f \n", t , En[testnode][0], En[testnode][1], En[testnode][2], En[testnode][3], En[testnode][4], En[testnode][5]);
  }
  fclose(fp);

  //if(t==0) { printf(" t = %5d dihedral_eng = %12.4e \n", t, dihedral_eng); getchar(); }

  /*
  ************************************************************************************************************
  * Compute the Coulombic potential energy between nodes
  ************************************************************************************************************
  */
  npair         = 0;
  ncharge       = 0;
  float rcut    = 1.2;  // cutoff distance used
  float rswitch = 1;    // distance at which to apply the shifting function for distance-dependent dielectric
  float epsfact = 15;

  /* Conversion from Coulomb's constant k_e= N m^2/C^2 = J m / C^2 to kJ nm / e^2 mol*/
  conv = 138.9355;      /* This represtents 1/(4 * pi * e_0) in write-up */ 
  
  float dist;
  for(i=0;i<num_nodes;i++){
    if(charge2[i] != 0){
      ncharge++;
      for(j=0;j<num_nodes;j++){                                   /* Let j>i so each bonds energy is computed only once */
        if(charge2[j] !=0 && i != j){
          bonded = check_bonds(i,j,bond_nodes,num_tot_bd);        /* check to make sure nodes i and j are not bonded together. */
	  //bonded = 0;
	  if(0 == bonded) {
            x1   = xyz[i][1] - xyz[j][1];                         /* x component of the distance between the two nodes */
            y1   = xyz[i][2] - xyz[j][2];                         /* y component of the distance between the two nodes */
            z1   = xyz[i][3] - xyz[j][3];                         /* z component of the distance between the two nodes */

            x1_0 = xyz0[i][1] - xyz0[j][1];                       /* x-component of the initial distance between nodes */
            y1_0 = xyz0[i][2] - xyz0[j][2];                       /* y-component of the initial distance between nodes */
            z1_0 = xyz0[i][3] - xyz0[j][3];                       /* z-component of the initial distance between nodes */

            dist = sqrtf(powf(x1,2) + powf(y1,2) + powf(z1,2));   /* distance between the two nodes */

            /* only include Coulombic poftential energy from nodes within a distance of 1.2nm of each other */
            if(dist <= rcut){

              /* part of the Force (derivative of energy) that will remain constant no matter what the component is */
              force_const = -1 * charge2[i] * charge2[j] * conv / epsfact * powf(powf(x1,2) + powf(y1,2) + powf(z1,2),-3/2);
                
              //Coulomb_engr    += charge2[i] * charge2[j] * conv / (epsfact * dist);
              Coulomb_engs    += charge2[i] * charge2[j] * conv / (epsfact * dist) * (1 - 2 * powf(dist/rcut,2) + powf(dist/rcut,4));    

              if(strstr(des2[i], "BAS") != NULL){
                En[i][0]   += force_const * x1 * x1_0; /* Energy from F_x * r_x */
                En[i][1]   += force_const * y1 * y1_0; /* Energy from F_y * r_y */
                En[i][2]   += force_const * z1 * z1_0; /* Energy from F_z * r_z */
                En[i][3]   += force_const * z1 * y1_0; /* Energy from F_z * r_y */
                En[i][4]   += force_const * z1 * x1_0; /* Energy from F_z * r_x */
                En[i][5]   += force_const * y1 * x1_0; /* Energy from F_y * r_x */
                En[i][6]   += force_const * y1 * z1_0; /* Energy from F_y * r_z */
                En[i][7]   += force_const * x1 * z1_0; /* Energy from F_x * r_z */
                En[i][8]   += force_const * x1 * y1_0; /* Energy from F_x * r_y */
              } else if(strstr(des2[i-1], "BAS") != NULL){
                //En[i-1][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
                //En[i-1][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
                //En[i-1][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
                //En[i-1][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
                //En[i-1][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
                //En[i-1][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
              } else if(strstr(des2[i-2], "BAS") != NULL){
                //En[i-2][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
                //En[i-2][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
                //En[i-2][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
                //En[i-2][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
                //En[i-2][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
                //En[i-2][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
              } else if(strstr(des2[i-3], "BAS") != NULL){
                //En[i-3][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
                //En[i-3][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
                //En[i-3][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
                //En[i-3][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
                //En[i-3][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
                //En[i-3][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
              } else if(strstr(des2[i-4], "BAS") != NULL){
                //En[i-4][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
                //En[i-4][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
                //En[i-4][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
                //En[i-4][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
                //En[i-4][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
                //En[i-4][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
              } else {
                printf("something went wrong w/ Coulumbic potential \n");
              }
            }
          }
        }
      }
    }
  }
  //getchar();

  /*
  *********************************************************************************************************************
  * Output Energy after Coulombic energy is added
  *********************************************************************************************************************
  */
  sprintf(title, "Energy_after_Coulomb_%d.txt", testnode + 1);
  if( t == 0) {
    fp = fopen(title, "w");
  } else {
    fp = fopen(title, "a");
  }
  if (fp == NULL) {
    printf("can't open output file for energy of testnode after Coulomb! \n");
  } else {
    // Angstroms
    fprintf(fp, "%d %f %f %f %f %f %f \n", t , En[testnode][0], En[testnode][1], En[testnode][2], En[testnode][3], En[testnode][4], En[testnode][5]);
  }
  fclose(fp);

  return 0;
}
