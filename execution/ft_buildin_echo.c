/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:28 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/11 15:40:34 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int is_n_key(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0' && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

static void	echo_print(char **args, int n_key, int i)
{
	if (args[i] == NULL)
	{
		if (n_key == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && n_key == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	ft_buildin_echo(char **args)
{
	int	i;
	int	n_key;

	i = 1;
	n_key = 0;
	while (args[i] != NULL && is_n_key(args[i]) == 1)
	{
		n_key = 1;
		i++;
	}
	echo_print(args, n_key, i);
	return(EXIT_SUCCESS);
}