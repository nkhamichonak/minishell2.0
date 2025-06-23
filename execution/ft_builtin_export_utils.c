/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:22:41 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:42:57 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	add_env_var(char ***env, char *var, char *new_value)
{
	int		index;
	char	**new_env;
	char	*joined;

	index = env_count(*env);
	new_env = reallocate_env_nodes(*env, index + 1);
	if (new_env == NULL)
		return (EXIT_FAILURE);
	*env = new_env;
	joined = ft_strjoin(var, new_value);
	if (joined == NULL)
		return (EXIT_FAILURE);
	(*env)[index] = joined;
	return (EXIT_SUCCESS);
}

static char	*create_new_value(char *value)
{
	char	*new_value;

	if (value == NULL)
		value = "";
	new_value = ft_strjoin("=", value);
	if (new_value == NULL)
		return (NULL);
	return (new_value);
}

static int	update_or_add_env_var(char ***env, char *var, char *new_value)
{
	int		index;
	char	*joined;

	index = get_env_index(*env, var);
	if (index != -1 && (*env)[index] != NULL)
	{
		free((*env)[index]);
		joined = ft_strjoin(var, new_value);
		if (joined == NULL)
		{
			free_ptr(new_value);
			return (EXIT_FAILURE);
		}
		(*env)[index] = joined;
	}
	else
	{
		if (add_env_var(env, var, new_value) == EXIT_FAILURE)
		{
			free_ptr(new_value);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	set_var_value(char ***env, char *var, char *value)
{
	char	*new_value;

	new_value = create_new_value(value);
	if (new_value == NULL)
		return (EXIT_FAILURE);
	if (update_or_add_env_var(env, var, new_value) == EXIT_FAILURE)
	{
		free_ptr(new_value);
		return (EXIT_FAILURE);
	}
	free_ptr(new_value);
	return (EXIT_SUCCESS);
}

char	**reallocate_env_nodes(char **env, int count)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i] && i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i-- > 0)
				free_ptr(new_env[i]);
			free(new_env);
			return (NULL);
		}
		free_ptr(env[i]);
		i++;
	}
	free(env);
	return (new_env);
}
