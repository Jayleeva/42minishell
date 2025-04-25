Projet de groupe du 4ème cercle du cursus 42

# HOW TO MAKE A MERGE REQUEST

- Work from your branch. 
- Once you're done, push: ``git add *``, ``git commit -m ""``, ``git push`` (if first push from this branch: ``git push --set-upstream origin yourbranch``).
- Go on the github page, on "branches", and select yours. Click on the "x commits ahead of" line. If it's not possible to automatically merge, you will have to choose what code to keep and what code to discard: don't hesitate to check with me if you think it needs discussion or if you need clarifications. Once it's possible to merge, click on "create pull request", then "merge pull request", "confirm merge".
- Pull to have the merged version locally: ``git pull``. If too complicated, suppress your local copy and reclone it: ``git clone``. 


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

On doit pouvoir utiliser les commandes qui existent dans les PATH et les executer avec execve(). On doit pouvoir lancer un programme (.sh, so_long, minishell!, ...) depuis minishell.

On peut lancer minishell en mode interactif ou non interactif (?). Pour lancer en non interactif, il faut ajouter le flag -c dans l'execution, d'ou la verification arg == 3 (pourquoi 3? le nom du programme, le flag, et?). Je ne sais pas a quoi ca sert ni si c'est vraiment demande. Aucun souvenir d'avoir du tester ca en eval; le sujet precise comment handle les ctrl en mode interactif, mais rien sur le mode non interactif.

Source to understand environement variables better: https://opensource.com/article/19/8/what-are-environment-variables

Sources to understand how a terminal should work:

https://brennan.io/2015/01/16/write-a-shell-in-c/

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf


when you type a command, the only reason your computer knows how to find the application corresponding to that command is that the PATH environment variable tells it where to look. Les commandes ont besoin des differents paths de la norme PATH? comment je sais lequel exactement, et commentj'y accede?

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


# Readline
Pour utiliser les fonctions de readline, ajouter ``-lreadline`` aux flags de compilation. 

Dans le header, ajouter les includes suivants:

```
#include <readline/readline.h>
#include <readline/history.h>
```

# Recevoir des inputs
Basiquement, on appelle **readline()** dans une boucle infinie. Un break l'arrête si l'input est interrompu par un EOF (``ctrl+D``).

Attention: d'autres façon de fermer le programme devront être gérées: la commande ``exit`` et le raccourci clavier ``ctrl+\`` (si pas dans une commande bloquante).

```
int	main(void)
{
	char *input;
	
	while (1)
	{
		input = NULL;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			process_input(input);
		}
		free(input);
	}
	free(input);
	input = NULL;
}
```

# Historique
Si la fonction **add_history()** est utilisée, les arrow keys font le taff toutes seules, pas besoin de coder la navigation dans l'historique.

# Signaux
Les seuls signaux à gérer dans ce projet sont les raccourcis claviers ``ctrl+C`` (**SIGINT**) et ``ctrl+\`` (**SIGQUIT**). En effet, ``ctrl+D`` est géré par le if (!input) dans la boucle décrite tout à l'heure: il remplace automatiquement l'input par un EOF, et rentre ainsi dans la condition qui mène au exit().

Déclarer la structure sigaction:
```
struct sigaction	your_sigaction_struct;
```

Préparer le masque/set pour sigaction:
```
sigset_t			your_set;

sigemptyset(&your_set);
sigaddset(&your_set, SIGINT);
sigaddset(&your_set, SIGQUIT);
your_sigaction_struct.sa_mask = your_set;
```

Déclarer les flags et la fonction qui gérera les signaux reçus. Si pas de flag SA_SIGINFO, utiliser .sa_handler à la place de sa_sigaction.
```
your_sigaction_struct.sa_flags = SA_SIGINFO | SA_RESTART;
your_sigaction_struct.sa_sigaction = &your_function_handling_signals;
```

Utiliser **sigaction()** dans la boucle pour pouvoir capter à tout moment les deux signaux:
```
sigaction(SIGINT, &your_sigaction_struct, NULL);
sigaction(SIGQUIT, &your_sigaction_struct, NULL);
```

