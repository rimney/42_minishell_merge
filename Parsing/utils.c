/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:00:29 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/03 17:30:58 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strsub(char *s, unsigned int start, int len)
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

void	print_lst(t_token *lst)
{
	while (lst)
	{
		printf("value = : %s\ntype = %d\nquote flag = : %c\n",
			lst->value, lst->type, lst->quote);
		lst = lst->next;
	}
}

void	print_redir(t_redir *lst)
{
	while (lst)
	{
		printf("file = : %s\nredir type = %d\n\n", lst->file, lst->type);
		lst = lst->next;
	}
}
