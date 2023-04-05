/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putposnbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	ft_print_zeroes2(char *number, int w, int prec)
{
	int	count;

	count = 0;
	while ((w--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	while ((prec--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	return (count);
}

static int	ft_print_zeroes(char *number, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (v->space)
		count += write(1, " ", 1);
	if (v->plus)
		count += write(1, "+", 1);
	if (number[0] == '0' && v->point && !v->prec)
		w++;
	if ((v->w && v->prec) || v->point)
	{
		while ((w--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
		while ((prec--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
		count += ft_print_zeroes2(number, w, prec);
	if (number[0] != '0' || (number[0] == '0' && v->point && v->prec)
		|| (number[0] == '0' && !v->point && !v->prec))
		count += ft_putstr(number);
	return (count);
}

static int	ft_print_w(char *number, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (number[0] == '0' && v->point && !v->prec)
		w++;
	while ((w--) > (int)ft_strlen(number))
		count += write(1, " ", 1);
	if (v->plus)
		count += write(1, "+", 1);
	while ((prec--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	if (v->space)
		count += write(1, " ", 1);
	if (number[0] != '0' || (number[0] == '0' && v->point && v->prec)
		|| (number[0] == '0' && !v->point && !v->prec))
		count += ft_putstr(number);
	return (count);
}

static int	ft_print_minus_w(char *number, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (number[0] == '0' && v->point && !v->prec)
		w++;
	if (v->space)
		count += write(1, " ", 1);
	if (v->plus)
		count += write(1, "+", 1);
	while ((prec--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	if (number[0] != '0' || (number[0] == '0' && v->point && v->prec)
		|| (number[0] == '0' && !v->point && !v->prec))
		count += ft_putstr(number);
	while ((w--) > (int)ft_strlen(number))
		count += write(1, " ", 1);
	return (count);
}

int	ft_format_putposnbr(t_buffer *v, unsigned long long nb)
{
	int		count;
	char	*number;

	count = 0;
	number = ft_utoa(nb);
	if (v->space || v->plus)
		v->w--;
	if (v->prec > (int)ft_strlen(number))
		v->w -= (v->prec - (int)ft_strlen(number));
	if (v->minus)
		count += ft_print_minus_w(number, v, v->w, v->prec);
	else if (v->zero)
		count += ft_print_zeroes(number, v, v->w, v->prec);
	else
		count += ft_print_w(number, v, v->w, v->prec);
	free(number);
	return (count);
}
