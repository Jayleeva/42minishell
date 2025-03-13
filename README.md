Projet de groupe du 4eme cercle du cursus 42

# Strategie
- Recreer un "serveur" et un "client" comme pour minitalk, mais combines dans le meme programme? On doit pouvoir envoyer des commandes au "serveur" qui les execute et nous rend la commande // affiche des messages d'erreurs. Utiliser signaux et bit shifting pour envoyer les prompt? ou scanf?
- Doit pouvoir traiter des commandes multiples grace au |: utiliser fork comme dans pipex. Peut-etre aussi besoin pour d'autres parties
- "your shell should have a working history": juste pas effacer les commandes precedentes? ou autre chose?
- gerer les chemins absolus ET relatifs ou utiliser PATH(?) pour chercher et lancer les executables
- gere les single et double quotes
- gerer les redirections(?) <, << (donner un delimiteur(?)), >, >> (rediriger en mode append(?))
- mode interactif? ctrl-C : rendre la commande (afficher un message, j'imagine un truc genre "user@post:~$"), ctrl-D : sort du shell, ctrl-\ : ne fait rien.
- pas besoin de gerer les eventuels leaks de readline(), mais les autres oui
- en cas de doute utiliser bash comme reference
