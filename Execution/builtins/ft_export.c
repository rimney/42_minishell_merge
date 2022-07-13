/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:57:52 by rimney            #+#    #+#             */
/*   Updated: 2022/07/12 03:59:04 by rimney           ###   ########.fr       */
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

int    ft_check_export_string(char *str)
{
    if(!(str[0] >= 'a' && str[0] <= 'z' ||
        str[0] >= 'A' && str[0] <= 'Z' || str[0] == '_'))
        return (0);
    return (1);
}

void    ft_apply_export(t_exec *exec, char **new)
{
    int i;
    int j;
    char **temp;
    int flag;

    i = 0;
    temp = exec->envp;
    flag = 0;
    printf("%d <<||<\n", ft_count_elements(new));
    exec->envp = malloc(sizeof(char *) * (ft_count_elements(temp) + ft_count_elements(new) + 1));
    while(temp[i])
    {
        exec->envp[i] = strdup(temp[i]);
        i++;
    }
    j = 0;
    while(j < ft_count_elements(new))
    {
        if(new[j][ft_find_variable_index(new[j], '=') + 1]  == '\"')
        flag = 1;
        exec->envp[i] = ft_mystrdup(new[j], flag);
        j++;
        i++;
    }
   // printf("%s <<here\n", new[i]);
    exec->envp[i] = NULL;
    ft_free(temp);
}

void    ft_export(t_exec *exec, char **argv) ////leak
{
    int i;
    int flag;
    int index;

    index = 1;
    // should count the len of
  
    printf("%s << argv[index]\n", argv[index]);
    i = 0;
    if(!argv[index]) // GGGGGGGG ?????? GGGGGGGGGGGGG ??????
    {
        ft_export_no_args_case(exec);
        return ;
    }
    if(!ft_check_export_string(argv[index]))
    {
        printf("minishell : \'%s\' : not a value identifier\n", argv[index]);
        exec->env.exit_value = 1;
    }
    if(!ft_find_variable_index(argv[index], '='))
    {
        index++;
        return ;
    }
    while(exec->envp[i])
    {
        if(ft_strncmp(argv[index], exec->envp[i], ft_find_variable_index(argv[index], '=')) == 0)
        {
            ft_export_replace(exec, argv[index], i);
            printf("%s <- new\n", exec->envp[i]);
            return;
        }
        i++;
    }
    if(ft_find_variable_index(argv[index], '='))
        ft_apply_export(exec, argv + 1);
}

