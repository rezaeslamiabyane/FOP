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
#include <math.h>
#include <time.h>
#include <stdint.h>
//#include <libavformat/avformat.h>

//regex_t regex; int reti; char msgbuf[100]; /* Compile regular expression */ reti = regcomp(&regex, "^a[[:alnum:]]", 0); if (reti) { fprintf(stderr, "Could not compile regex\n"); exit(1); } /* Execute regular expression */ reti = regexec(&regex, "abc", 0, NULL, 0); if (!reti) { puts("Match"); } else if (reti == REG_NOMATCH) { puts("No match"); } else { regerror(reti, &regex, msgbuf, sizeof(msgbuf)); fprintf(stderr, "Regex match failed: %s\n", msgbuf); exit(1); } /* Free memory allocated to the pattern buffer by regcomp() */ regfree(&regex)
typedef struct files_in_commits{ 
    char commit_num[1000];
    char address[1000];    
} files;

char * find_the_last_person_email();
int finding_last_commit_of_a_branch(char *);
char *find_the_last_person();
void show_tag(char *);
void print_tags();
bool tag_existance(char *);
void replace(char *,char*,int,char *);
void make(char *,char*,int,char *);
int create_tag(char **,int);
int finding_last_commit_folder(DIR *);
int nth_commit_of_a_branch(char *, int ,int);
void print_log(int ,char *,int);
int find_since_log_commit_ID(char *,int);
int find_before_log_commit_ID(char *,int);
int number_of_files_and_folders(DIR *);
bool comparing_head_and_curr_commit();
bool diff_whithout_line(char*,char *,char *,char *);

bool check_todo_txt(FILE *file){
    char text[1000];
    int i=0;
    while(!eof){
        text[i]=fgetc(file);
        i++;
    }
    text[i]='\0';
    if(strstr(text,"TODO")!=NULL){
        return false;
    }
    return true;
}

bool format_check(char * name){
    char h[1000][1000]={".c",".txt",".cpp",".mp4",".wav","mp3"};
    bool exist=false;
    for(int i=0;i<6;i++){
        if(strcmp(strrchr(name,'.'),h[i])==0){
            exist=true;
        }
    }
    return true;
}

bool character_limit(FILE *file){
    int i=0;
    while(!feof(file)){
        fgetc(file);
        i++;
    }
    if(i>20000){
        return false;
    }
    return true;
}

bool file_size_check(char *path){
    struct stat size;
    stat(path,&size);
    if(size.st_size>5000000){
        return false;
    }
    return true;
}

bool static_error_check(char *name){
    char command[1000];
    sprintf(command,"gcc -fsyntax-only %s 2>",name);
    if(system(command)==0){
        return true;
    }
    return false;
}

bool braces_balance(FILE *file){
    int b=0;
    int k=0;
    int p=0;
    char c;
    while(!feof(file)){
        c=fgetc(file);
        if(c=='{')
            k++;
        else if(c=='}')
            k--;
        else if(c=='(')
            p++;
        else if(c==')')
            p--;
        else if(c==']')
            b--;
        else if(c=='[')
            b++; 
    }
    if(b!=0||p!=0||k!=0)
        return false;
    return true;
}

bool eof_blank_space(FILE *file){
    char last;
    fseek(file,-1,SEEK_END);
    last=fgetc(file);
    fclose(file);
    if(isspace(last))
        return false;
    return true;
}

