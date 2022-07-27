/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/27 10:11:23 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo_single_quote(char *str)
{
	size_t	i;

	i = 1;
	while (i < ft_strlen(str) - 1)
		printf("%c", str[i++]);
}

int	ft_handle_quotes(char *str)
{
	char	s[1000];
	int i;
	int	k;
	int	c = 0;
	//int next_quote;

	k = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == '"')
		{
			while (str[i] && str[i] == '"')
			{
				i++;
				c++;
			}
			if (!str[i] && c % 2)
			{
				printf("quotes error\n");
				return 0;
			}
		}
		while (str[i] && str[i] != '"')
				s[k++] = str[i++];
		if (str[i] != '"')
			i++;
	}
	s[k] = '\0';
	printf("%s ", s);
	return (1);
}


// void	ft_echo_double_quotes(char *str)
// {
// 	// char	*temp;

// 	// temp = str;
// 	// str = ft_filter_command_double_quotes(str);
// 	// free(temp);
// 	ft_handle_quotes(str);
// 	// printf("%s", str);
// }

int	ft_find_expand(char **envp, char *arg)
{
	int		i;
	char	*temp;
	char	*mounir;
	
	i = 0;
	if(ft_contain(arg, '\"'))
	{
		mounir = arg;
		arg = ft_filter_command_double_quotes(arg);
		free(mounir);
	}
	//printf("%s <<\n", arg);
	while (envp[i])
	{
		if (ft_strncmp(arg + 1, envp[i],
				ft_find_variable_index(envp[i], '=')) == 0)
		{
			temp = ft_mystrdup(envp[i], 0);
			printf("%s", temp + ft_find_variable_index(arg + 1, '=') + 1);
			free(temp);
			free(arg);
			return (1);
		}
		i++;
	}
	free(arg);
	return (0);
}

void	ft_echo_norm(char **str, int i, t_exec *exec)
{
	while (str[i])
	{
		if (str[i][0] == '$' || ft_contain(str[i], '$'))
		{
			ft_find_expand(exec->envp, ft_mystrdup(str[i], 0));
			i++;
		}
		else if (str[i][0] == '\'')
		{
			ft_echo_single_quote(str[i]);
			i++;
		}
		// else if (str[i][0] == '\"')
		// {
		// 	ft_echo_double_quotes(str[i]);
		// 	i++;
		// 	continue ;
		// }
		if (!str[i])
			break ;
			printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_echo(char **str, t_exec *exec)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (ft_echo_edge_case(str[i]))
	{
		flag = 1;
		while (ft_echo_edge_case(str[i]))
			i++;
	}
	ft_echo_norm(str, i, exec);
	if (!flag)
		printf("\n");
	exec->env.exit_value = 0;
	return (1);
}

