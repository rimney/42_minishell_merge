/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:43:18 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/03 02:59:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}

int	ft_find_last_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_expand(char *expand, char **envp)
{
	int	i;

	i = 0;
	if (expand != NULL)
	{
		while (envp[i])
		{
			if (ft_strncmp(expand + 1, envp[i],
				ft_find_last_character(envp[i], '=')) == 0)	
				return (strdup(envp[i] + ft_find_last_character(envp[i], '=') + 1));
				i++;
		}
	}
	return (strdup(expand));
}

int	check_if_redir_exist(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '>')
			flag = 1;
		else if (str[i] == '<')
			flag = 1;
		else if (str[i] == '|')
			flag = 1;
		i++;
	}
	return (flag);
}
