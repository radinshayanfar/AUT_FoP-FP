program = game

ifeq ($(i),)
	run_param = 
else
	run_param = < $(i)
endif

run: compile
	@./$(program).out $(run_param)

compile: main
	@gcc *.o -o $(program).out -lm
	@rm *.o

main: parameters user list
	@gcc main.c -o main.o -c -lm

parameters:
	@gcc structures/sources/parameters.c -o parameters.o -c -lm

user:
	@gcc structures/sources/user.c -o user.o -c -lm

list:
	@gcc includes/sources/list.c -o list.o -c -lm