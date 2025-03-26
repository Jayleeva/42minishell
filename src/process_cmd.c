#include "../inc/minishell.h"
#include "../inc/shell_data.h"
#include "../inc/token.h"
#include "../libft/inc/libft.h"

void    process_exit(void)
{
    ft_printf("exit\n");
    exit (0);
}

void    process_other(char *cmd, t_sig *g_sig)
{
    char    *s;

    s = NULL;
    s = first_word(cmd); //là, pris que le premier mot: incomplet car si pipe, premier peut etre juste
    if (s == NULL)
        s = ft_strdup(cmd);
    ft_strlcat(s, ": command not found", ft_strlen(s) + 20);
    g_sig->exit_status = 127;
    ft_printf("%s\n", s);
    free(s);
}

char    *first_word(const char *s)
{
    size_t  i;
    char    *res;

    res = NULL;
    i = 0;
    while (s[i] != ' ')
        i ++;
    res = (char*)malloc((i) * sizeof(char));
    res = ft_memcpy(res, s, i);
    res[i] = '\0';
    return (res);
}

void    process_cmd(char *cmd, t_sig *g_sig)
{
    if (ft_strncmp(cmd, "exit", 5) == 0)
        process_exit();
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
        process_pwd(g_sig);
    else if (ft_strncmp(cmd, "cd", 2) == 0)
        process_cd(cmd, g_sig);
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        process_echo(cmd, g_sig);
    else if (ft_strncmp(cmd, "env", 4) == 0)
        process_env(cmd, g_sig);
    /*else if (ft_strncmp(cmd, "export", 7) == 0)
        process_export(cmd);
    else if (ft_strncmp(cmd, "unset", 6) == 0)
        process_unset(cmd);*/
    else if (ft_strncmp(cmd, "$?", 3) == 0)
        ft_printf("%d\n", g_sig->exit_status);
    else
        process_other(cmd, g_sig);
}
