#include "minishell.h"

int	ft_wordcount_meta(char *str, char c)
{
	int	i;
	int	wordcount;
    char    quote;

	i = 0;
	wordcount = 0;
    quote = 0;
	while (str[i])
	{
		if (ft_strrchr("\"\'", str[i]) && !quote)
			quote = str[i];
		else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
			quote = 0;
        while (str[i] && str[i] == c && !quote)
            i++;
        if (str[i] && !quote)
            wordcount++;
        while (str[i] && str[i] != c && !quote)
		{
			if (ft_strrchr("\"\'", str[i]) && !quote)
				quote = str[i];
			else if (ft_strrchr("\"\'", str[i]) && quote == str[i])
				quote = 0;
            i++;
		}
        //else
        i++;
	}
	return (wordcount);
}

static int	ft_wordlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*get_word(char *s, char c, char **words, int j)
{
	while (*s && *s == c)
		s++;
	if (*s)
		words[j] = ft_substr(s, 0, ft_wordlen(s, c));
	while (*s && *s != c)
		s++;
	return (s);
}

char	**ft_split_meta(char *s, char c)
{
	char	**words;
	int		wdcount;
    int     i;
	int		j;
	char	quote;

	i = 0;
    j = 0;
	quote = 0;
	if (!s)
		return (0);
	words = malloc(sizeof(char *) * (ft_wordcount_meta(s, c) + 1));
	if (!words)
		return (0);
	while (*s)
	{
		if (ft_strrchr("\"\'", *s) && !quote)
			quote = *s;
		else if (ft_strrchr("\"\'", *s) && quote == *s)
			quote = 0;
		if (!quote)
		{
			s = get_word(s, c, words, j);
			j++;
		}
		else
        	s++;
	}
	words[j] = 0;
	return (words);
}

int main(void)
{
	char *str = "ls a | cat a as\"da | ls\" ";
	char **split;
	int i = -1;

	split = ft_split_meta(str, '|');
	while (split[++i])
	    printf("%s\n", split[i]);
    printf("%d\n", ft_wordcount_meta(str, '|'));
	return (0);
}