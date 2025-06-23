/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:22:41 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:32:53 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**var_value_pair(char *arg)
{
	char	**temp;
	char	*pos;

	pos = ft_strchr(arg, '=');
	temp = malloc(3 * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	temp[0] = ft_substr(arg, 0, pos - arg);
	temp[1] = ft_substr(pos, 1, ft_strlen(pos));
	temp[2] = NULL;
	return (temp);
}

static	int	export_print(t_executer *exec, int count)
{
	int		i;
	char	**sorted;

	safe_redirect_fds(exec);
	sorted = malloc((count + 1) * sizeof(char *));
	if (sorted == NULL)
		exit (EXIT_FAILURE);
	if (exec->vars->global_vars == NULL)
		exit (EXIT_FAILURE);
	i = -1;
	while (++i < count)
		sorted[i] = exec->vars->global_vars[i];
	sorted[count] = NULL;
	bubble_sort(sorted, count);
	i = 0;
	while (sorted[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(sorted[i], STDOUT_FILENO);
		i++;
	}
	free(sorted);
	ft_exec_clean(exec);
	exit (EXIT_SUCCESS);
}

static	int	ft_export_print(t_executer *exec)
{
	pid_t	pid;
	int		status;
	int		count;

	count = env_count(exec->vars->global_vars);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		export_print(exec, count);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	ft_identifier_not_valid(char *args)
{
	ft_putstr_fd("-minishell: export `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	ft_builtin_export(t_executer *exec, char **args)
{
	int		i;
	char	**temp;

	if (args[1] == NULL)
		return (ft_export_print(exec));
	i = 0;
	while (args[++i] != NULL)
	{
		if (check_var(args[i]) == 1)
			return (ft_identifier_not_valid(args[i]));
		else if (ft_strchr(args[i], '=') == NULL)
			set_var_value(&exec->vars->global_vars, args[i], NULL);
		else
		{
			temp = var_value_pair(args[i]);
			if (temp == NULL)
				return (EXIT_FAILURE);
			set_var_value(&exec->vars->global_vars, temp[0], temp[1]);
			free_double_array(temp);
		}
	}
	return (EXIT_SUCCESS);
}
