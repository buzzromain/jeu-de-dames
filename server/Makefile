build: src/server.c src/game.c src/main.c src/request_handler.c src/response_handler.c src/utils.c src/db.c
	gcc -o bin/server src/server.c src/game.c src/main.c src/request_handler.c src/response_handler.c src/utils.c src/db.c

run: bin/server
	./bin/server

buildandrun:
	clear && make build && make run