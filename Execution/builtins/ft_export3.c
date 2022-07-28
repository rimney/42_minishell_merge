/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:12:20 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 09:12:45 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export_replace(t_exec *exec, char *arg, int index)
{
	char	*temp;
	int		flag;

	flag = 0;
	if (arg[ft_find_variable_index(arg, '=') + 1] == '\"')
		flag = 1;
	temp = exec->envp[index];
	exec->envp[index] = ft_mystrdup(arg, flag);
	free(temp);
}

int	ft_check_export_string(char *str)
{
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
		return (0);
	return (1);
}
