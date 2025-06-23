/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution_groups.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/14 12:36:07 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exec_and(t_executer *exec, t_ast_node *node)
{
	int	resault;

	resault = ft_exec_recursive(exec, node->left);
	if (errno != 0)
		return (resault);
	if (resault == 0)
		return (ft_exec_recursive(exec, node->right));
	return (resault);
}

int	ft_exec_or(t_executer *exec, t_ast_node *node)
{
	exec->vars->exit_status = ft_exec_recursive(exec, node->left);
	if (exec->vars->exit_status)
		return (ft_exec_recursive(exec, node->right));
	return (exec->vars->exit_status);
}

int	ft_exec_seq(t_executer *exec, t_ast_node *node)
{
	exec->vars->exit_status = ft_exec_recursive(exec, node->left);
	exec->red_status = 0;
	restore_fd(exec);
	exec->vars->exit_status = ft_exec_recursive(exec, node->right);
	return (exec->vars->exit_status);
}

int	ft_exec_group(t_executer *exec, t_ast_node *node)
{
	pid_t		pid;
	int			status;

	if (node->group_redirs != NULL)
		ft_redirection_group(exec, node);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exec->vars->exit_status = ft_exec_recursive(exec, node->subtree);
		ft_exec_clean(exec);
		exit(exec->vars->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
