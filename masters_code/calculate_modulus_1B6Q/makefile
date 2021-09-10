default: a.out

objects = main.o bondvalue.o anglevalue.o dihedralvalue.o \
 readpsf.o strain2.o LJ.o testdcd.o ang_struct.h \
 dcdfile.h initial_positions.o energycomp2.o \
 cauchy_stress.o elastic_mod_iso.o elastic_mod_trans.o
a.out: $(objects)
	gcc -lm -o a.out $(objects)

main.o: main.c 

anglevalue.o: anglevalue.c ang_struct.h
bondvalue.o: bondvalue.c
dihedralvalue.o: dihedralvalue.c
energycomp2.o: energycomp2.c check_bonds.c
check_bonds.o: check_bonds.c
initial_positions.o: initial_positions.c
LJ.o: LJ.c 
readpsf.o: readpsf.c
#least_sq_i.o: least_sq_i.c
#least_sq_t.o: least_sq_t.c
strain2.o: strain2.c
testdcd.o: testdcd.c dcdfile.h
cauchy_stress.o: cauchy_stress.c
elastic_mod_iso.o: elastic_mod_iso.c
elastic_mod_trans.o: elastic_mod_trans.c

clean:
	rm *.o a.out *.txt
