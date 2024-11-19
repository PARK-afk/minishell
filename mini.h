/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsepar <junsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 04:04:03 by suhyun            #+#    #+#             */
/*   Updated: 2023/09/18 00:48:48 by junsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define ERROR 1
# define CHILD 0
# define WRITE 1
# define READ 0

# define PIPE_ 4
# define FILE_OP 1
# define SPACE_ 5
# define OUTAPPEN 0
# define OUT	1
# define IN 2
# define HEREDOC 3
# define ARG 5

# define SQ 12
# define DQ 13
# define NOTQ 14

typedef enum s_type
{
	command = 0,
	option,
	argv,
	string,
	redict_out,
	redict_in,
	dict_out,
	dict_in,
	dquote,
	quote,
	pipe_,
	unexpect_token,
	special_heredoc,
}	t_type;

typedef struct s_fds
{
	int	pi_fd[2];
	int	std_fd[2];
}	t_fds;

typedef struct s_command
{
	int					infile;
	int					outfile;
	char				**cmd;
	int					cmd_index;
	struct s_command	*next;
}	t_command;

typedef struct s_data
{
	struct s_data		*next;
	int					type;
	char				*str;
	t_command			*cmd;
	int					num;
	char				**env;
	int					syntax;
}	t_data;

typedef struct s_ind
{
	int	i;
	int	st;
	int	len;
	int	type;
	int	flag_sq;
	int	flag_dq;
}	t_ind;

typedef struct s_
{
	t_data	*to_ex;
	t_data	*first;
	t_data	*head;
	t_data	*real;
}	t_l;

/* init */
void		init_env_and_exit_status(t_data *data, char **env);
void		init_data(t_l *new, char **env);

/* set term*/
void		pipe_set(pid_t pid, t_command *cur, int fd[]);
void		last_pipe_set(pid_t pid, t_command *cur, int fd[]);
void		only_built_set(pid_t pid, t_command *cur, int fd[]);
void		set_fd(pid_t pid, t_command *cur, int fd[]);
void		set_exit_status(pid_t pid);
void		new_free(t_l *new);

/* execute */
void		execute(t_data *data, t_command *cmd);
bool		check_valid(char *s);
void		after_any_file(t_l *new, t_command *cmd);
char		*path_parse(char **cmd, t_data *data);
void		cmd_list_free(t_command **cmd);
char		*ft_getenv(char *name, char **env);
void		exit_err_pro(t_command **cmd);
void		cmd_not_found(char *file, int flag);
void		specific_path_error(char *path);
void		data_free(t_data *data, t_command *cmd);
void		is_dir(char *path);
void		child_execute(t_command *cur, t_data *data);

/* builts */
int			ft_cd(t_command *dir_name, char ***env);
int			ft_env(char **env);
int			ft_echo(char **cmd);
int			ft_exit(char **str);
int			ft_export(char **cmd, t_data *data);
int			ft_pwd(void);
int			ft_unset(char **del, t_data *data);

/* builts utils*/
char		**copy_env(char **env);
int			export_env_add(char *cmd, char end, t_data *data);
int			export_print(char **env);
int			check_export_valid(char **cmd, t_data *data);
bool		check_valid(char *s);
int			is_equal_sign(char *s);
int			exe_built(t_command *command, t_data *data);
bool		is_built(t_command *command);
void		free_arr(char **arr);
int			ft_env_len(char **env);
int			ft_strcmp(char *s1, char *s2);

void		set_term(void);
void		set_originterm(void);

/* heredoc */
int			get_infile_heredoc(t_data *data, char *limit);
int			heredoc(int fd, char *limit);

// CIRCUIT_LIST List 순회공연
char		*rotate_envstring(t_data *data, char **env);
t_command	*rotate_list(t_data *data);

// CMD_UTILS // command utils 
int			count_cmd(t_data *data);
char		**make_cmd(t_data *data);
void		check_data(t_data *mydata);
void		check_exit_stat(t_command *cmd, t_l *new);
// DOLLAR // 달러 
int			ft_isdollar(char s);
int			ft_isspace(char s);
char		*substitution_dollar(char *line, char **env);
void		check_cmd(t_command *cmd);
int			check_qu(int sq, int dq, char *filename);
void		chec_how_qu(int *dq_flag, int *sq_flag, char *filename, int *i);
// ERROR_PRINT
void		error_exit(char *str, int num);

// FREE 
void		free_env(t_data *data);
void		free_data(t_data **data);

// HEREDOC_UTILS 
int			here_doc_num(t_data *real);
int			*open_here_doc(t_data *real, char *limit);
int			check_gal_qu(int *flag_dq, int *flag_sq);

// OPEN 
int			open_infile(char *filename);
int			open_outfile(char *filename, t_data *real);
void		open_any_file(t_data *real, t_command *cmd, int *hd);
void		replace_rotate(t_data *real, char **env, \
				t_command *cmd, int *hd);

// PARSE_UTILS
int			is_seperater(char *c);
int			is_seperater2(char *c);
int			skip_white_sapce(char *str);
int			check_whitespace(const char *line);
int			check_dollar(const char *line);
int			get_arg_len(char *str, int ignore_type);

// PARSE
t_data		*split_seperator(t_data *first);
void		parse(char *str, int ignore_type, t_data **mydata);
void		parse2(char *str, t_data **newdata);

// PUSH
void		push(t_data **data, char *str, int type);
void		push2(t_command **data, char **cmd, int infile, int outfile);
t_data		*push_type(t_data *mydata);
void		for_oap(t_data *mydata, t_data *real);
void		for_heredoc(t_data *mydata, t_data *real);
void		for_out(t_data *mydata, t_data *real);
void		for_in(t_data *mydata, t_data *real);
void		for_pipe(t_data *mydata, t_data *real);

// SIGNAL
void		handler_int(int signal);
void		set_sig(void);
void		get_sig(void);

// USING_QUOTES
char		*remove_quote(char *str, char **env);
void		replace_check(t_data *real, char **env);
void		set_index(t_command *cmd);

// handle_redir
void		handle_append(t_data **mydata, t_data **real);
void		handle_heredoc(t_data **mydata, t_data **real);
void		handle_right_redirect(t_data **mydata, t_data **real);
void		handle_left_redirect(t_data **mydata, t_data **real);
int			here_doc_num(t_data *real);

// parse
char		*rotate_envstring(t_data *data, char **env);
t_command	*rotate_list(t_data *data);

int			g_exit_status;

#endif