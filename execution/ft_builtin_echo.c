/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:28 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:32:16 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	is_n_key(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] != '\0' && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

static void	echo_print(t_executer *exec, char **args, int n_key, int i)
{
	safe_redirect_fds(exec);
	if (args[i] == NULL)
	{
		if (n_key == 0)
			ft_putchar_fd('\n', STDOUT_FILENO);
		ft_exec_clean(exec);
		exit (EXIT_SUCCESS);
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
	ft_exec_clean(exec);
	exit (EXIT_SUCCESS);
}

int	ft_builtin_echo(t_executer *exec, char **args)
{
	int		i;
	int		n_key;
	pid_t	pid;
	int		status;

	i = 1;
	n_key = 0;
	while (args[i] != NULL && is_n_key(args[i]) == 1)
	{
		n_key = 1;
		i++;
	}
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		echo_print(exec, args, n_key, i);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
