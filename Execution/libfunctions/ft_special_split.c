/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:44:32 by rimney            #+#    #+#             */
/*   Updated: 2022/07/22 21:43:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void				ft_bzero(void *b, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
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
	void *ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}


static	int	wc(const char *s, char c)
{
	int	counter;
	int	flag;
    unsigned char    q;

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

static	size_t	len_count(const	char *s, char c)
{
	char    q;
    size_t     i;

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

static	char	**abortmission(char **final, int i)
{
	if (i != 0)
	{
		while (i >= 0)
		{
			free(final[i]);
			i--;
		}
	}
	free(final);
	return (NULL);
}

static	char	**fill_it(char *s, char c, char **final)
{
	int	i;
	int	flag;
    char    q;

    q = 0;
	flag = 1;
	i = -1;
	while (*s)
	{
		while (*s == c && !q)
		{
			s++;
			flag = 1;
		}
        if (*s == '\"')
            q = !q;
		if (*s != c && flag == 1 && *s)
		{	
			final[++i] = (char *)ft_calloc(len_count(s, c) + 1, sizeof(char));
			if (final[i] == NULL)
				return (abortmission(final, i));
			ft_strlcpy(final[i], s, len_count(s, c) + 1);
			flag = 0;
		}
		if (*s)
			s++;
	}
	return (final);
}

char	**ft_split_special(char *s, char c)
{
	char	**final;

	if (s == NULL)
		return (NULL);
	final = (char **)ft_calloc((size_t)wc(s, c), sizeof(char *));
	if (final == NULL)
		return (NULL);
	final = fill_it(s, c, final);
	return (final);
}

// int main(int ac, char **av)
// {
//     int i;

//     i = 0;
//     char **str;
//     printf("%d\n", wc(av[1], ' '));
//     str = ft_split(av[1], ' ');
//     while(str[i])
//         printf("'%s'\n", str[i++]);
// }