/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_errors_rm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:12:16 by rimney            #+#    #+#             */
/*   Updated: 2022/07/20 17:19:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_redi_is_last(t_exec *exec)
{
    if(ft_is_another_flag(exec, ft_count_elements(exec->command - 1)) == PIPE)
        printf("minishell : syntax error near unexpected token `|\'");
    return (1);
}
