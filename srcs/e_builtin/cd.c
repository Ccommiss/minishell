#include "../../include/minishell.h"
#include <limits.h>

char	*get_pwd(void)
{
	char	*tmp;
	char	buf[PATH_MAX + 1];

	tmp = getcwd(buf, PATH_MAX);
	return (tmp);
}

char	*strjoin_char(char *str, char *str1, char c)
{
	char	*final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	final = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(str1) + 2)));
	if (final == NULL)
		return (NULL);
	while (str[i])
	{
		final[j] = str[i];
		i++;
		j++;
	}
	final[j++] = c;
	i = 0;
	while (str1[i])
	{
		final[j] = str1[i];
		j++;
		i++;
	}
	final[j] = '\0';
	return (final);
}

int	is_home_unset(t_env *tmp)
{
	while (tmp)
	{
		if (strcmp(tmp->key, "HOME") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		write(1, "cd: HOME not set\n", 17);
		return (-1);
	}
	else if (chdir(tmp->value) == -1)
		perror("cd:");
	return (0);
}

void	cd(t_env *env, char *pwd, int redir)
{
	t_env	*tmp;

	tmp = env;
	if (pwd == NULL)
	{
		
		if (is_home_unset(tmp) == -1)
			return ;
	}
	else
	{
		while (env)
		{
			if (strcmp(env->key, "OLDPWD") == 0)
			{
				free(env->value);
				env->value = ft_strdup(get_pwd());
				env->env = strjoin_char(env->key, env->value, '=');
				break ;
			}
			env = env->next;
		}
			if (chdir(pwd) == -1)
				perror("cd:");
		}
	}

void	set_the_pwd(t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(get_pwd());
			env->env = strjoin_char(env->key, env->value, '=');
			break ;
		}
		env = env->next;
	}
}
