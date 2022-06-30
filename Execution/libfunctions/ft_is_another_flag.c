/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_another_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:55:27 by rimney            #+#    #+#             */
/*   Updated: 2022/06/30 16:57:08 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_is_another_flag(t_exec *exec, int index)
{
	if(ft_strcmp(exec->command[index], ">>") == 0)
		return(APPEND);
	else if(ft_strcmp(exec->command[index], "|") == 0)
		return(PIPE);
	else if(ft_strcmp(exec->command[index], ">") == 0)
		return(REDIROUT);
	else if(ft_strcmp(exec->command[index], "<") == 0)
		return(REDIRIN);
	else if(ft_strcmp(exec->command[index], "<<") == 0)
		return(HEREDOC);
	return (0);
}

