/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:08:16 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:31:05 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exec_init(t_executer *exec, t_vars *vars)
{
	exec->vars = vars;
	if (init_wds(exec) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exec->vars->exit_status = 0;
	exec->red_status = 0;
	exec->ast = NULL;
	exec->isexit = 0;
	exec->in_fd = dup(STDIN_FILENO);
	if (exec->in_fd == -1)
		return (EXIT_FAILURE);
	exec->out_fd = dup(STDOUT_FILENO);
	if (exec->out_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	restore_fd(t_executer *exec)
{
	close(exec->in_fd);
	exec->in_fd = dup(STDIN_FILENO);
	if (exec->in_fd == -1)
		return (EXIT_FAILURE);
	close(exec->out_fd);
	exec->out_fd = dup(STDOUT_FILENO);
	if (exec->out_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}

void	safe_redirect_fds(t_executer *exec)
{
	if (dup2(exec->in_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 (stdin)");
		close(exec->in_fd);
		close(exec->out_fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 (stdout)");
		close(exec->in_fd);
		close(exec->out_fd);
		exit(EXIT_FAILURE);
	}
	if (close(exec->in_fd) == -1)
	{
		perror("close (in_fd)");
		exit(EXIT_FAILURE);
	}
	if (close(exec->out_fd) == -1)
	{
		perror("close (out_fd)");
		exit(EXIT_FAILURE);
	}
}

void	ft_exec_cleanup(t_executer *exec)
{
	free_ast(&exec->ast);
	if (exec->wd)
	{
		free(exec->wd);
		exec->wd = NULL;
	}
	if (exec->old_wd)
	{
		free(exec->old_wd);
		exec->old_wd = NULL;
	}
	if (exec->in_fd >= 0)
	{
		close(exec->in_fd);
		exec->in_fd = -1;
	}
	if (exec->out_fd >= 0)
	{
		close(exec->out_fd);
		exec->out_fd = -1;
	}
	unlink(HEREDOC_PATH);
}

void	ft_exec_clean(t_executer *exec)
{
	free_envp_copy(exec->vars->global_vars);
	free_ast(&exec->ast);
	if (exec->wd)
	{
		free(exec->wd);
		exec->wd = NULL;
	}
	if (exec->old_wd)
	{
		free(exec->old_wd);
		exec->old_wd = NULL;
	}
	if (exec->in_fd >= 0)
	{
		close(exec->in_fd);
		exec->in_fd = -1;
	}
	if (exec->out_fd >= 0)
	{
		close(exec->out_fd);
		exec->out_fd = -1;
	}
}
