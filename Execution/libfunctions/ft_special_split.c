/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:44:32 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:08:02 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**abortmission(char **final, int i)
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

static	void	ft_assign(int *i, char *q)
{
	*i = -1;
	*q = 0;
}

char	**fill_it(char *s, char c, char **final, int flag)
{
	int		i;
	char	q;

	ft_assign(&i, &q);
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
	final = fill_it(s, c, final, 1);
	return (final);
}