Et construire la fonction **your_function_handling_signals(int sig, siginfo_t *info, void *ucontext)** qui gère le comportement du programme en fonction du signal reçu.

Le problème des signaux, c'est qu'on ne peut pas leur passer de variable à nous, et que même si on pouvait, on n'en a pas le droit. Comment alors, mettre à jour l'exit status suite à des signaux? Le sujet nous autorise à créer une seule variable globale qui ne contienne strictement que la valeur du signal.
--> Piste: retirer le flag SA_RESTART et mettre un wait() pour s'assurer que le signal ait été entièrement traité avant de passer à la suite.

## SIGINT
*Interrompt le process et rend la commande.*

Créer une fonction qui permet de reset le prompt:
```
void    reset_prompt()
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```
Son exit status est de 130.

## SIGQUIT
*Si pas dans une commande bloquante, ferme le programme. Sinon, ne fait rien.*

Si bonnes conditions, utiliser **exit(0)**. ou exit(131)?

Son exit status est de 131.

# Built-in
Les commandes dites "built-in" se distinguent de celles présentes dans les PATH de l'environnement (?).

Attention: il faut aussi gérer leur **exit status**: si elles foirent pour une raison ou une autre, il faut changer la valeur de l'exit status, sinon, on le laisse à 0.

## pwd
*Affiche le current directory.*

N'attend pas d'argument:
- Si argument, l'ignore et fonctionne normalement (exit status = 0).

Appeler **getcwd()** et afficher le résultat.

## cd
*Change le current directory.*

Attend soit 0 soit 1 argument; argument doit être un chemin valable:
- Si aucun argument, renvoie à $HOME.
- Si 2 arguments, message d'erreur (exit status = 1).
- Si argument invalide, message d'erreur (exit status = 1).

Appeler **chdir()** en lui passant le chemin reçu en arguments.

## env
*Affiche toutes les variables de l'environnement.*

Dans le sujet, n'attend pas d'argument:
- Si argument, message d'erreur (exit status = 1) / ignore l'argument (exit status = 0).

Parcourir tout le tableau d'environnement reçu en argument à l'exécution de minishell et imprimer chaque élément.

## export
*Gère la création et la modification des variables d'environnement, avec une liste "tampon".*

Pour créer ou modifier une variable d'environnement:
```
export YOUR_VAR_NAME=your_var_value
```

Il est possible de ne pas spécifier la valeur de la variable, qui sera alors mise à NULL:
```
export YOUR_VAR_NAME=
```

Peut gérer 0 ou plusieurs arguments.
- Si aucun argument, affiche toutes les variables de la liste "tampon", chacune précédée de "declare -x ", et avec leur valeur entre guillemets.
- Si argument sans '=', crée la variable dans la liste "tampon" (sans =""), mais pas dans celle de l'environnement.
- Si argument contenant un '=': crée la nouvelle variable d'environnement dans la liste "tampon" (avec ="" si aucune valeur donnée, sinon ="your_var_value") et dans celle de l'environnement.
- Si plusieurs arguments, répète comportements ci-dessus autant de fois qu'il y a d'arguments.



## unset
*Supprime la variable d'environnement passée en argument (dans les deux listes). Si n'existe pas, ne fait rien.*

## echo
*Imprime ce qu'on lui passe en argument et termine par un retour à la ligne. Par défaut, il imprime dans le terminal, mais on peut lui faire imprimer ailleurs avec une redirection.*

### echo -n
*Pareil, mais sans retour à la ligne à la fin.*

## exit
*Ferme le programme.*

Dans le sujet, n'attend pas d'argument:
- Si argument, message d'erreur / ignore l'argument.

Appeler **exit(0)**.

# Autres commandes
Notre minishell doit pouvoir gérer toutes les commandes existantes dans l'environnement.

## $?
*Retourne l'exit status de la dernière commande. Son propre exit status est de 127.*

----- 

ATTENTION: ne pas free après un getenv(), car il ne malloc pas.