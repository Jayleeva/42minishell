#include "../inc/shell_data.h"
#include "../inc/linked_list.h"
#include "../libft/inc/libft.h"

static int	call_ft_by_type(char type, va_list list, int result)
{
	char	*str;

	if (type == '%')
		result = putchar_fd_pf('%', 1, result);
	else if (type == 'c')
		result = putchar_fd_pf((char)va_arg(list, int), 1, result);
	else if (type == 's')
		result = putstr_fd_pf(va_arg(list, char *), 1, result);
	else if (type == 'd' || type == 'i')
	{
		str = ft_itoa(va_arg(list, int));
		result = putstr_fd_pf(str, 1, result);
		free (str);
	}
	else if (type == 'u' || type == 'x' || type == 'X')
		result = print_unsigned(va_arg(list, unsigned int), type, result);
	else if (type == 'p')
		result = print_pointer(va_arg(list, unsigned long long), result);
	return (result);
}

int	printf_fd(int fd, const char *s, ...)
{
	va_list	args;
	int		j;
	int		result;

	va_start(args, s);
	result = 0;
	j = 0;
	while (s[j])
	{
		if (s[j] == '%')
		{
			j ++;
			result = call_ft_by_type(s[j], args, result);
		}
		else
			result = putchar_fd_pf(s[j], fd, result);
		j ++;
	}
	va_end(args);
	return (result);
}
