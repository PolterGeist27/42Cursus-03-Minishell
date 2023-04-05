/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pealexan <pealexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:44:13 by pealexan          #+#    #+#             */
/*   Updated: 2023/02/08 10:55:40 by pealexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

int	ft_check_type_format(va_list args, t_buffer *v)
{
	int	count;

	count = 0;
	if (v->conversion_type == 's')
		count += ft_format_putstr(v, va_arg(args, char *));
	if (v->conversion_type == 'c')
		count += ft_format_putchar(v, va_arg(args, int));
	if (v->conversion_type == 'd' || v->conversion_type == 'i')
		count += ft_format_putnbr(v, va_arg(args, int));
	if (v->conversion_type == 'u')
		count += ft_format_putunsignnbr(v, va_arg(args, unsigned int));
	if (v->conversion_type == 'x')
		count += ft_format_lowerhexa(v, va_arg(args, unsigned int));
	if (v->conversion_type == 'X')
		count += ft_format_upperhexa(v, va_arg(args, unsigned int));
	if (v->conversion_type == 'p')
		count += ft_format_putaddress(v, va_arg(args, unsigned long));
	if (v->conversion_type == '%')
		count += write(1, "%", 1);
	return (count);
}

static int	ft_check(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	if (c == 'u')
		count += ft_putunsignednbr(va_arg(args, unsigned int));
	if (c == 'x' || c == 'X')
		count += ft_puthexa(va_arg(args, unsigned int), c);
	if (c == 'p')
		count += ft_putaddress(va_arg(args, unsigned long));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == '%')
				count += write(1, "%", 1);
			else if (ft_strchr(TYPE, *str))
				count += ft_check(*str, args);
			else if (ft_strchr(FLAGS, *str) || ft_isdigit(*str))
				count += ft_get_format_buffer(&str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	int	i = 0;

	i = ft_printf("|%c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%-10c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10-c|\n", 'P');
	printf("%d\n", i);
	i = ft_printf("|%10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("|%#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("|%10#x|\n", 42);
	printf("%d\n", i);
	i = printf("1|%10x|\n", 42);
	printf("%d\n", i);
    i = printf("2|%#10x|\n", 42);
	printf("%d\n", i);
	i = printf("3|%-10x|\n", 42);
	printf("%d\n", i);
    i = printf("4|%-#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("1|%10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("2|%#10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("3|%-10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("4|%-#10x|\n", 42);
	printf("%d\n", i);
	i = printf("5|%010x|\n", 42);
	printf("%d\n", i);
    i = printf("6|%0#10x|\n", 42);
	printf("%d\n", i);
    i = printf("7|%#010x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("5|%010x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("6|%0#10x|\n", 42);
	printf("%d\n", i);
    i = ft_printf("7|%#010x|\n", 42);
	printf("%d\n", i);
	i = printf(".10x - |%.10x|\n", 42);
	printf("%d\n", i);
	i = ft_printf(".10x - |%.10x|\n", 42);
	printf("%d\n", i);
    i = printf("10.x - |%10.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("10.x - |%10.x|\n", 42);
	printf("%d\n", i);
	i = printf("#.5x - |%#.5x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#.5x - |%#.5x|\n", 42);
	printf("%d\n", i);
	i = printf("#10.x - |%#10.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#10.x - |%#10.x|\n", 42);
	printf("%d\n", i);
	i = printf("#.1x - |%#.1x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#.1x - |%#.1x|\n", 42);
	printf("%d\n", i);
    i = printf("#1.x - |%#1.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("#1.x - |%#1.x|\n", 42);
	printf("%d\n", i);
	i = printf(".3x - |%.3x|\n", 42);
	printf("%d\n", i);
	i = ft_printf(".3x - |%.3x|\n", 42);
	printf("%d\n", i);
    i = printf("4.x - |%4.x|\n", 42);
	printf("%d\n", i);
	i = printf("4.x - |%4.x|\n", 42);
	printf("%d\n", i);
	i = ft_printf("|%X|\n", 42);
	printf("%d\n", i);
    i = ft_printf("|%#X|\n", 10);
	printf("%d\n", i); 
	return(0);
} */
