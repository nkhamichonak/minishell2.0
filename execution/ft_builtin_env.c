/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:55:08 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:32:31 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	env_print(t_executer *exec)
{
	int	i;

	safe_redirect_fds(exec);
	i = 0;
	if (exec->vars->global_vars == NULL)
		return (EXIT_FAILURE);
	while (exec->vars->global_vars[i] != NULL)
	{
		ft_putendl_fd(exec->vars->global_vars[i], STDOUT_FILENO);
		i++;
	}
	ft_exec_clean(exec);
	exit (EXIT_SUCCESS);
}

int	ft_builtin_env(t_executer *exec)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		env_print(exec);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
