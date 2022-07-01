/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:09:21 by rimney            #+#    #+#             */
/*   Updated: 2022/07/01 20:04:37 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *ft_mystrdup(char *s1, int flag)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if(flag)
    {
        str = malloc(sizeof(char) * strlen(s1) - 1);
        while(i < ft_strlen(s1) - 1)
        {
            if(s1[i] == '\"')
            {
                printf("flag\n");
                i++;
            }
            str[j] = s1[i];
            i++;
            j++;
        }
        str[j] = '\0';
        return (str);
    }
    else
    {
        str = malloc(sizeof(char) * strlen(s1) + 1);
        printf("%lu<<\n", strlen(s1));
        while(s1[i])
        {
            str[i] = s1[i];
            i++;
        }
        str[i] = '\0';
    }
    return (str);
}

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;
	i = 0;
	while (tab[i] != 0)
	{
		j = i;
		while (tab[j] != 0)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}



void    ft_export_no_args_case(char **envp)
{
    char **temp;
    int i;

    i = 0;
    temp = malloc(sizeof(char *) * ft_count_elements(envp) + 1);
    while(envp[i])
    {
        temp[i] = strdup(envp[i]);
        i++;
    }
    temp[i] = 0;
    ft_sort_string_tab(temp);
    i = 0;
    while(temp[i])
    {
        printf("declare -x %s\n", temp[i]);
        i++;
    }
    ft_free(temp);
}

char    **ft_join_export(char **envp, char *arg)
{
    int i;
    char **temp;

    i = 0;
    temp = envp;
    envp = (char **)malloc(sizeof(char *) * ft_count_elements(envp) + 1 + 1);
    if(ft_find_variable_index(arg, '='))
	{
		while(temp[i])
		{
			envp[i] = strdup(temp[i]);
			i++;
		}
		envp[i] = strdup(arg);
		printf("| %s | has been joined  \n" , envp[i]);
		envp[i + 1] = 0;
	}
	return(envp);
}

void	ft_export_replace(char **envp, char *arg, int index)
{
	char *temp;
    int flag;

    flag = 0;
    if(arg[ft_find_variable_index(arg, '=') + 1]  == '\"')
        flag = 1;
	temp = envp[index];
	envp[index] = ft_mystrdup(arg, flag);
	free(temp);
}


void    ft_export(char **envp, char **argv, int index)
{
    int i;
    char **temp;
    int flag;

    i = 0;
    temp = NULL;
    flag = 0;
    if(!argv[index + 1])
    {
        ft_export_no_args_case(envp);
        return ;
    }
    if(!ft_find_variable_index(argv[index + 1], '='))
    {
        printf("DDD\n");
        return ;
    }
    while(envp[i])
    {
		if(ft_strncmp(argv[index + 1], envp[i], ft_find_variable_index(argv[index + 1], '=')) == 0)
		{
			printf("%d\n", ft_find_variable_index(argv[index + 1], '='));
			ft_export_replace(exec, argv[index + 1], i);
			printf("%s <- new\n", envp[i]);
			return ;
		}
		i++;
    }
    if(ft_find_variable_index(argv[index + 1], '='))
    {

        printf("EEE\n");
        temp = malloc(sizeof(char *) * ft_count_elements(envp) + 1);
        i = 0;
        while(i < ft_count_elements(envp))
        {
            printf("%s ee\n", envp[i]);
            temp[i] = strdup(envp[i]);
            i++;
        }
        if(argv[index + 1][ft_find_variable_index(argv[index + 1], '=') + 1] == '\"')
            flag = 1;
        temp[i] = ft_mystrdup(argv[index + 1], flag);
        temp[i + 1] = NULL;
        ft_free(envp);
        envp = temp;
    }
}