build: src/server.c src/game.c src/main.c src/request_handler.c src/response_handler.c
	gcc -o bin/server src/server.c src/game.c src/main.c src/request_handler.c src/response_handler.c

run: bin/server
	./bin/server

buildandrun:
	clear && make build && make run