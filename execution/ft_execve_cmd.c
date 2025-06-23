/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:08:16 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:33:06 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <signal.h>

static char	*search_cmd_in_path(char *cmd, t_executer *exec)
{
	char	**bin_paths;
	char	*new_cmd;
	int		i;

	bin_paths = get_bin_paths(exec->vars->global_vars);
	if (bin_paths == NULL)
		return (NULL);
	i = -1;
	while (bin_paths[++i] != NULL)
	{
		new_cmd = ft_strjoin_three(bin_paths[i], "/", cmd);
		if (new_cmd == NULL)
			return (NULL);
		if (access(new_cmd, X_OK) == 0)
		{
			free_double_array(bin_paths);
			return (new_cmd);
		}
		free(new_cmd);
	}
	free_double_array(bin_paths);
	return (NULL);
}

static char	*find_cmd(char *cmd, t_executer *exec)
{
	if (cmd[0] == '\0')
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	return (search_cmd_in_path(cmd, exec));
}

static void	ft_exec_child(t_executer *exec, t_ast_node *node)
{
	char	*cmd;

	restore_signals();
	safe_redirect_fds(exec);
	cmd = find_cmd(node->cmd->cmd_name, exec);
	if (cmd == NULL)
		exit(ft_cmd_not_found(exec, node->cmd->cmd_name));
	execve(cmd, node->cmd->args, exec->vars->global_vars);
	if (errno == EFAULT || errno == ENOENT)
		exit(ft_cmd_not_found(exec, node->cmd->cmd_name));
	else if (errno == EISDIR || errno == EACCES)
		exit(ft_cmd_is_directory(exec, node->cmd->cmd_name));
	exit(EXIT_FAILURE);
}

int	ft_execve_cmd(t_executer *exec, t_ast_node *node)
{
	int	prc_id;
	int	status;

	prc_id = fork();
	if (prc_id == -1)
		return (EXIT_FAILURE);
	if (prc_id == 0)
		ft_exec_child(exec, node);
	waitpid(prc_id, &status, 0);
	ignore_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
