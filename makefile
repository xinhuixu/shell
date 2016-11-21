test: shell.c
	gcc shell.c -o test
clean:
	rm *~
run: test
	./test
