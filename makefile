program = game

ifeq ($(i),)
	run_param = 
else
	run_param = < $(i)
endif

run: compile
	./$(program).out $(run_param)

compile: main
	gcc main.o -o $(program).out -lm
	rm *.o

main:
	gcc main.c -o main.o -c -lm

