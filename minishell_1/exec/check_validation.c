
#include "minishell.h"

int verify_path_validity(t_exec_step *step)
{
		return (step->cmd->arg_arr[0] && access(step->cmd->arg_arr[0], X_OK) != -1 && !ft_strchr(step->cmd->arg_arr[0], '/')) ? 1 : 0;
}

int verify_command_validity(t_exec_step *step, int valid_redirs)
{
		return (step->cmd->arg_arr[0] && ((access(step->cmd->arg_arr[0], X_OK) == -1 && !check_builtin_command(step)) || check_directory_status(step->cmd->arg_arr[0]) || !valid_redirs)) ? 1 : 0;
}

int detect_missing_command(t_exec_step *step, int valid_redirs)
{
		int check;

		check = (access(step->cmd->arg_arr[0], F_OK) == -1 && !check_builtin_command(step));
	   if ((check || check_directory_status(step->cmd->arg_arr[0])) && valid_redirs && !ft_strchr(step->cmd->arg_arr[0], '/'))
		   return 1;
	   if (access(step->cmd->arg_arr[0], F_OK) != -1 && access(step->cmd->arg_arr[0], X_OK) == -1 && !ft_strchr(step->cmd->arg_arr[0], '/') && valid_redirs)
		   return 1;
	   return 0;
}

int detect_missing_file(t_exec_step *step, int valid_redirs)
{
		return ((access(step->cmd->arg_arr[0], F_OK) == -1 && !check_builtin_command(step)) && valid_redirs && ft_strchr(step->cmd->arg_arr[0], '/')) ? 1 : 0;
}

int detect_permission_issue(t_exec_step *step, int valid_redirs)
{
		return ((access(step->cmd->arg_arr[0], X_OK) == -1 && !check_builtin_command(step)) && valid_redirs) ? 1 : 0;
}
