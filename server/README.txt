--- Compiler ---
make server 

--- Executer ---
./server

--- Utiliser la commande netcat pour tester le serveur --- 
echo "test" | nc localhost 8888
echo "blabla" | nc localhost 8888