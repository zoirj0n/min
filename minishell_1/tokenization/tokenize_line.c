
#include "minishell.h"

void	cleanup_environment_tokenization(t_list **el,
	t_list **tokens, bool *success)
{
	t_token	*token;

	token = (*el)->content;
	if (token->substr == NULL)
		ft_lstclear(el, release_token_memory);
	else if (ft_strncmp(token->substr, "$\"\"", 3) == 0)
	{
		deallocate_memory(&token->substr);
		token->substr = ft_strdup("");
		ft_lstadd_back(tokens, *el);
	}
	else if (ft_strlen(token->substr) != 0
		&& ft_strchr(token->substr, '$') != NULL)
		ft_lstadd_back(tokens, *el);
	else if (ft_strlen(token->substr) != 0)
	{
		*success = reprocess_environment_token(token, el, tokens);
	}
	else
	{
		token->type = DUMMY;
		ft_lstadd_back(tokens, *el);
	}
}

int	process_primary_tokens(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
		int	success;

		success = 1;
	if (line[*i] == '\'')
		el = create_single_quote_token(shell, line, i);
	else if (line[*i] == '\"')
		el = create_double_quote_token(shell, line, i,
				!check_previous_heredoc(*tokens));
	else if (detect_operator_character(line, *i) == true)
		el = process_operator_token(line, i);
	else
		el = create_subexpression_token(shell, line, i);
	   if (el == NULL)
	   {
		   handle_token_error(NULL, tokens, &success);
		   return 0;
	   }
	   ft_lstadd_back(tokens, el);
	   return 1;
}

int	process_secondary_tokens(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
		int	success;

		success = 1;
		if (line[*i] == '$' && check_previous_heredoc(*tokens) == 0)
	{
		el = extract_environment_variable(shell, line, i);
		   if (el == NULL)
		   {
			   handle_token_error("Parse Error\n", tokens, &success);
			   return 0;
		   }
		   cleanup_environment_tokenization(&el, tokens, &success);
		   if (success == 0)
		   {
			   handle_token_error(NULL, tokens, &success);
			   return 0;
		   }
	}
	   else if (line[*i] == ')')
	   {
		   handle_token_error("Parse Error\n", tokens, &success);
		   return 0;
	   }
	   return 1;
}

int	process_text_and_wildcard(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
		int	success;
	t_token	*token;

		success = 1;
		el = create_normal_token(shell, line, i, !check_previous_heredoc(*tokens));
	   if (el == NULL)
	   {
		   handle_token_error(NULL, tokens, &success);
		   return 0;
	   }
	token = el->content;
	   if (ft_strchr(token->substr, '*') != NULL)
	   {
		   if (process_wildcard_token(shell, &el, tokens, &success) == 0)
			   return 0;
	   }
	   else
		   ft_lstadd_back(tokens, el);
	   return 1;
}

t_list	*process_input_line(const t_shell *shell, const char *line, int *success)
{
	size_t	i;
	t_list	*tokens;

		*success = 1;
	   if (detect_token_syntax_errors(line, success) == 0)
		   return (NULL);
	tokens = NULL;
	i = 0;
	   while (line[i] != '\0')
	   {
		   if (line[i] == '\'' || line[i] == '"' || detect_operator_character(line, i) == 1
			   || line[i] == '(')
			   *success = process_primary_tokens(shell, line, &i, &tokens);
		   else if ((line[i] == '$' && check_previous_heredoc(tokens) == 0)
			   || line[i] == ')')
			   *success = process_secondary_tokens(shell, line, &i, &tokens);
		   else if (line[i] != ' ')
			   *success = process_text_and_wildcard(shell, line, &i, &tokens);
		   if (*success == 0)
			   return (NULL);
		   if (line[i] != '\0')
			   i++;
	   }
	   return (tokens);
}
