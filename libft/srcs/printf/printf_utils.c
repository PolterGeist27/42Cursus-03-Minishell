/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:02:23 by diogmart          #+#    #+#             */
/*   Updated: 2023/01/03 12:20:04 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	ft_nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

void	ft_addsign(char **to_print, char sign, t_token *token)
{
	char	*tmp;
	int		len;

	if (token->plus == 0 && sign == '+')
		return ;
	len = ft_strlen(*to_print);
	tmp = malloc((len + 2) * sizeof(char));
	tmp[0] = sign;
	tmp[len + 1] = '\0';
	ft_strlcpy(tmp + 1, *to_print, len + 1);
	free(*to_print);
	*to_print = tmp;
}

int	ft_hexlen(unsigned long long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

char	*ft_itoa_hex(unsigned long long n)
{
	int					len;
	unsigned long long	num;
	char				*nb;

	num = n;
	len = ft_hexlen(num);
	if (n == 0)
		len = 1;
	nb = (char *)malloc((len + 1) * sizeof(char));
	if (!nb)
		return (0);
	nb[len] = '\0';
	if (num == 0)
		nb[0] = '0';
	while (num > 0)
	{
		nb[len - 1] = "0123456789abcdef"[num % 16];
		num = num / 16;
		len--;
	}
	return (nb);
}

void	ft_str_toupper(char **s)
{
	char	*str;

	str = *s;
	if (!str)
		return ;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}
