/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:00:29 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/29 13:44:05 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cd(char **args, t_env **envir){
    char *path;
    (void)envir;
    char cwd[1024];
    if(!args[1]){
        path=getenv("HOME");;
        if(!path){
            printf("Error reading $HOME.\n");
            return;
        }
    }else if(args[1][0]=='-'){
        if(args[1][1]=='\0'){
            if(getcopyenv("OLDPWD", envir)!=NULL){
                path=getcopyenv("OLDPWD", envir);
            }else{
                printf("bash: cd: OLDPWD not set\n");
                return;
            }
        }
    }else{
            path=args[1];
    } 
    if(chdir(path)!=0){
        printf("cd: string not in pwd: %s\n", args[1]);
    }else{
        update_env_for_cd(envir, "OLDPWD", getcopyenv("PWD", envir));
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
            update_env_for_cd(envir, "PWD", cwd);
        } else {
            printf("Error getting current working directory.\n");
        }        
    }
}
