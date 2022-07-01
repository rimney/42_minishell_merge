/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:41:39 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 01:20:36 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_char(char *str, char charToRemmove)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == charToRemmove)
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

void	add_quote_lst(int *tools, char **s, t_token **lst, char *target, int *flag)
{
	if (tools[3] != -1)
	{
		(*lst)->value = ft_strsub(*s, tools[2] + 1, tools[3] - 1);
		if (tools[1] == '\"')
			(*lst)->value = remove_char((*lst)->value, '\"');
	}
	(*lst)->type = WORD;
	(*lst)->quote = tools[1];
	*flag = 1;
	target = ft_strsub(*s, tools[2], tools[3] + 1);
	*s = subtract(*s, target);
	free (target);
}

t_token	*handle_quotes(t_token *lst, int *flag, char **s)
{
	int		tools[4];
	char	*target;

	tools[0] = 0;
	tools[1] = '\'';
	while (tools[0] < 2)
	{
		if (**s == tools[1])
		{
			tools[2] = find_char_index(*s, tools[1]);
			tools[3] = find_end_index(*s + tools[2] + 1, tools[1]) + 1;
			if (tools[3] == -1 && tools[1] == '\"')
				lst->value = strdup("\0");
			else if (tools[3] == -1)
				return (handle_error("missing quote\n"));
			else if (tools[3] != -1)
				add_quote_lst(tools, s, &lst, target, flag);
			break ;
		}
		tools[0]++;
		tools[1] = '\"';
	}
	return (lst);
}

t_token	*handle_split(t_token *lst, int *flag, char **s, char c)
{
	if (*flag == 0)
	{
		lst->value = ft_strsub(*s, 0, ft_letters(*s, c));
		lst->type = types(lst);
		lst->quote = '\0';
		if (!lst->value)
			return (NULL);
	}
	*s = *s + ft_letters(*s, c);
	return (lst);
}

int	handle_words(char *s, char c, t_token *first)
{
	int	nbwords;

	nbwords = ft_words(s, c);
	if (nbwords <= 0)
	{
		free(first);
		handle_error("missing quote\n");
		return (-99);
	}
	return (nbwords);
}
