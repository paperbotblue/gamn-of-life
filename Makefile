all: 
	g++ ./*.cpp ./*.hpp -o gameoflife -lSDL2

run:
	./gameoflife
