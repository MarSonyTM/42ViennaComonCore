/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:40:14 by csturm            #+#    #+#             */
/*   Updated: 2024/05/01 12:49:59 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_process(t_cmd *cmd, int i, t_exec *exec, t_env **env)
{
	char	**envp;

	if (i != exec->processes - 1)
		duplicate_fd(exec->fd[1], 1, 0);
	if (i != 0)
	{
		duplicate_fd(exec->old_fd[0], 0, 0);
		close(exec->fd[0]);
		exec->open_fds[i * 2] = -1;
	}
	if (cmd->input)
		redirection(cmd, 0, 0);
	if (cmd->output)
		redirection(cmd, 1, 0);
	if (cmd->redirection_append)
		redirection(cmd, 2, 0);
	envp = env_to_array(cmd, env);
	signal(SIGQUIT, SIG_DFL);
	if (execve(cmd->cmd_path, cmd->cmd_arr, envp) == -1)
	{
		free_array(envp);
		exit (cmd->exit_status);
	}
}

static void	create_child_process(t_cmd *cmd, int i, t_exec *exec, t_env **env)
{
	int	custom_exit;

	if (cmd->next != NULL && handle_pipe(exec, i, cmd->next->cmd_path) == 1)
	{
		cmd->exit_status = 1;
		return ;
	}
	if (cmd->cmd_path == NULL)
	{
		custom_exit = handle_custom(cmd, env, &exec, i);
		if (custom_exit == 1 && cmd->exit_status == 0)
			cmd->exit_status = 1;
		return ;
	}
	child_setup_signal();
	exec->pid[i] = fork();
	if (exec->pid[i] == -1)
		exit(1);
	if (exec->pid[i] == 0)
	{
		child_process(cmd, i, exec, env);
		exit(0);
	}
	handle_fds(exec, i);
}

static int	init_exec(t_exec *exec, t_cmd *cmd, t_env **env)
{
	int	i;

	exec->processes = count_processes(cmd);
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->old_fd[0] = -1;
	exec->old_fd[1] = -1;
	if (allocate_memory(exec) == 1)
	{
		clean_up(cmd, *env);
		close_and_free(exec);
		exit (1);
	}
	i = 0;
	while (i < exec->processes * 2)
		exec->open_fds[i++] = -1;
	return (0);
}

int	executor(t_cmd *cmd, t_env **env, int exit_status)
{
	t_exec	exec;
	t_cmd	*tmp;
	int		i;
	int		j;
	int		last_exit_status;

	init_exec(&exec, cmd, env);
	last_exit_status = 0;
	cmd->prev_exit_status = exit_status;
	i = 0;
	j = exec.processes;
	tmp = cmd;
	while (j > 0)
	{
		create_child_process(tmp, i, &exec, env);
		j--;
		i++;
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
	last_exit_status = get_last_exit_status(cmd, &exec);
	close_and_free(&exec);
	return (last_exit_status);
}
