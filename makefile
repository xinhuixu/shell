test: shell.c func.c
	gcc shell.c func.c -o test
clean:
	rm *~ *.o
run: test
	./test
