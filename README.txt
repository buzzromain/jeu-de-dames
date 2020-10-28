=== Serveur === 
--- Compiler ---
make build
--- Lancer ---
make run

=== Client ===
--- Compiler ---
make build
--- Lancer ---
make run

--------------
REQUETE
--------------
message_type: [MESSAGE_TYPE]

[MESSAGE]
--------------

--------------
REPONSE
--------------
message_type: [MESSAGE_TYPE]
code: [CODE]

[MESSAGE]
--------------

Exemple de [MESSAGE_TYPE] : CREATE_ACCOUNT, GET_LAST_BOARD_GAME
Exemple de [CODE] : OK, USER_ALREADY_EXIST
Exemple de [MESSAGE] : 
game_id: 3
board: ```liste d'entier```
username: jean
password: superpassword

