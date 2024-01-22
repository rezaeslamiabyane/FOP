#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
    if(strcmp(argv[1],"config")==0){
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

    return 0;
}