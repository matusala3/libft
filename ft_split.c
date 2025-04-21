/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:08:01 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/21 13:02:48 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *copy_word(char const *s, int start, int len)
{
	char *word;
	int i;

	i = 0;
	word = (char *)malloc(len + 1);
	if(!word)
		return (NULL);
	while(i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int count_words(const char *s, char c)
{
	int i;
	int chr_in_word;
	int word;

	i = 0;
	chr_in_word = 0;
	word = 0;
	while(s[i])
	{
		if((s[i] != c) && (chr_in_word == 0))
		{
			word++;
			chr_in_word = 1;
		}
		else if(s[i] == c)
			chr_in_word = 0;
		i++;
	}
	return (word);
}

static int store_word(char **result, const char *s, int start, int word_i)
{
    int length = 0;

    while (s[start + length] && s[start + length] != ' ')
        length++;
    result[word_i] = copy_word(s, start, length);
    if (!result[word_i])
    {
        while (word_i--)
            free(result[word_i]);
        free(result);
        return 0;
    }
    return 1;
}



int fill_words(char **result, const char *s, char c)
{
	int i;
	int start;
	int word_i;

	start = -1;
	i = 0;
	word_i = 0;
	while(s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c && start == -1)
			start = i;
		else if ((s[i + 1] == c || s[i + 1] == '\0') && start >= 0)
		{
			if (!store_word(result, s, start, word_i))
    			return 0;
			word_i++;
			start = -1;
		}
		i++;
	}
	result[word_i] = NULL;
	return (1);
}



char **ft_split(char const *s, char c)
{
    int word_count;
    char **result;

    if (!s)
        return (NULL);

    word_count = count_words(s, c);
    result = malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return (NULL);

    if (!fill_words(result, s, c))
        return (NULL);

    result[word_count] = NULL;
    return (result);
}


//"Hello,world,thsis,is,mati"
