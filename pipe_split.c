#include "minishell.h"

int	ft_wordcount_meta(const char *str, char c)
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
        if (!quote)
        {
            while (str[i] && str[i] == c)
                i++;
            if (str[i])
                wordcount++;
            while (str[i] && str[i] != c)
                i++;
        }
        else
            i++;
	}
	return (wordcount);
}

static int	ft_wordlen(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	get_word(const char *s, char c, char **words, int j, int *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	if (s[*i])
		words[j] = ft_substr(s, 0, ft_wordlen(s, c));
	while (s[*i] && s[*i] != c)
		(*i)++;
}

char	**ft_split_meta(const char *s, char c)
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
	wdcount = ft_wordcount_meta(s, c);
	words = malloc(sizeof(char *) * (wdcount + 1));
	if (!words)
		return (0);
	while (s[i])
	{
		if (ft_strrchr("\"\'", s[i]) && !quote)
			quote = s[i];
		else if (ft_strrchr("\"\'", s[i]) && quote == s[i])
			quote = 0;
		if (!quote)
		{
			get_word(s, c, words, j, &i);
			j++;
		}
        else
            i++;
		//while (*s && *s == c && !quote)
		//	s++;
		//if (*s)
		//	words[j++] = ft_substr(s, 0, ft_wordlen(s, c));
		//while (*s && *s != c && !quote)
		//	s++;
	}
	words[j] = 0;
	return (words);
}

int main(void)
{
	char *str = "ls a | cat a asda ";
	char **split;
	int i = -1;

	split = ft_split_meta(str, '|');
	while (split[++i])
	    printf("%s\n", split[i]);
    printf("%d\n", ft_wordcount_meta(str, '|'));
	return (0);
}