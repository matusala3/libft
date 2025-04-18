/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:18:48 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:55 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// It searches through a block of memory, byte by byte,
// looking for the first occurrence of a given value.
//also later n change it to pointer and use * instead of [](like array)
void *ft_memchr(const void *s, int c, size_t n)
{
    int i;

    i = 0;
    while(i < n)
    {
        if(((const unsigned char *)s)[i] == c){
            return (void *)((unsigned char *)s +i);
        }
        i++;
    }
    return (NULL);
}