/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putaddress.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	ft_print_zeroes(char *hexastr, t_buffer *v, int prec)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (v->space || v->plus)
		len++;
	if (v->w && v->prec)
		count += ft_paddz1(hexastr, v, prec, len);
	else
		count += ft_paddz2(hexastr, v, len);
	count += ft_putstr(hexastr);
	return (count);
}

static int	ft_print_w(char *hexastr, t_buffer *v, int prec)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (v->space || v->plus)
		len++;
	if (ft_strncmp(hexastr, "(nil)", 6))
		len += 2;
	if (v->w && v->prec)
		count += ft_paddw1(hexastr, v, prec, len);
	else
		count += ft_paddw2(hexastr, v, len);
	count += ft_putstr(hexastr);
	return (count);
}

static int	ft_print_minus_w2(char *hexastr, t_buffer *v, int len)
{
	int	count;

	count = 0;
	if (v->space)
		count += write(1, " ", 1);
	if (v->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((v->prec--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	count += ft_putstr(hexastr);
	while ((v->w--) > len)
		count += write(1, " ", 1);
	return (count);
}

static int	ft_print_minus_w(char *hexastr, t_buffer *v, int prec)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(hexastr);
	if (v->plus || v->space)
		prec++;
	if (v->w && v->prec)
		count += ft_paddmw1(hexastr, v, prec, len);
	else
		count += ft_print_minus_w2(hexastr, v, len);
	return (count);
}

int	ft_format_putaddress(t_buffer *v, unsigned long nb)
{
	int		count;
	int		prec;
	char	*base;
	char	*hexastr;

	count = 0;
	base = "0123456789abcdef";
	if (!nb)
		hexastr = ft_strdup("(nil)");
	else
		hexastr = ft_get_hexastr(nb, base);
	prec = v->prec + 2;
	if (v->minus)
		count += ft_print_minus_w(hexastr, v, prec);
	else if (v->zero)
		count += ft_print_zeroes(hexastr, v, prec);
	else
		count += ft_print_w(hexastr, v, prec);
	free(hexastr);
	return (count);
}
