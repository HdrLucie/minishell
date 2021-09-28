#include "includes_builtins.h"

t_env   *ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = ft_lstlast_env(*alst);
	if (tmp == NULL)
		*alst = new;
	else
		tmp->next = new;
	new->next = NULL;
}