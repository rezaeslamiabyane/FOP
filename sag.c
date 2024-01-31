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
#include <math.h>
#include <time.h>
#include <stdint.h>
void print_log(int);
void show_commit_info_with_word_f_flag(int i,char **argv ,int argc ){
    char x[1000];
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    FILE *file;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)==i){
            chdir(entry->d_name);
            file=fopen("message.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            char * str=strtok(x,":");
            str=strtok(NULL,":");
            for(int j=4;j<argc;j++){
                if(strstr(str,argv[j])!=NULL){
                    print_log(i);
                    break;
                }
            }
            chdir("..");
            break;
        }
    }
    chdir("..");
    chdir("..");

}

void show_commit_info_with_word(int i,char * word){
    char x[1000];
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    FILE *file;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)==i){
            chdir(entry->d_name);
            file=fopen("message.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            char * str=strtok(x,":");
            str=strtok(NULL,":");
            if(strstr(str,word)!=NULL){
                print_log(i);
            }
            chdir("..");
            break;
        }
    }
    chdir("..");
    chdir("..");

}

void show_commit_info_with_person(int i, char *person){
    char x[1000];
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    FILE *file;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)==i){
            chdir(entry->d_name);
            file=fopen("person.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            char * str=strtok(x,":");
            str=strtok(NULL,":");
            if(strcmp(person,str)==0){
                print_log(i);
            }
            chdir("..");
            break;
        }
    }
    chdir("..");
    chdir("..");

}

void show_commit_info_with_branch(int i, char *branch){
    char x[1000];
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    FILE *file;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)==i){
            chdir(entry->d_name);
            file=fopen("branch.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            char * str=strtok(x,":");
            str=strtok(NULL,":");
            if(strcmp(branch,str)==0){
                print_log(i);
            }
            chdir("..");
            break;
        }
    }
    chdir("..");
    chdir("..");

}

void print_log(int i){
        char x[1000];
    printf("ID : %d\n",i);
            FILE *file=fopen("time.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("%s\n",x);
            file=fopen("message.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("%s\n",x);
            file=fopen("person.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("%s\n",x);
            file=fopen("branch.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("%s\n",x);
            file=fopen("file_nums.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("%s\n\n",x);

}
void show_commit_info(int i){
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    FILE *file;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)==i){
            chdir(entry->d_name);
            print_log(i);
            chdir("..");
            break;
        }
    }
    chdir("..");
    chdir("..");

}
int permissions(char *);
int add_deleted_file(char *path){
        char path_copy[1000];
        strcpy(path_copy,path);
        char dir_name[1000];
        dir_name[0]='\0';
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
            chdir("staged_area");
            getcwd(path_copy,sizeof(path_copy));
            mkdir(dir_name);
            chdir(dir_name);
            FILE *file=fopen("info.txt","w");
            fprintf(file,"%s\n%d\n%s",branch_name,permissions(path),path);
            fclose(file);
            chdir("..");
            chdir("..");
            return 1;
        }
        else{
            chdir("staged_area");
            getcwd(path_copy,sizeof(path_copy));
            chdir(dir_name);
            FILE *file=fopen("info.txt","w");
            fprintf(file,"%s\n%s",branch_name,path);
            fclose(file);
            chdir("..");
            chdir("..");
            return 1;
        }

}
bool check_if_it_was_commited(char * path){
    char path_copy[1000];
    strcpy(path_copy,path);
    char dir_name[100];
    char *str=strtok(path,"\\:.");
    while(str!=NULL){
        strcat(dir_name,str);
        str=strtok(NULL,"\\:.");
    }
    DIR *dir=opendir(".sag\\files");
    struct dirent *entry;
    int max=0;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(strcmp(dir_name,entry->d_name)==0){
            add_deleted_file(path_copy);
            return true;
        }
    }
    return false; 
}

int finding_last_commit_folder(DIR *dir){
    struct dirent *entry;
    int max=0;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(atoi(entry->d_name)>max){
            max=atoi(entry->d_name);
        }
    }
    return max;
}

char * find_the_last_person(){
    char line[100];
    char gl_p[1000];
    gl_p[0]='\0';
    char lo_p[1000];
    lo_p[0]='\0';
    FILE *file=fopen("C:\\Users\\Reza\\git\\global.txt","r");
    if(file!=NULL){
        while(fgets(line,sizeof(line),file)!=NULL){
            if(strncmp(line,"user.name",9)==0){
                sprintf(gl_p,"%s",line);
            }
        }
    }
    fclose(file);
    file=fopen(".sag\\local.txt","r");
    if(file!=NULL){
        while(fgets(line,sizeof(line),file)!=NULL){
            if(strncmp(line,"user.name",9)==0){
                sprintf(lo_p,"%s",line);
            }
        }
    }
    if (strlen(lo_p) > 0 && lo_p[strlen(lo_p) - 1] == '\n') {
        lo_p[strlen(lo_p) - 1] = '\0';
    }
    if (strlen(gl_p) > 0 && gl_p[strlen(gl_p) - 1] == '\n') {
        gl_p[strlen(gl_p) - 1] = '\0';
    }
    char *str=strtok(gl_p,"#");
    char *p1=strtok(NULL,"#");
    str=strtok(NULL,"#");
    char *boz=strtok(lo_p,"#");
    char *p2=strtok(NULL,"#");
    boz=strtok(NULL,"#");
    char *time1=strtok(str," ");
    time1=strtok(NULL," ");
    time1=strtok(NULL," ");
    time1=strtok(NULL," ");
    char *time2=strtok(boz," ");
    time2=strtok(NULL," ");
    time2=strtok(NULL," ");
    time2=strtok(NULL," ");
    int hour1;
    int hour2;
    int minute1;
    int minute2;
    int second1;
    int second2;
    sscanf(time1,"%d:%d:%d",&hour1,&minute1,&second1);
    sscanf(time2,"%d:%d:%d",&hour2,&minute2,&second2);
    if(hour1>hour2){
        return p1;
    }
    else if(hour2>hour1){
        return p2;
    }
    else{
        if(minute1>minute2){
            return p1;
        }
        else if(minute1<minute2){
            return p2;
        }
        else{
            if(second1>second2){
                return p1;
            }
            else if(second1<second2){
                return p2;
            }
        }
    }
} 

