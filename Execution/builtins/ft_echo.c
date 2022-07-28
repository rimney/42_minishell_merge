/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:47:28 by rimney            #+#    #+#             */
/*   Updated: 2022/07/28 05:39:22 by rimney           ###   ########.fr       */
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

int	ft_count_elemets(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_print_echo_double_quotes(char *str, int flag, t_exec *exec)
{
	int i;
	char **holder;
	i = 0;
	if(flag)
	{
		if(ft_count_elemets(str, ' ') > 0)
		{
			holder = ft_split(str, ' ');
			while(holder[i])
			{
				if(ft_contain(holder[i], '$') ||  holder[i][0] == '$')
				{
					ft_find_expand(exec->envp, ft_mystrdup(holder[i], 0));
				}
				else
					printf("%s ", holder[i]);
				i++;
			}
			ft_free(holder);
			return ;
		}
	}
	else
	{
		while(str[i])
			printf("%c", str[i++]);
	}
}

void	ft_echo_double_quotes(char *str, t_exec *exec)
{
	int		flag;
	char	*temp;

	flag = 0;
	if(str[0] == '\"')
	{
		temp = str;
		free(str);
		str = ft_filter_command_double_quotes(str);
	 	free(temp);
	}
	if(ft_contain(str, '$'))
		flag = 1;
	ft_print_echo_double_quotes(str, flag, exec);
	// printf("%s", str);
}

char	*ft_get_expand_env(char *str)
{
	int i;
	char *ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_find_variable_index(str, '=') + 1));
	while(i < ft_find_variable_index(str, '='))
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
	free(arg);
	return (0);
}

void	ft_echo_norm(char **str, int i, t_exec *exec)
{
	while (str[i])
	{
		if (str[i][0] == '$' && !ft_contain(str[i], ' '))
		{
			ft_find_expand(exec->envp, ft_mystrdup(str[i], 0));
			i++;
		}
		else if (str[i][0] == '\'')
		{
			ft_echo_single_quote(str[i]);
			i++;
		}
		else if (str[i][0] == '\"' || ft_contain(str[i], '$'))
		{
			ft_echo_double_quotes(ft_mystrdup(str[i], 0), exec);
			i++;
			continue ;
		}
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

