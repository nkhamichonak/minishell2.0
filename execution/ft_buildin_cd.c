/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:56:04 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/11 15:40:31 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	update_env_wds(t_executer *exec, char *path)
{
	set_var_value(exec, "OLDPWD", get_env_var(exec->env, "PWD"));
	set_var_value(exec, "PWD", path);
	if (exec->old_wd == NULL)
	{
		free_ptr(exec->old_wd);
		exec->old_wd = ft_strdup(exec->wd);
		if (exec->old_wd == NULL)
			return (0);
	}
	if (exec->wd == NULL)
	{
		free_ptr(exec->wd);
		exec->wd = ft_strdup(path);
		if (exec->wd == NULL)
			return (0);
	}
	return (1);
}

int change_dir(t_executer *exec, char *path)
{
	char	*buffer;
	char	*cwd;
	
	buffer = NULL;
	if (chdir(path) != 0)
		return (0);
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd == NULL)
		return (0);
	update_env_wds(exec, cwd);
	return (1);
}

int ft_buildin_cd(t_executer *exec, char **args)
{
	char	*path;
	
	if (args[2] != NULL)
		return (0);
	if (args[1] == NULL || ft_isspace(args[1][0]) != 0 \
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var(exec->env, "HOME");
		if (path == NULL || *path == '\0' || ft_isspace(*path) == 0 )
			return (0);
		change_dir(exec, path);
		return (1);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var(exec->env, "OLDPWD");
		if (path == NULL || *path == '\0' || ft_isspace(*path) == 0 )
			return (0);
		change_dir(exec, path);
		return (1);
	}
	change_dir(exec, args[1]);
	return (1);
}