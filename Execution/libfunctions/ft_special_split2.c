/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_split2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:48:59 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 08:10:22 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_bzero(void *b, size_t n)
{
	unsigned char		*dest;
	size_t				i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}

int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (src[count] != '\0')
		++count;
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

int	wc(const char *s, char c)
{
	int				counter;
	int				flag;
	unsigned char	q;

	q = 0;
	flag = 1;
	counter = 0;
	while (*s)
	{
		while (*s == c && !q)
		{
			s++;
			flag = 1;
		}
		if (*s == '\"')
			q = !q;
		if ((*s != c && flag == 1) && *s)
		{
			counter++;
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (counter + 1);
}

size_t	len_count(const char *s, char c)
{
	char	q;
	size_t	i;

	i = 0;
	q = 0;
	while (*s && (*s != c || q))
	{
		if (*s == '\"')
			q = !q;
		i++;
		s++;
	}
	return (i);
}
