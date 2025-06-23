/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/09 18:16:34 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static bool	ft_builtins(t_executer *exec, t_ast_node *node)
{
	if (ft_strcmp(node->cmd->cmd_name, "exit") == 0)
		exec->vars->exit_status = ft_builtin_exit(exec, node->cmd->args);
	else if (ft_strcmp(node->cmd->cmd_name, "pwd") == 0)
		exec->vars->exit_status = ft_builtin_pwd(exec);
	else if (ft_strcmp(node->cmd->cmd_name, "export") == 0)
		exec->vars->exit_status = ft_builtin_export(exec, node->cmd->args);
	else if (ft_strcmp(node->cmd->cmd_name, "cd") == 0)
		exec->vars->exit_status = ft_builtin_cd(exec, node->cmd->args);
	else if (ft_strcmp(node->cmd->cmd_name, "env") == 0)
		exec->vars->exit_status = ft_builtin_env(exec);
	else if (ft_strcmp(node->cmd->cmd_name, "unset") == 0)
		exec->vars->exit_status = ft_builtin_unset(exec, node->cmd->args);
	else if (ft_strcmp(node->cmd->cmd_name, "echo") == 0)
		exec->vars->exit_status = ft_builtin_echo(exec, node->cmd->args);
	else
		return (false);
	return (true);
}

int	ft_exec_cmd_or_builtin(t_executer *exec, t_ast_node *node)
{
	int		status;

	if (node->cmd->redirects != NULL)
		ft_redirection(exec, node);
	if (exec->red_status)
		status = exec->red_status;
	else if (node->cmd->cmd_name == NULL)
		status = exec->vars->exit_status;
	else if (ft_builtins(exec, node) == true)
		status = exec->vars->exit_status;
	else
	{
		ignore_signals();
		status = ft_execve_cmd(exec, node);
	}
	exec->vars->exit_status = status;
	return (exec->vars->exit_status);
}

int	ft_execution(t_executer *exec, t_ast_node *node)
{
	exec->red_status = 0;
	if (node == NULL)
		return (EXIT_SUCCESS);
	exec->ast = node;
	exec->vars->exit_status = ft_exec_recursive(exec, node);
	exec->ast = NULL;
	restore_fd(exec);
	return (exec->vars->exit_status);
}

int	ft_exec_recursive(t_executer *exec, t_ast_node *node)
{
	if (node->type == NODE_PIPE)
		return (ft_exec_pipe(exec, node));
	else if (node->type == NODE_COMMAND)
		return (ft_exec_cmd_or_builtin(exec, node));
	else if (node->type == NODE_AND)
		return (ft_exec_and(exec, node));
	else if (node->type == NODE_OR)
		return (ft_exec_or(exec, node));
	else if (node->type == NODE_GROUP)
		return (ft_exec_group(exec, node));
	else if (node->type == NODE_SEQUENCE)
		return (ft_exec_seq(exec, node));
	return (exec->vars->exit_status);
}
