all:
	g++ main.cpp cpu.cpp instruction.cpp -o sim

run:
	./sim