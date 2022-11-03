/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2022/11/02 16:23:48 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include <string.h>
# include <errno.h>

void	ft_error(char *errormsg);
char	*get_path(char *cmd, char **envp);
void	close_pipe(int fds[2]);

#endif
