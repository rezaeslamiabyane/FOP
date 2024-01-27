#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>
#include <sys/types.h>
#include <libgen.h>
#include <regex.h>
int check_changes(FILE *file1,FILE*file2){

}
int finding_last_commit_of_a_file(DIR *dir){
    struct dirent *entry;
    int max=-1;
    while((entry=readdir(dir))!=NULL){
        int tmp = atoi(entry->d_name);
        max = max > tmp ? max: tmp;
    }
    return max;
}
int chek_in_stage(FILE *stage,char*path){
    char line[1000];
    while (fgets(line, sizeof(line), stage) != NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (strcmp(path, line) == 0) return 1;
    }
    fclose(stage);
    return 0;
    
}
// int add_file(char *path){
//     char path_copy[1000];
//     strcpy(path_copy,path);
//     char boz[100];
//     FILE *stage;
//     char dir_name[1000];
//     dir_name[0]='\0';
//     FILE *file =fopen(path,"r");
//     chdir(".sag\\files");
//     char *str=strtok(path_copy,"\\:.");
//     while(str!=NULL){
//         strcat(dir_name,str);
//         str=strtok(NULL,"\\:.");
//     }
//     DIR *dir =opendir(dir_name);
//     if(dir==NULL){
//         chdir("..");
//         stage=fopen("staging.txt","a");
//         if(chek_in_stage(fopen("staging.txt","r"),path)){
//             return 0;
//         }
//         chdir("files");
//         mkdir(dir_name);
//         chdir("..");
//         fprintf(stage,"%s\n",path);
//         return 1;
//     }
//     chdir(dir_name);
//     char file_nme[1000];
//     sprintf(file_nme,"%d",finding_last_commit_of_a_file(dir));
//     FILE *file2=fopen(file_nme,"r");
//     chdir("..");
//     if(file2==NULL){
//         chdir("..");
//         stage=fopen("staging.txt","a");
//         if(chek_in_stage(fopen("staging.txt","r"),path)){
//             return 0;
//         }
//         fprintf(stage,"%s\n",path);
//         return 1;
//     }
//     char file_1[1000];
//     char file_2[1000];
//     while(!feof(file)||!feof(file2)){
//         if((feof(file)&&!feof(file2))||(feof(file2)&&!feof(file))){
//             chdir("..");
//             stage=fopen("staging.txt","a");
//             if(chek_in_stage(fopen("staging.txt","r"),path)){
//                 return 0;
//             }
//             fprintf(stage,"%s\n",path);
//             return 1;
//         }
//         fgets(file_1,1000,file);
//         fgets(file_2,1000,file2);
//         if(strcmp(file_1,file_2)!=0){
//             chdir("..");
//             stage=fopen("staging.txt","a");
//             if(chek_in_stage(fopen("staging.txt","r"),path)){
//                 return 0;
//             }
//             fprintf(stage,"%s\n",path);
//             return 1;
//         }
//     }
//     return 0;

// }
int add_file(char *path,char *directory,char *sag_path){
        char path_copy[1000];
        strcpy(path_copy,path);
        char dir_name[1000];
        dir_name[0]='\0';
        chdir(sag_path);
        FILE *branch=fopen(".sag\\curr_branch.txt","r");
        char branch_name[100];
        fscanf(branch,"%s",branch_name);
        chdir(".sag\\staged_area");
        DIR *dir=opendir(".");
        char *str=strtok(path_copy,"\\:.");
        while(str!=NULL){
            strcat(dir_name,str);
            str=strtok(NULL,"\\:.");
        }
        bool exist=false;
        struct dirent *entry;
        while((entry=readdir(dir))!=NULL){
            if(strcmp(entry->d_name,dir_name)==0){
                exist=true;
                goto lab;
            }
        }lab:
        if(!exist){
            chdir(sag_path);
            chdir("staged_area");
            mkdir(dir_name);
            chdir(dir_name);
            FILE *file=fopen("info.txt","w");
            char dir_path[100];
            getcwd(dir_path,sizeof(dir_path));
            fprintf(file,"%s\n%s",branch_name,path);
            fclose(file);
            char system_command[1000];
            chdir(directory);
            sprintf(system_command,"copy %s %s",path,dir_path);
            system(system_command);
            chdir(dir_path);
            chdir("..");
            chdir("..");
            return 1;
        }
        else{

        }



}
int is_dir_or_not(char * path){
    if(fopen(path,"rb")==NULL){
        return 0;
    }
    return 1;
}

