/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:14:05 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/19 16:23:16 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void pwd(){
    char cwd[1024];
    if(!getcwd(cwd, sizeof(cwd))){
        printf("Error with reading current directory");
    }else{
        printf("%s\n", getcwd(cwd, sizeof(cwd)));
    }
}
