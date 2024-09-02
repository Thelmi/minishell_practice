/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:27:04 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/29 16:23:32 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool is_executable(char *command){
    (void)command;
    return false;
}

static bool is_builtin(char *command){
    if(ft_strcmp("echo", command)==true||ft_strcmp("cd", command)==true || ft_strcmp("pwd", command)==true) {
        return true;
    }else if(ft_strcmp("export", command)==true || ft_strcmp("unset", command)==true || ft_strcmp("env", command)==true){
        return true;
    }else if(ft_strcmp("exit", command)==true){
        return true;
    }else{
        return false;
    }
}

t_env *execute_command(char *command, t_env *envir, int *last_exit_status)
{
    char **args;

    args = ft_split(command, ' '); // just for testing later we can parse better (temporary)
    modify_args(args, envir);
    if (!args || !args[0])
        return envir;
    if (is_builtin(args[0])==true)
    {
        envir = execute_builtin(envir , args, last_exit_status);
	}
    else if(is_executable(args[0])==true){
        // execute_external(command);
        *last_exit_status = 0; // assuming command executed succesfully
    }else{
        printf("bash:command not found: %s\n", args[0]); // modifying this based on the bash syntax
        *last_exit_status = 127; // status command not found
    }
    free_arr(args);
    return (envir);
}
