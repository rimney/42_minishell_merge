/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:57:52 by rimney            #+#    #+#             */
/*   Updated: 2022/07/08 06:00:31 by rimney           ###   ########.fr       */
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

void    ft_export_no_args_case(t_exec *exec)
{
    char **temp;
    int i;

    i = 0;
    temp = malloc(sizeof(char *) * ft_count_elements(exec->envp) + 1);
    while(exec->envp[i])
    {
        temp[i] = strdup(exec->envp[i]);
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

char    **ft_join_export(t_exec *exec, char *arg)
{
    int i;
    char **temp;

    i = 0;
    temp = exec->envp;
    exec->envp = (char **)malloc(sizeof(char *) * ft_count_elements(exec->envp) + 1 + 1);
    if(ft_find_variable_index(arg, '='))
    {
        while(temp[i])
        {
            exec->envp[i] = strdup(temp[i]);
            i++;
        }
        exec->envp[i] = strdup(arg);
        printf("| %s | has been joined  \n" , exec->envp[i]);
        exec->envp[i + 1] = 0;
    }
    return(exec->envp);
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

// int ft_check_export(char *str)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         if(!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] == '_'))
//             return (0);
//         i++;
//     }
//     return (1);
// }

void    ft_apply_export(t_exec *exec, char *new)
{
    int i;
    char **temp;
    int flag;

    i = 0;
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

void    ft_export(t_exec *exec, char **argv, int index) ////leak
{
    int i;
    int flag;

    i = 0;
    printf("PASS\n");
    if(!argv[index + 1]) // GGGGGGGG ?????? GGGGGGGGGGGGG ??????
    {
        ft_export_no_args_case(exec);
        return ;
    }
    if(!ft_find_variable_index(argv[index + 1], '='))
        return ;
    while(exec->envp[i])
    {
        if(ft_strncmp(argv[index + 1], exec->envp[i], ft_find_variable_index(argv[index + 1], '=')) == 0)
        {
            ft_export_replace(exec, argv[index + 1], i);
            printf("%s <- new\n", exec->envp[i]);
            return ;
        }
        i++;
    }
    if(ft_find_variable_index(argv[index + 1], '='))
        ft_apply_export(exec, argv[index + 1]);
}
