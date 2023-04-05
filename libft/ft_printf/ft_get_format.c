/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:58:16 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	ft_get_v(t_buffer *v, char *buffer)
{
	if (!v->point)
	{
		v->w = ft_atoi(buffer);
		return (ft_getlength(v->w, 10) - 1);
	}
	else
	{
		v->prec = ft_atoi(buffer);
		return (ft_getlength(v->prec, 10) - 1);
	}
}

static void	ft_read_buffer(char *buffer, t_buffer *v)
{
	while (*buffer)
	{
		if (*buffer == '-')
			v->minus = 1;
		else if (*buffer == '+')
			v->plus = 1;
		else if (*buffer == ' ')
			v->space = 1;
		else if (*buffer == '0')
			v->zero = 1;
		else if (*buffer == '#')
			v->hash = 1;
		else if (*buffer == '.')
			v->point = 1;
		else if ((*buffer >= '1' && *buffer <= '9'))
			buffer += ft_get_v(v, buffer);
	buffer++;
	}
}

static void	ft_init_format_buffer(t_buffer *v)
{
	v->conversion_type = 0;
	v->space = 0;
	v->zero = 0;
	v->plus = 0;
	v->minus = 0;
	v->hash = 0;
	v->point = 0;
	v->w = 0;
	v->prec = 0;
}

int	ft_get_format_buffer(const char **str, va_list args)
{
	t_buffer	v;
	char		*buffer;
	int			i;

	i = 0;
	ft_init_format_buffer(&v);
	while (!ft_strchr(TYPE, (*str)[i]))
		i++;
	buffer = ft_substr(*str, 0, i);
	ft_read_buffer(buffer, &v);
	(*str) += i;
	v.conversion_type = **str;
	free(buffer);
	return (ft_check_type_format(args, &v));
}
