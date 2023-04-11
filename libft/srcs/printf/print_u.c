/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:15:08 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:19:57 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static void	handle_minus(char **to_print, int lenght,
t_token *token, char **tmp)
{
	int		nbrlen;
	int		i;

	nbrlen = ft_strlen(*to_print);
	if (token->minus == 1)
	{
		ft_strlcat(*tmp, *to_print, lenght + 1);
		while (nbrlen < lenght)
			(*tmp)[nbrlen++] = ' ';
	}
	else if (token->space == 1 && token->plus == 0)
	{
		if (nbrlen + 1 >= lenght)
		{
			free(*tmp);
			ft_addsign(to_print, ' ', token);
			*tmp = *to_print;
			return ;
		}
		i = 0;
		while (i < (lenght - nbrlen + 1))
			(*tmp)[i++] = ' ';
		ft_strlcat(*tmp, *to_print, lenght + 2);
	}
	free(*to_print);
}

static char	*build_str(char *to_print, int lenght, t_token *token, char padding)
{
	int		nbrlen;
	char	*tmp;
	int		i;

	nbrlen = ft_strlen(to_print);
	if (nbrlen >= lenght && token->space == 0)
	{
		ft_addsign(&to_print, '+', token);
		return (to_print);
	}
	tmp = ft_calloc((lenght + 1), (sizeof(char)));
	if (token->plus == 1)
		*tmp++ = '+';
	if (token->minus == 1 || token->space == 1)
		handle_minus(&to_print, lenght, token, &tmp);
	else
	{
		i = 0;
		while (i < (lenght - nbrlen))
			tmp[i++] = padding;
		ft_strlcat(tmp, to_print, lenght + 1);
		free(to_print);
	}
	return (tmp);
}

static int	handle_positive(t_token *token, char **to_print)
{
	if (token->dot == 1)
		*to_print = build_str(*to_print, token->precision, token, '0');
	else if (token->minus == 1)
		*to_print = build_str(*to_print, token->padding, token, ' ');
	else if (token->zero == 1)
		*to_print = build_str(*to_print, token->padding, token, '0');
	else
		*to_print = build_str(*to_print, token->padding, token, ' ');
	ft_putstr_fd(*to_print, STDOUT_FILENO);
	return (ft_strlen(*to_print));
}

int	print_u(t_token *token, unsigned int u)
{
	int		bytes;
	char	*to_print;

	bytes = 0;
	to_print = ft_itoa(u);
	bytes += handle_positive(token, &to_print);
	free(to_print);
	return (bytes);
}
