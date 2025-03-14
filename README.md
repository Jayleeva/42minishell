Projet de groupe du 4ème cercle du cursus 42

# Stratégie
- recréer un "serveur" et un "client" comme pour minitalk, mais combinés dans le même programme? On doit pouvoir envoyer des commandes au "serveur" qui les exécute et nous rend la commande // affiche des messages d'erreurs. Utiliser signaux et bit shifting pour envoyer les prompt? ou scanf?
- doit pouvoir traiter des commandes multiples grâce au |: utiliser fork comme dans pipex. Peut-être aussi besoin pour d'autres parties. Comprendre | comme: exécuter la première commande, puis exécuter la deuxième en fonction du résultat de la première. "The output of each command in the pipeline is connected to the input of the next command via a pipe"
- "your shell should have a working history": juste pas effacer les commandes précédentes? ou autre chose?
- gérer les chemins absolus ET relatifs ou utiliser (define?) une variable PATH pour chercher et lancer les exécutables
- ne pas gérer les quotes non fermés ni les char spéciaux non requis comme \ et ; 
- gérer les single et double quotes
- gérer les redirections(?) <, << (donner un délimiteur(?)), >, >> (rediriger en mode append(?))
- gérer les variables d'environnement(?) qui doivent s'étendre à leurs valeurs(???)
- gérer ``$?`` qui doit s'étendre au statut exit(?) du foreground pipeline(?) exécuté en dernier 
- mode interactif(?) -> ctrl-C : rendre la commande (afficher un message, j'imagine un truc genre "user@post:~$" et attendre input), ctrl-D : sort du shell, ctrl-\ : ne fait rien. Doivent se comporter comme dans bash (que si pas en mode interactif?).
- implémenter les "builtin" suivants: echo (avec l'option -n), cd (avec path relatif et absolu, rien d'autre), pwd, export, unset, env (ni options ni arguments), exit. 
- droit à une globale mais ne doit permettre qu'à indiquer la réception d'un signal et ne doit ni accéder à ni fournir aucune autre donnée. Il est donc interdit de mettre une structure de type "normes" en globale.
- pas besoin de gérer les éventuels leaks de readline(), mais les autres oui
- en cas de doute utiliser bash comme référence
