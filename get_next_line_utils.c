/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbeatris <fbeatris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:09:23 by fbeatris          #+#    #+#             */
/*   Updated: 2021/10/16 19:09:24 by fbeatris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	else
	{
		while (s1[i])
		{
			s2[i] = s1[i];
			i++;
		}
		s2[i] = '\0';
		return (s2);
	}
}

int	ft_strchr_n(const char *s, int c)
{
	size_t	i;
	char	*arr;
	char	cc;

	cc = c;
	arr = (char *)s;
	i = 0;
	if (s[0] == '\0')
		return (-1);
	while (arr[i] && arr[i] != cc)
		i++;
	if (arr[i] == cc)
		return (i);
	else
		return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substring(char const *s, unsigned int start, size_t len)
{
	char	*subst;
	size_t	i;
	size_t	length;

	if (!s)
		return (NULL);
	i = start;
	length = 0;
	while (s[i++] && length < len)
		length++;
	if (length == 0 || start > ft_strlen(s))
		return (ft_strdup(""));
	subst = malloc(sizeof(*s) * (length + 1));
	if (!subst)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		subst[i] = s[start + i];
		i++;
	}
	subst[i] = '\0';
	return (subst);
}
