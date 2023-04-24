/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:38:28 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/24 09:22:14 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*input_handling(char *input)
{
	char	*temp;
	int		i;
	int		j;
	
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (ft_strrchr(METACHAR, input[i]))
		{
			if (input[i] == )
		}		
		else
			temp[j] = input[i]
	}
	return (final);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*final_input;

	while (1)
	{
		input = readline("$ >");
		add_history(input);
		if (!valid_input(input))
		{
			free(input);
			continue;
		}
		final_input = input_handling(input);
		//printf("%s\n", input);
		//trim_input = handle_input(input);
		free(input);
	}
	return (0);
}
