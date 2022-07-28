/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:19:15 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 05:47:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fix_norm(char *str, int i)
{
	if (str[i] == '|' && (str[i + 1] == '>' || str[i + 1] == '<'))
		return (0);
	if (str[i] == '>' && str[i + 1] == '|')
		return (0);
	if (str[i] == '<' && str[i + 1] == '|')
		return (0);
	return (1);
}

void	check_token_list_end(t_token **lst_token, int nbwords)
{
	t_token	*lst;

	lst = *lst_token;
	if (nbwords - 1 != 0)
		lst->next = (t_token *)malloc(sizeof(t_token));
	else
		lst->next = NULL;
}

int	contain(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	find_char_index(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == 1)
	{
		while (str[i] == 1)
			i++;
		return (i - 1);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-2);
}

char	*subtract(char *str, char *sub)
{
	int		len;
	char	*p;

	len = ft_strlen(sub);
	if (len > 0)
	{
		p = str;
		p = ft_strstr(p, sub);
		while (p != NULL)
		{
			ft_memmove(p, p + len, ft_strlen(p + len) + 1);
			p = ft_strstr(p, sub);
		}
	}
	return (str);
}
