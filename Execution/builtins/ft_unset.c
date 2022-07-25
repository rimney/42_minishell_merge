/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:37:07 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:04:32 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_env_is_last(char **envp)
{
	int		i;
	char	**temp;

	i = 0;
	temp = malloc(sizeof(char *) * (ft_count_elements(envp)));
	while (i < ft_count_elements(envp) - 1)
	{
		temp[i] = ft_strdup(envp[i]);
		i++;
	}
	temp[ft_count_elements(envp) - 1] = NULL;
	return (temp);
}

int	ft_get_unset(char **envp, char *str)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(str, envp[i], ft_find_variable_index(envp[i], '=')) == 0
			|| ft_strcmp(str, envp[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	**ft_new_unset(char **envp, int index)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char *) * (ft_count_elements(envp) + 1));
	while (i < ft_count_elements(envp))
	{
		if (i != index)
			temp[j++] = strdup(envp[i]);
		i++;
	}
	temp[j] = NULL;
	return (temp);
}

void	ft_apply_unset(char *str, t_exec *exec)
{
	int		i;
	int		j;
	int		unset;
	char	**temp;

	if (!str)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	unset = ft_get_unset(exec->envp, str);
	i = 0;
	temp = exec->envp;
	if (!unset)
		return ;
	i = 0;
	j = 0;
	temp = exec->envp;
	exec->envp = ft_new_unset(exec->envp, unset);
	ft_free(temp);
	printf("%d<\n", ft_count_elements(exec->envp));
}

void	ft_unset(char **str, t_exec *exec)
{
	int	i;

	i = 1;
	if (!str[i])
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (str[i])
		ft_apply_unset(str[i++], exec);
}
