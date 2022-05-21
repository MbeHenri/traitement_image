#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../entete/file.h"

i_file* info_file(const char* path){
    if (path==NULL)
        return NULL;
    i_file* info = malloc(sizeof(i_file));
    info->directory = "\0";
    info->name = "\0";
    info->format = "\0";
    
    int n = strlen(path);
    if (n==0)
        return info;
        
    int i=n-1;
    while (i >= 0 && path[i]!='/'){i--;}
    i++;
    int len_d=i;
    if (len_d > 0)
    {
        info->directory= malloc((len_d+1)*sizeof(char));
        for (i = 0; i < len_d; i++)
            info->directory[i] = path[i];
        info->directory[len_d]='\0';  
    }
    
    i=n-1;
    while (i >= 0 && path[i]!='.'){i--;}
    
    if(i == (n-1) || i < len_d){
        info->name = malloc((n-len_d+1)*sizeof(char));
        for (i = len_d; i < n; i++)
            info->name[i- len_d] = path[i];
        info->name[n-len_d]='\0';
        return info;
    }
    
    int j=0;
    info->name = malloc((i-len_d+1)*sizeof(char));
    for (j = len_d; j < i; j++)
        info->name[j- len_d] = path[j];
    info->name[i-len_d]='\0';
    
    i++;
    info->format = malloc((n-i+1)*sizeof(char));
    for (j = i; j < n; j++)
        info->format[j- i] = path[j];
    info->directory[n-i]='\0';
    return info;
}

void free_i_file(i_file* info){
    free(info->directory);
    free(info->name);
    free(info->format);
    free(info);
}