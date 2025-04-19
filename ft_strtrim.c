/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:51:42 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/19 10:35:56 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int is_in_set(char c, const char *set)
{
    size_t i;

    i = 0;
    while(set[i])
    {
        if (set[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char *ft_strtrim(char const *s1, char const *set)
{
    size_t i;
    size_t start;
    size_t end;
    char *res;

    i = 0;
    start = 0;
    end = ft_strlen(s1) - 1;
    if(s1 == NULL || set == NULL)
        return(NULL);
    while (s1[start] && is_in_set(s1[start], set))
        start++;
    while (end > start && is_in_set(s1[end], set))
        end--;
    return (ft_substr(s1, start, end - start + 1));
}