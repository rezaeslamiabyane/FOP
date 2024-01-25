#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>
#include <sys/types.h>
void init(){
    char path[1000];
    char path_copy[1000];
    getcwd(path,sizeof(path));
    getcwd(path_copy,sizeof(path_copy));
    struct dirent *entry;
    struct stat info;
    bool exist=false;
    while(strcmp(path_copy,"C:\\")!=0){
        DIR *dir=opendir(".");
        while((entry=readdir(dir))!=NULL){
            stat(entry->d_name,&info);
            if(strcmp(entry->d_name,".sag")==0&&S_ISDIR(info.st_mode)==0){
                exist=true;
                goto label;
            }
        }
        closedir(dir);
        chdir("..");
        getcwd(path_copy,sizeof(path_copy));
    }label:
    if(exist){
        printf("INITED BEFORRRRRRRR\n");
    }
    else{
        chdir(path);
        mkdir(".sag");
        printf("NOW IT IS INITED");
    }
}

void config(char * address,char *type,char *name){
                FILE *user=fopen(address,"r");
                if(user!=NULL){
                    FILE *user=fopen(address,"a");
                    fprintf(user,"%s : %s\n",type,name);
                }
                else{
                    FILE *user=fopen(address,"w");
                    fprintf(user,"%s : %s\n",type,name);
                }
}

void alias(char * address,char *type,char *name){
                FILE *user=fopen(address,"r");
                if(user!=NULL){
                    FILE *user=fopen(address,"a");
                    fprintf(user,"%s : %s\n",type,name);
                }
                else{
                    FILE *user=fopen(address,"w");
                    fprintf(user,"%s : %s\n",type,name);
                }
}

int main(int argc,char ** argv){
    if(strncmp(argv[1],"config",6)==0){
        if(strncmp(argv[2],"alias",5)==0){
            if(argv[2][5]!='.')
                printf("invalid alias");
            else{
            alias("C:\\Users\\Reza\\git\\alias_command.txt",argv[2],argv[3]);
            }
        }
        else if(strncmp(argv[3],"alias",5)==0){
            if(argv[3][5]!='.')
                printf("invalid alias");
            else if(strcmp(argv[2],"--global")==0){
                alias("C:\\Users\\Reza\\git\\alias_command.txt",argv[3],argv[4]);
            }
            else{
                printf("invalid alias");
            }

        }
        else{
            if(strcmp(argv[2],"--global")==0){
                config("C:\\Users\\Reza\\git\\global.txt",argv[3],argv[4]);
            }
            else{
                config("C:\\Users\\Reza\\git\\pr.txt",argv[2],argv[3]);
            }
        }
    }
    else if(strcmp(argv[1],"init")==0){
        init();
    }
    else if()

    return 0;
}