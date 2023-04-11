/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:03:34 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:19:18 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	print(t_token *token, va_list *args)
{	
	if (token->type == 'd' || token->type == 'i')
		return (print_i(token, va_arg((*args), int)));
	else if (token->type == '%')
		return (print_percent(token));
	else if (token->type == 'c')
		return (print_c(token, va_arg((*args), int)));
	else if (token->type == 's')
		return (print_s(token, va_arg((*args), char *)));
	else if (token->type == 'p')
		return (print_p(token, va_arg((*args), unsigned long long)));
	else if (token->type == 'u')
		return (print_u(token, va_arg((*args), unsigned int)));
	else if (token->type == 'x' || token->type == 'X')
		return (print_x(token, va_arg((*args), unsigned int)));
	return (0);
}

int	find_arg(const char **str, va_list *args)
{
	t_token	*token;
	int		bytes;

	token = NULL;
	bytes = 0;
	(*str)++;
	if (init_token(&token))
		return (0);
	while (ft_strchr(TYPE, **str) == NULL)
		(*str) += get_flags(&token, *str);
	token->type = **str;
	bytes = print(token, args);
	free(token);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		bytes;

	va_start(args, str);
	bytes = 0;
	while (*str != '\0')
	{
		if (*str == '%')
			bytes += find_arg(&str, &args);
		else
			bytes += write(STDOUT_FILENO, str, 1);
		str++;
	}
	va_end(args);
	return (bytes);
}
