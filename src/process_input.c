
#include "../inc/minishell.h"
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

void process_input(char *input)
{
    // Parse the input and execute the corresponding commands
    // This might involve tokenizing the input, handling pipes, redirections, etc.
    char        *path;
    char        *name;
    char        *s;
    
    path = NULL;
    name = "LOGNAME";
    s = NULL;
    if (ft_strncmp(input, "exit", 5) == 0)
    {
        ft_printf("exit\n");
        exit (0);
    }
    else if (ft_strncmp(input, "pwd", 4) == 0)
    {
        path = getcwd(path, 0);
        if (path == NULL)
            return ;
        ft_printf("%s\n", path);
        free(path);
    }
    /*else if (ft_strncmp(input, "cd", 3) == 0)
    {
        path = input after cd;
        chdir(path);
    }*/
    else if (ft_strncmp(input, "echo", 4) == 0)
    {
        if (input[4] == '\0')
            ft_printf("\n");
        else
        {
            s = ft_substr(input, 5, ft_strlen(input));
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
    else if (ft_strncmp(input, "env", 4) == 0)
    {
       path = getenv(name);
       if (path == NULL)
           return;
        ft_printf("%s\n", path);
        free(path);
    }
    /*else if (ft_strncmp(input, "export", 7) == 0)
    {

    }*/
    /*else if (ft_strncmp(input, "unset", 6) == 0)
    {

    }*/
    /*else if (ft_strncmp(input, "$?", 3) == 0)
    {
        ft_printf("%d", g_sig.exit_status);
    }*/
    else
    {
        s = first_word(input); //la, pris que le premier mot: incomplet car si pipe, premier peut etre juste
        if (s == NULL)
            s = ft_strdup(input);
        ft_strlcat(s, ": command not found", ft_strlen(s) + 20);
        ft_printf("%s\n", s);
    }
}
