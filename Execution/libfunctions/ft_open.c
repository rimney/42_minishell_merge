/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 05:06:59 by rimney            #+#    #+#             */
/*   Updated: 2022/07/25 04:01:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_open(t_exec *exec, int kind, int index)
{
	int		fd;
	char	**file;

	fd = -1;
	file = ft_split(exec->command[index], ' ');
	ft_filter_command_double_quotes_2d_array(file);
	ft_filter_command_single_quote_2d_array(file);
	if (kind == 1)
		fd = open(".temp", O_CREAT | O_RDONLY | O_TRUNC, 0644);
	if (kind == REDIROUT)
		fd = open(file[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (kind == APPEND)
		fd = open(file[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (kind == REDIRIN)
	{
		fd = open(file[0], O_RDONLY);
		if (fd == -1)
		{
			ft_free(file);
			perror("minishell : ");
			return (0);
		}
	}
	ft_free(file);
	return (fd);
}
