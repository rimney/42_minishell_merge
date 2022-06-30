/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:20:10 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 15:50:42 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_split(t_token *first, char *s, char c)
{
	int		nbwrd_flg[2];
	t_token	*lst;
	t_token	*head;

	nbwrd_flg[0] = handle_words(s, c, first);
	if (nbwrd_flg[0] == -99)
		return (NULL);
	lst = (t_token *)malloc(sizeof(t_token));
	head = lst;
	while (nbwrd_flg[0])
	{
		while (*s == c && *s != '\0')
			s++;
		nbwrd_flg[1] = 0;
		lst = handle_quotes(lst, &nbwrd_flg[1], &s);
		lst = handle_split(lst, &nbwrd_flg[1], &s, c);
		if (*s == '\0')
			nbwrd_flg[0] = 1;
		check_token_list_end(&lst, nbwrd_flg[0]);
		lst = lst->next;
		nbwrd_flg[0]--;
	}
	free(first);
	first = head;
	return (first);
}

t_tok_red	*parser(t_tok_red *lst, char *line)
{
	int	i;

	i = 0;
	lst->lst_token = token_split(lst->lst_token, line, ' ');
	if (!lst->lst_token)
		return (lst);
	if (check_if_redir_exist(line))
		lst->lst_redir = fill_redir_lst(lst->lst_redir, lst->lst_token);
	if (!parse_env(&lst->lst_token))
		return (NULL);
	return (lst);
}
