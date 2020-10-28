# jeu-de-dames
Jeu de dames en réseau (socket TCP) écrit en langage C.

Serv minimaliste ayant pour base "https://broux.developpez.com/articles/c/sockets/#LV-C", donc qui mérite encore d'autre modification pour être plus que du plagiat (Mais je me voyais pas réinventer les serveur à attente multiple bloquante non plus...).
Par dessus ce serv j'ai fait un fork() dont :
- Le fils s'occupera de gérer tout les aspect lié au jeu .
- Et le pére tout les aspect communications .
Le pére communique actuellement les requêtes des clients au fils. 
J'ai fait ça pour éviter de faire faire des actions lourdes au serv. 

A suivre : 
- Isoler dans un autre fichier les aspects lié au jeux .
- Faire le jeux mdr 
- Interfacer le serv et le jeux 
- Paufiner
