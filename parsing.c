#include "minishell.h"

void split_cmd(char *line, t_cmd **cmd)
{
	size_t i;
	size_t end;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return ;
	cmd_back(cmd, ft_substr(line, i, escaped(line, i, "\t ") - i));
	end = ft_strlen(line);
	while (i < end)
	{
		i = escaped(line, i, "\t ") + 1;
		while (i < end && ft_isspace(line[i]))
			i++;
		if (i < end)
			tkn_back(cmd, ft_substr(line, i, escaped(line, i, "\t ") - i));
	}
}

t_cmd *parsing(char *line, t_env *envp, int *last_exit)
{
	t_cmd *cmd;

	if (!line)
		return (NULL);
	cmd = NULL;
	split_cmd(line, &cmd);
	parser_dollar(cmd, envp, *last_exit);
	parser_special_char(cmd, "|", parse_pipe);
	parser_special_char(cmd, "<>", parser_redirect);
	rm_redirect_pipe(cmd);
	rm_quote(cmd);
	return (cmd);
}