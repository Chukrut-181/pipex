/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:10:39 by igchurru          #+#    #+#             */
/*   Updated: 2024/09/25 10:51:08 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* This function finds a string inside another string and returns a pointer
to the first matching element. Only scans a given len. In this case it is 
used to filter out all env variables except the line that begins "PATH=" */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (haystack[i + j] == '\0' && needle[j] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

/* Appends s2 to the end of s1 and null terminates the result. Returns a
pointer (s3) to the newly created string with a memory allocation. Freeing it
is to be handled by the caller. */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 && s2)
	{
		lens1 = ft_strlen(s1);
		lens2 = ft_strlen(s2);
		s3 = (char *)malloc(1 * (lens1 + lens2 + 1));
		if (s3 == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			s3[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			s3[lens1] = s2[i];
			lens1++;
		}
		s3[lens1] = '\0';
		return (s3);
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (0 < n)
	{
		*p = 0;
		p++;
		n--;
	}
}
