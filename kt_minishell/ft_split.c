/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:20:03 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/21 18:15:47 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// functions from libft... temperorally, until we upload a libft to our minishell project 


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src || dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	i = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * i);
	ft_strlcpy(s2, s1, i);
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s || start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
	{
		str = malloc((sizeof(char) * (ft_strlen(s) - start + 1)));
		if (!str)
			return (NULL);
		ft_strlcpy(str, s + start, ft_strlen(s) - start + 1);
	}
	else
	{
		str = malloc((sizeof(char) * len + 1));
		if (!str)
			return (NULL);
		ft_strlcpy(str, s + start, len + 1);
	}
	return (str);
}

int	wordcount(char *str, char sep)
{
	int	i;
	int	word;

	word = 0;
	i = 1;
	if (!*str)
		return (0);
	while (str[i])
	{
		if ((str[i] == sep && str[i - 1] != sep)
			|| (str[i] != sep && str[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**getwords(char **arr, char *s, char c, int word)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] && k < word)
	{
		j = 0;
		if (s[i] && s[i] != c)
		{
			while (s[i + j] && s[i + j] != c)
				j++;
			arr[k] = ft_substr(s, i, j);
			if (!arr[k])
				return (free_arr(arr));
			k++;
			i += j;
		}
		else
			i++;
	}
	arr[k] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		word;

	if (!s)
		return (NULL);
	word = wordcount((char *)s, c);
	arr = malloc(sizeof(char *) * (word + 1));
	if (!arr)
		return (NULL);
	return (getwords(arr, (char *)s, c, word));
}
