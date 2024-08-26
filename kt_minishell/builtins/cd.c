/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:00:29 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/20 14:38:23 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd(char **command){
    const char *path;
    if(!command[1]){
        path=getenv("HOME");
        if(!path){
            printf("Error reading $HOME.\n");
        }
    }else{
        path=command[1];
    }
    if(chdir(path)!=0){
        printf("cd: string not in pwd: %s\n", command[1]);
    }
}
