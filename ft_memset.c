/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:46:25 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/16 12:45:16 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memset(void *s, int c, size_t n)
{
    size_t i;
    unsigned char val = (unsigned char)c;
    unsigned char *ptr = (unsigned char *)s;

    i = 0;
    while(i < n)
    {
        ptr[i] = val;
        i++;
    }
    return (s);
}