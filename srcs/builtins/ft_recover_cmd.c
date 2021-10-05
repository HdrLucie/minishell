#include "includes_builtins.h"

int ft_recover_cmd(char **cmd, t_env *env)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (ft_strcmp(cmd[i], "env") == 0)
			ft_print_env(env);
		else if (ft_strcmp(cmd[i], "pwd") == 0)
			print_pwd(env);
		else
			return (2);
        i++;
    }
    return (1);
}