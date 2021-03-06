/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:42:34 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 08:52:34 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_apply_exit_norm(char **argv, t_exec *exec, int count)
{
	if (!is_all_num(argv[count - 1]))
	{
		printf("exit\n");
		printf("minishell: exit : %s: numeric argument required\n",
			argv[count - 1]);
		exec->env.exit_value = 255;
		return (1);
	}
	if (is_all_num(argv[count - 1]) && ft_atoi(argv[count - 1]) > 255)
	{
		printf("exit\n");
		exec->env.exit_value = ft_atoi(argv[count - 1]) % 256;
		return (1);
	}
	if (is_all_num(argv[count - 1]) && ft_atoi(argv[count - 1]) < 255)
	{
		printf("exit\n");
		exec->env.exit_value = ft_atoi(argv[count - 1]);
		return (1);
	}
	return (0);
}

int	ft_exit_norm(char **argv, t_exec *exec)
{
	if (!is_all_num(argv[1]))
	{
		printf("exit\n");
		printf("minishell : exit : %s : numeric argument reuquired\n",
			argv[1]);
		exec->env.exit_value = 255;
		return (1);
	}
	return (0);
}

int	apply_exit(char **argv, t_exec *exec)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1)
	{
		printf("exit\n");
		exit(exec->env.exit_value % 255);
	}
	if (count > 2)
	{
		if (ft_exit_norm(argv, exec))
			return (1);
		printf("minishell: exit : too many arguments\n");
		exec->env.exit_value = 1;
		return (0);
	}
	if (count == 2)
	{
		if (ft_apply_exit_norm(argv, exec, count))
			return (1);
	}
	return (0);
}

void	ft_exit(t_exec *exec, int index, char **argv)
{
	index = 0;
	if (apply_exit(argv, exec))
		exit(exec->env.exit_value);
}
