/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:05:34 by pealexan          #+#    #+#             */
/*   Updated: 2023/04/20 15:50:37 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_print_w(char *str, t_buffer *v)
{
	int	count;

	count = 0;
	while (v->w > (int)ft_strlen(str))
	{
		count += write(1, " ", 1);
		v->w--;
	}
	count += ft_putstr(str);
	free(str);
	return (count);
}

static int	ft_print_minus_w(char *str, t_buffer *v)
{
	int	count;

	count = 0;
	{
		count += ft_putstr(str);
		while (v->w > (int)ft_strlen(str))
		{
			count += write(1, " ", 1);
			v->w--;
		}
	}
	free(str);
	return (count);
}

int	ft_format_putstr(t_buffer *v, char *str)
{
	int		count;
	char	*aux;

	count = 0;
	if (!str)
		aux = ft_strdup("(null)");
	else
		aux = ft_strdup(str);
	if (v->point)
	{
		if (!ft_strncmp(aux, "(null)", 6) && v->prec < 6)
			aux = ft_strdup("");
		else
			ft_strlcpy(aux, aux, v->prec + 1);
	}
	if (v->minus == 1)
		count += ft_print_minus_w(aux, v);
	else
		count += ft_print_w(aux, v);
	return (count);
}
