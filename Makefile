all: build run

build: 
	@mkdir -p out
	@gcc -o out/main main.c

run: 
	@./out/main