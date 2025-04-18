/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:44:08 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/16 11:35:52 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;
    const unsigned char * s1 = (unsigned char *)src;
    unsigned char * s2 = (unsigned char *)dest;

    i = 0;
    while (i < n)
    {
        s2[i] = s1[i];
        i++;
    }
    return (dest);
}