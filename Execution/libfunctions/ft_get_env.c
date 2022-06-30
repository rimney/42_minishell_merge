/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:27:20 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 16:28:58 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_get_env(t_exec *exec, char **env)
{
    int     i;

    i = 0;
    exec->envp = malloc(sizeof(char *) * ft_count_elements(env) + 1);
    while(i < ft_count_elements(env))
    {
        exec->envp[i] = strdup(env[i]);
        i++;
    }
    exec->envp[i] = 0;
   // return (envp);
} 
