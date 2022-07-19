/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:37:07 by rimney            #+#    #+#             */
/*   Updated: 2022/07/19 02:11:58 by rimney           ###   ########.fr       */
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

int ft_get_unset(char **envp, char *str)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if(ft_strncmp(str, envp[i], ft_find_variable_index(envp[i], '=')) == 0 ||
            ft_strcmp(str, envp[i]) == 0)
			return (i);
		i++;
	}
    return (0);
}

char    **ft_new_unset(char **envp, int index)
{
    int i;
    int j;

    i = 0;
    j = 0;
    int k = 0;
    char **temp;
    temp = malloc(sizeof(char *) * (ft_count_elements(envp) + 1));

    while (i < ft_count_elements(envp))
    {
        if(i != index)
            temp[j++] = strdup(envp[i]);
        i++;
    }
    temp[j] = NULL;
    // while(temp[k])
    // {
    //     printf("%s <\n", temp[k++]);
    // }
    return (temp);
}

void    ft_unset(char *str, t_exec *exec)
{
    int i;
    int j;
    int unset;
    char **temp;

    unset = ft_get_unset(exec->envp, str);
    i = 0;
    temp = exec->envp;
    if(!unset)
        return ;
    if(ft_strncmp(str, "PWD", 3) == 0 || ft_strncmp(str, "OLDPWD", 6) == 0)
    {
        printf("YOUC CAN'T DO THAT\n");
        return ;
    }
    i = 0;
    j = 0;
    // exec->envp = malloc(sizeof(char *) * (ft_count_elements(exec->envp) + 1));
    // if(unset == ft_count_elements(exec->envp) - 1)
    // {
    //     printf("FALAAAGGG\n");
    //     temp = exec->envp;
    //     exec->envp = ft_env_is_last(exec->envp);
    //     ft_free(temp);
    //     return ;
    // }
    // else
    // {
       temp = exec->envp;
        exec->envp = ft_new_unset(exec->envp, unset);
       ft_free(temp);
    // }

    // while(i < ft_count_elements(temp))
    // {
    //     if(i != unset)
    //         exec->envp[j++] = strdup(temp[i]);
    //     i++;
    // }
    // exec->envp[i] = NULL;
    // if(unset != ft_count_elements(exec->envp) - 1)
    // {
    //     temp = malloc(sizeof(char *) * ft_count_elements(exec->envp));
    //     while (exec->envp[i + 1])
    //     {
    //         if(j == unset)
    //             i++;
    //         temp[j] = strdup(exec->envp[i]);
    //         i++;
    //         j++;
    //     }
    //     temp[ft_count_elements(exec->envp)] = NULL;
    //ft_free(temp);
        printf("%d<\n", ft_count_elements(exec->envp));
    // }
}
