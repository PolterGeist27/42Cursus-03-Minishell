/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:30:23 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/28 20:17:25 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	quote_value(char c, char quote)
{
	if (ft_strrchr("\"\'", c) && !quote)
		return (c);
	else if (ft_strrchr("\"\'", c) && quote == c)
		return (0);
	return (quote);
}

int	isalnumextra(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

void	get_exit_status(void)
{
	pid_t	i;
	int		status;

	i = 1;
	while (i > 0)
	{
		i = waitpid(0, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}
