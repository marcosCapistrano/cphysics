build:
	gcc -o main main.c physics/particle.c physics/force.c physics/body.c physics/shape.c -lraylib -lm

run:
	./main