void create_commit_file( int nums,char *message) {
    char commit_dirpath[1000];
    strcpy(commit_dirpath, ".sag\\commits\\");
    char tmp[10];
    sprintf(tmp, "%d", finding_last_commit_folder(opendir(".sag\\commits"))+1);
    FILE * curr_commit=fopen(".sag\\curr_commit.txt","w");
    fprintf(curr_commit,"%s",tmp);
    strcat(commit_dirpath, tmp);
    mkdir(commit_dirpath);
    char branch[100];
    char mes[100];
    char time1[100];
    char person[100];
    char files[100];
    char file_nums[100];
    time_t curr=time(NULL);
    sprintf(branch,"%s\\branch.txt",commit_dirpath);
    sprintf(mes,"%s\\message.txt",commit_dirpath);
    sprintf(files,"%s\\files.txt",commit_dirpath);
    sprintf(file_nums,"%s\\file_nums.txt",commit_dirpath);
    sprintf(person,"%s\\person.txt",commit_dirpath);
    sprintf(time1,"%s\\time.txt",commit_dirpath);
    FILE *file=fopen(file_nums,"w");
    fprintf(file,"file nums :%d",nums);
    fclose(file);
    file=fopen(branch,"w");
    FILE *file2=fopen(".sag\\curr_branch.txt","r");
    fgets(branch,sizeof(branch),file2);
    fprintf(file,"branch :%s",branch);
    fclose(file);
    if (strlen(branch) > 0 && branch[strlen(branch) - 1] == '\n') {
        branch[strlen(branch) - 1] = '\0';
    }
    file=fopen(mes,"w");
    fprintf(file,"message :%s",message);
    fclose(file);
    file=fopen(person,"w");
    fprintf(stdout, "commit successfully with commit ID %s \ntime : %s", tmp,ctime(&curr));
    fprintf(file,"person :%s",find_the_last_person());
    fclose(file);
    file=fopen(time1,"w");
    fprintf(file,"time :%s",ctime(&curr));
    fclose(file);
    file=fopen(files,"w");
    chdir(".sag\\files");
    DIR *dir=opendir(".");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        chdir(entry->d_name);
        struct dirent *entry2;
        int max=0;
        DIR *dir2=opendir(".");
        char addr[1000];
        int commit_num;
        int z=0;
        while((entry2=readdir(dir2))!=NULL){
            if(strcmp(entry2->d_name,".")==0||strcmp(entry2->d_name,"..")==0||strcmp(entry2->d_name,".sag")==0)
                continue;
            struct dirent *entry3;
            int x=0;
            chdir(entry2->d_name);
            DIR *dir3=opendir(".");
            char address[1000];
            char b[1000];
            bool exist=false;
            while((entry3=readdir(dir3))!=NULL){
                if(strcmp(entry3->d_name,".")==0||strcmp(entry3->d_name,"..")==0||strcmp(entry3->d_name,".sag")==0)
                    continue;
                x++;
                FILE * inf=fopen("info.txt","r");
                if(strcmp("info.txt",entry3->d_name)==0){
                    fgets(b,sizeof(b),inf);
                    if (strlen(b) > 0 && b[strlen(b) - 1] == '\n') {
                        b[strlen(b) - 1] = '\0';
                    }
                    if(strcmp(b,branch)==0){
                        exist=true;
                        z=1;
                    }
                    fgets(b,sizeof(b),inf);
                    fgets(address,sizeof(address),inf);
                    
                }
                fclose(inf);
            }
            chdir("..");
            if(x==1){
                z=0;
            }
            else if(x==2&&exist&&atoi(entry2->d_name)>max){
                sprintf(addr,"%s",address);
                commit_num=atoi(entry2->d_name);
            }    
        }
        if(z==1){
            fprintf(file,"%s#%d\n",addr,commit_num);
        }
        chdir("..");
    }
    chdir("..");
    chdir("..");
    
    
}

bool check_file_directory_exists(char *filepath) {
    DIR *dir = opendir(".sag\\files");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filepath) == 0) return true;
    }
    closedir(dir);

    return false;
}

int run_commit(char * const argv[]) {
    char message[1000];
    strcpy(message, argv[3]);
    DIR *dir=opendir(".sag\\staged_area"); 
    struct dirent *entry;
    int x=0;
    while((entry=readdir(dir))!=NULL){
        char dir_path[1000];
        char dir_path_copy[1000];
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        x++;
        if (!check_file_directory_exists(entry->d_name)) {
            strcpy(dir_path, ".sag\\files\\");
            strcat(dir_path, entry->d_name);
            if (mkdir(dir_path) != 0) return 1;
        }
        char system_command[1000];
        sprintf(system_command,"move .sag\\staged_area\\%s .sag\\files\\%s\\%d",entry->d_name,entry->d_name,finding_last_commit_folder(opendir(".sag\\commits"))+1);
        system(system_command);
        // sprintf(system_command,"ren .sag\\files\\%s .sag\\files\\%d",entry->d_name,finding_last_commit_folder(opendir(".sag\\commits"))+1);
        // system(system_command);
        // commit_staged_file(1, );
        // track_file(line);
    }
    if(x==0){
        printf("NOTHING IN STAGE TO BE COMMITEDDDD");
        return 0;
    }
    create_commit_file(x,message);
    return 0;
}




