/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:52:57 by rimney            #+#    #+#             */
/*   Updated: 2022/07/21 17:54:52 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void    ft_putnbr(int nb)
{
    long nbr;
    char c;

    nbr = (long)nb;
    if(nbr < 0)
    {
        nbr = -nbr;
        write(1, "-", 1);
    }
    if(nb < 10)
    {
        c = nb + '0';
        write(1, &c, 1);
    }
    else
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
}