
#ifndef BUILTINS_H
# define BUILTINS_H

# include "parsing.h"

typedef struct s_shell	t_shell;

/* ---- BUILTINS CHECK FUNCTIONS ---- */
int	execute_builtin_command(t_exec_step *step, t_shell *shell, int child);
int		compare_strings(char *s1, char *s2);
int	check_builtin_command(t_exec_step *step);
int	requires_parent_execution(t_exec_step *step);

/* ---- ECHO - PWD - ENV - EXIT - FUNCTIONS ---- */
void	display_echo_output(t_exec_step *command, t_shell *shell);
void	print_working_directory(t_exec_step *command, t_shell *shell);
void	show_environment_variables(t_shell *shell, t_exec_step *step);
void	terminate_shell(t_exec_step *step, t_shell *shell, int child);

/* ---- CD FUNCTIONS ---- */
void	change_directory(t_exec_step *step, char **env, t_shell *shell);
void	refresh_old_working_directory(t_shell *shell, char **env, char *oldpwd);
void	refresh_current_working_directory(char **env, t_shell *shell);
void	navigate_to_home(t_shell *shell, t_exec_step *step, char **env, char *home);

/* ---- EXPORT FUNCTIONS ---- */
void	export_environment_variable(t_shell *shell, t_exec_step *step);
size_t	calculate_environment_length(char **env);
void	modify_environment_variable(t_shell *shell, const char *str);
void	modify_declared_variable(t_shell *shell, char *str);
int	validate_export_argument(const char *arg);

void	display_export_error(char *arg);
char	**resize_string_array(char **old, size_t new_size);
int	set_variable_value(t_shell *shell, char *to_look,
			char *key, char *key_val);
void	display_export_variables(char **val, char **key);
void	process_export_arguments(char **args, t_shell *shell, int *error);

/* ---- UNSET FUNCTIONS ---- */
void	remove_environment_variable(t_shell *shell, t_exec_step *step);
void	delete_variable(t_shell *shell, const char *var);
void	erase_environment_entry(t_shell *shell, char **env_copy, char *to_look);
void	delete_declared_variable(t_shell *shell, const char *var);
void	erase_declared_entry(t_shell *shell, char **env_copy, char *to_look);

#endif
