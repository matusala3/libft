/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:44:56 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/21 15:39:48 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

void ft_putnbr_fd(int n, int fd)
{
    long num = n;
    if (num < 0)
	{
		ft_putchar_fd('-', fd);
        num = -num;
		ft_putnbr_fd(num, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
    ft_putchar_fd(num + '0', fd);
}