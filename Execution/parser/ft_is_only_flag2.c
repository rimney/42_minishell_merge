/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_flag2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:55:42 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/25 01:56:33 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int only_pipe_flag(t_exec *exec)
{
	if(exec->pipe_count > 0 && exec->input_count == 0 && exec->append_count == 0
		&& exec->heredoc_count == 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}
