/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:49 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/30 16:09:30 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unexpected_tokens(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		quote = quote_value(input[i], quote);
		if (input[i] == '|' && input[i + 1] == ' ' && !quote)
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '|')
				return (syntax_error_token(UNTOKEN, '|', 0));
		}
		else if (ft_strrchr(REDIR, input[i]) && !quote)
			if (unexpected_token_redir(input, &i))
				return (1);
	}
	return (0);
}

int	no_support_operators(char *input)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (input[++i])
	{
		quote = quote_value(input[i], quote);
		if (i + 1 < (int)ft_strlen(input)
			&& input[i] == '|' && input [i + 1] == '|' && !quote)
			return (syntax_error_operator(NOSUPPORT, "||"));
		else if (ft_strrchr(NOTHANDLE, input[i]) && !quote)
			return (syntax_error_token(NOSUPPORT, input[i], 0));
		else if (input[i] == '<' && input [i + 1] == '>' && !quote)
			return (syntax_error_operator(NOSUPPORT, "<>"));
		else if (i + 2 < (int)ft_strlen(input)
			&& input[i] == '<' && input [i + 1] == '<'
			&& input [i + 2] == '<' && !quote)
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

int	invalid_syntax(char *input)
{
	if (input[1] && input[0] == '|' && input[1] != '|')
		return (syntax_error_token(UNTOKEN, '|', 0));
	else if (input[1] && input[0] == '|' && input[1] == '|')
		return (syntax_error_token(UNTOKEN, '|', 1));
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putstr_fd("minishell: pipe handling only between commands\n", 2);
		return (1);
	}
	else if (strrchr(REDIR, input[ft_strlen(input) - 1]))
		return (syntax_error_operator(UNTOKEN, "newline"));
	return (0);
}

int	valid_input(char *input)
{
	if (!input || input[0] == '\0')
		return (0);
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: unclosed quotes\n", 2);
		return (0);
	}
	if (invalid_syntax(input))
		return (0);
	if (no_support_operators(input))
		return (0);
	return (1);
}
