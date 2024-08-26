/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:56:46 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/20 14:07:49 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void echo(char **command){
    bool n_flag;
    int i;
    n_flag=false;
    i=1;
    if(ft_strcmp("-n",command[1])==true){
        n_flag=true;
        i++;
    }
    while(command[i]){
        printf("%s", command[i]);
        if(command[i+1]){
            printf(" ");
        }
        i++;
    }

    if(n_flag==false){
        printf("\n");
    }
}