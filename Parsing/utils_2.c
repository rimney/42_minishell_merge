/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:29:54 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 01:21:01 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c < 58)
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	find_end_index(char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = -2;
	if (c == '\"')
	{
		if (str[i] == '\"')
		{
			while (str[i] == '\"')
				i++;
			return (i - 1);
		}
	}
	while (str[i])
	{
		if ((str[i] == c && str[i + 1] == ' ')
			|| (str[i] == c && !str[i + 1]))
			return (i);
		i++;
	}
	return (flag);
}
