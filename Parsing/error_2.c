/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:31:36 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/30 01:20:13 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_repitition(char *stro, char c, int count)
{
	int		i;
	char	*str;
	int		count_redir;

	i = 0;
	count_redir = 0;
	str = ft_strdup(stro);
	str = remove_char(str, ' ');
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		if ((str[i] == c && str[i + 1] == '\0'))
			return (0);
		help_rep_redir(str[i], c, &count, &count_redir);
		if (count > 2)
			return (0);
		i++;
	}
	count = count_redir;
	free(str);
	return (1);
}

int	check_repitition_pipe(char *stro, char c, int count)
{
	int		i;
	char	*str;
	int		count_pipe;

	i = 0;
	count_pipe = 0;
	str = ft_strdup(stro);
	str = remove_char(str, ' ');
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		if ((str[i] == c && str[i + 1] == '\0'))
			return (0);
		help_rep_pipe(str[i], c, &count, &count_pipe);
		if (count > 1)
			return (0);
		i++;
	}
	count = count_pipe;
	free(str);
	return (1);
}

int	fix_diff(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '<')
			|| (str[i] == '<' && str[i + 1] == '>'))
			return (0);
		i++;
	}
	return (1);
}

int	check_redir_correctness(char *str)
{
	char	*redir_in;
	char	*redir_out;
	char	*pipes;
	int		tab[2];

	tab[1] = 0;
	redir_in = "<";
	redir_out = ">";
	pipes = "|";
	tab[0] = 0;
	while (str[tab[0]] == ' ' && str[tab[0]])
		tab[0]++;
	if (!fix_diff(str) || str[tab[0]] == '|')
		return (0);
	tab[0] = 0;
	while (redir_in[tab[0]] && redir_out[tab[0]] && pipes[tab[0]])
	{
		if (!check_repitition(str, redir_in[tab[0]], tab[1])
			|| !check_repitition(str, redir_out[tab[0]], tab[1])
			|| !check_repitition_pipe(str, pipes[tab[0]], tab[1]))
			return (0);
		tab[0]++;
	}
	return (1);
}
