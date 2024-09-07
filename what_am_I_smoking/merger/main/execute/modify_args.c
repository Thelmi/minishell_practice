/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:04:39 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/30 15:36:39 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

static int count_esc(char *str){
    int count;
    int i;
    i=0;
    count=0;
    while(str[i]){
        if(str[i]=='\\')
            count++;
        i++;
    }
    return count;
}

static char *no_quotes(char *arg){
    int i;
    int j;
    int len;
    char *res;
    i=0;
    j=0;
    len=ft_strlen(arg);
    res=malloc(sizeof(char)*(len-count_esc(arg)+1));
    if(!res){
        return NULL;
    }
    while(i<len){
        if (arg[i] == '\\')
            i++;
        res[j]=arg[i];
        i++;
        j++;
    }
    res[j]='\0';
    return res;
}

static char *double_quotes(char *arg, t_env *envir){
    int i;
    int j;
    int len;
    char *res;
    (void)envir;
    i=0;
    j=0;
    len=ft_strlen(arg);
    res=malloc(sizeof(char)*(len-1));
    if(!res){
        return NULL;
    }
    while(i<len){
        if(arg[i]=='"' && (i == 0 || i == len - 1)){
            i++;
        }
        if (arg[i] == '\\' && (arg[i + 1] == '$'|| arg[i + 1] == '"'))
            i++;
        res[j]=arg[i];
        i++;
        j++;
    }
    res[j]='\0';
    return res;
}

static char *single_quotes(char *arg){
    int i;
    int len;
    char *res;
    i=0;
    len=ft_strlen(arg);
    res=malloc(sizeof(char)*(len-1));
    while(i<len-2){
        res[i]=arg[i+1];
        i++;
    }
    res[i]='\0';
    return res;
}

void modify_args(char **args, t_env *envir){
    int i;
    char *tmp;
    i=0;
    while(args[i]){
        if(args[i][1] && args[i][0]=='$'){     
            tmp=getcopyenv(args[i]+1, &envir);
            if(!tmp){
                tmp = ft_strdup(""); 
            }
        }else if(args[i][0]=='\'' && args[i][ft_strlen(args[i])-1]=='\''){
            tmp = single_quotes(args[i]);
        }else if(args[i][0]=='"' && args[i][ft_strlen(args[i])-1]=='"'){
            tmp = double_quotes(args[i], envir);
        }else{
            tmp = no_quotes(args[i]); 
        }
        free(args[i]);
        args[i] = tmp;
        i++;
    }
}
