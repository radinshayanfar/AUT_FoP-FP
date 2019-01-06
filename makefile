program = game

ifeq ($(i),)
	run_param = 
else
	run_param = < $(i)
endif

run: compile
	./$(program).out $(run_param)

compile: main
	gcc main.o parameters.o user.o -o $(program).out -lm
	rm *.o

main: parameters user
	gcc main.c -o main.o -c -lm

parameters:
	gcc structures/sources/parameters.c -o parameters.o -c -lm

user:
	gcc structures/sources/user.c -o user.o -c -lm