OBJECTS = trace.o window.o scene.o pathtracer.o rng.o

.phone: all run clean

all: a.out

run: a.out
	./a.out

clean:
	rm *.o
	rm a.out

%.o: %.cpp
	g++ -c -o $@ $^ -O3

a.out: ${OBJECTS}
	g++ -O3 -flto $^ -o a.out -lSDL2 -lm