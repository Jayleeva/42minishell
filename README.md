Projet de groupe du 4ème cercle du cursus 42

# Stratégie
Create a program that runs as long as the user needs it and closes on command. Use a loop that stops only once the user gives a closing input? And that lets the user give as many inputs as they want via readline().

Stock the inputs in a history via add_history(). Where? In what format? how can we access it? should work like in the terminal: call precedent command with a up arrow key. 

Handle echo, cd, pwd, export, unset, env, and exit. Recreate their bash behavior. 
  - we must access files beyond the one of the program then? how? by using env to get the path?
  - how do we execute the commands? with execve?

Handle ctrl c (SIGINT: interruption from keyboard), ctrl \ (SIGQUIT: quit from keyboard), ctrl d (pas de signal: met un EOF, et il faut lire et gerer le EOF).

- ctrl + C redonne un prompt que la ligne soit vide ou pleine ou qu'on soit dans une commande bloquante comme cat
- ctrl + D exit si la ligne est vide et redonne un prompt dans un commande bloquante comme grep ""
- ctrl + \ ne fait rien sauf dans une commande bloquante, il permet de kill le process avec un message d'erreur ("exit"?).


Source to understand environement variables better: https://opensource.com/article/19/8/what-are-environment-variables

Sources to understand how a terminal should work:

https://brennan.io/2015/01/16/write-a-shell-in-c/

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


when you type a command, the only reason your computer knows how to find the application corresponding to that command is that the PATH environment variable tells it where to look.

Steps:
- Create a loop that stops only when receiving an exit command, and that allows the user to give as many inputs as they want, one by one. DONE
- Implement a first, simple command like **pwd** for example: figure out how to find a path, and print it if found, print error if not.

env = affiche toutes les variables d'environnement, dont les PATH dont on a besoin pour les commandes. 
.
- recréer un "serveur" et un "client" comme pour minitalk, mais combinés dans le même programme? On doit pouvoir envoyer des commandes au "serveur" qui les exécute et nous rend la commande // affiche des messages d'erreurs. Utiliser signaux et bit shifting pour envoyer les prompt? pensé à scanf() mais pas autorisé. Rôle de la fonction readline(): lit et retourne la ligne du terminal.
- doit pouvoir traiter des commandes multiples grâce au |: utiliser fork comme dans pipex. Peut-être aussi besoin pour d'autres parties. Comprendre | comme: exécuter la première commande, puis exécuter la deuxième en fonction du résultat de la première. "The output of each command in the pipeline is connected to the input of the next command via a pipe"
- "your shell should have a working history": on doit pouvoir appeler la commande precedente en utilisant la touche fleche haut par ex.
- gérer les chemins absolus ET relatifs ou utiliser (define?) une variable PATH pour chercher et lancer les exécutables
- ne pas gérer les quotes non fermés ni les char spéciaux non requis comme \ et ; 
- gérer les single et double quotes
- gérer les redirections(?) <, << (donner un délimiteur(?)), >, >> (rediriger en mode append(?))
- gérer les variables d'environnement(?) qui doivent s'étendre à leurs valeurs(???)
- gérer ``$?`` qui doit s'étendre au statut exit(?) du foreground pipeline(?) exécuté en dernier : doit donner la valeur d'exit du dernier process.
- mode interactif(?) -> ctrl-C : rendre la commande (afficher un message, j'imagine un truc genre "user@post:~$" et attendre input), ctrl-D : sort du shell, ctrl-\ : ne fait rien. Doivent se comporter comme dans bash (que si pas en mode interactif?).
- implémenter les "builtin" suivants: **echo** (avec l'option **-n**), **cd** (avec path relatif et absolu, rien d'autre), **pwd**, **export**, **unset**, **env** (ni options ni arguments), **exit**. 
- droit à une globale mais ne doit servir qu'à indiquer la réception d'un signal et ne doit ni accéder à ni fournir aucune autre donnée. Il est donc interdit de mettre une structure de type "normes" en globale.
- pas besoin de gérer les éventuels leaks de readline(), mais les autres oui
- en cas de doute utiliser bash comme référence

Se renseigner sur les fonctions autorisées encore inconnues: https://web.mit.edu/gnu/doc/html/rlman_2.html

Pour utiliser les fonctions de readline, ajouter ``-lreadline`` aux flags de compilation.

```
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

int	main(void)
{
	static char *line_read = (char *)NULL;
	line_read = readline("Enter a line: ");
	add_history(line_read);
	printf("%s\n", ttyname(1));
}
```
