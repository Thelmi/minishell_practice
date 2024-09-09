/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:58:22 by krazikho          #+#    #+#             */
/*   Updated: 2024/09/02 20:08:06 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ev){
    (void)ac;
    (void)av;
    char *command;
    t_env *envir;
    int last_exit_status;
	last_exit_status = 0; 
    envir = storing_env(ev);
    while(1)
    {
        command = readline("minishell$ ");
        if (command == NULL) {
            break;
        }
        if (*command) {
            add_history(command);
            envir = execute_command(command, envir, &last_exit_status, ev);
            
        }
        free(command);
    }
    free_env(envir);
    return (last_exit_status);
}
