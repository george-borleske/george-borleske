/* This code computes the elastic modulus of protein on the scale of amino acid.
 * This example is using the protein 1B6Q. Inputs are pdb and psf files describing the protein itself,
 * and a dcd file which was generated form a namd simulation. 
 * Included are several matlab codes to help visualize results.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
  int  num_nodes  = 120;             /* number of nodes */
  int  start_node = 1 - 1;         /* start node of the secondary structure of intrest. Either beta sheet or alpha helix */
  int  end_node   = 120 - 1;         /* end node of the secondary structure of intrest. Either beta sheet or alpha helix */
  int  testnode   = 64 - 1;         /* Node to sample to look at stress/strain */
  char dcd_name[100];               /* Title of the dcd file */
  char psf_name[100];               /* Title of the psf file */
  char initial_name[100];           /* Title of the intial position (in 'equilibrium') file */
  sprintf(dcd_name, "1B6Q_1-118.dcd");
  sprintf(psf_name, "1B6Q_CG.psf");
  sprintf(initial_name, "1B6Q_frame5.pdb");
  int output_pos       = 1;         /* 1 outputs node positions during simulation into text files. 0 Does not. */
  int output_cau_str   = 1;         /* 1 outputs cauchy stress, and strain computed from the deformation gradient into text files. 0 Does not. */
  int output_iso_eng   = 1;         /* 1 outputs engineering constants for isotropic material (Youngs, Poisson, Shear) into text files */
  int output_trans_eng = 1;         /* 1 outputs engineering constants for transversely isotropic materials into text files. */

  int    loop = 1;
  int    i=0, w=0;
  int    j, k, t;
  FILE  *fp, *f_str, *f_LJ;
  char   rep2[num_nodes][10];      /* includes info about the node such as charge and secondary structure, is changed during the program */
  char   rep3[num_nodes][10];      /* stores original copy of rep2 as is in the psf file */
  char   des2[num_nodes][10];      /* is the node a backbone or sidechain */
  char   amino2[num_nodes][10];    /* name of the amino acid */
  float  mass2[num_nodes];         /* mass of the node */
  float  charge2[num_nodes];       /* charge of the node */
  int    bond_nodes[1000][2];      /* The nodes of every bond in the system */
  double bond_para[1000][2];       /* 0 is the bond k value, 1 is the equilibrium distance */
  int    angle_nodes[1000][3];     /* 0-2 are the nodes that form an angle energy bond */
  double angle_para[1000][2];      /* 0 is the equilibrium angle, 1 is the k value */
  double angle_para2[1000][2];     /* 0 is the equilibrium angle, 1 is the k value */
  int    dihedral_nodes[1000][4];  /* 0-3 are the ndoes, 4 is the angle, and 5 is the k value */
  double dihedral_para[1000][2];   /* 0 is the equilibrium angle, 1 is the k value */
  int    Vb[1000][2];              /* bonded backbone nodes */
  float  En[num_nodes][9];         /* energy split into 9 components of F x r; 
				      components order: x, y, z, zy, zx, yx, yz, xz, xy; units are kJ/mol */
  float den;                       /* density of protein = 1170 kg/mol */
  char  title[100];                /* title of text output */
  float shear[2];                  /* Shear modulus G and G' (mu and mu_0) */
  float young[2];                  /* Young's modulus, E and E' */
  float poisson[2];                /* Poisson ratio v and v' */ 
  float stress[num_nodes][9];      /* stress tensor of whole protein */
  int   ls_size = 20;              /* how large will the moving frame be for the least squares computation of the elastic modulus */
  float LHS_t[ls_size*3];          /* Left hand side of equation when solving for engineering constants in elastic modulus of transversely isotropic material */
  float mat_t[ls_size*3][4];       /* mat is the overdetermined system solving for engineering constants of trans iso material and mat^T * mat * x =  mat^T * b */
  int   num_tot_bd;                /* number of total bonds between nodes */
  float def_grad_avg[3][3];        /* average of def_grad and def_grad2 */
  float xyz0[num_nodes][4];        /* initial positions of the protein after minimization (in equilibrium) */
  float xyz[num_nodes][4];         /* position of each node at the current timestep t */
                                   /* Column 0 of xyz is the node. */ 
                                   /* Columns 1-3 are the xyz coord of this node during the timestep. */
  float ***dcd;                    /* Position of every node at every frame */
  float ***def_fms;                /* Strain of backbone nodes at every frame */
  float ***str_fms;                /* Nominal Stress of backbone nodes at every frame */
  float ***str_cau;                /* Cauchy Stress of backbone nodes at every frame */

  /* Positions of each node, dimensions: node, frame, x/y/z component */
  if ((dcd = (float***) malloc(num_nodes * sizeof(float**))) == NULL){
   printf("Error: malloc fails at first part \n"); 
   printf("Program is being paused: ");
   getchar();
  }
  for (i=0;i<num_nodes;i++){
    if ((dcd[i] = (float**) malloc(10000 * sizeof(float*))) == NULL){
      printf("Error: malloc fails at second part \n");
      printf("Program is being paused: ");
      getchar();
    }
  }
  for (i=0;i<num_nodes;i++){
    for(j=0;j<10000;j++){
      if((dcd[i][j] = (float*) malloc(3 * sizeof(float))) == NULL){
	printf("Error: malloc fails at third part \n");
	printf("Program is being paused ");
	getchar();
      }
    }
  }

  /* Strain. dimensions: node, component of strain tensor, timestep */  
  if((def_fms = (float***) malloc(num_nodes * sizeof(float**))) == NULL) {
    printf("Error: malloc fails at first part of def_fms \n");
    printf("Program is being paused: ");
    getchar();
  }
  for(i=0;i<num_nodes;i++){
    if((def_fms[i] = (float**) malloc(6 * sizeof(float*))) == NULL) {
      printf("Error: malloc fails at second part of def_fms \n");
      printf("Program is being paused: ");
      getchar();
    }
  }
  for(i=0;i<num_nodes;i++){
    for(j=0;j<6;j++){
      if((def_fms[i][j] = (float*) malloc(5000 * sizeof(float))) == NULL) {
        printf("Error: malloc fails at third part \n");
        printf("Program is being paused \n");
        getchar();
      }
    }
  }

  /* Nominal Stress. dimensions: node, component of stress tensor, timestep */ 
  if((str_fms = (float***) malloc(num_nodes * sizeof(float**))) == NULL) {
    printf("Error: malloc fails at first part of def_fms \n");
    printf("Program is being paused: ");
    getchar();
  }
  for(i=0;i<num_nodes;i++){
    if((str_fms[i] = (float**) malloc(9 * sizeof(float*))) == NULL) {
      printf("Error: malloc fails at second part of def_fms \n");
      printf("Program is being paused: ");
      getchar();
    }
  }
  for(i=0;i<num_nodes;i++){
    for(j=0;j<9;j++){
      if((str_fms[i][j] = (float*) malloc(5000 * sizeof(float))) == NULL) {
        printf("Error: malloc fails at third part \n");
        printf("Program is being paused \n");
        getchar();
      }
    }
  }

  /* Cauchy Stress. dimensions: node, component of stress tensor, timestep */ 
  if((str_cau = (float***) malloc(num_nodes * sizeof(float**))) == NULL) {
    printf("Error: malloc fails at first part of def_fms \n");
    printf("Program is being paused: ");
    getchar();
  }
  for(i=0;i<num_nodes;i++){
    if((str_cau[i] = (float**) malloc(9 * sizeof(float*))) == NULL) {
      printf("Error: malloc fails at second part of def_fms \n");
      printf("Program is being paused: ");
      getchar();
    } 
  }
  for(i=0;i<num_nodes;i++){
    for(j=0;j<9;j++){
      if((str_cau[i][j] = (float*) malloc(5000 * sizeof(float))) == NULL) {
        printf("Error: malloc fails at third part \n");
        printf("Program is being paused \n");
        getchar();
      }
    }
  }

  sprintf(title, "node%d_stress.txt",testnode+1);
  fp = fopen(title, "w");
  fclose(fp);
  f_str = fopen(title, "a");

  sprintf(title, "Energy_after_LJ_%d.txt", testnode + 1);
  fp = fopen(title, "w");
  fclose(fp);
  f_LJ = fopen(title, "a");

  /* Reads information from the psf file */
  num_tot_bd = readpsf(rep2, des2, amino2, mass2, charge2, bond_nodes, angle_nodes, dihedral_nodes,psf_name);

  /* Find the mass of each backbone node, and include the mass from its sidechain nodes units are amu */
  w=0;
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      if(strstr(des2[i+1], "SI") != NULL){
        mass2[i]=mass2[i]+mass2[i+1];
        if(strstr(des2[i+2], "SI") != NULL){
          mass2[i]=mass2[i]+mass2[i+2];
          if(strstr(des2[i+3], "SI") != NULL){
            mass2[i]=mass2[i]+mass2[i+3];
            if(strstr(des2[i+4], "SI") != NULL){
              mass2[i]=mass2[i]+mass2[i+4];
            }
          }
        }
      }
    }
  }
  
  /* Convert the mass in amu to kg/mol; 1 amu = 10^(-3) kg/mol */
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      mass2[i] = mass2[i] * powf(10,-3);
    }
  }

  /* Stores rep2 into rep3 since rep2 will be changed */
  for(i=0;i<num_nodes;i++){
    for(j=0;j<5;j++){
      rep3[i][j]=rep2[i][j];
    }
  }

  /* Some of the representations have an extra letter in front. This shifts the rep so we can ignore the extra letter */
  for (i=0;i<num_nodes;i++) {
    if(rep2[i][0] != 'Q' && rep2[i][0] != 'P' && rep2[i][0] != 'N' && rep2[i][0] != 'C'){
      for(k=0;k<4;k++){
        rep2[i][k]=rep2[i][k+1];
      }
    }
  }

  /* Reads the x, y, and z coordinates of each node during each timestep from the dcd file. */
  /* dcd format */
  /* first dimension (n) is the node */
  /* second dimension (10000) is the frame */
  /* third dimension is the x, y, or z coordinate of that node on that frame */
  int nframes;
  nframes = testdcd(dcd, dcd_name);
  printf("nframes = %d \n",nframes);
  
  /* Compute Initial node positions. Units are 1 Angstrom = 1/10 Nanometers */
  initial_positions(xyz0,initial_name);
  //printf("Don't forget to change initial position txt \n");
  //getchar();

  /* Change units from Angstroms to Nanometers */
  for(i=0;i<num_nodes;i++){
    xyz0[i][1] = xyz0[i][1] / 10;
    xyz0[i][2] = xyz0[i][2] / 10;
    xyz0[i][3] = xyz0[i][3] / 10;
  }

  sprintf(title, "initial_positions.txt");
  fp = fopen(title, "w");
  if (fp == NULL) {
    printf("can't open output file for initial positions! \n");
  } else {
    // Nanometers
    for (i=0;i<num_nodes;i++) {
      fprintf(fp, "%f %f %f %f \n", xyz0[i][0], xyz0[i][1], xyz0[i][2], xyz0[i][3]);
    }
  }
  fclose(fp);

  i=0;
  loop = 1;
  w=0;
  /* Find the number of bonds between backbone nodes */
  while(loop==1){
    if (bond_nodes[i][0] > num_nodes || bond_nodes[i][1] > num_nodes || bond_nodes[i][0] == '\0') {
      loop = 0;
      i    = i-1;
    } else {
      if(strstr(des2[bond_nodes[i][0]-1], "BAS") != NULL && strstr(des2[bond_nodes[i][1]-1], "BAS") != NULL){
        Vb[w][0]=bond_nodes[i][0];
        Vb[w][1]=bond_nodes[i][1];
        w=w+1;
      }
    }
    i=i+1;
  }

  /*
  ************************************************************************************************************
  * Store Energy coefficients
  ************************************************************************************************************
  */
  /* Finds bond constants k_b and equilibrium distance */
  bondvalue(bond_nodes,bond_para,rep2,des2,amino2,num_nodes);

  /* Finds angle constants k_a and equilibrium angle */
  anglevalue(angle_nodes,angle_para,rep2,des2,amino2,num_nodes);

  /* Finds dihedral constants k_d and equilibrium dihedral angle */
  dihedralvalue(dihedral_nodes,dihedral_para,rep2,des2,amino2,num_nodes);

  /* Set energy to 0 */
  for(i=0;i<num_nodes;i++){
    for(j=0;j<6;j++){
      En[i][j]=0;
    }
  }
  for(i=0;i<num_nodes;i++){
    xyz[i][1] = xyz0[i][1];
    xyz[i][2] = xyz0[i][2];
    xyz[i][3] = xyz0[i][3];
  }
  
  t = -1;
  /* Computes the potential energies */
  LJ(En,rep2,rep3,des2,num_nodes,xyz0,xyz,bond_nodes,num_tot_bd,t,testnode);
  energycomp2(En,xyz,bond_nodes,bond_para,angle_nodes,angle_para,dihedral_nodes,dihedral_para,des2,charge2,num_nodes,xyz0,testnode,t, rep2,num_tot_bd);
 
