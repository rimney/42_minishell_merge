 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:57:52 by rimney            #+#    #+#             */
/*   Updated: 2022/07/18 23:32:35 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_sort_string_tab(char **tab)
{
    int             i;
    int             j;
    char    *tmp;
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

char    *ft_mystrdup(char *s1,  int flag)
{
    size_t i;
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
        while(s1[i])
        {
            str[i] = s1[i];
            i++;
        }
        str[i] = '\0';
    }
    return (str);
}

void    ft_export_no_args_case(t_exec *exec)
{
    int i;
    int j;
    int flag;

    i = 0;
    ft_sort_string_tab(exec->envp);
    while(exec->envp[i])
    {
    flag = 0;
        j = 0;
        printf("declare -x ");
        while(exec->envp[i][j])
        {
            if(j != 0 && exec->envp[i][j - 1] == '=' && flag == 0)
            {
                printf("\"");
                flag = 1;
            }
            printf("%c", exec->envp[i][j]);
            j++;
        }
        if(ft_contain(exec->envp[i], '='))
            printf("\"");
        printf("\n");
        i++;
    }
}

void    ft_export_replace(t_exec *exec, char *arg, int index)
{
    char *temp;
    int flag;
    flag = 0;
    if(arg[ft_find_variable_index(arg, '=') + 1]  == '\"')
        flag = 1;
    temp = exec->envp[index];
    exec->envp[index] = ft_mystrdup(arg, flag);
    free(temp);
}

int ft_check_export_string(char *str)
{
    if(!((str[0] >= 'a' && str[0] <= 'z') ||
        (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
        return (0);
    return (1);
}

void    ft_apply_export(t_exec *exec, char *new)
{
    int i;
    int j;
    char **temp;
    int flag;

    i = 0;
    j = 0;
    temp = exec->envp;
    flag = 0;
    exec->envp = malloc(sizeof(char *) * (ft_count_elements(temp) + 2));
    while(temp[i])
    {
        exec->envp[i] = strdup(temp[i]);
        i++;
    }
    if(new[ft_find_variable_index(new, '=') + 1]  == '\"')
        flag = 1;
    exec->envp[i] = ft_mystrdup(new, flag);
    exec->envp[i + 1] = NULL;
    ft_free(temp);
}


void    ft_export(t_exec *exec, char **argv)
{
    int i;
    int flag;
    int index;

    index = 1;
    flag = -1;
    i = 0;
    if(!argv[index]) 
    {
        ft_export_no_args_case(exec);
        return ;
    }
    if(!ft_check_export_string(argv[index]))
    {
        printf("minishell : \'%s\' : not a value identifier\n", argv[index]);
        exec->env.exit_value = 1;
    }
    while(exec->envp[i])
    {
        if(ft_strncmp(argv[index], exec->envp[i], ft_find_variable_index(exec->envp[i], '=')) == 0)
        {
            ft_export_replace(exec, argv[index], i);
            return ;
        }
        i++;
    }
    while(argv[index])
        ft_apply_export(exec, argv[index++]);
}

