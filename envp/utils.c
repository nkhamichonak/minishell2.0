/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:53:17 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/10 16:51:23 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

char	*get_env_value(char **global_vars, const char *var_name)
{
	int		i;
	size_t	len;

	if (!global_vars || !var_name)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (global_vars[i])
	{
		if (ft_strncmp(global_vars[i], var_name, len) == 0
			&& global_vars[i][len] == '=')
			return ((global_vars[i] + len + 1));
		i++;
	}
	return ("");
}

char	**get_envp_copy(char **envp)
{
	int		i;
	int		count;
	char	**envp_copy;

	count = 0;
	while (envp[count])
		count++;
	envp_copy = malloc((count + 1) * sizeof(char *));
	if (envp_copy == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (envp_copy[i] == NULL)
		{
			free_envp_copy(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

void	free_envp_copy(char **envp_copy)
{
	int		i;

	if (!envp_copy)
		return ;
	i = 0;
	while (envp_copy[i])
	{
		free(envp_copy[i]);
		i++;
	}
	free(envp_copy);
	envp_copy = NULL;
}

int	initialise_vars(t_vars *vars, char **envp)
{
	char	**envp_copy;

	envp_copy = get_envp_copy(envp);
	if (envp_copy == NULL)
		return (ENVP_CRITICAL_ERROR);
	vars->global_vars = envp_copy;
	vars->exit_status = 0;
	return (ENVP_DEFAULT);
}

void	update_temp(t_token **temp, t_token *prev, t_token **tokens)
{
	if (prev)
		*temp = prev->next;
	else
		*temp = *tokens;
}