int add_derectory(char *path,char *directory,char *sag_path){
    chdir(directory);
    DIR *dir=opendir(path);
    struct dirent *entry;
    struct stat info;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        char path_dir[1000];
        sprintf(path_dir,"%s\\%s",path,entry->d_name);
        stat(path_dir,&info);
        if(strstr(entry->d_name,".")!=NULL){
            printf("%s\n",entry->d_name);
            add_file(path_dir,directory,sag_path);
        }
        else{
            add_derectory(path_dir,directory,sag_path);
        }
    }
}


int init(int test,char * sag_path){
    char path_copy[1000];
    char path[1000];
    getcwd(path,sizeof(path));
    getcwd(path_copy,sizeof(path));
    struct dirent *entry;
    struct stat info;
    bool exist=false;
    while(strcmp(path_copy,"C:\\")!=0){
        DIR *dir=opendir(".");
        while((entry=readdir(dir))!=NULL){
            stat(entry->d_name,&info);
            if(strcmp(entry->d_name,".sag")==0&&S_ISDIR(info.st_mode)){
                chdir(path_copy);
                exist=true;
                goto label;
            }
        }
        closedir(dir);
        chdir("..");
        getcwd(path_copy,sizeof(path_copy));
    }label:
    if(exist){
        chdir(".sag");
        getcwd(sag_path,sizeof(sag_path));
        chdir("..");
        if(test==1){
            return 0;
        }
        printf("INITED BEFORRRRRRRR\n");
    }
    else{
        if(test==1){
            return 1;
        }
        chdir(path);
        mkdir(".sag");
        chdir(".sag");
        mkdir("files");
        mkdir("commits");
        // mkdir("config");
        // chdir("config");
        FILE *file=fopen("staging.txt","w");
        fclose(file);
        file=fopen("add_log.txt","w");
        fclose(file);
        file=fopen("curr_branch.txt","w");
        fprintf(file,"%s\n","master");
        fclose(file);
        mkdir("staged_area");
        file=fopen("all_branches.txt","w");
        fprintf(file,"%s\n","master");
        fclose(file);
        getcwd(sag_path,sizeof(sag_path));
        chdir("..");
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
        char sag_path[1000];
        char path[1000];
        getcwd(path,sizeof(path));
        init(0,sag_path);
    }
    
    else if(strcmp(argv[1],"add")==0){
        char sag_path[1000];
        char path_dir[100];
        getcwd(path_dir,sizeof(path_dir));
        FILE *log;
        if(strcmp(argv[2],"-f")==0){
            for(int i=3;i<argc;i++){
                if(is_dir_or_not(argv[i])){
                    FILE *file1=fopen(argv[i],"r");
                    if(init(1,sag_path)==1){
                        printf("NOT INITED YET");
                    }
                    else if(file1 == NULL){
                        printf("NO FILE");
                    }
                    else{
                        if(add_file(argv[i],path_dir,sag_path)){
                            log=fopen("add_log.txt","a");
                            fprintf(log,"%s   ",argv[i]);
                        }
                    }
                }
                else{
                    DIR *dir=opendir(argv[i]);
                    if(init(1,sag_path)==1){
                        printf("NOT INITED YET");
                    }
                    else if(dir==NULL){
                        printf("NO DIRECTORY");
                    }
                    else{
                        
                        add_derectory(argv[i],path_dir,sag_path);
                        

                    }  
                }

            }

        }
        else{
            if(is_dir_or_not(argv[2])){
                FILE *file1=fopen(argv[2],"r");
                if(init(1,sag_path)==1){
                    printf("NOT INITED YET");
                }
                else if(file1 == NULL){
                    printf("NO FILE");
                    return 0;
                }
                else{
                    if(add_file(argv[2],path_dir,sag_path)){
                        log=fopen("add_log.txt","a");
                        fprintf(log,"%s\n",argv[2]);
                    }
                } 
            }
            else{
                DIR *dir=opendir(argv[2]);
                if(init(1,sag_path)==1){
                    printf("NOT INITED YET");
                }
                else if(dir==NULL){
                    printf("NO DIRECTORY");
                    return 0;
                }
                else{
                    add_derectory(argv[2],path_dir,sag_path);

                }  
             }
        }
    }

    return 0;
}