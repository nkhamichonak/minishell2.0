/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/13 15:48:09 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exec_cmd(t_executer *exec, t_ast_node *node)
{
	int		fd_in;
	int		fd_out;

	if (node->cmd->redirects != NULL)
	{
		if (node->cmd->redirects->redir_type == 9)
		{
			fd_out = open(node->cmd->redirects->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(exec->out_fd);
			exec->out_fd = fd_out;
		}
		if (node->cmd->redirects->redir_type == 8)
		{
			fd_in = open(node->cmd->redirects->filename, O_RDONLY);
			close(exec->in_fd);
			exec->in_fd = fd_in;
		}
	}
	if (ft_strcmp(node->cmd->cmd_name, "export") == 0)
		return (ft_buildin_export(exec, node->cmd->args));
	execve_cmd(exec, node);
	close(exec->out_fd);
	exec->out_fd = dup(STDOUT_FILENO);
	close(exec->in_fd);
	exec->in_fd = dup(STDIN_FILENO);
	return (0);
}

int	ft_execution(t_executer *exec, t_ast_node *node)
{
	if (node == NULL)
		return (-1);
	exec->ast = node;
	ft_exec_recursive(exec, node);
	return (0);
}

int	ft_exec_recursive(t_executer *exec, t_ast_node *node)
{

	if (node == NULL)
		return (-1);
	if (node->type == NODE_PIPE)
		ft_exec_pipe(exec, node);
	else if (node->type == NODE_COMMAND)
		ft_exec_cmd(exec, node);
	return (0);
}