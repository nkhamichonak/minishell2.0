/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:19:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 12:47:21 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	remove_env_var(t_executer *exec, int index)
{
	if (index > env_count(exec->vars->global_vars))
		return (EXIT_FAILURE);
	free_ptr(exec->vars->global_vars[index]);
	while (exec->vars->global_vars[index + 1] != NULL)
	{
		exec->vars->global_vars[index] = \
			ft_strdup(exec->vars->global_vars[index + 1]);
		if (exec->vars->global_vars[index] == NULL)
			return (EXIT_FAILURE);
		free_ptr(exec->vars->global_vars[index + 1]);
		index++;
	}
	exec->vars->global_vars = \
		reallocate_env_nodes(exec->vars->global_vars, index);
	if (exec->vars->global_vars == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_builtin_unset(t_executer *exec, char **args)
{
	int	i;
	int	index;

	i = 1;
	while (args[i] != NULL)
	{
		index = get_env_index(exec->vars->global_vars, args[i]);
		if (index != -1)
			remove_env_var(exec, index);
		i++;
	}
	return (EXIT_SUCCESS);
}