int finding_last_commit_of_a_branch(char *branch){
    chdir(".sag\\commit");
    DIR *dir=opendir(".");
    struct dirent *entry;
    int max=-1;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        chdir(entry->d_name);
        FILE *file=fopen("branch.txt","r");
        char b[100];
        fgets(b,sizeof(b),file);
        if (strlen(b) > 0 && b[strlen(b) - 1] == '\n') {
            b[strlen(b) - 1] = '\0';
        }
        if(strcmp(branch,b)==0){
            max=atoi(entry->d_name);
        }
        chdir("..");
    }
    chdir("..");
    chdir("..");
    return max;
}


void grep(char *path,int test,char * word){
    FILE *file=fopen(path,"r");
    char line[1000];
    char line_copy[1000];
    int x=1;
    while (fgets(line, sizeof(line), file) != NULL) {
        bool exist=false;
        
        strcpy(line_copy,line);
        char *str=strtok(line_copy," ");
        while(str!=NULL){
            if(strcmp(word,str)==0){
                exist=true;
            }
            str=strtok(NULL," ");
        }
        if(exist){
            if(test){
                printf("%d %s",x,line);
            }
            else{
                printf("%s",line);
            }
        }
        x++;
    }
}

void diff_whithout_line(char * absolute_adress1,char *absolute_adress2){
    char name1[1000];
    char name2[1000];
    FILE *file1=fopen(absolute_adress1,"r");
    FILE *file2=fopen(absolute_adress2,"r");
    char *str=strtok(absolute_adress1,"\\");
    while(str!=NULL){
        strcpy(name1,str);
        str=strtok(NULL,"\\");
    }
    char *boz=strtok(absolute_adress2,"\\");
    while(boz!=NULL){
        strcpy(name2,boz);
        boz=strtok(NULL,"\\");
    }
    int begin1=1;
    int begin2=1;
    char line1[1000];
    char line2[1000];
    void *l1=NULL;
    void *l2=NULL;
    int check=0;
    while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL&&(l2=fgets(line2, sizeof(line2), file2)) != NULL) {
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line1);i++){
                if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line1, sizeof(line1), file1)==NULL){
                    l1=NULL;
                    goto l;
                }
                //begin1++; 
            }
            else{
                break;
            }
        }
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line2, sizeof(line2), file2)==NULL){
                    l2=NULL;
                    goto l;
                }
                //begin2++; 
            }
            else{
                break;
            }
        }
        if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
            line1[strlen(line1) - 1] = '\0';
        }
        if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        if(strcmp(line1,line2)!=0){
            printf("%s-%d\n\e[0;31m%s\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,begin1,line1,name2,begin2,line2);
        }
        begin1++;
        begin2++;
    }
    l:
    if(l1!=NULL){
        while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL) {
            while(1){
                bool exist=true;
                for(int i=0;i<strlen(line1);i++){
                    if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                        exist=false;
                    }
                }
                if(exist){
                    if(fgets(line1, sizeof(line1), file1)==NULL){
                        l1=NULL;
                        goto l;
                    }
                    //begin1++; 
                }
                else{
                    break;
                }
            }
            printf("%s-%d\n\e[0;31m%s\e[0m\n%s-%d\n\e[0;32mEMPTY\e[0m\n",name1,begin1,line1,name2,begin1);
            begin1++;
        }
        
        
    }
    else if(l2!=NULL){
        while ((l2=fgets(line2, sizeof(line2), file2)) != NULL) {
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line2, sizeof(line2), file2)==NULL){
                    l2=NULL;
                    goto lz;
                }
                //begin2++; 
            }
            else{
                break;
            }
        
        }
        if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        printf("%s-%d\n\e[0;31mEMPTY\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,begin2,name2,begin2,line2);
        begin2++;
        }
    }
    lz:
}

