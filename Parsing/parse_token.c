/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:06:02 by atarchou          #+#    #+#             */
/*   Updated: 2022/07/27 21:41:47 by atarchou         ###   ########.fr       */
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
			if (s[i] == 25 || s[i] == '\'')
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

int check_quotes_existence(char *str, char quote)
{
  int i = 0;
  int count = 0;
  while (str[i]) {
    if (str[i] == quote)
      count++;
    i++;
  }
  if (count == 0)
    return (0);
  else
    return (count);
}

int ft_letters(char *s, char c)
{
	int count;
	int k;
	char quotes;
	int i;
	int flag;
	int j;

	flag = 0;
	
	k = 0;
	quotes = '\'';
	while(k < 2)
	{	count = 0;
		i = 0;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == quotes && flag != 2)
				flag = 1;
			if (flag == 1)
			{
				j = i;
				if (check_quotes_existence(s, quotes) % 2 == 0)
				{
					while (s[j] != quotes && s[j] != '\0')
					{
						if (s[j] == c)
							s[j] = '\200';
						j++;
						flag = 2;
   					}
				}
			}
			count++;
			i++;
		}
		k++;
		quotes = '\"';
	}
	return (count);
}

int	types(t_token *lst)
{
	if (ft_strcmp(lst->value, "|") == 0)
		lst->type = PIPE;
	else if (ft_strcmp(lst->value, "<") == 0)
		lst->type = REDIROUT;
	else if (ft_strcmp(lst->value, ">") == 0)
		lst->type = REDIRIN;
	else if (ft_strcmp(lst->value, "<<") == 0)
		lst->type = HEREDOC;
	else if (ft_strcmp(lst->value, ">>") == 0)
		lst->type = APPEND;
	else
		lst->type = WORD;
	return (lst->type);
}

int	check_if_op(char c, char s)
{
	if (c == '>' && s == '>')
		return (2);
	if (c == '<' && s == '<')
		return (2);
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
