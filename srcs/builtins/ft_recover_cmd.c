#include "includes_builtins.h"

int ft_recover_cmd(char **cmd, char **env)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (ft_strncmp(cmd[i], "env", ft_strlen("env")))
            create_env_lst(env);
        i++;
    }
    return (1);
}