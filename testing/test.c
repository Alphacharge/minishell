#include <stdio.h>
#include <stdlib.h>

/*Checks for shell tokens but not for quotation marks.*/
int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f'
		|| c == '\r' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	get_arg_length(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && ft_isspace(s[i]) == 0 && is_token(s[i]) == 0)
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"')
			{
				s[j] = s[i];
				i++;
				j++;
			}
			if (s[i] == '\"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
			{
				s[j] = s[i];
				i++;
				j++;
			}
			if (s[i] == '\'')
				i++;
		}
	printf("test\n");
		if (j != i)
		{
		s[j] = s[i];
		printf("%c -> %c\n", s[j], s[i]);
		}
		i++;
		j++;
	}
	printf("get_arg_length: clean string |%s|\n", s);
	return (j);
}

int	main()
{
	char	*s;

	s = malloc(20);
	s = "c\"a\"t -e   ";
	printf("found length %i\n", get_arg_length(s));
}
