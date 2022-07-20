/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:49:49 by rimney            #+#    #+#             */
/*   Updated: 2022/07/19 23:21:46 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void    ft_cd_export_replace(t_exec *exec, char *arg)
{
    int i;
    char*temp;

    i = 0;
    while(exec->envp[i])
    {
        if(ft_strncmp(exec->envp[i], arg, ft_find_variable_index(arg, '=') == 0))
        {
            temp = exec->envp[i];
            exec->envp[i] = strdup(arg);
            free(temp);
            return ;
        }
        i++;
    }   
}

void    ft_cd(char *path, t_exec *exec)
{
    char *s;
    char *p;
    char *temp;

    s = getcwd(NULL, 0);
    temp = s;
    s = ft_simple_strjoin("OLDPWD=", s);
    free(temp);
    if(chdir(path) == -1)
    {
        printf("cd: %s: no such file or directory\n", path);
        exec->env.exit_value = 1;
        free(s);
        return ;
    }
    p = getcwd(NULL, 0);
    temp = p;
    p = ft_simple_strjoin("PWD=", p);
    free(temp);
    ft_cd_export_replace(exec, p);
    free(p);
    ft_cd_export_replace(exec, s);
    free(s);
   // free(exec->command[0]);
}

