/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:49:49 by rimney            #+#    #+#             */
/*   Updated: 2022/07/22 01:48:38 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int    ft_cd_export_replace(t_exec *exec, char *arg)
{
    int i;
    char *temp;

    i = 0;
    while(exec->envp[i])
    {
        if(ft_strncmp(exec->envp[i], arg, ft_find_variable_index(arg, '=') == 0))
        {
            temp = exec->envp[i];
            exec->envp[i] = strdup(arg);
            free(temp);
            return (1);
        }
        i++;
    }
    return (0);
}

char    *ft_strjoin_f(char *s1, char *s2)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    while(s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while(s2[j])
    {
        str[i] = s2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    return (str);
}
void    ft_cd(char *path, t_exec *exec)
{
    char *s;
    char *p;
    char *temp;

    s = getcwd(NULL, 0);
    temp = s;
    s = ft_strjoin_f("OLDPWD=", s);
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
    p = ft_strjoin_f("PWD=", p);
    free(temp);
    ft_export(exec, p);
    free(p);
    ft_export(exec, s);
    free(s);
}

