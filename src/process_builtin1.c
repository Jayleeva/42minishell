#include "../inc/minishell.h"
#include "../inc/shell_data.h"
#include "../inc/token.h"
#include "../libft/inc/libft.h"

void    process_cd(char *cmd, t_sig *g_sig)
{
    char    *path;

	g_sig->exit_status = 0;
    path = NULL;
    path = ft_substr(cmd, 3, ft_strlen(cmd));
    path = cutstr(path, path[0], ' ');  //ATTENTION: si autre chose après le path, n'est pas pris en compte + pour l'instant ne gère pas les quotes
    if (chdir(path) == -1)
	{
		g_sig->exit_status = 1;
        ft_printf("cd: %s: No such file or directory\n", path);
	}
    free(path);
}

void    process_pwd(t_sig *g_sig)
{
    char    *path;

	g_sig->exit_status = 0;
    path = NULL;
    path = getcwd(path, 0);
    if (path == NULL)
	{
		g_sig->exit_status = 1;
        return ;
	}
    ft_printf("%s\n", path);
    free(path);
}

void    process_env(char *cmd, t_sig *g_sig)
{
    char    *path;
    char    *name;

	(void)cmd;
	g_sig->exit_status = 0;
    name = "HOSTNAME";
    path = NULL;
    path = getenv(name);
    if (path == NULL)
	{
		g_sig->exit_status = 127;
        return;
	}
     ft_printf("%s\n", path);
     free(path);
}

/*void	process_export(char *cmd, t_sig *g_sig)
{

}

void	process_unset(char *cmd, t_sig *g_sig)
{
	
}*/