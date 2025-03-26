#include "../inc/minishell.h"
#include "../inc/shell_data.h"
#include "../inc/token.h"
#include "../libft/inc/libft.h"

void    process_echo(char *cmd, t_sig *g_sig)
{
    char    *s;

	g_sig->exit_status = 0;
    s = NULL;
    if (cmd[4] == '\0')
        ft_printf("\n");
    else
    {
        s = ft_substr(cmd, 5, ft_strlen(cmd));

		/*if (s[0] == '\"' && s[1] == '\'')
			s = ft_strtrim(s, "\"");
		if (s[0] == '\'' && s[1] == '\"')
			s = ft_strtrim(s, "\'");*/
		// ATTENTION si les single sont dans des double, doivent etre print, sinon non, ET pareil pour les double dans des single.
        if (s[0] == '$')
            ft_printf("!! look for environnement variable\n");
        else
            ft_printf("%s\n", s);
        free(s);
    }
}
