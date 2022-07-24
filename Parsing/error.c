/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:48:12 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/24 21:59:56 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size_new_line(char *str)
{
	int	i;
	int	c;
	int	size;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (check_if_op(str[i], str[i + 1]) && (!ft_isspace(str[i - 1])
				|| !ft_isspace(str[i + 1])))
			c = c + 2;
		i++;
	}
	size = ft_strlen(str) + c;
	return (size);
}

char	*get_new_line(char *str, char *tab, int i, int j)
{
	while (str[i])
	{
		if (check_if_op(str[i], str[i + 1]) == 2)
		{
			tab[j++] = ' ';
			tab[j++] = str[i++];
			tab[j++] = str[i];
			tab[j] = ' ';
		}
		else if ((check_if_op(str[i], str[i + 1]) && (!ft_isspace(str[i - 1])
					|| !ft_isspace(str[i + 1]))))
		{
			tab[j++] = ' ';
			tab[j++] = str[i];
			tab[j] = ' ';
		}
		else
			tab[j] = str[i];
		j++;
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

char	*fix_line(char *str)
{
	char	*tab;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = get_size_new_line(str);
	tab = (char *)malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	tab = get_new_line(str, tab, i, j);
	return (tab);
}

void	help_rep_redir(char str, char c, int *count, int *count_redir)
{
	if (str == c)
		(*count)++;
	else if (*count != 0)
	{
		if (*count == 2 || *count == 1)
			(*count_redir)++;
		*count = 0;
	}
}

void	help_rep_pipe(char str, char c, int *count, int *count_pipe)
{
	if (str == c)
		(*count)++;
	else if (*count != 0)
	{
		if (*count == 1)
			(*count_pipe)++;
		*count = 0;
	}
}
