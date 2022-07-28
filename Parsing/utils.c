/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:00:29 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 03:56:55 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clean_lst_token(t_token *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->value[i])
		{
			if (lst->value[i] == '\200')
				lst->value[i] = ' ';
			i++;
		}
	lst = lst->next;
	}
}

char	*ft_strsub(char *s, int start, int len)
{
	int		i;
	char	*tmp;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	if (start > j)
		return (NULL);
	tmp = protected_malloc(len);
	if (tmp == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		tmp[i] = s[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*init_props(char *stro)
{
	char	*str;

	str = ft_strdup(stro);
	str = remove_char(str, ' ');
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
