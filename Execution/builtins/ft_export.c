/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:57:52 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 03:54:01 by atarchou         ###   ########.fr       */
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

void	ft_apply_export(t_exec *exec, char *new)
{
	int		i;
	int		j;
	char	**temp;
	int		flag;

	i = 0;
	j = 0;
	temp = exec->envp;
	flag = 0;
	exec->envp = malloc(sizeof(char *) * (ft_count_elements(temp) + 2));
	while (temp[i])
	{
		exec->envp[i] = strdup(temp[i]);
		i++;
	}
	if (new[ft_find_variable_index(new, '=') + 1] == '\"')
		flag = 1;
	exec->envp[i] = ft_mystrdup(new, flag);
	exec->envp[i + 1] = NULL;
	ft_free(temp);
}

int	ft_check_export_replace(t_exec *exec, char **argv, int index)
{
	int	i;

	i = 0;
	while (exec->envp[i])
	{
		if (ft_strncmp(argv[index], exec->envp[i],
				ft_find_variable_index(exec->envp[i], '=')) == 0)
		{
			ft_export_replace(exec, argv[index], i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_exec *exec, char **argv)
{
	int	i;
	int	flag;
	int	index;

	index = 1;
	flag = -1;
	i = 0;
	if (!argv[index])
	{
		ft_export_no_args_case(exec);
		return ;
	}
	if (!ft_check_export_string(argv[index]))
	{
		printf("minishell : \'%s\' : not a value identifier\n", argv[index]);
		exec->env.exit_value = 1;
	}
	while (argv[index])
	{
		if (!ft_check_export_replace(exec, argv, index))
			ft_apply_export(exec, argv[index]);
		index++;
	}
}
