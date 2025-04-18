/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:47:20 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/16 20:11:54 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t i;
    size_t j;

    i = 0;
    if (*needle == '\0')
        return ((char *)haystack);
    while (len > i)
    {
        j = 0;
        while(i + j < len && haystack[i + j] == needle[j])
        {
            if(needle[j] == '\0')
            return((char *)&haystack[i]);
            j++;
        }
        if (needle[j] == '\0')
            return ((char *)&haystack[i]);
        i++;
    }
    return (NULL);
}