#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <limits.h>
void ardu(char command[], char *arg[]){
	int status;
	pid_t pid;
	pid = fork();
	if(pid == 0){
		execv(command, arg);
	}
	else{
		((wait(&status))>0);
	}
}
int main(int argc,char* argv[]){
    pid_t cid1,cid2;
    int status1,status2,status;
    cid1=fork();
    if(cid1==0){
   char *argv[]={"unzip", "-q","/home/ghifari/modul2/petshop/pets.zip", NULL};
   ardu("/usr/bin/unzip", argv);
    }
    while((wait(&status))>0);;
    char *full_path;
    DIR *dir;
    struct dirent *entry;
    int r=-1;
     size_t path_len = strlen("/home/ghifari/modul2/petshop");
    dir=opendir("/home/ghifari/modul2/petshop");
        if (dir){
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(dir))) {
            int r2 = -1;
            char *buf;
            size_t len;

            
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = path_len + strlen(p->d_name) + 2; 
            buf = malloc(len);

            if (buf) {
             struct stat statbuf;

                snprintf(buf, len, "%s", p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode)){
                        
                        DIR *subdir;
                        struct dirent *sub;
                        subdir=opendir(buf);
                            while((sub=readdir(subdir))){
                            char aku[100];
                            memset(aku,0,sizeof(aku));
                            strcpy(aku,buf);
                            strcat(aku, "/");
                            strcat (aku, sub->d_name);
                            remove(aku);
                    }
                    closedir(subdir);
                    r2 = rmdir(buf);

                }
                    else
                        continue;
             }
             free(buf);
            }
            
        }
        closedir(dir);
        }
      while(wait(&status1) > 0);;
    DIR *diir;
    struct dirent *eentry;
    diir=opendir("/home/ghifari/modul2/petshop");
        if (diir){
        while ((eentry=readdir(diir))!=NULL){
            char file[100]="";
            strcpy(file,"/home/ghifari/modul2/petshop/");
            strcat(file,eentry->d_name);
              if (strcmp(eentry->d_name, ".") != 0 && strcmp(eentry->d_name, "..") != 0)
        {
            if(strstr(file, ".jpg")){
            strtok(file,";");
                char *argv[]={"mkdir","-p",file,NULL};
                ardu("/bin/mkdir",argv);
        }
        }
        
        }
        closedir(diir);
        }
        while(wait(&status2) > 0);
    
}
