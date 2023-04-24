/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:20:03 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/24 08:56:38 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parsing(char *input, t_minishell *mini)
{
    int	i;
	int	j;
	char	**args;

	i = 0;
	args = ft_split(input, " ");
	while (args[i])
	{
		j = 0;
		while(args[i][j])
		{
			if (args[i][j] == '>')
			{
				
			}
			j++;
		}
		i++;
	}
}