void diff_line_given(char * absolute_adress1,int begin1,int end1,char * absolute_adress2,int begin2,int end2){
    char name1[1000];
    char name2[1000];
    FILE *file1=fopen(absolute_adress1,"r");
    FILE *file2=fopen(absolute_adress2,"r");
    char *str=strtok(absolute_adress1,"\\");
    while(str!=NULL){
        strcpy(name1,str);
        str=strtok(NULL,"\\");
    }
    char *boz=strtok(absolute_adress2,"\\");
    while(boz!=NULL){
        strcpy(name2,boz);
        boz=strtok(NULL,"\\");
    }
    char line1[1000];
    char line2[1000];
    for(int x=1;x<begin1;x++){
        fgets(line1,sizeof(line1),file1);
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line1);i++){
                if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                    exist=false;
                }
            }
            if(!exist){
                break;
            }
            else{
                fgets(line1,sizeof(line1),file1);
            }
        }   
    }
    for(int x=1;x<begin2;x++){
        fgets(line2, sizeof(line2), file2);
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(!exist){
                break;
            }
            else{
                fgets(line2, sizeof(line2), file2);
            }
        }
    }
    void *l1=NULL;
    void *l2=NULL;
    while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL&&(l2=fgets(line2, sizeof(line2), file2)) != NULL){
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line1);i++){
                if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line1, sizeof(line1), file1)==NULL){
                    l1=NULL;
                    goto lt;
                }
                //begin1++; 
            }
            else{
                break;
            }
        }
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line2, sizeof(line2), file2)==NULL){
                    l2=NULL;
                    goto lt;
                }
                //begin2++; 
            }
            else{
                break;
            }
        }
        if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
            line1[strlen(line1) - 1] = '\0';
        }
        if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        if(strcmp(line1,line2)!=0){
            printf("%s-%d\n\e[0;31m%s\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,begin1,line1,name2,begin2,line2);
        }
        begin1++;
        begin2++;
        if(begin1==end1+1){
            goto lt;
        }
        else if(begin2==end2+1){
            goto lt;
        }

    }
    lt:
    if(begin2==end2+1){
        if(begin1==end1+1)
            return;
        while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL) {
            while(1){
                bool exist=true;
                for(int i=0;i<strlen(line1);i++){
                    if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                        exist=false;
                    }
                }
                if(exist){
                    if(fgets(line1, sizeof(line1), file1)==NULL){
                        return;
                    }
                    //begin1++; 
                }
                else{
                    break;
                }
            }
            if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
                line1[strlen(line1) - 1] = '\0';
            }

            printf("%s-%d\n\e[0;31m%s\e[0m\n%s-%d\n\e[0;32mNOT IN THE GIVEN LINE\e[0m\n",name1,begin1,line1,name2,begin2);
            begin1++;
            begin2++;
            if(begin1==end1+1){
            return;
        }
        }
    }
    else if(begin1==end1+1){
        while ((l2=fgets(line2, sizeof(line2), file2)) != NULL) {
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line2, sizeof(line2), file2)==NULL){
                    return;
                }
                //begin2++; 
            }
            else{
                break;
            }
        
        }
        if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        printf("%s-%d\n\e[0;31mNOT IN THE GIVEN LINE\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,begin1,name2,begin2,line2);
        begin2++;
        begin1++;
        if(begin2==end2+1){
            return;
        }
    }

    }
    else if(l2==NULL){
        while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL) {
            while(1){
                bool exist=true;
                for(int i=0;i<strlen(line1);i++){
                    if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
                        exist=false;
                    }
                }
                if(exist){
                    if(fgets(line1, sizeof(line1), file1)==NULL){
                        return;
                    }
                    //begin1++; 
                }
                else{
                    break;
                }
            }
            if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
                line1[strlen(line1) - 1] = '\0';
            }
            printf("%s-%d\n\e[0;31m%s\e[0m\n%s-%d\n\e[0;32mNOT IN THE GIVEN LINE\e[0m\n",name1,begin1,line1,name2,begin2);
            begin1++;
            begin2++;
            if(begin1==end1+1){
            return;
        }
        }

    }
    else if(l1==NULL){
        while ((l2=fgets(line2, sizeof(line2), file2)) != NULL) {
        while(1){
            bool exist=true;
            for(int i=0;i<strlen(line2);i++){
                if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
                    exist=false;
                }
            }
            if(exist){
                if(fgets(line2, sizeof(line2), file2)==NULL){
                    return;
                }
                //begin2++; 
            }
            else{
                break;
            }
        
        }
        if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
            line2[strlen(line2) - 1] = '\0';
        }
        printf("%s-%d\n\e[0;31mNOT IN THE GIVEN LINE\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,begin1,name2,begin2,line2);
        begin2++;
        begin1++;
        if(begin2==end2+1){
            return;
        }
    }

    }
}

void commit(){

}

int finding_last_commit_of_a_file(DIR *dir,char * branch){
    struct dirent *entry;
    int max=-1;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        chdir(entry->d_name);
        FILE*file=fopen("info.txt","r");
        char line[1000];
        fgets(line,sizeof(line),file);
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if(strcmp(line,branch)==0){
            max=atoi(entry->d_name);
        }
        chdir("..");
    }
    return max;
}

bool difference(FILE * file1,FILE *file2){
    int byte1=0;
    int byte2=0;
    int j=0;
    char * text1=(char *)malloc(1000000*sizeof(char));
        while(!feof(file1)){
            text1[j]=fgetc(file1);
            j++;
        }  
        text1[j]='\0';
        j=0;
    char * text2=(char *)malloc(1000000*sizeof(char));
        while(!feof(file2)){
            text2[j]=fgetc(file2);
            j++;
        }  
        text2[j]='\0';
    if(strcmp(text1,text2)==0){
        return false;
    }

    return true;
}
int permissions(char *);
bool check_in_stage(char *);
int finding_permission(char *name){
    chdir(".sag\\staged_area");
    chdir(name);
    FILE *per=fopen("info.txt","r");
    char line[100];
    fgets(line,sizeof(line),per);
    fgets(line,sizeof(line),per);
    int length = strlen(line);
    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }
    return atoi(line);
}
void showing_status_for_A(char *path,char ** files,int x){
    DIR *dir=opendir(path);
    struct dirent *entry;
    struct stat info;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        char path_dir[1000];
        sprintf(path_dir,"%s\\%s",path,entry->d_name);
        stat(path_dir,&info);
        if(S_ISDIR(info.st_mode)==0){
            bool exist=false;
            for(int i=0;i<x;i++){
                if(strcmp(files[i],entry->d_name)==0){
                    exist=true;
                    break;
                }
            }
            if(exist){
                continue;
            }
            else{
                printf("%s -A\n",entry->d_name);
            }
            
        }
        else{
            showing_status_for_A(path_dir,files,x); 
        }
    }

}

