/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:14:53 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/14 12:25:22 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "parser.h"
# include "lexer.h"
# include "envp.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <sys/stat.h>

# define HEREDOC_PATH "/goinfre/heredoc"

extern int	g_signal;

typedef struct s_executer
{
	t_ast_node	*ast;
	t_vars		*vars;
	char		*wd;
	char		*old_wd;
	int			in_fd;
	int			out_fd;
	int			isexit;
	int			red_status;
}	t_executer;

int			ft_cmd_not_found(t_executer *exec, char *cmd);
int			ft_cmd_is_directory(t_executer *exec, char *cmd);
char		**get_bin_paths(char **env);
char		*ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int			check_limit(int sign, unsigned long long number, int count);
void		bubble_sort(char **arr, int n);
int			handle_redirection_error(char *file);
int			handle_cd_error(char *dir);
int			ft_exec_and(t_executer *exec, t_ast_node *node);
int			ft_exec_or(t_executer *exec, t_ast_node *node);
int			ft_exec_seq(t_executer *exec, t_ast_node *node);
int			ft_exec_group(t_executer *exec, t_ast_node *node);

int			ft_redirection(t_executer *exec, t_ast_node *node);
int			ft_redirection_group(t_executer *exec, t_ast_node *node);
int			ft_redirection_heredoc(t_executer *exec, \
				t_redirect *redirects, t_redirect *save);
int			ft_create_heredoc(t_executer *exec, t_redirect *redirects, \
				t_redirect *save);
int			ft_execve_cmd(t_executer *exec, t_ast_node *node);
t_redirect	*ft_reverse_redirection(t_redirect *redirects);
int			ft_redirection_out(t_executer *exec, t_redirect *redirects);
int			ft_redirection_append(t_executer *exec, t_redirect *redirects);
int			ft_redirection_in(t_executer *exec, t_redirect *redirects);

void		ft_free_redirects(t_redirect *redirects);
char		*text_until_dollar(char *result, char *start, char *var_start);
char		*handle_special_var_exit(char *result, t_vars *vars);
char		*process_variable(char *result, char **start, \
				char *var_start, t_vars *vars);
char		*expand_variables(char *line, t_vars *vars);

int			init_env(t_executer *exec, char **env);
int			init_wds(t_executer *exec);
int			ft_exec_init(t_executer *exec, t_vars *vars);
int			ft_exec_pipe(t_executer *exec, t_ast_node *node);
int			ft_execution(t_executer *exec, t_ast_node *node);
int			ft_exec_recursive(t_executer *exec, t_ast_node *node);

int			ft_builtin_cd(t_executer *exec, char **args);
int			ft_builtin_echo(t_executer *exec, char **args);
int			ft_builtin_env(t_executer *exec);
int			ft_builtin_exit(t_executer *exec, char **args);
int			ft_builtin_export(t_executer *exec, char **args);
int			ft_builtin_pwd(t_executer *exec);
int			ft_builtin_unset(t_executer *exec, char **args);

void		free_ptr(void *ptr);
void		free_double_array(char **array);
int			check_var(char *var);
int			check_int(char *var);
void		safe_redirect_fds(t_executer *exec);
int			env_count(char **env);
int			get_env_index(char **env, char *var);
char		*get_env_var(char **env, char *var);
int			set_var_value(char ***env, char *key, char *value);
char		**reallocate_env_nodes(char **env, int count);
void		ft_exec_clean(t_executer *exec);
void		ft_exec_cleanup(t_executer *exec);
int			restore_fd(t_executer *exec);
void		restore_signals(void);
void		ignore_signals(void);
void		ignore_sigint(int sig);
void		ignore_ctrl_c(void);
void		signal_heredoc(void);

#endif