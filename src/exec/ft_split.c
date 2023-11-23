/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:53:58 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/23 16:00:16 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = malloc(ft_strlen((char *)s1) + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*arr;

	i = 0;
	arr = (char *)s;
	while (i < n)
	{
		arr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = malloc(sizeof(char) * (count * size));
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	size;

	i = 0;
	if (!s && s[0] == '\0')
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (len > i)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static size_t	strcount(char const *s, char c)
{
	size_t	i;
	size_t	check;

	i = 0;
	check = 0;
	while (*s)
	{
		if (*s != c && check == 0)
		{
			i++;
			check = 1;
		}
		if (*s == c)
			check = 0;
		s++;
	}
	return (i);
}

static size_t	getstart(char const *s, char c, size_t start)
{
	while (s[start] != '\0')
	{
		while (s[start] == c)
		{
			start++;
		}
		return (start);
	}
	return (start);
}

static size_t	getlen(char const *s, char c, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		i++;
		return (len);
	}
	return (len);
}

static void	ft_free(char **new, size_t o)
{
	while (o > 0)
	{
		free(new[o - 1]);
		o--;
	}
	free(new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	o;
	size_t	start;

	i = 0;
	o = 0;
	if (!s)
		return (NULL);
	new = ft_calloc(sizeof(char *), strcount(s, c) + 1);
	if (new == NULL)
		return (NULL);
	while (o < strcount(s, c))
	{
		start = getstart(s, c, i);
		i = getstart(s, c, i);
		new[o] = ft_substr(s, start, getlen(s, c, i));
		if (new[o] == NULL)
			return (ft_free(new, o), NULL);
		i = i + getlen(s, c, i);
		o++;
	}
	new[o] = NULL;
	return (new);
}
