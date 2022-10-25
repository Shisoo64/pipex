/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/25 19:18:00 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*strjoin_pipex(char *s1, char *s2)
{
	char	*str;
	int		length;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = malloc(sizeof(char) * length);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, length);
	ft_strlcat(str, "/", length);
	ft_strlcat(str, s2, length);
	return (str);
}

char	*create_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*path;
	int		i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=/", ft_strlen("PATH=/")))
			path_list = ft_split(envp[i], ':');
	i = 0;
	while (path_list[i])
	{
		path = strjoin_pipex(path_list[i++], cmd);
		if (!access(path, X_OK))
		{
			free(path_list);
			return (path);
		}
		free(path);
	}
	free(path_list);
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	*path;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		path = ft_strdup(cmd);
		if (!access(path, X_OK))
			return (path);
	}
	else
	{
		path = create_path(cmd, envp);
		if (path)
			return (path);
	}
	free(path);
	return (NULL);
}

void	cmd1(char **av, char **envp, int pipefd[2])
{
	int		fd_in;
	char	**args;
	char	*path;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in < 0)
		ft_error("Error FD CMD1");
	args = ft_split(av[3], ' ');
	path = get_path(args[0], envp);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	if (!path || (execve(path, args, envp)) == -1)
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

	fd_out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (fd_out < 0)
		ft_error("Error FD CMD2");
	args = ft_split(av[2], ' ');
	path = get_path(args[0], envp);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	if (!path || (execve(path, args, envp)) == -1)
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
