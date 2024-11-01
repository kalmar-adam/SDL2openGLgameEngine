run:
	g++ -fdiagnostics-color=always -g *.cpp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL -o game
	./game