void showing_status(){
    char **files=(char**)malloc(100*sizeof(char *));
    for(int i=0;i<100;i++){
        files[i]=(char*)malloc(100*sizeof(char));
    }
    char staged[1000][1000];
    FILE *tracked=fopen(".sag\\tracked","r");
    chdir(".sag\\staged_area");
    DIR *dir=opendir(".");
    struct dirent *entry;
    int i=0;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        strcpy(staged[i],entry->d_name);
        chdir(entry->d_name);
        FILE *file=fopen("info.txt","r");
        char line[1000];
        char line_copy[1000];
        int x=0;
        int permission;
        while (fgets(line, sizeof(line), file)!=NULL) {
            int length = strlen(line);
            if (length > 0 && line[length - 1] == '\n') {
                line[length - 1] = '\0';
            }
            if(x==1){
                permission=atoi(line);
            }
            strcpy(line_copy,line);
            x++;
        }
        strcpy(line,line_copy);
        char name[1000];
        char tra[1000];
        char *str=strtok(line_copy,"\\");
            while(str!=NULL){
                strcpy(name,str);
                str=strtok(NULL,"\\");
            }
        strcpy(files[i],name);
        if(fopen(line,"r")==NULL){
            printf("%s +D\n",name);
        }
        else{
            // bool exist=false;
            // while(fgets(tra,sizeof(tra),tracked)!=NULL){
            //     int length = strlen(tra);
            //     if (length > 0 && tra[length - 1] == '\n') {
            //         tra[length - 1] = '\0';
            //     }
            //     if(strcmp(tra,line)==0){
            //         exist=true;
            //         break;
            //     }
            // }
            //if(exist){
                if(difference(fopen(line,"r"),fopen(name,"r"))){
                    printf("%s +M\n",name);
                }
            //}

            else if(permission!=permissions(line)){
                printf("%s +T\n",name);
            }
            else{
                printf("%s +A\n",name);
            }
        }
        chdir("..");
        i++;
    }
    int z=i;
    chdir("..");
    chdir("commits");
    dir=opendir(".");
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        bool e=false;
        for(int j=0;j<i;j++){
            if(strcmp(entry->d_name,staged[j])==0){
                e=true;
                break;
            }
        }
        
        if(!e){
            chdir(entry->d_name);
            char num[100];
            sprintf(num,"%d",finding_last_commit_of_a_file(opendir("."),"master"));
            chdir(num);
            FILE *file=fopen("info.txt","r");
            char line[1000];
            char line_copy[1000];
            int x=0;
            int permission;
            while (fgets(line, sizeof(line), file)!=NULL) {
                int length = strlen(line);
                if (length > 0 && line[length - 1] == '\n') {
                    line[length - 1] = '\0';
                }
                if(x==1){
                    permission=atoi(line);
                }
                strcpy(line_copy,line);
                x++;
            }
            strcpy(line,line_copy);
            char name[1000];
            char tra[1000];
            char *str=strtok(line_copy,"\\");
                while(str!=NULL){
                    strcpy(name,str);
                    str=strtok(NULL,"\\");
                }
                strcpy(files[z],name);
            if(fopen(line,"r")==NULL){
                printf("%s -D\n",name);
            }
            else{
                if(difference(fopen(line,"r"),fopen(name,"r"))){
                    printf("%s -M\n",name);
                }
                else if(permission!=permissions(line)){
                    printf("%s -T\n",name);
                }
            }
            chdir("..");
            chdir("..");
            z++;
        }
    }
    
    chdir("..");
    chdir("..");
    char path[1000];
    getcwd(path,sizeof(path));
    showing_status_for_A(path,files,z);

}


int permissions(char *path){
    int first_digit=0;
    int second_digit=0;
    int third_digit=0;
    int permission=0;
    struct stat info;
    stat(path,&info);
    if ((info.st_mode & S_IRUSR) && (info.st_mode & S_IREAD))
          first_digit+=4;
    if ((info.st_mode & S_IWUSR) && (info.st_mode & S_IWRITE))
          first_digit+=2;
    if ((info.st_mode & S_IXUSR) && (info.st_mode & S_IEXEC))
          first_digit+=1;
    if ((info.st_mode & S_IRGRP) && (info.st_mode & S_IREAD))
          second_digit+=4;
    if ((info.st_mode & S_IRGRP) && (info.st_mode & S_IWRITE))
          second_digit+=2;
    if ((info.st_mode & S_IRGRP) && (info.st_mode & S_IEXEC))
          second_digit+=1;
    if ((info.st_mode & S_IROTH) && (info.st_mode & S_IREAD))
          third_digit+=4;
    if ((info.st_mode & S_IROTH) && (info.st_mode & S_IWRITE))
          third_digit+=2;
    if ((info.st_mode & S_IROTH) && (info.st_mode & S_IEXEC))
          third_digit+=1;
    permission=first_digit*100+second_digit*10+third_digit;
    return permission;

}
void reset_undo(FILE* file){
    char line[1000];
    char line_copy[1000];
    while (fgets(line, sizeof(line), file)!=NULL) {
        int length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        strcpy(line_copy,line);
    }
    fclose(file);
    char *str1=strtok(line_copy,"#");
    char addreses[1000][1000];
    int i=0;
    while(str1!=NULL){
        strcpy(addreses[i],str1);
        if(strcmp(str1,"\n")==0)
            break;
        str1=strtok(NULL,"#");
        i++;
    }
    for(int j=0;j<i;j++){
        char dir_name[1000];
        dir_name[0]='\0';
        char *str=strtok(addreses[j],"\\:.");
        while(str!=NULL){
            strcat(dir_name,str);
            str=strtok(NULL,"\\:.");
        }
        char system_command[1000];
        chdir(".sag\\staged_area");
        char path[100];
        getcwd(path,sizeof(path));
        sprintf(system_command,"rmdir /s /q %s\\%s",path,dir_name);
        system(system_command);
        chdir("..");
        chdir("..");
    }
    FILE *log=fopen(".sag\\add_log.txt","r");
    FILE *log_copy=fopen(".sag\\add_log1.txt","w");
    while (fgets(line, sizeof(line), log)!=NULL) {
        if(strncmp(line,line_copy,strlen(line_copy))==0){
            break;
        }
        fputs(line,log_copy);
    }
    fclose(log);
    fclose(log_copy);
    remove(".sag\\add_log.txt");
    rename(".sag\\add_log1.txt",".sag\\add_log.txt");
}