bool add_hooks_to_files(FILE * file,char *name,int all,char **hooks){
    char *x=strrchr(name,'.');
    printf("\e[0;35m%s\e[0m\n",name);
    if(strcmp(x,".c")==0||strcmp(x,".cpp")==0){
        for(int i=0;i<all;i++){
            if(strcmp(hooks[i],"eof-blank-space")==0){
                if(eof_blank_space(fopen(name,"r"))){
                    printf("eof-blank-space   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("eof-blank-space   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"braces-balance")==0){
                if(braces_balance(fopen(name,"r"))){
                    printf("braces-balance   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("braces-balance   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"static-error-check")==0){
                if(static_error_check(name)){
                    printf("static-error-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("static-error-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"file-size-check")==0){
                if(file_size_check(name)){
                    printf("file-size-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("file-size-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"character-limit")==0){
                if(character_limit(fopen(name,"r"))){
                    printf("character-limit   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("character-limit   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"format-check")==0){
                if(format_check(name)){
                    printf("format-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("format-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else{
                printf("%s   \e[0;33mskipped\e[0m\n",hooks[i]);
            }
        }
        
    }
    else if(strcmp(x,".txt")==0){
        for(int i=0;i<all;i++){
            if(strcmp(hooks[i],"eof-blank-space")==0){
                if(eof_blank_space(fopen(name,"r"))){
                    printf("eof-blank-space   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("eof-blank-space   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"balance-braces")==0){
                if(braces_balance(fopen(name,"r"))){
                    printf("balance-braces   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("balance-braces   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"file-size-check")==0){
                if(file_size_check(name)){
                    printf("file-size-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("file-size-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"character-limit")==0){
                if(character_limit(fopen(name,"r"))){
                    printf("character-limit   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("character-limit   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"format-check")==0){
                if(format_check(name)){
                    printf("format-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("format-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else if(strcmp(hooks[i],"todo-check")==0){
                if(check_todo_txt(fopen(name,"r"))){
                    printf("todo-check   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("todo-check   \e[0;31mfailed\e[0m\n");
                }
            }
            else{
                printf("%s   \e[0;33mskipped\e[0m\n",hooks[i]);
            }

        }
    }
    else{
        for(int i=0;i<all;i++){
            if(strcmp(hooks[i],"time-limit")==0){
                char command[1000];
                sprintf(command, "ffmpeg -i %s 2>&1 | grep Duration | cut -d ' ' -f 4 | sed s/,//", name);
                FILE *fp = popen(command, "r");
                char duration[20];
                fgets(duration, sizeof(duration), fp);
                if(atoi(duration)/60>10){
                    printf("time-limit   \e[0;32mpassed\e[0m\n");
                }
                else{
                    printf("time-limit   \e[0;31mfailed\e[0m\n");
                }
                pclose(fp);
            }
            else{
                printf("%s   \e[0;33mskipped\e[0m\n",hooks[i]);
            }
        }
    }
}

void add_hooks_to_stag_area(){
    char **hooks=(char **)malloc(1000*sizeof(char *));
    for(int i=0;i<10;i++){
        hooks[i]=(char *)malloc(1000);
    }
    char line[1000];
    int i=0;
    FILE *file=fopen(".sag\\hooks.txt","r");
    while(fgets(line,sizeof(line),file)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
        }
        strcpy(hooks[i],line);
        i++;
    }
    chdir(".sag\\staged_area");
    DIR *dir=opendir(".");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        chdir(entry->d_name);
        DIR *dir2=opendir(".");
        struct dirent *entry2;
        while((entry2=readdir(dir2))!=NULL){
            if(strcmp(entry2->d_name,".")==0||strcmp(entry2->d_name,"..")==0)
                continue;
            if(strcmp(entry2->d_name,"info.txt")!=0){
                add_hooks_to_files(fopen(entry2->d_name,"r"),entry2->d_name,i,hooks);
            }
        }
        chdir("..");
    }
    chdir("..");
    chdir(".."); 
}

bool in_head_of_branch_or_not(){
    char line[1000];
    int commit;
    FILE*file=fopen(".sag\\curr_branch.txt","r");
    fgets(line,sizeof(line),file);
    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
    file=fopen(".sag\\curr_commit.txt","r");
    fscanf(file,"%d",&commit);
    if(commit==finding_last_commit_of_a_branch(line)){
        return true;
    }
    return false;
}



int find_last_merg_id(FILE *file){
    int max=0;
    char line[1000];
    while(fgets(line,sizeof(line),file)!=NULL){
        char *str=strtok(line,"#");
        if(atoi(str)>max)
            max=atoi(str);
    }
    return max;
}


void check_diff_commit(char *commit1,char *commit2){
    char path1[1000];
    char path2[1000];
    sprintf(path1,".sag\\commits\\%s\\files.txt",commit1);
    sprintf(path2,".sag\\commits\\%s\\files.txt",commit2);
    files * first_commit=(files *)malloc(1000*sizeof(files));
    files * second_commit=(files *)malloc(1000*sizeof(files));
    FILE *file1=fopen(path1,"r");
    FILE*file2=fopen(path2,"r");
    char line[1000];
    int n=0;
    while(fgets(line,sizeof(line),file1)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(first_commit[n].address,strtok(line,"#"));
        strcpy(first_commit[n].commit_num,strtok(NULL,"#"));
        n++;
    }
    int m=0;
    while(fgets(line,sizeof(line),file2)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(second_commit[m].address,strtok(line,"#"));
        strcpy(second_commit[m].commit_num,strtok(NULL,"#"));
        m++;
    }
    int x=0;
    fclose(file1);
    fclose(file2);
    // chdir(di);
    for(int i=0;i<n;i++){
        bool exist=false;
        for(int j=0;j<m;j++){
            if(strcmp(first_commit[i].address,second_commit[j].address)==0){
                exist=true;
                x=j;
                break;
            }
        }
        if(exist==true){
            char dir_name[1000];
            dir_name[0]='\0';
            char name1[1000];
            char name2[1000];
            char copy1[1000];
            char copy2[1000];
            strcpy(copy1,first_commit[i].address);
            strcpy(copy2,first_commit[i].address);
            char *str=strtok(copy1,"\\");
            while(str!=NULL){
                strcpy(name1,str);
                str=strtok(NULL,"\\");
            }
            char *boz=strtok(copy2,"\\:.");
            while(boz!=NULL){
                strcat(dir_name,boz);
                boz=strtok(NULL,"\\:.");
            }
            char path1[1000];
            sprintf(path1,".sag\\files\\%s\\%s\\%s",dir_name,first_commit[i].commit_num,name1);
            FILE *file1=fopen(path1,"r");
            char path2[1000];
            sprintf(path2,".sag\\files\\%s\\%s\\%s",dir_name,second_commit[x].commit_num,name1);
            diff_whithout_line(path1,path2,first_commit[i].address,first_commit[i].address);
            printf("\n");
            // f=fopen("files.txt","a");
            // fprintf(f,"%s#%s\n",first_commit[i].address,first_commit[i].commit_num);
            // num++;
            // fclose(f);
        }
        else{
            char name1[1000];
            char copy1[1000];
            strcpy(copy1,first_commit[i].address);
            char *str=strtok(copy1,"\\");
            while(str!=NULL){
                strcpy(name1,str);
                str=strtok(NULL,"\\");
            }
            printf("%s IS NOT IN BOTH COMMITS\n\n",name1);
        }
    }
    for(int i=0;i<m;i++){
        bool exist=false;
        for(int j=0;j<n;j++){
            if(strcmp(first_commit[j].address,second_commit[i].address)==0){
                exist=true;
                x=j;
                break;
            }
        }
        if(exist==false){
            char name1[1000];
            char copy1[1000];
            strcpy(copy1,second_commit[i].address);
            char *str=strtok(copy1,"\\");
            while(str!=NULL){
                strcpy(name1,str);
                str=strtok(NULL,"\\");
            }
            printf("%s IS NOT IN BOTH COMMITS\n\n",name1);
        }
    }

}

void add_main_branch_to_secondary_branch_files(char *main_branch,char *secondary_branch){
    char path[1000];
    sprintf(path,".sag\\files");
    DIR*dir=opendir(path);
    struct dirent *entry;
    char line[1000];
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        sprintf(path,".sag\\files\\%s",entry->d_name);
        DIR*dir2=opendir(path);
        struct dirent *entry1;
        while((entry1=readdir(dir2))!=NULL){
            if(strcmp(entry1->d_name,".")==0||strcmp(entry1->d_name,"..")==0)
                continue;
            sprintf(path,".sag\\files\\%s\\%s\\info.txt",entry->d_name,entry1->d_name);
            FILE *file=fopen(path,"r");
            bool b1=false,b2=false;
            fgets(line,sizeof(line),file);
            if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0';
            }
            char line_copy[1000];
            strcpy(line_copy,line);
            char new_branch[1000];
            new_branch[0]='\0';
            char *str=strtok(line_copy,"/");
            int x=0;
            while(str!=NULL){
                if(strcmp(str,secondary_branch)==0){
                    b2=true;
                }
                else{
                    if(x!=0)
                        strcat(new_branch,"/");
                    strcat(new_branch,str);

                }
                if(strcmp(str,main_branch)==0){
                    b1=true;
                }
                x++;
                str=strtok(NULL,"/");
            }
            if(b2){
                if(b1){
                    char path2[1000];
                    sprintf(path2,".sag\\files\\%s\\%s\\info1.txt",entry->d_name,entry1->d_name);
                    FILE *file2=fopen(path2,"w");
                    fprintf(file2,"%s\n",new_branch);
                    fgets(line,sizeof(line),file);
                    fprintf(file2,"%s",line);
                    fgets(line,sizeof(line),file);
                    fprintf(file2,"%s",line);
                    fclose(file);
                    fclose(file2);
                    remove(path);
                    rename(path2,path);
                }
                else{
                    char path2[1000];
                    sprintf(path2,".sag\\files\\%s\\%s\\info1.txt",entry->d_name,entry1->d_name);
                    FILE *file2=fopen(path2,"w");
                    if(new_branch[0]!='\0'){
                        strcat(new_branch,"/");
                    }
                    strcat(new_branch,main_branch);
                    fprintf(file2,"%s\n",new_branch);
                    fgets(line,sizeof(line),file);
                    fprintf(file2,"%s",line);
                    fgets(line,sizeof(line),file);
                    fprintf(file2,"%s",line);
                    fclose(file);
                    fclose(file2);
                    remove(path);
                    rename(path2,path);
                }
            }
            else{
                continue;
            }
        }        
    }
}


void add_main_branch_to_secondary_branch_commits(char *main_branch,char *secondary_branch){
    char path[1000];
    sprintf(path,".sag\\commits");
    DIR*dir=opendir(path);
    struct dirent *entry;
    char line[1000];
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        char path2[1000];
        sprintf(path,".sag\\commits\\%s\\branch.txt",entry->d_name);
        FILE *file=fopen(path,"r");
        bool b1=false,b2=false;
        char f[1000];
        f[0]='\0';
        while(fgets(line,sizeof(line),file)!=NULL){
            if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = '\0';
            }
            if(strcmp(line,secondary_branch)==0){
                b2=true;
            }
            else{
                strcat(f,line);
                strcat(f,"\n");
            }
            if(strcmp(line,main_branch)==0){
                b1=true;
            }
        }
        if(b2){
            if(b1){
                file=fopen(path,"w");
                fprintf(file,"%s",f);
                fclose(file);
            }
            else{
                file=fopen(path,"w");
                strcat(f,main_branch);
                strcat(f,"\n");
                fprintf(file,"%s",f);
                fclose(file);
            }
        }
        else{
            continue;
        }
        
    }

}

void merge_branches(int HEAD_main,int HEAD_secondary,int last_commit_ID,char *main_branch,char *secondary_branch,int *arr,int nums){
    //char *person="asasasas";
    char path[1000];
    FILE *a=fopen(".sag\\merge_IDs.txt","a");
    // fprintf(file,"%s#%s#%s\n",last_commit_ID,main_branch,secondary_branch);
    fprintf(a,"%d#%s#%s\n",last_commit_ID,main_branch,secondary_branch);
    char person[1000];
    strcpy(person,find_the_last_person());
    char email[1000];
    strcpy(email,find_the_last_person_email());
    char di[1000];
    sprintf(di,".sag\\commits\\%d",last_commit_ID+1);
    mkdir(di);
    chdir(di);
    FILE*f=fopen("files.txt","w");
    chdir("..");
    chdir("..");
    chdir("..");
    sprintf(path,".sag\\commits\\%d\\files.txt",HEAD_main);
    FILE * file1=fopen(path,"r");
    sprintf(path,".sag\\commits\\%d\\files.txt",HEAD_secondary);
    FILE * file2=fopen(path,"r");
    char line[1000];
    int t=0;
    while(fgets(line,sizeof(line),file1)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        fprintf(f,"%s\n",line);
        t++;
    }
    int n=0;
    while(fgets(line,sizeof(line),file2)!=NULL){
        bool x=true;
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        for(int i=0;i<nums;i++){
            if(*(arr+i)==n){
                x=false;
                break;
            }
        }
        if(x){
            t++;
            fprintf(f,"%s\n",line);
        }
        n++;
    }
    chdir(di);
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
    f=fopen("message.txt","w");
    fprintf(f,"message :merge %s to %s",secondary_branch,main_branch);
    f=fopen("branch.txt","w");
    fprintf(f,"%s",main_branch);
    f=fopen("person.txt","w");
    fprintf(f,"%s<%s>",person,email);
    f=fopen("time.txt","w");
    fprintf(f,"%s",my_time);
    f=fopen("file_nums.txt","w");
    fprintf(f,"file nums :%d",t);
    fclose(f);
    chdir("..");
    chdir("..");
    chdir("..");
    add_main_branch_to_secondary_branch_commits(main_branch,secondary_branch);
    add_main_branch_to_secondary_branch_files(main_branch,secondary_branch);
}

int merge_branches_check(char *main_branch,char *secondary_branch){
    int HEAD_main=finding_last_commit_of_a_branch(main_branch);
    int HEAD_secondary=finding_last_commit_of_a_branch(secondary_branch);
    int last_commit_ID=finding_last_commit_folder(opendir(".sag\\commits"));
    int u[1000];
    files * first_commit=(files *)malloc(1000*sizeof(files));
    files * second_commit=(files *)malloc(1000*sizeof(files));
    char path[1000];
    sprintf(path,".sag\\commits\\%d\\files.txt",HEAD_main);
    FILE * file1=fopen(path,"r");
    sprintf(path,".sag\\commits\\%d\\files.txt",HEAD_secondary);
    FILE * file2=fopen(path,"r");
    char line[1000];
    int n=0;
    while(fgets(line,sizeof(line),file1)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(first_commit[n].address,strtok(line,"#"));
        strcpy(first_commit[n].commit_num,strtok(NULL,"#"));
        n++;
    }
    int m=0;
    int x=0;
    while(fgets(line,sizeof(line),file2)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(second_commit[m].address,strtok(line,"#"));
        strcpy(second_commit[m].commit_num,strtok(NULL,"#"));
        m++;
    }
    int num=0;
    fclose(file1);
    fclose(file2);
    bool ex=true;
    int khar=0;
    for(int i=0;i<n;i++){
        bool exist=false;
        for(int j=0;j<m;j++){
            if(strcmp(first_commit[i].address,second_commit[j].address)==0){
                exist=true;
                x=j;
                break;
            }
        }
        if(exist==true){
            char dir_name[1000];
            dir_name[0]='\0';
            char name1[1000];
            char name2[1000];
            char copy1[1000];
            char copy2[1000];
            strcpy(copy1,first_commit[i].address);
            strcpy(copy2,first_commit[i].address);
            char *str=strtok(copy1,"\\");
            while(str!=NULL){
                strcpy(name1,str);
                str=strtok(NULL,"\\");
            }
            char *boz=strtok(copy2,"\\:.");
            while(boz!=NULL){
                strcat(dir_name,boz);
                boz=strtok(NULL,"\\:.");
            }
            char path1[1000];
            sprintf(path1,".sag\\files\\%s\\%s\\%s",dir_name,first_commit[i].commit_num,name1);
            FILE *file1=fopen(path1,"r");
            char path2[1000];
            sprintf(path2,".sag\\files\\%s\\%s\\%s",dir_name,second_commit[x].commit_num,name1);
            if(diff_whithout_line(path1,path2,first_commit[i].address,first_commit[i].address)){
                
                ex=false;
                printf("\n");
                
            }
            else{
                u[khar]=x;
                khar++;
            }
            // f=fopen("files.txt","a");
            // fprintf(f,"%s#%s\n",first_commit[i].address,first_commit[i].commit_num);
            // num++;
            // fclose(f);
        }
    }
    if(ex){
        merge_branches(HEAD_main,HEAD_secondary,last_commit_ID,main_branch,secondary_branch,u,khar);
        return 1;
    }
    return 0;
        // for(int i=0;i<m;i++){
    //     bool exist=false;
    //     for(int j=0;j<n;j++){
    //         if(strcmp(second_commit[i].address,first_commit[j].address)==0){
    //             exist=true;
    //             break;
    //         }
    //     }
    //     if(exist==false){
    //         f=fopen("files.txt","a");
    //         fprintf(f,"%s#%s\n",second_commit[i].address,second_commit[i].commit_num);
    //         num++;
    //         fclose(f);
    //     }
    // }
    // chdir("..");
    // chdir("..");
    // chdir("..");

    
}

// void print_diff(char *line1,char *line2){
//     char first_line[1000][1000];
//     char second_line[1000][1000];
//     char line1_copy[1000];
//     char line2_copy[1000];
//     strcpy(line1_copy,line1);
//     strcpy(line2_copy,line2);
//     int i=0;
//     char *str=strtok(line1_copy," ");
//     while(str!=NULL){
//         strcpy(first_line[i],str);
//         i++;
//         str=strtok(NULL," ");
//     }
//     int j=0;
//     char *str=strtok(line2_copy," ");
//     while(str!=NULL){
//         strcpy(second_line[j],str);
//         j++;
//         str=strtok(NULL," ");
//     }

// }

bool comparing_head_and_curr_commit(){
    FILE *file=fopen(".sag\\curr_commit.txt","r"); 
    FILE *file2=fopen(".sag\\curr_branch.txt","r");
    char curr_branch[1000]; 
    int curr_commit;
    fgets(curr_branch,sizeof(curr_branch),file2);
    if (strlen(curr_branch) > 0 && curr_branch[strlen(curr_branch) - 1] == '\n') {
    curr_branch[strlen(curr_branch) - 1] = '\0';
    }
    fscanf(file,"%d",curr_commit);

    if(curr_commit==finding_last_commit_of_a_branch(curr_branch)){
        return true;
    }
    return false;
}

int find_since_log_commit_ID(char * given_time,int max){
    chdir(".sag\\commits");
    char num[1000];
    int ID;
    int x=100000;
    for(int i=1;i<=max;i++){
        sprintf(num,"%d",i);
        chdir(num);
        FILE *file=fopen("time.txt","r");
        char line[1000];
        fgets(line,sizeof(line),file);
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
        }
        if(strcmp(line,given_time)>=0){
            x=i;
            chdir("..");
            break;
        }
        chdir("..");
    }
    chdir("..");
    chdir("..");
    return x;
}

int find_before_log_commit_ID(char * given_time,int max){
    chdir(".sag\\commits");
    char num[1000];
    int ID;
    int x=-10;
    for(int i=1;i<=max;i++){
        sprintf(num,"%d",i);
        chdir(num);
        FILE *file=fopen("time.txt","r");
        char line[1000];
        fgets(line,sizeof(line),file);
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
        }
        if(strcmp(line,given_time)>0){
            x=i;
            chdir("..");
            break;
        }
        chdir("..");
    }
    chdir("..");
    chdir("..");
    if(x<0){
        return max+1;
    }
    return x;
}

int number_of_files_and_folders(DIR *dir){
    int num=0;
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        num++;
    }
    return num;
}


void add_the_new_branch_to_commits(char *branch,int commit_num){
    char path[1000];
    sprintf(path,".sag\\commits\\%d\\branch.txt",commit_num);
    FILE *file=fopen(path,"a");
    fprintf(file,"%s\n",branch);
}
void add_the_new_branch_to_files(char *branch,int commit_num){
    char path[1000];
    sprintf(path,".sag\\commits\\%d\\files.txt",commit_num);
    FILE *file=fopen(path,"r");
    while(fgets(path,sizeof(path),file)!=NULL){
        if (strlen(path) > 0 && path[strlen(path) - 1] == '\n') {
        path[strlen(path) - 1] = '\0';
        }
        char dir_name[1000];
        dir_name[0]='\0';
        char *address=strtok(path,"#");
        char *ID=strtok(NULL,"#");
        char *str=strtok(address,"\\:.");
        while(str!=NULL){
            strcat(dir_name,str);
            str=strtok(NULL,"\\:.");
        }
        char f1[1000];
        char f2[1000];
        sprintf(f1,".sag\\files\\%s\\%s\\info.txt",dir_name,ID);
        sprintf(f2,".sag\\files\\%s\\%s\\info1.txt",dir_name,ID);
        FILE *file1=fopen(f1,"r");
        FILE *file2=fopen(f2,"w");
        char info[1000];
        fgets(info,sizeof(info),file1);
        if (strlen(info) > 0 && info[strlen(info) - 1] == '\n') {
        info[strlen(info) - 1] = '\0';
        }
        char x[1000];
        sprintf(x,"/%s\n",branch);
        strcat(info,x);
        fputs(info,file2);
        fgets(info,sizeof(info),file1);
        fputs(info,file2);
        fgets(info,sizeof(info),file1);
        fputs(info,file2);
        fclose(file1);
        remove(f1);
        fclose(file2);
        rename(f2,f1);
    }
}
void show_tag(char *name){
    char x[1000];
    chdir(".sag\\tags");
    chdir(name);
    printf("tag name : %s\n",name);
    FILE *file=fopen("commit_ID.txt","r");
    fgets(x,sizeof(x),file);
    if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
    }
    printf("%s\n",x);
    fclose(file);
    file=fopen("author.txt","r");
    fgets(x,sizeof(x),file);
    if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
    }
    printf("%s\n",x);
    fclose(file);
    file=fopen("time.txt","r");
    fgets(x,sizeof(x),file);
    if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
    }
    printf("%s\n",x);
    fclose(file);
    file=fopen("message.txt","r");
    if(file!=NULL){
        fgets(x,sizeof(x),file);
        if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
        x[strlen(x) - 1] = '\0';
        }
        printf("%s\n",x);
        fclose(file);
    }
    chdir("..");
    chdir("..");
    chdir("..");
}

void print_tags(){
    char **tags=(char**)malloc(1000*sizeof(char *));
    for(int i=0;i<100;i++){
        tags[i]=(char*)malloc(1000*sizeof(char));
    }
    int num=0;
    DIR *dir=opendir(".sag\\tags");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        strcpy(tags[num],entry->d_name);
        num++;
    }
    for(int i=0;i<num-1;i++){
        for(int j=0;j<num-i-1;j++){
            if(strcmp(tags[j],tags[j+1])>0){
                char *x=tags[j];
                tags[j]=tags[j+1];
                tags[j+1]=x;
            }
        }
    }
    for(int i=0;i<num;i++){
        printf("%s\n",tags[i]);
    }
}

bool tag_existance(char *name){
    DIR *dir=opendir(".sag\\tags");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
            continue;
        if(strcmp(name,entry->d_name)==0){
            return true;
        }
    }
    return false;
}

void replace(char *name,char*message,int num,char *commit_num){
    char author[1000];
    strcpy(author,find_the_last_person());
    char email[1000];
    strcpy(email,find_the_last_person());
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
    char system_command[1000];
    sprintf(system_command,"rmdir /s .sag\\tags\\%s",name);
    system(system_command);
    sprintf(system_command,".sag\\tags\\%s",name);
    mkdir(system_command);
    chdir(system_command);
    if(num==1){
        FILE *file=fopen("message.txt","w");
        fprintf(file,"message : %s",message);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("commit_ID.txt","w");
        fprintf(file,"commit ID : %s",commit_num);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s<%s>",author,email);
        file=fopen("time.txt","w");
        fprintf(file,"time : %s",my_time);
    }
    else if(num==3){
        FILE *file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("commit_ID.txt","w");
        fprintf(file,"commit ID : %s",commit_num);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("time.txt","w");
        fprintf(file,"time : %s",my_time);
    }
    chdir("..");
    chdir("..");
    chdir("..");
}

void make(char *name,char*message,int num,char *commit_num){
    char author[1000];
    strcpy(author,find_the_last_person());
    char email[1000];
    strcpy(email,find_the_last_person());
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
    char system_command[1000];
    sprintf(system_command,".sag\\tags\\%s",name);
    mkdir(system_command);
    chdir(system_command);
    if(num==1){
        FILE *file=fopen("message.txt","w");
        fprintf(file,"message : %s",message);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("commit_ID.txt","w");
        fprintf(file,"commit ID : %s",commit_num);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s<%s>",author,email);
        file=fopen("time.txt","w");
        fprintf(file,"time : %s",my_time);
    }
    else if(num==3){
        FILE *file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("commit_ID.txt","w");
        fprintf(file,"commit ID : %s",commit_num);
        file=fopen("author.txt","w");
        fprintf(file,"author : %s",author);
        file=fopen("time.txt","w");
        fprintf(file,"time : %s",ctime(&curr));
    }
    chdir("..");
    chdir("..");
    chdir("..");

}

int create_tag(char **argv,int argc){
   
    FILE *file=fopen(".sag\\curr_commit.txt","r");
    char curr[1000];
    fgets(curr,sizeof(curr),file);

    if(argc==4){
        if(tag_existance(argv[3])){
            printf("CREATED BEFORE"); 
        }
        else{
            make(argv[3],"no",3,curr);
        }
    }
    else if(argc==5){
        if(tag_existance(argv[3])){
            replace(argv[3],"no",3,curr);
        }
        else{
            make(argv[3],"no",3,curr);
        }
    }
    else if(argc==6){
        if(strcmp(argv[4],"-m")==0){
            if(tag_existance(argv[3])){
                printf("CREATED BEFORE");   
            }
            else{
                make(argv[3],argv[5],1,curr);
            }
        }
        else{
            if(tag_existance(argv[3])){
                printf("CREATED BEFORE"); 
            }
            else{
                make(argv[3],"no",3,argv[5]);
            }
        }

    }
    else if(argc==7){
        if(strcmp(argv[4],"-m")==0){
            if(tag_existance(argv[3])){
                replace(argv[3],argv[5],1,curr);  
            }
            else{
                make(argv[3],argv[5],1,curr);
            }
        }
        else{
            if(tag_existance(argv[3])){
                replace(argv[3],"no",3,argv[5]);
            }
            else{
                make(argv[3],"no",3,argv[5]);
            }
        }   
    }
    else if(argc==8){
        if(tag_existance(argv[3])){
            printf("CREATED BEFORE");
        }
        else{
            make(argv[3],argv[5],1,argv[7]);
        }
    }
    else if(argc==9){
        if(tag_existance(argv[3])){
            replace(argv[3],argv[5],1,argv[7]);
        }
        else{
            make(argv[3],argv[5],1,argv[7]);
        }
    }




    // if(strcmp(argv[argc-1],"-f")==0){
    //     if(strcmp(argv[4],"-m")==0){
    //         if(argc==9){
    //             if(tag_existance(argv[3])){
    //                 replace(argv[3],argv[5],1,argv[7]);
    //             }
    //             else{
    //                 make(argv[3],argv[5],1,argv[7]);
    //             }
    //         }
    //         else{
    //             if(tag_existance(argv[3])){
    //                 replace(argv[3],argv[5],1,curr);
    //             }
    //             else{
    //                 make(argv[3],argv[5],1,curr);
    //             }
    //         }
    //     }
    //     else{
    //         if(strcmp(argv[4],"-c")==0){
    //             if(tag_existance(argv[3])){
    //                 replace(argv[3],"no",3,argv[5]);
    //             }
    //             else{
    //                 make(argv[3],"no",3,argv[5]);
    //             }
    //         }
    //         else{
    //             if(tag_existance(argv[3])){
    //                 replace(argv[3],"no",3,curr);
    //             }
    //             else{
    //                 make(argv[3],"no",3,curr);
    //             }
    //         }
    //     }
    // }
    // else{
    //     if(strcmp(argv[4],"-m")==0){
    //         if(strcmp(argv[6],"-c")==0){
    //             if(tag_existance(argv[3])){
    //                 printf("CREATED BEFORE");
    //             }
    //             else{
    //                 make(argv[3],argv[5],1,argv[7]);
    //             }
    //         }
    //         else{
    //             if(tag_existance(argv[3])){
    //                 printf("CREATED BEFORE");   
    //             }
    //             else{
    //                 make(argv[3],argv[5],1,curr);
    //             }
    //         }
    //     }
    //     else{
    //         if(strcmp(argv[4],"-c")==0){
    //             if(tag_existance(argv[3])){
    //                 printf("CREATED BEFORE"); 
    //             }
    //             else{
    //                 make(argv[3],"no",3,argv[5]);
    //             }
    //         }
    //         else{
    //             if(tag_existance(argv[3])){
    //                 printf("CREATED BEFORE"); 
    //             }
    //             else{
    //                 make(argv[3],"no",3,curr);
    //             }
    //         }
    //     }
    // }
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
    closedir(dir);
    return max;
}

int nth_commit_of_a_branch(char *branch , int max,int n){
    char line[1000];
    chdir(".sag\\commits");
    char num[100];
    int x=max;
    for(int i=max;n>0;i--){
        sprintf(num,"%d",i);
        chdir(num);
        FILE *file=fopen("branch.txt","r");
        while(fgets(line,sizeof(line),file)){
            if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
            }
            if(strcmp(line,branch)==0){
                n--;
                break;
            }

        }
        chdir("..");
        x=i;
    }
    chdir("..");
    chdir("..");
    return x;
}

void delete_all_files(){
    DIR *dir=opendir(".");
    struct stat info;
    struct dirent *entry;
    char system_command[1000];
    while((entry=readdir(dir))!=NULL){
        stat(entry->d_name,&info);
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(S_ISDIR(info.st_mode)){
            sprintf(system_command,"rmdir /s /q %s",entry->d_name);
            system(system_command);
        }
        else{
           sprintf(system_command,"del %s",entry->d_name);
            system(system_command); 
        }
        
        
    }
    
}
void change_project_to_the_commit_id(int id){
    char path[1000];
    char file_path[1000];
    char file_name[1000];
    char line[1000];
    char address_copy[1000];
    sprintf(path,".sag\\commits\\%d\\files.txt",id);
    FILE *file=fopen(path,"r");
    while(fgets(line,sizeof(line),file)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        char dir_name[1000];
        dir_name[0]='\0';
        char *address=strtok(line,"#");
        char *file_commit_num=strtok(NULL,"#");
        sprintf(address_copy,"%s",address);
        char *str=strtok(address_copy,"\\:.");
        while(str!=NULL){
            strcat(dir_name,str);
            str=strtok(NULL,"\\:.");
        }
        sprintf(file_path,".sag\\files\\%s\\%s",dir_name,file_commit_num);
        DIR *dir=opendir(file_path);
        struct dirent *entry;
        while((entry=readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
                continue;
            if(strcmp(entry->d_name,"info.txt")!=0){
                sprintf(file_name,"%s",entry->d_name);
            }
            
        }
        sprintf(file_path,".sag\\files\\%s\\%s\\%s",dir_name,file_commit_num,file_name);
        char *dir_address_proj=dirname(address);
        char system_command[1000];
        sprintf(system_command,"mkdir %s",dir_address_proj);
        system(system_command);
        sprintf(system_command,"copy %s %s",file_path,dir_address_proj);
        system(system_command);
    }
}

void checkout_with_num(char *x,int test){
    delete_all_files();
                char file_path[1000];
                char line[1000];
                sprintf(file_path,".sag\\commits\\%s\\branch.txt",x);
                FILE *file=fopen(file_path,"r");
                fgets(line,sizeof(line),file);
                fclose(file);
                if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                }
                // printf("%s",line);
                // if(test==1){
                //     file=fopen(".sag\\curr_branch.txt","w");
                //     fprintf(file,"%s",line);
                // }
                file=fopen(".sag\\curr_commit.txt","w");
                fprintf(file,"%s",x);
                change_project_to_the_commit_id(atoi(x));

}

void checkout_with_branch(char * argv){
int last_barnch_commit=finding_last_commit_of_a_branch(argv);
                    delete_all_files();
                    FILE *file=fopen(".sag\\curr_branch.txt","w");
                    fprintf(file,"%s",argv);
                    file=fopen(".sag\\curr_commit.txt","w");
                    fprintf(file,"%d",last_barnch_commit);
                    change_project_to_the_commit_id(last_barnch_commit);
                

}
void checkout_with_HEAD(){
char line[100];
                FILE *file=fopen(".sag\\curr_branch.txt","r");
                fgets(line,sizeof(line),file);
                int last_barnch_commit=finding_last_commit_of_a_branch(line);
                    delete_all_files();
                    file=fopen(".sag\\curr_commit.txt","w");
                    fprintf(file,"%d",last_barnch_commit);
                    change_project_to_the_commit_id(last_barnch_commit);
                

}
void checkout_with_HEAD_n(char *n){
                delete_all_files();
                char line[100];
                FILE *file=fopen(".sag\\curr_branch.txt","r");
                fgets(line,sizeof(line),file);
                int last_barnch_commit=finding_last_commit_of_a_branch(line);
                    int nth_branch=nth_commit_of_a_branch(line,last_barnch_commit,atoi(n));
                    printf("%d",nth_branch);
                    file=fopen(".sag\\curr_commit.txt","w");
                    fprintf(file,"%d",nth_branch);
                    change_project_to_the_commit_id(nth_branch);
                

}
void copy_commit(char *n){
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
    char system_command[1000];
    sprintf(system_command,"xcopy .sag\\commits\\%s .sag\\commits\\%d",n,finding_last_commit_folder(opendir(".sag\\commits"))+1);
    FILE *file=fopen(".sag\\curr_commit.txt","w");
    fprintf(file,"%d",finding_last_commit_folder(opendir(".sag\\commits")));
    system(system_command);
    sprintf(system_command,".sag\\commits\\%d\\time.txt.txt",finding_last_commit_folder(opendir(".sag\\commits")));
    file=fopen(system_command,"w");
    fprintf(file,"%s",my_time);

}

void copy_commit_with_message(char *n,char *message){
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
    char system_command[1000];
    int x=finding_last_commit_folder(opendir(".sag\\commits"));
    sprintf(system_command,"xcopy .sag\\commits\\%s .sag\\commits\\%d",n,x+1);
    system(system_command);
    FILE *file=fopen(".sag\\curr_commit.txt","w");
    fprintf(file,"%d",x+1);
    sprintf(system_command,".sag\\commits\\%d\\message.txt",x+1);
    file=fopen(system_command,"w");
    fprintf(file,"message :%s",message);
    sprintf(system_command,".sag\\commits\\%d\\time.txt",x+1);
    file=fopen(system_command,"w");
    fprintf(file,"%s",my_time);
}

void revert_with_HEAD_n(char *n){
                char line[100];
                FILE *file=fopen(".sag\\curr_branch.txt","r");
                fgets(line,sizeof(line),file);
                int last_barnch_commit=finding_last_commit_of_a_branch(line);
                    int nth_branch=nth_commit_of_a_branch(line,last_barnch_commit,atoi(n));
                    char x[1000];
                    sprintf(x,"%d",nth_branch);
                    copy_commit(x);
                

}
void revert_with_HEAD_n_message(char *n,char *message){
                char line[100];
                FILE *file=fopen(".sag\\curr_branch.txt","r");
                fgets(line,sizeof(line),file);
                int last_barnch_commit=finding_last_commit_of_a_branch(line);
                
                    int nth_branch=nth_commit_of_a_branch(line,last_barnch_commit,atoi(n));
                    // file=fopen(".sag\\curr_commit.txt","w");
                    // fprintf(file,"%d",nth_branch);
                    char x[1000];
                    sprintf(x,"%d",nth_branch);
                    copy_commit_with_message(x,message);
                

}


bool is_it_branch(char* name){
    char name_copy[1000];
    strcpy(name_copy,name);
    strcat(name_copy,".txt");
    DIR *dir=opendir(".sag\\all_branches");
    struct dirent *entry;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        if(strcmp(name_copy,entry->d_name)==0){
            return true;
        }
    }
    return false;
}
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
                    print_log(i,"a",0);
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
                print_log(i,"a",0);
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
                print_log(i,"a",0);
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
            while(fgets(x,sizeof(x),file)!=NULL){
                if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
                x[strlen(x) - 1] = '\0';
                }
                if(strcmp(branch,x)==0){
                    print_log(i,branch,1);
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

void print_log(int i,char *branch,int test){
        char x[1000];
    printf("ID : %d\n",i);
            FILE *file=fopen("time.txt","r");
            fgets(x,sizeof(x),file);
            if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
            x[strlen(x) - 1] = '\0';
            }
            printf("time :%s\n",x);
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
            if(test==1){
                printf("branch : %s\n",branch);
            }
            else{
                printf("branch(s) : ");
                file=fopen("branch.txt","r");
                while(fgets(x,sizeof(x),file)!=NULL){
                    if (strlen(x) > 0 && x[strlen(x) - 1] == '\n') {
                    x[strlen(x) - 1] = '\0';
                    }
                    printf("%s      ",x);
                }
                printf("\n");  
            }
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
            print_log(i,"a",0);
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



char * find_the_last_person(){
    char line[100];
    char gl_p[1000];
    gl_p[0]='\0';
    char lo_p[1000];
    lo_p[0]='\0';
    FILE *file1=fopen("C:\\Users\\Reza\\git\\global.txt","r");
    if(file1!=NULL){
        while(fgets(line,sizeof(line),file1)!=NULL){
            if(strncmp(line,"user.name",9)==0){
                sprintf(gl_p,"%s",line);
            }
        }
    }
    FILE *file=fopen(".sag\\local.txt","r");
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
    if(file==NULL){
        return p1;
    }
    if(file1==NULL){
        return p2;
    }
    if(strcmp(boz,str)>0){
        return p2;
    }
    else{
        return p1;
    }
}

char * find_the_last_person_email(){
    char line[100];
    char gl_p[1000];
    gl_p[0]='\0';
    char lo_p[1000];
    lo_p[0]='\0';
    FILE *file1=fopen("C:\\Users\\Reza\\git\\global.txt","r");
    if(file1!=NULL){
        while(fgets(line,sizeof(line),file1)!=NULL){
            if(strncmp(line,"user.email",9)==0){
                sprintf(gl_p,"%s",line);
            }
        }
    }
    FILE *file=fopen(".sag\\local.txt","r");
    if(file!=NULL){
        while(fgets(line,sizeof(line),file)!=NULL){
            if(strncmp(line,"user.email",9)==0){
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
    if(file==NULL){
        return p1;
    }
    if(file1==NULL){
        return p2;
    }
    if(strcmp(boz,str)>0){
        return p2;
    }
    else{
        return p1;
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
    time_t curr;
    time(&curr);
    struct tm *temp;
    temp=localtime(&curr);
    char my_time[1000];
    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
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
    fprintf(file,"%s\n",branch);
    fclose(file);
    if (strlen(branch) > 0 && branch[strlen(branch) - 1] == '\n') {
        branch[strlen(branch) - 1] = '\0';
    }
    file=fopen(mes,"w");
    fprintf(file,"message :%s",message);
    fclose(file);
    file=fopen(person,"w");
    fprintf(stdout, "commit successfully with commit ID %s \ntime : %s", tmp,my_time);
    fprintf(file,"person :%s<%s>",find_the_last_person(),find_the_last_person_email());
    fclose(file);
    file=fopen(time1,"w");
    fprintf(file,"%s",my_time);
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
                    char *str=strtok(b,"/");
                    while(str!=NULL){
                        if(strcmp(str,branch)==0){
                        exist=true;
                        z=1;
                        break;
                        }
                        str=strtok(NULL,"/");
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

int run_commit(char * const argv) {
    char message[1000];
    strcpy(message, argv);
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
    chdir(".sag\\commits");
    DIR *dir=opendir(".");
    struct dirent *entry;
    int max=-1;
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
            continue;
        chdir(entry->d_name);
        FILE *file=fopen("branch.txt","r");
        char b[100];
        while(fgets(b,sizeof(b),file)!=NULL){
            if (strlen(b) > 0 && b[strlen(b) - 1] == '\n') {
            b[strlen(b) - 1] = '\0';
            }
            if(strcmp(branch,b)==0){
                max=atoi(entry->d_name);
                break;
            }
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
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
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
                printf("%d %s\n",x,line);
            }
            else{
                printf("%s\n",line);
            }
        }
        x++;
    }
}

bool diff_whithout_line(char * absolute_adress1,char *absolute_adress2,char *print_add1,char *print_add2){
    char name1[1000];
    char name2[1000];
    char copy1[1000];
    char copy2[1000];
    strcpy(copy2,absolute_adress2);
    strcpy(copy1,absolute_adress1);
    FILE *file1=fopen(absolute_adress1,"r");
    FILE *file2=fopen(absolute_adress2,"r");
    char *str=strtok(copy1,"\\");
    while(str!=NULL){
        strcpy(name1,str);
        str=strtok(NULL,"\\");
    }
    char *boz=strtok(copy2,"\\");
    while(boz!=NULL){
        strcpy(name2,boz);
        boz=strtok(NULL,"\\");
    }
    int begin1=1;
    int begin2=1;
    char line1[1000];
    char line2[1000];
    bool exist=false;
    void *l1=NULL;
    void *l2=NULL;
    l1=fgets(line1, sizeof(line1), file1);
    l2=fgets(line2, sizeof(line2), file2);
    while (l1!= NULL||l2!= NULL) {
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
                    break;
                }
                begin1++; 
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
                    break;
                }
                begin2++; 
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
        if(l1==NULL&&l2==NULL){
            break;
        }
        if(l2==NULL){
            exist=true;
            printf("<<<%s>>>\n%s-%d\n\e[0;31m%s\e[0m\n<<<%s>>>\n%s-_\n\e[0;32mEMPTY\e[0m\n",print_add1,name1,begin1,line1,print_add2,name2);
        }
        else if(l1==NULL){
            exist=true;
            printf("<<<%s>>>\n%s-_\n\e[0;31mEMPTY\e[0m\n<<<%s>>>\n%s-%d\n\e[0;32m%s\e[0m\n",print_add1,name1,print_add2,name2,begin2,line2);
        }
        else if(strcmp(line1,line2)!=0){
            exist=true;
            printf("<<<%s>>>\n%s-%d\n\e[0;31m%s\e[0m\n<<<%s>>>\n%s-%d\n\e[0;32m%s\e[0m\n",print_add1,name1,begin1,line1,print_add2,name2,begin2,line2);
        }
        begin1++;
        begin2++;
        l1=fgets(line1, sizeof(line1), file1);
        l2=fgets(line2, sizeof(line2), file2);
    }
    return exist;
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
                x++;
                if(x+1==begin1){
                    goto a;
                }
            }
        }   
    }
    a:
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
                x++;
                if(x+1==begin2){
                    goto b;
                }
            }
        }
    }
    b:
    void *l1=NULL;
    void *l2=NULL;
    l1=fgets(line1, sizeof(line1), file1);
    l2=fgets(line2, sizeof(line2), file2);
    while (l1!= NULL||l2!= NULL){
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
                    break;
                }
                begin1++; 
                if(begin1==end1){
                    break;
                }
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
                    break;
                }
                begin2++; 
                if(begin2==end2){
                    break;
                }
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
        if(l1==NULL&&l2==NULL){
            return;
        }
        if(begin1==end1&&begin2==end2){
            return;
        }
        if(l2==NULL){
            printf("<<<%s>>>\n%s-%d\n\e[0;31m%s\e[0m\n<<<%s>>>\n%s-_\n\e[0;32mEMPTY\e[0m\n",absolute_adress1,name1,begin1,line1,absolute_adress2,name2);
        }
        else if(end2==begin2){
            printf("<<<%s>>>\n%s-%d\n\e[0;31m%s\e[0m\n<<<%s>>>\n%s-_\n\e[0;32mEMPTY\e[0m\n",absolute_adress1,name1,begin1,line1,absolute_adress2,name2);
        }
        else if(l1==NULL){
            printf("<<<%s>>>\n%s-_\n\e[0;31mEMPTY\e[0m\n<<<%s>>>\n%s-%d\n\e[0;32m%s\e[0m\n",absolute_adress1,name1,absolute_adress2,name2,begin2,line2);
        }
        else if(begin1==end1){
            printf("<<<%s>>>\n%s-_\n\e[0;31mEMPTY\e[0m\n<<<%s>>>\n%s-%d\n\e[0;32m%s\e[0m\n",absolute_adress1,name1,absolute_adress2,name2,begin2,line2);
        }
        else if(strcmp(line1,line2)!=0){
            printf("<<<%s>>>\n%s-%d\n\e[0;31m%s\e[0m\n<<<%s>>>\n%s-%d\n\e[0;32m%s\e[0m\n",absolute_adress1,name1,begin1,line1,absolute_adress2,name2,begin2,line2);
        }
        begin1++;
        begin2++;
        l1=fgets(line1, sizeof(line1), file1);
        l2=fgets(line2, sizeof(line2), file2);
    }
    // lt:
    // if(begin2==end2+1){
    //     if(begin1==end1+1)
    //         return;
    //     while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL) {
    //         while(1){
    //             bool exist=true;
    //             for(int i=0;i<strlen(line1);i++){
    //                 if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
    //                     exist=false;
    //                 }
    //             }
    //             if(exist){
    //                 if(fgets(line1, sizeof(line1), file1)==NULL){
    //                     return;
    //                 }
    //                 begin1++; 
    //                 if(begin1==end1+1){
    //                     return;
    //                 }
    //             }
    //             else{
    //                 break;
    //             }
    //         }
    //         if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
    //             line1[strlen(line1) - 1] = '\0';
    //         }

    //         printf("%s-%d\n\e[0;31m%s\e[0m\n%s-_\n\e[0;32mNOT IN THE GIVEN LINE\e[0m\n",name1,begin1,line1,name2);
    //         begin1++;
    //         begin2++;
    //         if(begin1==end1+1){
    //         return;
    //     }
    //     }
    // }
    // else if(begin1==end1+1){
    //     while ((l2=fgets(line2, sizeof(line2), file2)) != NULL) {
    //     while(1){
    //         bool exist=true;
    //         for(int i=0;i<strlen(line2);i++){
    //             if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
    //                 exist=false;
    //             }
    //         }
    //         if(exist){
    //             if(fgets(line2, sizeof(line2), file2)==NULL){
    //                 return;
    //             }
    //             begin2++; 
    //             if(begin2==end2+1){
    //                 return;
    //             }
    //         }
    //         else{
    //             break;
    //         }
        
    //     }
    //     if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
    //         line2[strlen(line2) - 1] = '\0';
    //     }
    //     printf("%s-_\n\e[0;31mNOT IN THE GIVEN LINE\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,name2,begin2,line2);
    //     begin2++;
    //     begin1++;
    //     if(begin2==end2+1){
    //         return;
    //     }
    // }

    // }
    // else if(l2==NULL){
    //     while ((l1=fgets(line1, sizeof(line1), file1) )!= NULL) {
    //         while(1){
    //             bool exist=true;
    //             for(int i=0;i<strlen(line1);i++){
    //                 if(line1[i]!='\n'&&line1[i]!='\t'&&line1[i]!=' '){
    //                     exist=false;
    //                 }
    //             }
    //             if(exist){
    //                 if(fgets(line1, sizeof(line1), file1)==NULL){
    //                     return;
    //                 }
    //                 begin1++;
    //                 if(begin1==end1+1){
    //                     return;
    //                 } 
    //             }
    //             else{
    //                 break;
    //             }
    //         }
    //         if (strlen(line1) > 0 && line1[strlen(line1) - 1] == '\n') {
    //             line1[strlen(line1) - 1] = '\0';
    //         }
    //         printf("%s-%d\n\e[0;31m%s\e[0m\n%s-_\n\e[0;32mNOT IN THE GIVEN LINE\e[0m\n",name1,begin1,line1,name2);
    //         begin1++;
    //         begin2++;
    //         if(begin1==end1+1){
    //         return;
    //     }
    //     }

    // }
    // else if(l1==NULL){
    //     while ((l2=fgets(line2, sizeof(line2), file2)) != NULL) {
    //     while(1){
    //         bool exist=true;
    //         for(int i=0;i<strlen(line2);i++){
    //             if(line2[i]!='\n'&&line2[i]!='\t'&&line2[i]!=' '){
    //                 exist=false;
    //             }
    //         }
    //         if(exist){
    //             if(fgets(line2, sizeof(line2), file2)==NULL){
    //                 return;
    //             }
    //             begin2++; 
    //             if(begin2==end2+1){
    //                 return;
    //             }
    //         }
    //         else{
    //             break;
    //         }
        
    //     }
    //     if (strlen(line2) > 0 && line2[strlen(line2) - 1] == '\n') {
    //         line2[strlen(line2) - 1] = '\0';
    //     }
    //     printf("%s-_\n\e[0;31mNOT IN THE GIVEN LINE\e[0m\n%s-%d\n\e[0;32m%s\e[0m\n",name1,name2,begin2,line2);
    //     begin2++;
    //     begin1++;
    //     if(begin2==end2+1){
    //         return;
    //     }
    // }

    // }
}

