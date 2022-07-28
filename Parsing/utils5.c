/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:58:52 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 06:07:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequote(char *str, char chartoremmove)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == chartoremmove && !ft_isalpha(str[i + 1]))
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			i--;
		}
		i++;
	}
	return (str);
}

int	end_norm(char *str, int i)
{
	if (str[i] == '\"')
	{
		while (str[i] == '\"')
			i++;
		return (i - 1);
	}
	return (1);
}

int	find_end_index(char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = -2;
	if (c == '\"')
		end_norm(str, i);
	while (str[i])
	{
		if ((str[i] == c && ft_isalpha(str[i + 1])))
		{
			while (str[i] != ' ' && str[i])
				i++;
			return (i);
		}
		else if ((str[i] == c && str[i + 1] == ' ')
			|| (str[i] == c && !str[i + 1]))
			return (i);
		i++;
	}
	return (flag);
}

int	types(t_token *lst)
{
	if (ft_strcmp(lst->value, "|") == 0)
		lst->type = PIPE;
	else if (ft_strcmp(lst->value, "<") == 0)
		lst->type = REDIROUT;
	else if (ft_strcmp(lst->value, ">") == 0)
		lst->type = REDIRIN;
	else if (ft_strcmp(lst->value, "<<") == 0)
		lst->type = HEREDOC;
	else if (ft_strcmp(lst->value, ">>") == 0)
		lst->type = APPEND;
	else
		lst->type = WORD;
	return (lst->type);
}

int	check_if_op(char c, char s)
{
	if (c == '>' && s == '>')
		return (2);
	if (c == '<' && s == '<')
		return (2);
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
