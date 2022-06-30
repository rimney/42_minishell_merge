/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:15:29 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 01:21:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!str1 && !str2)
		return (NULL);
	while (i < n)
	{
		((char *)str1)[i] = ((char *)str2)[i];
		i++;
	}
	return (str1);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (dst > src)
	{
		while (len--)
			s1[len] = s2[len];
	}
	else
		ft_memcpy(s1, s2, len);
	return (dst);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = (char *)malloc(sizeof(*dest) * (ft_strlen(src) + 1));
	if (!dest)
		return (0);
	ft_strcpy((char *)dest, (char *)src);
	return (dest);
}

char	*protected_malloc(int size)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
