/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/09/20 16:26:20 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int	pid;
	int	pipefd[2];

	if (ac < 5)
		return (1);
	pipefd[0] = open(av[1], O_RDONLY);
	pipefd[1] = open(av[4], O_RDONLY);
	if (pipe(pipefd) == -1)
	{
		// Error PIPE
		exit(1);
	}
	dup2();
	pid = fork();
	if (pid == -1)
	{
		// Error FORK
		exit (1);
	}
	else if (pid == 0)
	{
		// On est dans le fils
	}
	else
	{
		// On est dans le père
	}
	return (0);
}
