/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putaddress2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:22:03 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_paddmw1(char *hexastr, t_buffer *v, int prec, int len)
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
	while ((v->w--) > prec)
		count += write(1, " ", 1);
	return (count);
}

int	ft_paddz2(char *hexastr, t_buffer *v, int len)
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
	while ((v->w--) > len)
		count += write(1, "0", 1);
	while ((v->prec--) > len)
		count += write(1, "0", 1);
	return (count);
}

int	ft_paddz1(char *hexastr, t_buffer *v, int prec, int len)
{
	int	count;

	count = 0;
	while ((v->w--) > prec)
		count += write(1, " ", 1);
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
	return (count);
}

int	ft_paddw2(char *hexastr, t_buffer *v, int len)
{
	int	count;

	count = 0;
	while ((v->w--) > len)
		count += write(1, " ", 1);
	if (v->space)
		count += write(1, " ", 1);
	if (v->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
		count += write(1, "0x", 2);
	while ((v->prec--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

int	ft_paddw1(char *hexastr, t_buffer *v, int prec, int len)
{
	int	count;

	count = 0;
	while ((v->w--) > prec)
		count += write(1, " ", 1);
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
	return (count);
}
