TESTS = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25

build: KMP.o BMBC.o BMGS.o

KMP.o:
	gcc KMP.c -o KMP

BMBC.o:
	gcc BMBC.c -o BMBC

BMGS.o:
	gcc BMGS.c -o BMGS

run-p1:
	$(foreach var,$(TESTS),./KMP $(var);)

run-p2:
	$(foreach var,$(TESTS),./BMBC $(var);)

run-p3:
	$(foreach var,$(TESTS),./BMGS $(var);)

run-best:
	$(foreach var,$(TESTS),./BMGS $(var);)

clean:
	rm KMP
	rm BMBC
	rm BMGS
