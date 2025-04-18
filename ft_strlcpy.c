/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:40:28 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/17 18:31:10 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t i = 0;
    size_t src_len = ft_strlen(src);

    while (src[i] && i + 1 < size)
    {
        dst[i] = src[i];
        i++;
    }
    if (size > 0)
        dst[i] = '\0';

    return src_len;
}
