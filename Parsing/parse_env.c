/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:00:18 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/23 00:30:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_var(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '$')
	{
		if (str[i])
		{
			while (str[i])
			{
				if (ft_isdigit(str[i]))
					return (0);
				i++;
			}
		}
		else
			return (0);
	}
	return (1);
}

int	parse_env(t_token **lst_token)
{
	t_token	*lst;

	lst = *lst_token;
	while (lst)
	{
		if (lst->value)
		{
			if (contain(lst->value, '$'))
			{
				if (!check_env_var(lst->value))
				{
					free(lst->value);
					free(lst);
					handle_error("wrong env variable\n");
					return (0);
				}
			}
		}
		lst = lst->next;
	}
	return (1);
}
