/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:38:28 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/21 11:01:28 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_input(char *input);
int	check_quotes(char *str);
int	no_support_operators(char *input);
int	unexpected_tokens(char *input);
int	unexpected_tokens2(char *input, int *i);
int	invalid_syntax(char *input);
int	syntax_error_token(char metachar);
int	syntax_error_operator(char *operator);

/* char	handle_input(char *input)
{
    int i;
	char	*trim_input;

    i = 0;
	if (check_quotes(input))

	trim_input = ft_strtrim(input, " /t");
    while (*input)
    {
        while (*input && *input == ' ')
            input++;
        input++;
    }
	return (trim_input);
}
 */

int	syntax_error_operator(char *error, char *operator)
{
	ft_putstr_fd(error, 2);
	ft_putstr_fd(operator, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	syntax_error_token(char *error, char metachar)
{
	ft_putstr_fd(error, 2);
	ft_putchar_fd(metachar, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	valid_syntax(char *input)
{
	if (input[0] == '|')
		return (syntax_error_token('|'));
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putstr_fd("minishell: pipe handling only between commands\n", 2);
		return (1);
	}
	if (strrchr(REDIR, input[ft_strlen(input) - 1]))
		return (syntax_error_operator(UNTOKEN, "newline"));
	return (0);
}
/// @brief 
/// @param input 
/// @param i 
/// @return 
int	unexpected_tokens2(char *input, int *i)
{
	if (input[*i] == ' ')
	{
		while (input[*i] && input [*i] == ' ')
			*i++;
		if (ft_strrchr(METACHAR, input[*i]))
		{
			if (input[*i] == '|')
			{
				if (input[i + 1] == '|')
					return (syntax_error_operator(UNTOKEN, "||"));
				else
					return (syntax_error_token(UNTOKEN, input[*i + 1]));
			}
			else if (input[*i])
	}
	if (ft_strrchr(METACHAR, input[*i]))
		return (syntax_error_token(UNTOKEN, input[*i]));
	}
	return (0);
}

int	unexpected_token_redir(char *input, int *i)
{
	if (input[*i] == input[*i + 1])
		i = *i + 1;
	if (input[*i] == '<')
	if (input[*i] == ' ')
	{
		while (input[*i] && input [*i] == ' ')
			i = *i + 1;
		if (input[*i] == '|')
			return (syntax_error_token(UNTOKEN, input[*i + 1]));
		else if (input[*i] == '>')
			return (syntax_error_token(UNTOKEN, input[*i + 1]));
		else if (input[*i] == '<')
			return (syntax_error_token(UNTOKEN, input[*i + 1]));
		
		
		
		if (ft_strrchr(METACHAR, input[*i]))
		{
			if (input[*i] == '|')
				return (syntax_error_token(UNTOKEN, input[*i + 1]));
			}
			else if (input[*i])
	}
	if (ft_strrchr(METACHAR, input[*i]))
		return (syntax_error_token(UNTOKEN, input[*i]));
	}
	return (0);
}

int	unexpected_tokens(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		if (ft_strrchr("\"\'", input[i]) && !quote)
			quote = input[i];
		else if (ft_strrchr("\"\'", input[i]) && quote == input[i])
			quote = 0;
		if (input[i] == '|' && input[i + 1] == ' ')
		{
			i++;
			while(input[i] == ' ')
				i++;
			if (input[i] == '|')
				return (syntax_error_token(UNTOKEN, '|'));
		}
		else if (ft_strrchr(REDIR, input[i]) && !quote)
			if (unexpected_token_redir(input, &i))
				return (1);
	}
	return (invalid_syntax(input));
}

int	no_support_operators(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		if (ft_strrchr("\"\'", input[i]) && !quote)
			quote = input[i];
		else if (ft_strrchr("\"\'", input[i]) && quote == input[i])
			quote = 0;
		if (i + 1 < ft_strlen(input)
			&& input[i] == '|' && input [i + 1] == '|' && !quote)
			return (syntax_error_operator(NOSUPPORT, "||"));
		else if (ft_strrchr(NOTHANDLE, input[i]) && !quote)
			return (syntax_error_token(NOSUPPORT, input[i]));
		else if (input[i] == '<' && input [i + 1] == '>' && !quote)
			return (syntax_error_operator(NOSUPPORT, "<>"));
		else if (i + 2 < ft_strlen(input)
			&& input[i] == '<' && input [i + 1] == '<'
			&& input [i + 2] == '<' && !quotes)
			return (syntax_error_operator(NOSUPPORT, "<<<"));
	}
	return (unexpected_tokens(input));
}

int	check_quotes(char *input)
{
	char	quote;

	quote = 0;
	while (*input && !quote)
	{
		if (ft_strrchr("\"\'", *input))
			quote = *input;
		input++;
	}
	while (*input && quote)
	{
		if (*input && *input == quote)
			quote = 0;
		input++;
	}
	if (*input)
		return (check_quotes(input));
	else if (!quote)
		return (0);
	else
		return (1);
}

int	valid_input(char *input)
{
	if (!input || input[0] == '\0')
		return (0);
	else if (!valid_syntax(input))
		return (0);
	else if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", 2);
		return (0);
	}
	else if (no_support_operators(input))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*trim_input;

	while (1)
	{
		input = readline("$ >");
		add_history(input);
		if (!valid_input(input))
		{
			free(input);
			exit (2);
		}
		printf("%s\n", input);
		//trim_input = handle_input(input);
		free(input);
	}
	return (0);
}
