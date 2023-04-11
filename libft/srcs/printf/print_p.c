/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:15:26 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:19:36 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static char	*handle_minus(char *tmp, int lenght, t_token *token, char *to_print)
{
	int	nbrlen;

	nbrlen = ft_strlen(to_print);
	if (token->minus == 1)
	{
		ft_strlcat(tmp, to_print, lenght + 1);
		while (nbrlen < lenght)
			tmp[++nbrlen] = ' ';
	}
	return (tmp);
}

static char	*handle_other(char *to_print, int lenght, t_token *token)
{
	int		nbrlen;
	char	*tmp;

	nbrlen = ft_strlen(to_print);
	if (nbrlen <= lenght)
	{
		ft_addsign(&to_print, '+', token);
		return (to_print);
	}
	tmp = ft_calloc((lenght + 1), (sizeof(char)));
	if (token->plus == 1)
		*tmp++ = '+';
	if (token->minus == 1)
		handle_minus(tmp, lenght, token, to_print);
	else
	{
		while (++nbrlen < lenght)
			*tmp++ = '0';
		ft_strlcat(tmp, to_print, lenght + 1);
	}
	free(to_print);
	return (tmp);
}

static char	*build_str(char *to_print, int lenght, t_token *token)
{
	int		strlen;
	char	*tmp;
	int		i;

	strlen = ft_strlen(to_print);
	if (strlen >= lenght)
		return (to_print);
	tmp = ft_calloc((lenght + 1), (sizeof(char)));
	if (token->minus == 1)
	{
		ft_strlcat(tmp, to_print, lenght + 1);
		while (strlen < lenght)
			tmp[strlen++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (lenght - strlen))
			tmp[i++] = ' ';
		ft_strlcat(tmp, to_print, lenght + 1);
	}
	free(to_print);
	return (tmp);
}

int	handle_cases(t_token *token, char *nbr, char **to_print)
{
	if (token->dot == 1)
	{
		nbr = handle_other(nbr, token->precision, token);
		*to_print = ft_strjoin("0x", nbr);
		free(nbr);
	}
	else if (token->zero == 1)
	{
		nbr = handle_other(nbr, token->padding, token);
		*to_print = ft_strjoin("0x", nbr);
		free(nbr);
	}
	else
	{
		*to_print = ft_strjoin("0x", nbr);
		free(nbr);
		*to_print = build_str(*to_print, token->padding, token);
	}
	if (token->type == 'X')
		ft_str_toupper(to_print);
	ft_putstr_fd(*to_print, STDOUT_FILENO);
	return (ft_strlen(*to_print));
}

int	print_p(t_token *token, unsigned long long p)
{
	int		bytes;
	char	*to_print;
	char	*nbr;

	bytes = 0;
	if (p == 0 && token->type == 'p')
	{
		ft_putstr_fd("(nil)", STDOUT_FILENO);
		return (5);
	}
	nbr = ft_itoa_hex(p);
	bytes += handle_cases(token, nbr, &to_print);
	free(to_print);
	return (bytes);
}
