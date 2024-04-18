all: build run

build: 
	@mkdir -p out
	@gcc -c ArvoreAVL.c
	@mv *.o out
	@gcc -o out/main main.c out/ArvoreAVL.o

run: 
	@./out/main