program = game

ifeq ($(i),)
	run_param = 
else
	run_param = < $(i)
endif

run: compile
	@./$(program).out $(run_param)

problem_create:
	@cd choices ; \
	gcc problem_create.c -o problem_create.out -lm ; \
	./problem_create.out

compile: main
	@gcc *.o -o $(program).out -lm
	@rm *.o

main: parameters user list file leaderboard
	@gcc main.c -o main.o -c -lm

parameters:
	@gcc structures/sources/parameters.c -o parameters.o -c -lm

user:
	@gcc structures/sources/user.c -o user.o -c -lm

list:
	@gcc includes/sources/list.c -o list.o -c -lm

file:
	@gcc includes/sources/file.c -o file.o -c -lm

leaderboard:
	@gcc includes/sources/leaderboard.c -o leaderboard.o -c -lm