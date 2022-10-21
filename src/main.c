/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/21 17:53:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *str)
{
	char	*path;

	return (path);
}

void	cmd1(char **av, char **envp, int pipefd[2])
{
	int	fd_in;
	char	**args;
	char	*path;

	fd_in = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd_in < 0)
		ft_error("Error FD CMD1");
	args = ft_split(av[3], ' ');
	path = get_path(args[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	if (!access(path, X_OK))
		if ((execve(path, args, envp)) == -1)
		{
			free(path);
			free(args);
			ft_error("Error EXECVE CMD1");
		}
	free(args);
	free(path);
}

void	cmd2(char **av, char **envp, int pipefd[2])
{
	int		fd_out;
	char	**args;
	char	*path;

	fd_out = open(av[1], O_RDONLY);
	if (fd_out < 0)
		ft_error("Error FD CMD2");
	args = ft_split(av[2], ' ');
	path = get_path(args[0]);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	if (!access(path, X_OK))
		if ((execve(path, args, envp)) == -1)
		{
			free(path);
			free(args);
			ft_error("Error EXECVE CMD2");
		}
	free(args);
	free(path);
}

int	main(int ac, char **av, char **envp)
{
	int	pid;
	int	pipefd[2];

	if (ac < 5)
	{
		ft_putendl_fd("Wrong arguments number", 2);
		return (1);
	}
	if (pipe(pipefd) == -1)
		ft_error("Error PIPE");
	pid = fork();
	if (pid == -1)
		ft_error("Error FORK");
	else if (pid == 0)
		cmd1(av, envp, pipefd);
	waitpid(pid, NULL, -1);
	cmd2(av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
