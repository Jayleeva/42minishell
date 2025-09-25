Projet de groupe du 4ème cercle du cursus 42

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
your_sigaction_struct.sa_sigaction = &your_handling_signals_function;
```

Utiliser **sigaction()** dans la boucle pour pouvoir capter à tout moment les deux signaux:
```
sigaction(SIGINT, &your_sigaction_struct, NULL);
sigaction(SIGQUIT, &your_sigaction_struct, NULL);
```

Et construire la fonction **your_handling_signals_function(int sig, siginfo_t *info, void *ucontext)** qui gère le comportement du programme en fonction du signal reçu.

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
