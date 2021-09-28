#include "includes_builtins.h"

/*
** Retours d'erreurs : -1, arret du programme.
**					   -2, erreur, mais le process continue. 
*/

void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env   *ft_lstlast_env(t_env *lst);

void	ft_print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

int	ft_fill_env_lst(char *str, t_env *env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != '=')
		i++;
	env->name = malloc(sizeof(char) * i + 1);
	if (!env->name)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		k = i;
		env->name[i] = str[i];
		i++;
	}
	env->name[i] = '\0';
	while (str[++i])
		j++;
	env->value = malloc(sizeof(char) * j + 1);
	if (!env->value)
		return (-1);
	j = 0;
	while (str[k])
		env->value[j++] = str[k++];
	env->value[j] = '\0';
	return (1);
}

int	create_env_lst(char **env)
{
	t_env	*env_lst;
	t_env	*current_node;
	int		i;

	i = 0;
	env_lst = NULL;
	current_node = NULL;
	while (env[i])
	{
		current_node = malloc(sizeof(t_env));
		ft_lstadd_back_env(&env_lst, current_node);
		if (!ft_fill_env_lst(env[i], current_node))
			return (-1);
		i++;
	}
	ft_print_env(env_lst);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	if (!create_env_lst(env))
		printf("Error\n");
	return (0);
}
