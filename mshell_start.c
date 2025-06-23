/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:27 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/09 16:45:10 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_start(t_mshell *mshell, char **envp)
{
	if (initialise_vars(&mshell->vars, envp) != ENVP_DEFAULT)
		return (MINISHELL_CLEANUP);
	if (ft_exec_init(&mshell->exec, &mshell->vars) == EXIT_FAILURE)
		return (MINISHELL_CLEANUP);
	mshell->input = NULL;
	mshell->tokens = NULL;
	mshell->ast = NULL;
	mshell->prompt = "minishell> ";
	return (MINISHELL_READLINE);
}
