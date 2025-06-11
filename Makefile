build:
	gcc -o main main.c physics/force.c physics/body.c physics/shape.c physics/collision.c graphics/graphics.c -lraylib -lm

run:
	./main