/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:23:45 by rimney            #+#    #+#             */
/*   Updated: 2022/07/24 18:31:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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

void	ft_exec_command_norm(char **env, char *command, char **temp)
{
	int i;

	i = 0;
	while(temp[i])
	{
		env[i] = ft_strjoin(temp[i], "/", command);
		i++;
	}
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
	ft_exec_command_norm(env, command, temp);
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