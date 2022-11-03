/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:45:55 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/03 14:36:24 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

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
		path = strjoin_pipex(path_list[i], cmd);
		free(path_list[i++]);
		if (!access(path, X_OK))
		{
			while (path_list[i])
				free(path_list[i++]);
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

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		path = ft_strdup(cmd);
		if (!access(path, X_OK))
			return (path);
	}
	path = create_path(cmd, envp);
	if (path)
		return (path);
	free(path);
	return (NULL);
}

void	ft_error(char *msg)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}
