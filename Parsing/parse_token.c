/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:06:02 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/28 06:07:21 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_words(char *s, int *count)
{
	int	i;

	i = 0;
	i++;
	while (s[i])
	{
		if (s[i] == 25)
		{
			(*count)++;
			break ;
		}
		i++;
	}
}

int	ft_words(char *s, char c)
{
	int		i;
	int		tool[2];

	i = 0;
	tool[0] = 0;
	tool[1] = 0;
	while (s[i] != '\0')
	{
		if (tool[1] == 0 && s[i] != c)
		{
			if (s[i] == '\"' || s[i] == '\'')
				count_words(s, &tool[0]);
			else
			{
				tool[1] = 1;
				tool[0]++;
			}
		}
		else if (tool[1] == 1 && s[i] == c)
		tool[1] = 0;
		i++;
	}
	return (tool[0]);
}

void	norm_fix(char *s, int j, int flag, char quote)
{
	while ((s[j] != quote && s[j] != '\0'))
	{
		if (s[j] == ' ')
			s[j] = '\200';
		j++;
		flag = 2;
	}
}

int	ft_letters(char *s, char c)
{
	int	tools[4];

	tools[0] = 0;
	tools[1] = 0;
	tools[2] = 0;
	while (s[tools[2]] != c && s[tools[2]] != '\0')
	{
		if (s[tools[2]] == '\"' && tools[0] != 2)
			tools[0] = 1;
		else if (s[tools[2]] == '\'' && tools[0] != 2)
			tools[0] = 1;
		if (tools[0] == 1 && s[tools[2]] == '\"')
		{
			tools[3] = tools[2] + 1;
			norm_fix(s, tools[3], tools[0], '\'');
		}
		else if (tools[0] == 1 && s[tools[2]] == '\'')
		{
			tools[3] = tools[2] + 1;
			norm_fix(s, tools[3], tools[0], '\"');
		}
		tools[1]++;
		tools[2]++;
	}
	return (tools[1]);
}
