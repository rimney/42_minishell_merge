/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:27:20 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 08:39:48 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_get_env(t_exec *exec, char **env)
{
	int	i;

	i = 0;
	exec->err_flag = 0;
	exec->envp = malloc(sizeof(char *) * (ft_count_elements(env) + 2));
	while (i < ft_count_elements(env))
	{
		exec->envp[i] = strdup(env[i]);
		i++;
	}
	exec->envp[i] = 0;
}
