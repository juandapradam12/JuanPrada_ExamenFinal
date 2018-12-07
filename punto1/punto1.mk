# compilo con make -f punto1.mk


*.pdf : *.dat plots1.py
	python plots1.py

*.dat : punto1_c
	./punto1_c

punto1_c : punto1.c
	gcc -fopenmp punto1.c -lm -o punto1_c

clean :
	rm *.dat  *_c




