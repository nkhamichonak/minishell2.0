/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:56:04 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 16:55:39 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	update_env_wds(t_executer *exec, char *path)
{
	if (set_var_value(&exec->vars->global_vars, \
		"OLDPWD", get_env_var(exec->vars->global_vars, "PWD")) != 0)
		return (-1);
	if (set_var_value(&exec->vars->global_vars, "PWD", path) != 0)
		return (-1);
	if (exec->old_wd == NULL)
	{
		free_ptr(exec->old_wd);
		exec->old_wd = ft_strdup(exec->wd);
		if (exec->old_wd == NULL)
			return (-1);
	}
	if (exec->wd == NULL)
	{
		free_ptr(exec->wd);
		exec->wd = ft_strdup(path);
		if (exec->wd == NULL)
			return (-1);
	}
	return (0);
}

int	change_dir(t_executer *exec, char *path)
{
	char	*cwd;
	char	*buffer;

	buffer = NULL;
	if (chdir(path) != 0)
		return (handle_cd_error(path));
	if (exec->old_wd != NULL)
		free (exec->old_wd);
	exec->old_wd = ft_strdup(exec->wd);
	if (exec->old_wd == NULL)
		return (-1);
	if (exec->wd != NULL)
		free (exec->wd);
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd == NULL)
		return (-1);
	exec->wd = ft_strdup(cwd);
	if (exec->wd == NULL)
		return (-1);
	if (update_env_wds(exec, cwd) != 0)
		return (-1);
	free(cwd);
	return (0);
}

int	ft_builtin_cd(t_executer *exec, char **args)
{
	char	*path;

	path = args[1];
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	else if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0 \
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var(exec->vars->global_vars, "HOME");
		if (path == NULL || *path == '\0' || ft_isspace(*path) != 0)
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var(exec->vars->global_vars, "OLDPWD");
		if (path == NULL || *path == '\0' || ft_isspace(*path) != 0)
			return (EXIT_FAILURE);
	}
	if (change_dir(exec, path) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