/*
*********************************************************************************************************************
* Start of the for loop
*********************************************************************************************************************
*/
for(t = 0; t < nframes; t++){
  printf("begining of for loop, t is %d \n",t);
  /*Column 0 of xyz is the node. 
  * first dimension (n) is the node
  * second dimension (10000) is the frame
  * third dimension is the x, y, or z coordinate of that node on that frame */
  for(i=0;i<num_nodes;i++){
    xyz[i][0] = t;
    xyz[i][1] = dcd[i][t][0];
    xyz[i][2] = dcd[i][t][1];
    xyz[i][3] = dcd[i][t][2];
  }

  /* Convert units on coordinates from Angstroms to nanometers */
  for(i=0;i<num_nodes;i++){
    for(j=1;j<4;j++){
      xyz[i][j]=xyz[i][j]/10;
    }
  }

  /* Set energy to 0 */
  for(i=0;i<num_nodes;i++){
    for(j=0;j<9;j++){
      En[i][j]=0;
    }
  }

  /* Output the position of the testnode */
  if(output_pos) {
    sprintf(title, "Position_node_%d.txt", testnode+1);
    if( t == 1) {
      fp = fopen(title, "w");
    } else {
      fp = fopen(title, "a");
    }
    if (fp == NULL) {
      printf("can't open output file for position of testnode! \n");
    } else {
      // Angstroms
      fprintf(fp, "%f %f %f %f \n", xyz[testnode][0], xyz[testnode][1], xyz[testnode][2], xyz[testnode][3]);
    }
    fclose(fp);
  }
  
  
  /* Output the position of the backbone nodes */
  if(output_pos) {
    for(j=start_node;j<end_node;j++){
      if(strstr(des2[j], "BAS") != NULL && j != testnode){
        sprintf(title, "Position_node_%d.txt",j+1);
        if( t == 1) {
          fp = fopen(title, "w");
        } else {
          fp = fopen(title, "a");
        }
        if (fp == NULL) {
          printf("can't open output file for positions of nodes towards end of alpha helix! \n");
        } else {
          // Angstroms
          fprintf(fp, "%f %f %f %f \n", xyz[j][0], xyz[j][1], xyz[j][2], xyz[j][3]);
        }
        fclose(fp);
      }
    }
  } 
  

  /* Computes the potential energy from the bonds, angles, dihedrals, and Coulumbic potential */
  energycomp2(En,xyz,bond_nodes,bond_para,angle_nodes,angle_para,dihedral_nodes,dihedral_para,des2,charge2,num_nodes,xyz0,testnode,t, rep2,num_tot_bd);

  /* Computes the potential energy from the Lennard Jones potential */
  LJ(En,rep2,rep3,des2,num_nodes,xyz0,xyz,bond_nodes,num_tot_bd,t,testnode);

  /* Output Energy after Lennard Jones energy is added */
  fprintf(f_LJ, "%d %f %f %f %f %f %f \n", t , En[testnode][0], En[testnode][1], En[testnode][2], En[testnode][3], En[testnode][4], En[testnode][5]);

  /* Convert the potential energy in KJ/mol to J/mol; 1 KJ/mol = 10^(3) J/mol */
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      for(j=0;j<9;j++){
        En[i][j]= En[i][j] * powf(10,3);
      }
    }
  }
  
  /* Compute the stress by .5 * potential energy/(-volume) */
  /* Density is given in kg/m^3, negative sign comes from dividing by negative volume*/
  den = 1170;

  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      /* den/mass*En is the potential energy/volume */
      /* Units: (kg/m^3) / (kg/mol) * (J/mol) =  J/m^3 = Pa = 10^(-9) GPa */
      stress[i][0] = .5 * den / mass2[i] * En[i][0] * powf(10,-9); // the Fx,rx component of stress
      stress[i][1] = .5 * den / mass2[i] * En[i][1] * powf(10,-9); // the Fy,ry component of stress
      stress[i][2] = .5 * den / mass2[i] * En[i][2] * powf(10,-9); // the Fz,rz component of stress

      stress[i][3] = .5 * den / mass2[i] * En[i][3] * powf(10,-9); // the Fz,ry component of stress
      stress[i][4] = .5 * den / mass2[i] * En[i][4] * powf(10,-9); // the Fz,rx component of stress
      stress[i][5] = .5 * den / mass2[i] * En[i][5] * powf(10,-9); // the Fy,rx component of stress

      stress[i][6] = .5 * den / mass2[i] * En[i][6] * powf(10,-9); // the Fy,rz component of stress
      stress[i][7] = .5 * den / mass2[i] * En[i][7] * powf(10,-9); // the Fx,rz component of stress
      stress[i][8] = .5 * den / mass2[i] * En[i][8] * powf(10,-9); // the Fx,ry component of stress

    /* check to make sure no sidechain nodes have potential energy */
    } else if(strstr(des2[i], "SI") != NULL && En[i][0] != 0){
      //printf("Side chain node has energy at node %d with energy En[i][0] = \n",i+1,En[i][0]);

    /* check to make sure every backbone node has some potential energy */
    } else if(strstr(des2[i], "BAS") != NULL && En[i][0] == 0){
      printf("Backbone node has no energy at node %d \n",i+1);
    }
  }

  /* Store Nominal Stress for computation of Cauchy Stress outside t-loop */
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      //printf("i = %d \n",i);
      //getchar();
      for(j=0;j<9;j++){
	str_fms[i][j][t] = stress[i][j];
      }
    }
  }

  /* Output 1st Piola Kirchoff stress of testnode into text file. Units are Giga Pascals */
  fprintf(f_str, "%d %f %f %f %f %f %f %f %f %f\n", t, stress[testnode][0], stress[testnode][1], stress[testnode][2], stress[testnode][3], stress[testnode][4], stress[testnode][5], stress[testnode][6], stress[testnode][7], stress[testnode][8]);  
  /*
  ************************************************************************************************************
  * End of t-loop
  ************************************************************************************************************
  */
}
fclose(f_str);
fclose(f_LJ);

printf("t-loop ended \n");

cauchy_stress(dcd,str_fms,str_cau,def_fms,def_grad_avg,xyz0,des2,nframes,num_nodes,t,testnode,output_cau_str);

printf("finished cauchy stress \n");

/* Computation of elastic modulus from engineering constants for isotropic matrerial */
elastic_mod_iso(str_cau,def_fms,des2,young,poisson,shear,ls_size,nframes,num_nodes,testnode,output_iso_eng);

/* Computation of elastic modulus from engineering constants for transversely isotropic matrerial */
elastic_mod_trans(str_cau,def_fms,des2,young,poisson,shear,ls_size,nframes,num_nodes,testnode,start_node,end_node,output_trans_eng);

  printf("Hello world!\n");
  return 0;
}
