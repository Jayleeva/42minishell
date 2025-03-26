#include "../inc/minishell.h"
#include "../inc/shell_data.h"
#include "../inc/token.h"
#include "../libft/inc/libft.h"

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

void process_cmd(char *cmd)
{
    // Parse the cmd and execute the corresponding commands
    // This might involve tokenizing the cmd, handling pipes, redirections, etc.
    char        *path;
    char        *name;
    char        *s;
    
    path = NULL;
    name = "LOGNAME";
    s = NULL;
    if (ft_strncmp(cmd, "exit", 5) == 0)
    {
        ft_printf("exit\n");
        exit (0);
    }
    else if (ft_strncmp(cmd, "pwd", 4) == 0)
    {
        path = getcwd(path, 0);
        if (path == NULL)
            return ;
        ft_printf("%s\n", path);
        free(path);
    }
    /*else if (ft_strncmp(cmd, "cd", 3) == 0)
    {
        path = cmd after cd;
        chdir(path);
    }*/
    else if (ft_strncmp(cmd, "echo", 4) == 0)
    {
        if (cmd[4] == '\0')
            ft_printf("\n");
        else
        {
            s = ft_substr(cmd, 5, ft_strlen(cmd));
            if (s[0] == '\"' && s[1] == '\'')
                s = ft_strtrim(s, "\"");
            if (s[0] == '\'' && s[1] == '\"')
                s = ft_strtrim(s, "\'");
             // ATTENTION si les single sont dans des double, doivent etre print, sinon non, ET pareil pour les double dans des single.
            if (s[0] == '$')
                ft_printf("!! look for environnement variable\n");
            else
                ft_printf("%s\n", s);
            free(s);
        }
    }
    else if (ft_strncmp(cmd, "env", 4) == 0)
    {
       path = getenv(name);
       if (path == NULL)
           return;
        ft_printf("%s\n", path);
        free(path);
    }
    /*else if (ft_strncmp(cmd, "export", 7) == 0)
    {

    }*/
    /*else if (ft_strncmp(cmd, "unset", 6) == 0)
    {

    }*/
    /*else if (ft_strncmp(cmd, "$?", 3) == 0)
    {
        ft_printf("%d", g_sig.exit_status);
    }*/
    else
    {
        s = first_word(cmd); //la, pris que le premier mot: incomplet car si pipe, premier peut etre juste
        if (s == NULL)
            s = ft_strdup(cmd);
        ft_strlcat(s, ": command not found", ft_strlen(s) + 20);
        ft_printf("%s\n", s);
    }
}
