
#ifndef PARSING_H
# define PARSING_H

typedef struct s_exec_step	t_exec_step;
typedef struct s_cmd		t_cmd;
typedef struct s_redir		t_redir;

struct	s_redir
{
	t_token_type	type;
	char			*file;
	char			*limiter;
};

struct	s_cmd
{
	t_list	*args;
	char	**arg_arr;
	int		pid;
	t_list	*redirs;
};

struct	s_exec_step
{
	t_cmd	*cmd;
	char	*subexpr_line;
	int		exit_code;
	int	pipe_next;
	int	and_next;
	int	or_next;
};

 t_list		*analyze_token_stream(t_list *tokens, int *success);
void		release_execution_step(void *exec_step_ptr);
void		release_redirection(void *redir_ptr);
void		display_execution_step(t_list *exec_steps);
void		convert_list_to_array(void *step_ptr);
int		check_token_terminator(const t_token *token);
int		check_token_redirection(const t_token *token);
int		detect_parsing_errors(t_list *tokens);
int		report_parsing_error(t_redir *redir, t_exec_step *step);
int		validate_subexpression_token(t_list *tokens, t_token **token,
			   t_exec_step *step, int *success);
int		validate_following_token(t_list *cmd_end, t_token **token,
			   t_exec_step *step, t_list *tokens);
 t_list		*process_parsing_step(t_list **tokens, t_token **token, t_list **steps,
			   int *success);

#endif