// int finding_last_commit_of_a_file(DIR *dir,char * branch){
//     struct dirent *entry;
//     int max=-1;
//     while((entry=readdir(dir))!=NULL){
//         if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0||strcmp(entry->d_name,".sag")==0)
//             continue;
//         chdir(entry->d_name);
//         FILE*file=fopen("info.txt","r");
//         char line[1000];
//         fgets(line,sizeof(line),file);
//         int length = strlen(line);
//         if (length > 0 && line[length - 1] == '\n') {
//             line[length - 1] = '\0';
//         }
//         if(strcmp(line,branch)==0){
//             max=atoi(entry->d_name);
//         }
//         chdir("..");
//     }
//     return max;
// }

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
int showing_status_for_A(char *path,char ** files,int x,int test){
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
                if(test==1)
                    return 1;
                printf("%s -A\n",entry->d_name);
            }
            
        }
        else{
            showing_status_for_A(path_dir,files,x,test); 
        }
    }
    return 0;
}

int showing_status(char * branch,int test){
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
            if(test==1)
                return 1;
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
                    if(test==1){
                        return 1;
                    }
                    printf("%s +M\n",name);
                }
            //}

            else if(permission!=permissions(line)){
                if(test==1)
                    return 1;
                printf("%s +T\n",name);
            }
            else{
                if(test==1)
                    return 1;
                printf("%s +A\n",name);
            }
        }
        chdir("..");
        i++;
    }
    int z=i;
    // chdir("..");
    // chdir("commits");
    // dir=opendir(".");
    // while((entry=readdir(dir))!=NULL){
    //     if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
    //         continue;
    //     bool e=false;
    //     for(int j=0;j<i;j++){
    //         if(strcmp(entry->d_name,staged[j])==0){
    //             e=true;
    //             break;
    //         }
    //     }
        
    //     if(!e){
    //         chdir(entry->d_name);
    //         char num[100];
    //         sprintf(num,"%d",finding_last_commit_of_a_file(opendir("."),branch));
    //         chdir(num);
    //         FILE *file=fopen("info.txt","r");
    //         char line[1000];
    //         char line_copy[1000];
    //         int x=0;
    //         int permission;
    //         while (fgets(line, sizeof(line), file)!=NULL) {
    //             int length = strlen(line);
    //             if (length > 0 && line[length - 1] == '\n') {
    //                 line[length - 1] = '\0';
    //             }
    //             if(x==1){
    //                 permission=atoi(line);
    //             }
    //             strcpy(line_copy,line);
    //             x++;
    //         }
    //         strcpy(line,line_copy);
    //         char name[1000];
    //         char tra[1000];
    //         char *str=strtok(line_copy,"\\");
    //             while(str!=NULL){
    //                 strcpy(name,str);
    //                 str=strtok(NULL,"\\");
    //             }
    //             strcpy(files[z],name);
    //         if(fopen(line,"r")==NULL){
    //             printf("%s -D\n",name);
    //         }
    //         else{
    //             if(difference(fopen(line,"r"),fopen(name,"r"))){
    //                 printf("%s -M\n",name);
    //             }
    //             else if(permission!=permissions(line)){
    //                 printf("%s -T\n",name);
    //             }
    //         }
    //         chdir("..");
    //         chdir("..");
    //         z++;
    //     }
    // }
    
    // chdir("..");
    // chdir("..");
    chdir("..");
    chdir("..");
    // chdir("commits");
    // dir=opendir(".");
    // while((entry=readdir(dir))!=NULL){
    //     if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
    //         continue;
    //     bool e=false;
    //     for(int j=0;j<i;j++){
    //         if(strcmp(entry->d_name,staged[j])==0){
    //             e=true;
    //             break;
    //         }
    //     }
    char last_commit_path[1000];
    char line[1000];
    int last=finding_last_commit_of_a_branch(branch);
    sprintf(last_commit_path,".sag\\commits\\%d\\files.txt",last);
    FILE *file=fopen(last_commit_path,"r");
    while(fgets(line,sizeof(line),file)!=NULL){
        if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        char *address=strtok(line,"#");
        char *id=strtok(NULL,"#");
        char address_copy[1000];
        char dir_name[1000];
        char name[1000];
        dir_name[0]='\0';
        strcpy(address_copy,address);
        char *str=strtok(address_copy,"\\:.");
        while(str!=NULL){
            strcat(dir_name,str);
            str=strtok(NULL,"\\:.");
        }
        strcpy(address_copy,address);
        char *boz=strtok(address_copy,"\\");
        while(boz!=NULL){
            strcpy(name,boz);
            boz=strtok(NULL,"\\");
        }
        bool e=false;
        for(int j=0;j<i;j++){
            if(strcmp(dir_name,staged[j])==0){
                e=true;
                break;
            }
        }
        if(e==true)
            continue;
        char file_path[1000];
        sprintf(file_path,".sag\\files\\%s\\%s",dir_name,id);
        chdir(file_path);
        DIR *dir=opendir(".");
        struct dirent *entry;
        while((entry=readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
                continue;
            if(strcmp(entry->d_name,"info.txt")!=0){
                if(fopen(address,"r")==NULL){
                    if(test==1)
                        return 1;
                    printf("%s -D\n",entry->d_name);
                }
                else if(difference(fopen(address,"r"),fopen(entry->d_name,"r"))){
                    if(test==1)
                        return 1;
                    printf("%s -M\n",entry->d_name);
                }
            }
            else{
                char l[100];
                FILE *fi=fopen("info.txt","r");
                fgets(l,sizeof(l),fi);
                fgets(l,sizeof(l),fi);
                if (strlen(l) > 0 && l[strlen(l) - 1] == '\n') {
                    l[strlen(l) - 1] = '\0';
                }
                if(permissions(address)!=atoi(l)){
                    if(test==1)
                        return 1;
                    if(fopen(address,"r")!=NULL){
                        printf("%s -T\n",name);
                    }  
                }
            }
        }
        strcpy(files[z],name);
        chdir("..");
        chdir("..");
        chdir("..");
        chdir("..");
        z++;
    }
    x:
    char path[1000];
    getcwd(path,sizeof(path));
    if(showing_status_for_A(path,files,z,test)==1)
        return 1;
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
        sprintf(system_command,"rmdir /s %s\\%s",path,dir_name);
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
            fprintf(file,"%s\n%d\n%s",branch_name,permissions(path),path);
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
    if(opendir(path)==NULL){
        return 1;
    }
    return 0;
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
        mkdir("tags");
        // mkdir("config");
        // chdir("config");
        FILE *file=fopen("add_log.txt","w");
        fclose(file);
        file=fopen("curr_branch.txt","w");
        fprintf(file,"%s","master");
        fclose(file);
        file=fopen("curr_commit.txt","w");
        fclose(file);
        file=fopen("commit_shorts.txt","w");
        fclose(file);
        file=fopen("merge_IDs.txt","w");
        fclose(file);
        file=fopen("hooks.txt","w");
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
                    time_t curr;
                    time(&curr);
                    struct tm *temp;
                    temp=localtime(&curr);
                    char my_time[1000];
                    strftime(my_time,sizeof(my_time),"%Y/%m/%d %H:%M:%S",temp);
                FILE *user=fopen(address,"r");
                if(user!=NULL){
                    FILE *user=fopen(address,"a");
                    fprintf(user,"%s#%s#%s\n",type,name,my_time);
                }
                else{
                    FILE *user=fopen(address,"w");
                    fprintf(user,"%s#%s#%s\n",type,name,my_time);
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
            // if(argv[2][5]!='.')
            //     printf("invalid alias");
            // else{
                if(init(1)==1){
                    alias("C:\\Users\\Reza\\git\\alias_command_local.txt",argv[2]+6,argv[3]);
                }
                else{
                    alias(".sag\\alias_command_local.txt",argv[2]+6,argv[3]);
                }
            
            //}
        }
        else if(strncmp(argv[3],"alias",5)==0){
            // // if(argv[3][5]!='.')
            // //     printf("invalid alias");
            if(strcmp(argv[2],"--global")==0){
                alias("C:\\Users\\Reza\\git\\alias_command_global.txt",argv[3]+6,argv[4]);
            // }
            // else{
            //     printf("invalid alias");
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
                if(is_dir_or_not(absolute_adress)){
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
        else if(in_head_of_branch_or_not()==false){
            printf("NOT IN THE HEAD");
        }
        else{
            char absolute_adress[1000];
            getcwd(absolute_adress,sizeof(absolute_adress));
            FILE *file=fopen(".sag\\curr_branch.txt","r");
            char line[1000];
            fgets(line,sizeof(line),file);
            showing_status(line,0);
        }
    }
    else if(strcmp(argv[1],"commit")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else if(number_of_files_and_folders(opendir(".sag\\staged_area"))==0){
        }
        else{
            char absolute_adress[1000];
            getcwd(absolute_adress,sizeof(absolute_adress));
            if(strcmp(argv[2],"-m")==0){
                if(argc<4){
                    printf("MESSAGE??????\n");
                }
                else if(strlen(argv[3])>72){
                    printf("BIG MESSAGE\n");
                }
                else{
                    run_commit(argv[3]);
                }
            }
            else{
                printf("sasa");
                FILE *file=fopen(".sag\\commit_shorts.txt","r");
                char short_name[1000];
                bool exist=false;
                while(fgets(short_name,sizeof(short_name),file)!=NULL){
                    if (strlen(short_name) > 0 && short_name[strlen(short_name) - 1] == '\n') {
                        short_name[strlen(short_name) - 1] = '\0';
                    }
                    char *str=strtok(short_name,"#");
                    if(strcmp(str,argv[3])==0){
                        str=strtok(NULL,"#");
                        exist=true;
                        run_commit(str);
                    }
                }
                if(exist==false){
                    printf("NO SHORTCUT");
                }
                
            }
        }
    }
    else if(strcmp(argv[1],"set")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            FILE *file=fopen(".sag\\commit_shorts.txt","a");
            fprintf(file,"%s#%s\n",argv[5],argv[3]);
        }
    }
    else if(strcmp(argv[1],"replace")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            FILE *file=fopen(".sag\\commit_shorts.txt","r");
            FILE *file2=fopen(".sag\\commit_shorts1.txt","w");
                char short_name[1000];
                char short_name_c[1000];
                bool exist=false;
                while(fgets(short_name,sizeof(short_name),file)!=NULL){
                    if (strlen(short_name) > 0 && short_name[strlen(short_name) - 1] == '\n') {
                        short_name[strlen(short_name) - 1] = '\0';
                    }
                    strcpy(short_name_c,short_name);
                    char *str=strtok(short_name_c,"#");
                    if(strcmp(str,argv[5])==0){
                        exist=true;
                        fprintf(file2,"%s#%s\n",argv[5],argv[3]);
                    }
                    else{
                        fprintf(file2,"%s\n",short_name);
                    }
                }
                if(exist==false){
                    printf("NO SHORTCUT");
                }
                fclose(file);
                fclose(file2);
            system("del .sag\\commit_shorts.txt");
            rename(".sag\\commit_shorts1.txt",".sag\\commit_shorts.txt");
        }
    }
    else if(strcmp(argv[1],"remove")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            FILE *file=fopen(".sag\\commit_shorts.txt","r");
            FILE *file2=fopen(".sag\\commit_shorts1.txt","w");
                char short_name[1000];
                char short_name_c[1000];
                bool exist=false;
                while(fgets(short_name,sizeof(short_name),file)!=NULL){
                    if (strlen(short_name) > 0 && short_name[strlen(short_name) - 1] == '\n') {
                        short_name[strlen(short_name) - 1] = '\0';
                    }
                    strcpy(short_name_c,short_name);
                    char *str=strtok(short_name_c,"#");
                    if(strcmp(str,argv[3])==0){
                        exist=true;
                    }
                    else{
                        fprintf(file2,"%s\n",short_name);
                    }
                }
                if(exist==false){
                    printf("NO SHORTCUT");
                }
                fclose(file);
                fclose(file2);
            system("del .sag\\commit_shorts.txt");
            rename(".sag\\commit_shorts1.txt",".sag\\commit_shorts.txt");
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
                diff_whithout_line(absolute_adress1,absolute_adress2,absolute_adress1,absolute_adress2);
            }
        }
        else{
            check_diff_commit(argv[3],argv[4]);
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
            else if(strcmp(argv[2],"-since")==0){
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                printf("%d",find_since_log_commit_ID(argv[3],max));
                for(int i=max;i>=find_since_log_commit_ID(argv[3],max);i--){
                    char path[1000];
                    sprintf(path,".sag\\commits\\%d",i);
                    chdir(path);
                    print_log(i,"a",0);
                    chdir("..");
                    chdir("..");
                    chdir("..");
                }
            }
            else if(strcmp(argv[2],"-before")==0){
                int max=finding_last_commit_folder(opendir(".sag\\commits"));
                for(int i=find_before_log_commit_ID(argv[3],max)-1;i>=1;i--){
                    char path[1000];
                    sprintf(path,".sag\\commits\\%d",i);
                    chdir(path);
                    print_log(i,"a",0);
                    chdir("..");
                    chdir("..");
                    chdir("..");
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
                    int x=finding_last_commit_of_a_branch("master");
                    add_the_new_branch_to_commits(argv[2],x);
                    add_the_new_branch_to_files(argv[2],x);
                }
            }
        }
    }
    else if(strcmp(argv[1],"checkout")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else if(number_of_files_and_folders(opendir(".sag\\staged_area"))!=0){
            printf("STAGE IS NOT EMPTY");
            return 0;
        }
        // char path[1000];
        // getcwd(path,sizeof(path));
        // FILE *file=fopen(".sag\\curr_branch.txt","r");
        // char line[1000];
        // fgets(line,sizeof(line),file);
        // if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
        // line[strlen(line) - 1] = '\0';
        // }
        // if(showing_status(line,1)==1){
        //     printf("SOMTHING HAD CHANGED");
        // }
        else{
            // chdir(path);
            if(strncmp(argv[2],"HEAD-",5)==0){
                checkout_with_HEAD_n(argv[2]+5);
            }
            else if(strcmp(argv[2],"HEAD")==0){
                checkout_with_HEAD();
            }
            else if(is_it_branch(argv[2])){
                checkout_with_branch(argv[2]);
            }
            else{
                checkout_with_num(argv[2],1);
            }
        }
    }
    else if(strcmp(argv[1],"revert")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            FILE *file=fopen(".sag\\curr_branch.txt","r");
            char line[1000];
            fgets(line,sizeof(line),file);
            fclose(file);
            file=fopen(".sag\\merge_IDs.txt","r");
            int max=find_last_merg_id(file);
            fclose(file);
            if(strcmp(argv[2],"-n")==0){
                if(argc==4){
                    if(strcmp(line,"master")==0){
                        if(atoi(argv[3])<=max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    checkout_with_num(argv[3],1);
                }
                else{
                    FILE *file2=fopen(".sag\\curr_commit.txt","r");
                    int t;
                    fscanf(file2,"%d",&t);
                    if(strcmp(line,"master")==0){
                        if(t==max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    FILE *file=fopen(".sag\\curr_branch.txt","r");
                    char line[1000];
                    fgets(line,sizeof(line),file);
                    char x[1000];
                    sprintf(x,"%d",finding_last_commit_of_a_branch(line));
                    checkout_with_num(x,1);
                }
            }
            else if(strcmp(argv[2],"-m")==0){
                if(strncmp(argv[4],"HEAD-",5)==0){
                    if(strcmp(line,"master")==0){
                        if(atoi(argv[4]+5)<=max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    checkout_with_HEAD_n(argv[4]+5);
                    revert_with_HEAD_n_message(argv[4]+5,argv[3]);
                }
                else{
                    if(strcmp(line,"master")==0){
                        if(atoi(argv[4])<=max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    checkout_with_num(argv[4],0);
                    copy_commit_with_message(argv[4],argv[3]);
                }
                
            }
            else{
                if(strncmp(argv[2],"HEAD-",5)==0){
                    if(strcmp(line,"master")==0){
                        if(atoi(argv[2]+5)<=max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    checkout_with_HEAD_n(argv[2]+5);
                    revert_with_HEAD_n(argv[2]+5);
                }
                else{
                    if(strcmp(line,"master")==0){
                        if(atoi(argv[2])<=max){
                            printf("MERGEEEE");
                            return 0;
                        }
                    }
                    checkout_with_num(argv[2],0);
                    copy_commit(argv[2]);
                }

            }

        }
    }
    else if(strcmp(argv[1],"tag")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(argc==2){
                print_tags();
            }
            else if(strcmp(argv[2],"show")==0){
                show_tag(argv[3]);
            }
            else if(strcmp(argv[2],"-a")==0){
                create_tag(argv,argc);
            } 
        } 
    }
    else if(strcmp(argv[1],"grep")==0){
        char absolute_address[1000];
        getcwd(absolute_address,sizeof(absolute_address));
        strcat(absolute_address,"\\");
        strcat(absolute_address,argv[3]);
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(argc==6){
                grep(absolute_address,0,argv[5]);
            }
            else if(argc==7){
                grep(absolute_address,1,argv[5]);
            }
            else if(argc==8){
                char dir_name[1000];
                char path[1000];
                char name[1000];
                dir_name[0]='\0';
                strcpy(path,absolute_address);
                char *str=strtok(path,"\\:.");
                while(str!=NULL){
                    strcat(dir_name,str);
                    str=strtok(NULL,"\\:.");
                }
                strcpy(path,absolute_address);
                char *boz=strtok(path,"\\");
                while(boz!=NULL){
                    strcpy(name,boz);
                    boz=strtok(NULL,"\\");
                }
                sprintf(path,".sag\\files\\%s\\%s\\%s",dir_name,argv[7],name);
                grep(path,0,argv[5]);
            }
            else if(argc==9){
                    char dir_name[1000];
                    char path[1000];
                    char name[1000];
                    dir_name[0]='\0';
                    strcpy(path,absolute_address);
                    char *str=strtok(path,"\\:.");
                    while(str!=NULL){
                        strcat(dir_name,str);
                        str=strtok(NULL,"\\:.");
                    }
                    strcpy(path,absolute_address);
                    char *boz=strtok(path,"\\");
                    while(boz!=NULL){
                        strcpy(name,boz);
                        boz=strtok(NULL,"\\");
                    }
                    sprintf(path,".sag\\files\\%s\\%s\\%s",dir_name,argv[7],name);
                    grep(path,1,argv[5]);
            }

            // if(strcmp(argv[argc-1],"-n")==0){
            //     if(strcmp(argv[6],"-c")==0){
            //         char dir_name[1000];
            //         char path[1000];
            //         char name[1000];
            //         dir_name[0]='\0';
            //         strcpy(path,absolute_address);
            //         char *str=strtok(path,"\\:.");
            //         while(str!=NULL){
            //             strcat(dir_name,str);
            //             str=strtok(NULL,"\\:.");
            //         }
            //         strcpy(path,absolute_address);
            //         char *boz=strtok(path,"\\");
            //         while(boz!=NULL){
            //             strcpy(name,boz);
            //             boz=strtok(NULL,"\\");
            //         }
            //         sprintf(path,".sag\\files\\%s\\%s\\%s",dir_name,argv[7],name);
            //         grep(path,1,argv[5]);
            //     }
            //     else{
            //         grep(absolute_address,1,argv[5]);
            //     }
            // }
            // else{
            //     if(argc>6){
            //         char dir_name[1000];
            //         char path[1000];
            //         char name[1000];
            //         dir_name[0]='\0';
            //         strcpy(path,absolute_address);
            //         char *str=strtok(path,"\\:.");
            //         while(str!=NULL){
            //             strcat(dir_name,str);
            //             str=strtok(NULL,"\\:.");
            //         }
            //         strcpy(path,absolute_address);
            //         char *boz=strtok(path,"\\");
            //         while(boz!=NULL){
            //             strcpy(name,boz);
            //             boz=strtok(NULL,"\\");
            //         }
            //         sprintf(path,".sag\\files\\%s\\%s\\%s",dir_name,argv[7],name);
            //         grep(path,0,argv[5]);
            //     }
            //     else{
            //         grep(absolute_address,0,argv[5]);
            //     }
            // }
        }
    }
    else if(strcmp(argv[1],"merge")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(merge_branches_check(argv[3],argv[4])){
                char system_command[1000];
                sprintf(system_command,"del .sag\\all_branches\\%s.txt",argv[4]);
                system(system_command);
                checkout_with_branch("master");
            }
        }
    }
    else if(strcmp(argv[1],"pre-commit")==0){
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            if(argc==2){
                add_hooks_to_stag_area();
            }
            else if(strcmp(argv[2],"hooks")==0){
                printf("todo-check\neof-blank-space\nformat-check\nbalance-braces\nindentation-check\nstatic-error-check\nfile-size-check\ncharacter-limit\ntime-limit\n");
            }
            else if(strcmp(argv[2],"applied")==0){
                FILE *file=fopen(".sag\\hooks.txt","r");
                char line[1000];
                while(fgets(line,sizeof(line),file)!=NULL){
                    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                    }
                    printf("%s\n",line);
                }
            }
            else if(strcmp(argv[2],"add")==0){
                FILE *file=fopen(".sag\\hooks.txt","a");
                fprintf(file,"%s\n",argv[4]);
            }
            else if(strcmp(argv[2],"remove")==0){
                FILE *file=fopen(".sag\\hooks.txt","a");
                FILE *file_copy=fopen(".sag\\hooks1.txt","w");
                char line[1000];
                while(fgets(line,sizeof(line),file)!=NULL){
                    if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                    }
                    if(strcmp(line,argv[4])!=0){
                        fprintf(file_copy,"%s\n",line);
                    }
                }
                fclose(file_copy);
                fclose(file);
                remove(".sag\\hooks.txt");
                rename(".sag\\hooks1.txt",".sag\\hooks.txt");
            }
        }
    }
    else{
        if(init(1)==1){
            printf("NOT INITED YET");
        }
        else{
            FILE*file=fopen(".sag\\alias_command_local.txt","r");
            char line[1000];
            while(fgets(line,sizeof(line),file)!=NULL){
                if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                }
                char *str=strtok(line,"#");
                if(strcmp(str,argv[1])==0){
                    str=strtok(NULL,"#");
                    system(str);
                    return 0;
                }
            }
            file=fopen("C:\\Users\\Reza\\git\\alias_command_global.txt","r");
            while(fgets(line,sizeof(line),file)!=NULL){
                if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {
                    line[strlen(line) - 1] = '\0';
                }
                char *str=strtok(line,"#");
                if(strcmp(str,argv[1])==0){
                    str=strtok(NULL,"#");
                    system(str);
                    return 0;
                }
            }
        }
    }  
    return 0;
}