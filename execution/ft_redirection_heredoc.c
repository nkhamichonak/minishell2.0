/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:10:38 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/14 12:24:05 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <readline/readline.h>

static void	ft_write_heredoc(char *limeter, int fd, t_executer *exec, bool exp)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limeter) == 0)
		{
			free(line);
			break ;
		}
		if (exp == false)
		{
			expanded = expand_variables(line, exec->vars);
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

static void	write_heredoc(t_executer *exec, t_redirect *heredocs)
{
	int			fd;

	fd = open(HEREDOC_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		exit(EXIT_FAILURE);
	}
	ft_write_heredoc(heredocs->filename, fd, exec, heredocs->quoted);
	close(fd);
}

int	ft_create_heredoc(t_executer *exec, t_redirect *redirects, t_redirect *save)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		signal_heredoc();
		write_heredoc(exec, redirects);
		ft_exec_clean(exec);
		ft_free_redirects(save);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	ignore_ctrl_c();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	ft_redirection_heredoc(t_executer *exec, \
		t_redirect *redirects, t_redirect *save)
{
	ignore_signals();
	if (ft_create_heredoc(exec, redirects, save) == 130)
	{
		exec->vars->exit_status = 130;
		return (130);
	}
	else
	{
		close(exec->in_fd);
		exec->in_fd = open(HEREDOC_PATH, O_RDONLY);
		return (0);
	}
}
