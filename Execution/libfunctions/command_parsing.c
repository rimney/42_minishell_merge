/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:23:45 by rimney            #+#    #+#             */
/*   Updated: 2022/07/22 05:47:59 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_locate_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	return (env[i]);
}

int	ft_count_elements(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_filter_command(char *command)
{
	char	*ret;
	int		i;

	i = 0;
	if (ft_is_space(command))
		return (command);
	while (command[i] && command[i] != ' ')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (command[i] != ' ')
	{
		ret[i] = command[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_exec_command(char **envp, char *command)
{
	int		i;
	char	*ret;
	char	**env;
	char	**temp;

	i = 0;
	env = NULL;
	if((access(command, F_OK) == 0 && command[0] == '/') || command[0] == '.')
		return (command);
	if(ft_strcmp(command, "ls") == 0 && ft_path_exists(envp))
		return ("/bin/ls");
	temp = ft_split(ft_locate_env(envp) + 5, ':');
	env = malloc(sizeof(char *) * (ft_count_elements(temp)));
	while(temp[i])
	{
		env[i] = ft_strjoin(temp[i], "/", command);
		i++;
	}
	i = 0;
	while (env[i])
	{
		if (access(env[i], F_OK) == 0)
		{
			ret = strdup(env[i]);
			return (ret);
		}
		i++;
	}
	return (0);
}