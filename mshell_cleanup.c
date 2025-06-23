/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:34:07 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/09 16:36:14 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_cleanup(t_mshell *mshell)
{
	if (mshell->input)
		free(mshell->input);
	if (mshell->vars.global_vars)
		free_envp_copy(mshell->vars.global_vars);
	if (mshell->tokens)
		free_tokens(&mshell->tokens);
	if (mshell->ast)
		free_ast(&mshell->ast);
	ft_exec_cleanup(&mshell->exec);
	return (MINISHELL_EXIT);
}
