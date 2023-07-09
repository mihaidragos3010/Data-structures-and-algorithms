build: 
	gcc -g -o tema1 functii-tabHash.c functiiLG.c tema1.c
run:
	./tema1

valgrind:
	valgrind --error-exitcode=1 --leak-check=yes --vgdb=no --track-origins=yes ./tema1 input/in0.txt
clean:
	rm -rf tema1
