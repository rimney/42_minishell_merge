/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:37:07 by rimney            #+#    #+#             */
/*   Updated: 2022/07/02 18:52:39 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    **ft_env_is_last(char **envp)
{
    int i;
    char **temp;

    i = 0;
    temp = malloc(sizeof(char *) * (ft_count_elements(envp)));
    while(i < ft_count_elements(envp) - 1)
    {
        temp[i] = ft_strdup(envp[i]);
        i++;
    }
    temp[ft_count_elements(envp) - 1] = NULL;

    return (temp);
}

void    ft_unset(char *str, t_exec *exec)
{
    int i;
    int j;
    int unset;
    char **temp;

    unset = 0;
    i = 0;
    temp = NULL;
    if(ft_strncmp(str, "PWD", 3) == 0 || ft_strncmp(str, "OLDPWD", 6) == 0)
    {
        printf("YOUC CAN'T DO THAT\n");
        return ;
    }
    while (exec->envp[i])
    {
        if(ft_strncmp(str, exec->envp[i], ft_find_variable_index(exec->envp[i], '=')) == 0)
			unset = i;
		i++;
	}
    i = 0;
    j = 0;
    if(unset == ft_count_elements(exec->envp) - 1)
    {
        exec->envp = ft_env_is_last(exec->envp);
        return ;
    }
    if(unset != ft_count_elements(exec->envp) - 1)
    {
        temp = malloc(sizeof(char *) * ft_count_elements(exec->envp));
        while (exec->envp[i + 1])
        {
            if(j == unset)
                i++;
            temp[j] = strdup(exec->envp[i]);
            i++;
            j++;
        }
        temp[ft_count_elements(exec->envp)] = NULL;
    //    ft_free(exec->envp);
        exec->envp = temp;
    }
}