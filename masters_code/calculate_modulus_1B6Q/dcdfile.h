typedef struct DCDHeader{
   int fid;
   int endoffile;
   int NSET;
   int ISTART;
   int NSAVC;
   int NAMNF;
   int charmm;
   int charmm_extrablock;
   int charmm_4dims;
   int DELTA;
   int N;
   int FREEINDEXES;
}  DCDHeader;

typedef struct psfpar{
   int    res_id;
   int    res_id2;

   // bonded interactions: backbone-backbone
   double bcb_Kb[5];
   double bcb_db[5];
   double bcb_Ka[5];
   double bcb_phia[5];
   double bcb_Kd[5];
   double bcb_phid[5];
   double bcb_Kim[5];
   double bcb_phim[5];

   // bonded interactions: backbone-sidechains
   double bcbs_Kb[20];
   double bcbs_db[20];
   double bcbs_Ka[20];
   double bcbs_phia[20];
   double bcbs_Kd[20];
   double bcbs_phid[20];
   double bcbs_Kim[20];
   double bcbs_phim[20];

   // bonded interactions: among sidechains of the same residue
   double ss_Kb[20];
   double ss_db[20];
   double ss_Ka[20];
   double ss_phia[20];
   double ss_Kd[20];
   double ss_phid[20];
   double ss_Kim[20];
   double ss_phim[20];
}  psfpar;

/*
int what_is_resid(char *amino, char *des, char *rep);
int what_is_resid2(char *amino, char *des, char *rep){
    printf("entered this program");
    printf("%s", amino[2]);
}
*/



