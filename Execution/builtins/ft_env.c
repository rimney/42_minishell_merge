/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:15:41 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 03:51:25 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->envp[i])
	{
		if (ft_contain(exec->envp[i], '='))
			printf("%s\n", exec->envp[i]);
		i++;
	}
}
