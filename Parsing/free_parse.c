/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:27:53 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/23 00:30:05 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst_token(t_token *lst)
{
	t_token	*prev;

	while (lst)
	{	
		if (lst->value)
			free(lst->value);
		prev = lst;
		lst = lst->next;
		free(prev);
	}
}

void	free_lst_redir(t_redir *lst)
{
	t_redir	*prev;

	while (lst)
	{
		prev = lst;
		lst = lst->next;
		free(prev);
	}
}

void	*handle_error(char *str)
{
	printf("%s", str);
	g_flag = 1;
	rl_on_new_line();
	return (NULL);
}
