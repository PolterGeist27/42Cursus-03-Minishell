/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:15:11 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:19:52 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

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

static int	handle_dot(char **str, int precision)
{
	char	*tmp;

	if (precision >= (int)ft_strlen(*str))
		return (ft_strlen(*str));
	tmp = ft_substr(*str, 0, precision);
	free(*str);
	*str = tmp;
	return ((int)ft_strlen(*str));
}

int	print_s(t_token *token, char *str)
{
	int		bytes;
	char	*final;

	if (str == NULL)
	{
		ft_putstr_fd("(null)", STDOUT_FILENO);
		return (6);
	}
	final = ft_strdup(str);
	bytes = 0;
	if (token->dot == 1)
		bytes += handle_dot(&final, token->precision);
	else
	{
		final = build_str(final, token->padding, token);
		bytes += ft_strlen(final);
	}
	ft_putstr_fd(final, STDOUT_FILENO);
	free(final);
	return (bytes);
}
