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

=== Base de données basique ===
-Format CSV
id,username,password,nb_won

id : identifiant unique dans la base de données.
username : nom d'utilisateur;
password: mot de passe utilisateur
nb_won : nombre de parties gagnés.

=== A ne pas oublier ===
-Faire en sorte que lorsqu'un utilisateur se deconnecter, cela quitte sa partie et notifie l'adversaire.
