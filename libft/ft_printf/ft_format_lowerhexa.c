/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_lowerhexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:59:53 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static int	ft_print_zeroes2(char *hexastr, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (v->hash && hexastr[0] != '0')
		count += write(1, "0x", 1);
	while ((w--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	while ((prec--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

static int	ft_print_zeroes(char *hexastr, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (hexastr[0] == '0' && !v->prec)
		w++;
	if ((v->w && v->prec) || v->point)
	{
		while ((w--) > (int)ft_strlen(hexastr))
			count += write(1, " ", 1);
		if (v->hash && hexastr[0] != '0')
			count += write(1, "0x", 1);
		while ((prec--) > (int)ft_strlen(hexastr))
			count += write(1, "0", 1);
	}
	else
		count += ft_print_zeroes2(hexastr, v, w, prec);
	if (hexastr[0] != '0' || (v->prec))
		count += ft_putstr(hexastr);
	return (count);
}

static int	ft_print_w(char *hexastr, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (hexastr[0] == '0' && v->point && !v->prec)
		w++;
	while ((w--) > (int)ft_strlen(hexastr))
		count += write(1, " ", 1);
	if (v->hash && hexastr[0] != '0')
		count += write(1, "0x", 1);
	while ((prec--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	if (hexastr[0] != '0' || (hexastr[0] == '0' && v->point && v->prec)
		|| (hexastr[0] == '0' && !v->point && !v->prec))
		count += ft_putstr(hexastr);
	return (count);
}

static int	ft_print_minus_w(char *hexastr, t_buffer *v, int w, int prec)
{
	int	count;

	count = 0;
	if (v->hash && hexastr[0] != '0')
			count += write(1, "0x", 1);
	if (hexastr[0] == '0' && v->point && !v->prec)
		w++;
	while ((prec--) > (int)ft_strlen(hexastr))
			count += write(1, "0", 1);
	if (hexastr[0] != '0' || (hexastr[0] == '0' && v->point && v->prec)
		|| (hexastr[0] == '0' && !v->point && !v->prec))
		count += ft_putstr(hexastr);
	while ((w--) > (int)ft_strlen(hexastr))
		count += write(1, " ", 1);
	return (count);
}

int	ft_format_lowerhexa(t_buffer *v, unsigned long long nb)
{
	int		count;
	char	*hexastr;

	count = 0;
	hexastr = ft_get_hexastr(nb, "0123456789abcdef");
	if (v->hash && hexastr[0] != '0')
		v->w -= 2;
	if (v->prec > (int)ft_strlen(hexastr))
		v->w -= (v->prec - (int)ft_strlen(hexastr));
	if (v->minus)
		count += ft_print_minus_w(hexastr, v, v->w, v->prec);
	else if (v->zero)
		count += ft_print_zeroes(hexastr, v, v->w, v->prec);
	else
		count += ft_print_w(hexastr, v, v->w, v->prec);
	free(hexastr);
	return (count);
}
