
#include "../../includes/minishell.h"

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void add_back_env(t_env **my_env, t_env *new_env)
{
	t_env	*res;

	if (my_env && new_env)
	{
		if (!(*my_env))
			*my_env = new_env;
		else
		{
			res = env_last(*my_env);
			res->next = new_env;
		}
	}
}

t_env *creat_env(char *argum, t_all *all)
{
	t_env	*temp;

	if (!(temp = init_env()))
		return (ft_error("unset", "out of memory", 12, all));
	temp->name = ft_strcut(argum, '=');
	temp->value = ft_strdup(ft_strnstr(argum, "=", ft_strlen(argum)) + 1);
	temp->standard = 2;
	return (temp);
}

