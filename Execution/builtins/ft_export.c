/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:57:52 by rimney            #+#    #+#             */
/*   Updated: 2022/07/02 00:17:13 by rimney           ###   ########.fr       */
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

void    ft_2d(char **str)
{
    int i;

    i = 0;
    while(str[i])
        printf("%s ||RR<<\n", str[i++]);
}


void    ft_export(t_exec *exec, char **argv, int index)
{
    int i;
    char **temp;
    int flag;

    i = 0;
    // temp = NULL;
    flag = 0;
    if(!argv[index + 1])
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
                        printf("%d\n", ft_find_variable_index(argv[index + 1], '='));
                        ft_export_replace(exec, argv[index + 1], i);
                        printf("%s <- new\n", exec->envp[i]);
                        return ;
                }
                i++;
    }
    i = 0;
    if(ft_find_variable_index(argv[index + 1], '='))
    {
        printf("PASSED\n");
        temp = malloc(sizeof(char *) * (ft_count_elements(exec->envp) + 1));
        printf("%d\n",ft_count_elements(exec->envp));

        while(i < ft_count_elements(exec->envp))
        {
            temp[i] = strdup(exec->envp[i]);
            i++;
        }
    //     if(argv[index + 1][ft_find_variable_index(argv[index + 1], '=') + 1] == '\"')
    //        flag = 1;
        temp[i] = strdup(argv[index + 1]);
        temp[i + 1] = NULL;
    //     // if(envp[0])
    //     //     ft_free(envp);

        //ft_free(envp);
         exec->envp = temp;
       //  ft_free(temp);
      //   temp = NULL;
        ft_2d(exec->envp);
    }
}