bool check_in_stage(char *name){
    chdir(".sag\\staged_area");
    DIR * dir=opendir(".");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,name)==0){
            chdir("..");
            chdir("..");
            return true;
        }
    }
    chdir("..");
    chdir("..");
    return false;
}

void unstaging(char *path){
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
            char dir_name[1000];
            dir_name[0]='\0';
            char *str=strtok(path_dir,"\\:.");
            while(str!=NULL){
                strcat(dir_name,str);
                str=strtok(NULL,"\\:.");
            }
            char system_command[1000];
            sprintf(system_command,"move .sag\\staged_area\\%s .sag\\reset_files_for_redo ",dir_name);
            system(system_command);
        }
        else{
            unstaging(path_dir);
            
        }
    }
}

void serching_for_staged(char *path,int depth,int now){
    DIR *dir=opendir(path);
    struct dirent *entry;
    struct stat info;
    if(now<depth){
        while((entry=readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
                continue;
            char path_dir[1000];
            sprintf(path_dir,"%s\\%s",path,entry->d_name);
            stat(path_dir,&info);
            if(S_ISDIR(info.st_mode)==0){
                char dir_name[1000];
                dir_name[0]='\0';
                char path_copy[1000];
                strcpy(path_copy,path);
                char *str=strtok(path_dir,"\\:.");
                while(str!=NULL){
                    strcat(dir_name,str);
                    str=strtok(NULL,"\\:.");
                }
                if(check_in_stage(dir_name)){
                    printf("%s is in stage\n",entry->d_name);
                }
                else{
                    printf("%s is not in stage\n",entry->d_name);
                }
            }
            else{
                serching_for_staged(path_dir,depth,now+1);
            }
        }
    }
    
}

// int chek_in_stage(FILE *stage,char*path){
//     char line[1000];
//     while (fgets(line, sizeof(line), stage) != NULL) {
//         int length = strlen(line);
//         if (length > 0 && line[length - 1] == '\n') {
//             line[length - 1] = '\0';
//         }
//         if (strcmp(path, line) == 0) return 1;
//     }
//     fclose(stage);
//     return 0;
    
// }
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
int add_file(char *path){
        char path_copy[1000];
        strcpy(path_copy,path);
        char dir_name[1000];
        dir_name[0]='\0';
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
            chdir("staged_area");
            getcwd(path_copy,sizeof(path_copy));
            mkdir(dir_name);
            chdir(dir_name);
            FILE *file=fopen("info.txt","w");
            fprintf(file,"%s\n%d\n%s",branch_name,permissions(path),path);
            fclose(file);
            char system_command[1000];
            sprintf(system_command,"copy %s",path);
            system(system_command);
            chdir("..");
            chdir("..");
            return 1;
        }
        else{
            chdir("staged_area");
            getcwd(path_copy,sizeof(path_copy));
            chdir(dir_name);
            FILE *file=fopen("info.txt","w");
            fprintf(file,"%s\n%s",branch_name,path);
            fclose(file);
            char system_command[1000];
            sprintf(system_command,"copy %s",path);
            system(system_command);
            chdir("..");
            chdir("..");
            return 1;
        }
}
int is_dir_or_not(char * path){
    if(fopen(path,"rb")==NULL){
        return 0;
    }
    return 1;
}

int add_derectory(char *path,FILE*log){
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
            if(add_file(path_dir)==1){
                log=fopen("add_log.txt","a");
                fprintf(log,"%s###",path_dir);
            }
        }
        else{
            add_derectory(path_dir,log);
        }
    }
}


int init(int test){
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
        mkdir("reset_files_for_redo");
        mkdir("stash_area");
        // mkdir("config");
        // chdir("config");
        FILE *file=fopen("add_log.txt","w");
        fclose(file);
        file=fopen("curr_branch.txt","w");
        fprintf(file,"%s\n","master");
        fclose(file);
        file=fopen("curr_commit.txt","w");
        fclose(file);
        file=fopen("tracked.txt","w");
        mkdir("staged_area");
        mkdir("all_branches");
        chdir("all_branches");
        file=fopen("master.txt","w");
        chdir("..");
        fclose(file);
        system("MOVE C:\\Users\\Reza\\git\\local.txt");
        system("MOVE C:\\Users\\Reza\\git\\alias_command_local.txt");
        chdir("..");
        printf("NOW IT IS INITED");
    }
}

void config(char * address,char *type,char *name){
                time_t curr=time(NULL);
                FILE *user=fopen(address,"r");
                if(user!=NULL){
                    FILE *user=fopen(address,"a");
                    fprintf(user,"%s#%s#%s\n",type,name,ctime(&curr));
                }
                else{
                    FILE *user=fopen(address,"w");
                    fprintf(user,"%s#%s#%s\n",type,name,ctime(&curr));
                }
}

void alias(char * address,char *type,char *name){
                FILE *user=fopen(address,"r");
                if(user!=NULL){
                    FILE *user=fopen(address,"a");
                    fprintf(user,"%s#%s\n",type,name);
                }
                else{
                    FILE *user=fopen(address,"w");
                    fprintf(user,"%s#%s\n",type,name);
                }
}

