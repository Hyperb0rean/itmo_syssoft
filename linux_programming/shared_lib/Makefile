all: solution

solution: solution.c 
	gcc solution.c -fPIC -ldl -Wl,-rpath=. -o solution
clean:
	-rm -rf *.o
	-rm -rf *.so