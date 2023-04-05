/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	ft_print_zeroes(char *number, t_buffer *v)
{
	int	count;

	count = 0;
	if (v->point && !v->prec)
		v->w--;
	if (!v->point && !v->prec)
	{
		count += write(1, "-", 1);
		while ((v->w--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		while ((v->w--) > ft_max((int)ft_strlen(number + 1), v->prec))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
	}
	while ((v->prec--) > (int)ft_strlen(number) - 1)
		count += write(1, "0", 1);
	count += ft_putstr(number + 1);
	return (count);
}

static int	ft_print_w(char *number, t_buffer *v)
{
	int	count;

	count = 0;
	if (!v->prec)
	{
		while ((v->w--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
	}
	else
	{
		while ((v->w--) > ft_max((int)ft_strlen(number + 1), v->prec))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((v->prec--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
	}
	count += ft_putstr(number + 1);
	return (count);
}

static int	ft_print_minus_w(char *number, t_buffer *v)
{
	int	count;
	int	prec;

	count = 0;
	count += write(1, "-", 1);
	prec = v->prec;
	if (!v->prec)
	{
		count += ft_putstr(number + 1);
		while ((v->w--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
	}
	else
	{
		while ((prec--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
		count += ft_putstr(number + 1);
		while ((v->w--) > ft_max((int)ft_strlen(number + 1), v->prec))
			count += write(1, " ", 1);
	}
	return (count);
}

int	ft_format_putnbr(t_buffer *v, long long nb)
{
	int		count;
	char	*number;

	count = 0;
	if (nb >= 0)
		count += ft_format_putposnbr(v, nb);
	else
	{
		number = ft_itoa(nb);
		if (v->prec && v->w)
			v->w--;
		if (v->minus)
			count += ft_print_minus_w(number, v);
		else if (v->zero)
			count += ft_print_zeroes(number, v);
		else
			count += ft_print_w(number, v);
		free(number);
	}
	return (count);
}