int main(int argc,char ** argv){
  if(strncmp(argv[1],"config",6)==0){
        if(strncmp(argv[2],"alias",5)==0){
            if(argv[2][5]!='.')
                printf("invalid alias");
            else{
            alias("C:\\Users\\Reza\\git\\alias_command_local.txt",argv[2],argv[3]);
            }
        }
        else if(strncmp(argv[3],"alias",5)==0){
            if(argv[3][5]!='.')
                printf("invalid alias");
            else if(strcmp(argv[2],"--global")==0){
                alias("C:\\Users\\Reza\\git\\alias_command_global.txt",argv[3],argv[4]);
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
                if(init(1)==1){
                    
                    config("C:\\Users\\Reza\\git\\local.txt",argv[2],argv[3]);
                }
                else{
                    config(".sag\\local.txt",argv[2],argv[3]);
                }
            }
        }
    }
    else if(strcmp(argv[1],"init")==0){
        init(0);
    }
    
    else if(strcmp(argv[1],"add")==0){
        char path_dir[100];
        getcwd(path_dir,sizeof(path_dir));
        FILE *log;
        if(strcmp(argv[2],"-f")==0){
            for(int i=3;i<argc;i++){
                char absolute_adress[1000];
                sprintf(absolute_adress,"%s\\%s",path_dir,argv[i]);
                if(is_dir_or_not(absolute_adress)){
                    FILE *file1=fopen(absolute_adress,"r");
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    
                    else if(file1 == NULL){
                        char absolute_adress_copy[1000];
                        strcpy(absolute_adress_copy,absolute_adress);
                        if(check_if_it_was_commited(absolute_adress_copy)){
                            log=fopen(".sag\\add_log.txt","a");
                            fprintf(log,"%s###",absolute_adress);  
                        }
                        else{
                            printf("NO FILE");
                        }  
                    }
                    else{
                        if(add_file(absolute_adress)){
                            log=fopen("add_log.txt","a");
                            fprintf(log,"%s###",absolute_adress);
                        }
                    }
                }
                else{
                    DIR *dir=opendir(absolute_adress);
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(dir==NULL){
                        printf("NO DIRECTORY");
                    }
                    else{
                        add_derectory(absolute_adress,log);
                    }  
                }

            }
            chdir(".sag");
            log=fopen("add_log.txt","a");
            fprintf(log,"\n");

        }
        else if(strcmp(argv[2],"-n")==0){
            char absolute_adress[1000];
            getcwd(absolute_adress,sizeof(absolute_adress));
            if(init(1)==1){
                printf("NOT INITED YET");
            }
            else{
                serching_for_staged(absolute_adress,atoi(argv[3]),0);
            }
        }
        else if(strcmp(argv[2],"-redo")==0){
            if(init(1)==1){
                printf("NOT INITED YET");
            }
            else{
                struct dirent *entry;
                DIR *dir=opendir(".sag\\reset_files_for_redo");
                while((entry=readdir(dir))!=NULL){
                    if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
                        continue;
                    char system_command[1000];
                    sprintf(system_command,"move .sag\\reset_files_for_redo\\%s .sag\\staged_area",entry->d_name);
                    system(system_command);
                }
            }
        }
        else{
            for(int i=2;i<argc;i++){
                char absolute_adress[1000];
                sprintf(absolute_adress,"%s\\%s",path_dir,argv[i]);
                if(1){
                    FILE *file1=fopen(absolute_adress,"r");
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(file1 == NULL){
                        char absolute_adress_copy[1000];
                        strcpy(absolute_adress_copy,absolute_adress);
                        if(check_if_it_was_commited(absolute_adress_copy)){
                            log=fopen("add_log.txt","a");
                            fprintf(log,"%s###",absolute_adress);
                        }
                        else{
                            printf("NO FILE");
                            
                        }
                    }
                    else{
                        if(add_file(absolute_adress)){
                            log=fopen("add_log.txt","a");
                            fprintf(log,"%s###",absolute_adress);
                        }
                    } 
                }
                else{
                    DIR *dir=opendir(absolute_adress);
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(dir==NULL){
                        printf("NO DIRECTORY");
                        return 0;
                    }
                    else{
                        add_derectory(absolute_adress,log);
                    }  
                }
            }
            chdir(".sag");
            log=fopen("add_log.txt","a");
            fprintf(log,"\n");
        }
    }
    else if(strcmp(argv[1],"reset")==0){
        char path_dir[100];
        getcwd(path_dir,sizeof(path_dir));
        FILE *log;
        if(strcmp(argv[2],"-f")==0){
            for(int i=3;i<argc;i++){
                char absolute_adress[1000];
                sprintf(absolute_adress,"%s\\%s",path_dir,argv[i]);
                if(is_dir_or_not(absolute_adress)){
                    FILE *file1=fopen(absolute_adress,"r");
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(file1 == NULL){
                        printf("NO FILE");
                    }
                    else{
                        char dir_name[1000];
                        dir_name[0]='\0';
                        char *str=strtok(absolute_adress,"\\:.");
                        while(str!=NULL){
                            strcat(dir_name,str);
                            str=strtok(NULL,"\\:.");
                        }
                        char system_command[1000];
                        sprintf(system_command,"move .sag\\staged_area\\%s .sag\\reset_files_for_redo ",dir_name);
                        system(system_command);
                    }
                }
                else{
                    DIR *dir=opendir(absolute_adress);
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(dir==NULL){
                        printf("NO DIRECTORY");
                    }
                    else{
                        unstaging(absolute_adress);
                    }  
                }

            }
        }
        else if(strcmp(argv[2],"-undo")==0){
            if(init(1)==1){
                printf("NOT INITED YET");
            }
            else{
                reset_undo(fopen(".sag\\add_log.txt","r+"));
            }
        }
        else{
            for(int i=2;i<argc;i++){
                char absolute_adress[1000];
                sprintf(absolute_adress,"%s\\%s",path_dir,argv[i]);
                if(is_dir_or_not(absolute_adress)){
                    FILE *file1=fopen(absolute_adress,"r");
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(file1 == NULL){
                        printf("NO FILE");
                        return 0;
                    }
                    else{
                        char dir_name[1000];
                        dir_name[0]='\0';
                        char *str=strtok(absolute_adress,"\\:.");
                        while(str!=NULL){
                            strcat(dir_name,str);
                            str=strtok(NULL,"\\:.");
                        }
                        char system_command[1000];
                        sprintf(system_command,"move .sag\\staged_area\\%s .sag\\reset_files_for_redo",dir_name);
                        system(system_command);
                    } 
                }
                else{
                    DIR *dir=opendir(absolute_adress);
                    if(init(1)==1){
                        printf("NOT INITED YET");
                    }
                    else if(dir==NULL){
                        printf("NO DIRECTORY");
                        return 0;
                    }
                    else{
                        unstaging(absolute_adress);
                    }  
                }
            }
        }
    }
    else if(strcmp(argv[1],"status")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            char absolute_adress[1000];
            getcwd(absolute_adress,sizeof(absolute_adress));
            showing_status();
        }
    }
    else if(strcmp(argv[1],"commit")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            char absolute_adress[1000];
            getcwd(absolute_adress,sizeof(absolute_adress));
            if(strlen(argv[3])>72){
                printf("BIG MESSAGE\n");
            }
            else if(argc<4){
                printf("MESSAGE??????\n");
            }
            else{
                run_commit(argv);
            }
        }
    }
    else if(strcmp(argv[1],"diff")==0){
        char path_dir[100];
        getcwd(path_dir,sizeof(path_dir));
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        if(strcmp(argv[2],"-f")==0){
            char absolute_adress1[1000];
            sprintf(absolute_adress1,"%s\\%s",path_dir,argv[3]);
            char absolute_adress2[1000];
            sprintf(absolute_adress2,"%s\\%s",path_dir,argv[4]);
            if(argc>5){
                int begin1;
                int begin2;
                int end1;
                int end2;
                char *str=strtok(argv[6],"-");
                begin1=atoi(str);
                str=strtok(NULL,"-");
                end1=atoi(str);
                char *boz=strtok(argv[8],"-");
                begin2=atoi(boz);
                boz=strtok(NULL,"-");
                end2=atoi(boz);
                diff_line_given(absolute_adress1,begin1,end1,absolute_adress2,begin2,end2);
            }
            else{
                diff_whithout_line(absolute_adress1,absolute_adress2);
            }
        }
        else{

        }
        
    }
    else if(strcmp(argv[1],"log")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(argc<3){
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                for(int i=max;i>0;i--){
                    show_commit_info(i);
                }
            }
            else if(strcmp(argv[2],"-n")==0){
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                int num=atoi(argv[3]);
                for(int i=max;num>0;i--,num--){
                    show_commit_info(i);
                }
            }
            else if(strcmp(argv[2],"-branch")==0){
                DIR *dir=opendir(".sag\\all_branches");
                struct dirent *entry;
                bool exist=false;
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                char boz[100];
                sprintf(boz,"%s.txt",argv[3]);
                while((entry=readdir(dir))!=NULL){
                    if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
                        continue;
                    if(strcmp(boz,entry->d_name)==0){
                        exist=true;
                        break;
                    }     
                }
                if(exist){
                   for(int i=max;i>0;i--){
                        show_commit_info_with_branch(i,argv[3]);
                    } 
                }
                else{
                    printf("NO BRANCH WITH THAT NAME");
                }
                
            }
            else if(strcmp(argv[2],"-author")==0){
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                for(int i=max;i>0;i--){
                    show_commit_info_with_person(i,argv[3]);
                }   
            }
            else if(strcmp(argv[2],"-search")==0){
                    int max=finding_last_commit_folder(opendir(".sag\\commits"));
                if(strcmp(argv[3],"-f")==0){
                    for(int i=max;i>0;i--){
                        show_commit_info_with_word_f_flag(i,argv,argc);
                    }
                }
                else{
                    for(int i=max;i>0;i--){
                        show_commit_info_with_word(i,argv[3]);
                    }
                }   
            }
        }

    }
    else if(strcmp(argv[1],"branch")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(argc==2){
                DIR *dir=opendir(".sag\\all_branches");
                struct dirent *entry;
                while((entry=readdir(dir))!=NULL){
                    if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
                        continue;
                    for(int i=0;i<strlen(entry->d_name)-4;i++){
                        printf("%c",entry->d_name[i]);
                    }
                    printf("\n");
                }   
            }
            else{
                char branch[1000];
                
                strcpy(branch,argv[2]);
                strcat(branch,".txt");
                DIR *dir=opendir(".sag\\all_branches");
                struct dirent *entry;
                bool exist=false;
                while((entry=readdir(dir))!=NULL){
                    if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
                        continue;
                    if(strcmp(branch,entry->d_name)==0){
                        exist=true;
                        break;
                    }
                }
                if(exist){
                    printf("THIS BRANCH HAD CREATED BEFOR");
                }
                else{
                    char create[1000];
                    sprintf(create,".sag\\all_branches\\%s",branch);
                    FILE *file=fopen(create,"w");
                    fprintf(file,"%d",finding_last_commit_folder(opendir(".sag\\commits")));
                }
            }
        }

    }
    return 0;
}