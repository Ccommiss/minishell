/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:17:37 by ccommiss          #+#    #+#             */
/*   Updated: 2021/09/14 18:57:33 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <string.h>
#include <stdio.h>
 #include <readline/readline.h>
#include <readline/history.h>




int	pipex (int ac, char **argv, char **envp);
char	**ft_split(char const *s, char c);

struct token t_token;


typedef struct s_token	t_token;

typedef struct s_token {
	int		type;
	s_token *next;
	s_token	*prev;
}				t_token;

enum type {
	T_WORD = 1, // Commande ou argument de commande
	T_PIPE, // | 
	T_GREAT, // > 
	T_GREATGREAT, //>> 
	T_LESS, // <
	T_LESSLESS // <<
}
#endif 