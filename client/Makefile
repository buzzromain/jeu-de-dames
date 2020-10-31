build: src/client.c src/game.c src/main.c src/connector.c src/connector_utils.c src/utils.c
	gcc -o bin/client src/client.c src/game.c src/main.c src/connector.c src/connector_utils.c src/utils.c

run: bin/client
	./bin/client

buildandrun:
	clear && make build && make run