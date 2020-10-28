build: src/client.c src/game.c src/main.c src/connector.c
	gcc -o bin/client src/client.c src/game.c src/main.c src/connector.c

run: bin/client
	./bin/client

buildandrun:
	clear && make build && make run