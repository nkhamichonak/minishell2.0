/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:51:45 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/09 19:44:49 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "libft.h"
# include "lexer.h"
# include <dirent.h>

# define ENVP_DEFAULT 0
# define ENVP_ERROR 1
# define ENVP_CRITICAL_ERROR 2

typedef struct s_vars
{
	char	**global_vars;
	int		exit_status;
}	t_vars;

int		initialise_vars(t_vars *vars, char **envp);
char	**get_envp_copy(char **envp);
void	free_envp_copy(char **envp_copy);
char	*get_env_value(char **global_vars, const char *var_name);
void	expand_exit_var(t_token *token, int exit_status, int *status);
void	expand_var(t_token **head, t_token *token, char **g_vars, int *status);
void	expand_quoted_str(t_token *token, t_vars vars, int *status);
void	parse_wildcards(t_token **tokens, int *status);
void	parse_variables(t_token **tokens, t_vars vars, int *status);
void	update_temp(t_token **temp, t_token *prev, t_token **tokens);

#endif
