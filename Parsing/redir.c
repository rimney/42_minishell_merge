/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:10:31 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/21 15:55:23 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_redir(int type)
{
	if (type == 0)
		return (0);
	return (1);
}

int	count_redir(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (check_if_redir(lst->type))
			count++;
		lst = lst->next;
	}
	return (count);
}

void	parse_red(t_redir **red, t_token *tok, int *counts)
{
	t_redir	*lst;
	int		i;

	i = 0;
	lst = *red;
	lst->type = tok->type;
	lst->file = tok->next->value;
	if (counts[1] - 1 != 0)
		lst->next = (t_redir *)malloc(sizeof(t_redir));
	else
		lst->next = NULL;
}

t_redir	*fill_redir_lst(t_redir *lst, t_token *lst_token)
{
	t_redir	*head;
	t_token	*head_tok;
	int		counts[2];

	head = NULL;
	counts[0] = 0;
	counts[1] = count_redir(lst_token);
	head_tok = lst_token;
	if (counts[1] == 0)
		return (NULL);
	while (lst_token)
	{
		if (check_if_redir(lst_token->type))
		{
			if (!lst)
				lst = (t_redir *)malloc(sizeof(t_redir));
			parse_red(&lst, lst_token, counts);
			if (counts[0]++ == 0)
				head = lst;
			counts[1]--;
			lst = lst->next;
		}
		lst_token = lst_token->next;
	}
	return (head);
}
