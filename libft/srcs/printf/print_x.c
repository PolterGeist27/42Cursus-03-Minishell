/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:15:40 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:20:00 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static char	*build_str(char *to_print, int lenght, t_token *token, char padding)
{
	int		nbrlen;
	char	*tmp;
	int		i;

	nbrlen = ft_strlen(to_print);
	if (nbrlen >= lenght)
		return (to_print);
	tmp = ft_calloc((lenght + 1), (sizeof(char)));
	if (token->minus == 1)
	{
		ft_strlcat(tmp, to_print, lenght + 1);
		while (nbrlen < lenght)
			tmp[nbrlen++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (lenght - nbrlen))
			tmp[i++] = padding;
		ft_strlcat(tmp, to_print, lenght + 1);
	}
	free(to_print);
	return (tmp);
}

static int	handle_others(t_token *token, char **to_print)
{
	if (token->dot == 1)
		*to_print = build_str(*to_print, token->precision, token, '0');
	else if (token->minus == 1)
		*to_print = build_str(*to_print, token->padding, token, ' ');
	else if (token->zero == 1)
		*to_print = build_str(*to_print, token->padding, token, '0');
	else
		*to_print = build_str(*to_print, token->padding, token, ' ');
	if (token->type == 'X')
		ft_str_toupper(to_print);
	ft_putstr_fd(*to_print, STDOUT_FILENO);
	return (ft_strlen(*to_print));
}

int	print_x(t_token *token, unsigned int x)
{
	int		bytes;
	char	*to_print;

	bytes = 0;
	if (token->hash == 1 && x > 0)
	{
		bytes += print_p(token, (unsigned long long)x);
		return (bytes);
	}
	to_print = ft_itoa_hex((unsigned long long)x);
	bytes += handle_others(token, &to_print);
	free(to_print);
	return (bytes);
}
