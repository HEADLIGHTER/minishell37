#include "minishell.h"

//void built_in_env

static void handle_logic(t_env *env, t_list *tkn)
{
	int i;
	t_env *tmp;

	if (!is_var_declaration(tkn->content))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(tkn->content, 2);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		return ;
	}
	i = find_char(tkn->content, '=');
	if (((char *)tkn->content)[i] == '=')
	{
		tmp = env_new(ft_substr(tkn->content, 0, i),
					  ft_substr(tkn->content,i + 1,
								ft_strlen(tkn->content + i + 1)), 1);
		envp_back(&env, tmp);
	}
}

int built_in_export(t_env *env, t_list *tkn)
{
	t_env *tmp;

//	ю/ьшif (!tkn)
//		built_in_env(env);
	while (tkn)
	{
		if ((tmp = get_env(env, tkn->content)))
		{
			if (is_var_declaration(tkn->content))
				env_value(tmp, tkn->content);
			tmp->set = 1;
		}
		else
			handle_logic(env, tkn);
		tkn = tkn->next;
	}
	return (0);
}