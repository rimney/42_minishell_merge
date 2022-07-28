/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:33:18 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 10:00:33 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo_edge_case(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	ft_print_echo_double_quotes(char *str, int flag, t_exec *exec, int i)
{
	char	**holder;

	if (flag)
	{
		if (ft_count_elemets(str, ' ') > 0)
		{
			holder = ft_split(str, ' ');
			while (holder[i])
			{
				if (ft_contain(holder[i], '$') || holder[i][0] == '$')
					ft_find_expand(exec->envp, holder[i]);
				else
				{
					printf("%s ", holder[i]);
					i++;
				}
				i++;
			}
			ft_free(holder);
			flag = 0;
		}
	}
	else
		printf("%s ", str);
}

void	ft_echo_double_quotes(char *str, t_exec *exec)
{
	int		flag;
	char	*temp;

	flag = 0;
	if (str[0] == '\"')
	{
		temp = str;
		str = ft_filter_command_double_quotes(str);
	}
	if (ft_contain(str, '$'))
		flag = 1;
	ft_print_echo_double_quotes(str, flag, exec, 0);
}

char	*ft_get_expand_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_find_variable_index(str, '=') + 1));
	while (i < ft_find_variable_index(str, '='))
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_find_expand(char **envp, char *arg)
{
	int		i;
	char	*temp;
	char	*xtemp;

	i = 0;
	while (envp[i])
	{
		xtemp = ft_get_expand_env(envp[i]);
		if (ft_strcmp(arg + 1, xtemp) == 0)
		{
			temp = ft_mystrdup(envp[i], 0);
			printf("%s ", temp + ft_find_variable_index(arg + 1, '=') + 1);
			free(temp);
			free(xtemp);
			return (1);
		}
		i++;
		free(xtemp);
	}
	return (0);
}
