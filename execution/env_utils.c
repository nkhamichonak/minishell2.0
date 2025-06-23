/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:51 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:12:03 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

int	init_env(t_executer *exec, char **env)
{
	int	i;

	i = 0;
	exec->vars->global_vars = ft_calloc(env_count(env) + 1, sizeof(char *));
	if (exec->vars->global_vars == NULL)
		return (0);
	while (env[i] != NULL)
	{
		exec->vars->global_vars[i] = ft_strdup(env[i]);
		if (exec->vars->global_vars[i] == NULL)
			return (0);
		i++;
	}
	return (i);
}

int	get_env_index(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (temp == NULL)
		return (-1);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
		{
			free_ptr(temp);
			return (i);
		}
		i++;
	}
	free_ptr(temp);
	return (-1);
}

char	*get_env_var(char **env, char *var)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(temp, env[i], ft_strlen(temp)) == 0)
		{
			free_ptr(temp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(temp);
	return (NULL);
}

int	init_wds(t_executer *exec)
{
	char	buffer[PATH_MAX];
	char	*wd;
	char	*old_pwd;

	wd = getcwd(buffer, PATH_MAX);
	if (wd == NULL)
		return (EXIT_FAILURE);
	exec->wd = ft_strdup(wd);
	if (exec->wd == NULL)
		return (EXIT_FAILURE);
	old_pwd = get_env_var(exec->vars->global_vars, "OLDPWD");
	if (old_pwd != NULL)
	{
		exec->old_wd = ft_strdup(old_pwd);
		if (exec->old_wd == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		exec->old_wd = ft_strdup(wd);
		if (exec->old_wd == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
