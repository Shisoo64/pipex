/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/03 14:29:19 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1(char **av, char **envp, int pipefd[2])
{
	int		fd_in;
	char	**args;
	char	*path;
	int		i;

	i = 0;
	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
		ft_error(av[1]);
	args = ft_split(av[2], ' ');
	path = get_path(args[0], envp);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd_in);
	close_pipe(pipefd);
	if (!path || (execve(path, args, envp)) == -1)
	{
		free(path);
		while (args[i])
			free(args[i++]);
		free(args);
		ft_error(av[2]);
	}
	exit(1);
}

void	cmd2(char **av, char **envp, int pipefd[2])
{
	int		fd_out;
	char	**args;
	char	*path;
	int		i;

	i = 0;
	fd_out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd_out < 0)
		ft_error(av[4]);
	args = ft_split(av[3], ' ');
	path = get_path(args[0], envp);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd_out);
	close_pipe(pipefd);
	if (!path || (execve(path, args, envp)) == -1)
	{
		free(path);
		while (args[i])
			free(args[i++]);
		free(args);
		ft_error(av[3]);
	}
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	int	pid[2];
	int	pipefd[2];

	if (ac < 5)
	{
		ft_putendl_fd("Wrong arguments number", 2);
		return (1);
	}
	if (pipe(pipefd) == -1)
		ft_error("Error PIPE");
	pid[0] = fork();
	if (pid[0] == -1)
		ft_error("Error FORK");
	else if (pid[0] == 0)
		cmd1(av, envp, pipefd);
	pid[1] = fork();
	if (pid[1] == -1)
		ft_error("Error FORK");
	else if (pid[1] == 0)
		cmd2(av, envp, pipefd);
	close_pipe(pipefd);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
