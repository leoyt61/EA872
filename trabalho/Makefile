CLIENT_SOURCES = App/client.cpp src/Controllers/jogo/jogo.cpp src/Controllers/timer/timer.cpp Include/Controllers/jogo/json.hpp src/Controllers/imageprocessing/imageprocessing.cpp src/Models/personagem/personagem.cpp src/Models/cenarioJogo/cenarioJogo.cpp src/Models/bolinha/bolinha.cpp src/Models/textura/textura.cpp src/Models/teclado/teclado.cpp src/Views/view.cpp -lSDL2 -lSDL2_image -Isrc/ -lfreeimage -lpthread -lboost_system
SERVER_SOURCES = App/server.cpp src/Controllers/jogo/jogo.cpp src/Controllers/timer/timer.cpp Include/Controllers/jogo/json.hpp src/Controllers/imageprocessing/imageprocessing.cpp src/Models/personagem/personagem.cpp src/Models/cenarioJogo/cenarioJogo.cpp src/Models/bolinha/bolinha.cpp src/Models/textura/textura.cpp src/Models/teclado/teclado.cpp src/Views/view.cpp -lSDL2 -lSDL2_image -Isrc/ -lfreeimage -lpthread -lboost_system

all: server client

server:
	g++ -g -Wall -o server $(SERVER_SOURCES)

client:
	g++ -g -Wall -o client $(CLIENT_SOURCES)

zip: client
	zip -R ex3.zip Makefile *.cpp *.hpp *.png *jpeg

clean:
	rm -rf *.zip ./client ./server