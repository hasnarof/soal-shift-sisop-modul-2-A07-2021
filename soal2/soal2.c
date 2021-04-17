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

int main(int argc,char* argv[]){
 pid_t cid1,cid2,cid3,cid4,cid5,cid6,cid7,cid8,cid9,cid10,cid11,cid12,cid13,cid14,cid15;
    int status;
    cid1=fork();
    if(cid1<0){exit(EXIT_FAILURE);}
    if(cid1==0){
   char *argv[]={"unzip", "-q","/home/ghifari/modul2/petshop/pets.zip", NULL};
   execv("/usr/bin/unzip", argv);
 } 
    sleep(5);
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
        
        cid3=fork();
                            if  (cid3<0){exit(EXIT_FAILURE);}
                            if (cid3==0){
                            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/betta",NULL};
                            execv("/bin/mkdir",argv);
                            }
     
        while((wait(&status)) >0);
        
        cid4=fork();
        if  (cid4<0){exit(EXIT_FAILURE);}
        if (cid4==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/cat",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        
        cid5=fork();
        if  (cid5<0){exit(EXIT_FAILURE);}
        if (cid5==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/dog",NULL};
            execv("/bin/mkdir",argv);
        }
        
       // while((wait(&status)) >0);
        cid6=fork();
        if  (cid6<0){exit(EXIT_FAILURE);}
        if (cid6==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/chicken",NULL};
            execv("/bin/mkdir",argv);
        }
        cid6=fork();
        if  (cid6<0){exit(EXIT_FAILURE);}
        if (cid6==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/frog",NULL};
           execv("/bin/mkdir",argv);
        }
        
        while((wait(&status)) >0);
        cid7=fork();
        if  (cid7<0){exit(EXIT_FAILURE);}
        if (cid7==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/guinea pig",NULL};
            execv("/bin/mkdir",argv);
        }
         while((wait(&status)) >0);
        cid7=fork();
        if  (cid7<0){exit(EXIT_FAILURE);}
        if (cid7==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/hamster",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid8=fork();
        if  (cid8<0){exit(EXIT_FAILURE);}
        if (cid8==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/iguana",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid9=fork();
        if  (cid9<0){exit(EXIT_FAILURE);}
        if (cid9==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/ilama",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid10=fork();
        if  (cid10<0){exit(EXIT_FAILURE);}
        if (cid10==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/otter",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid11=fork();
        if  (cid11<0){exit(EXIT_FAILURE);}
        if (cid11==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/parrot",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid12=fork();
        if  (cid12<0){exit(EXIT_FAILURE);}
        if (cid12==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/rabbit",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid13=fork();
        if  (cid13<0){exit(EXIT_FAILURE);}
        if (cid13==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/racoon",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid14=fork();
        if  (cid14<0){exit(EXIT_FAILURE);}
        if (cid14==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/sheep",NULL};
            execv("/bin/mkdir",argv);
        }
        while((wait(&status)) >0);
        cid15=fork();
        if  (cid15<0){exit(EXIT_FAILURE);}
        if (cid15==0){
            char *argv[]={"mkdir","-p","/home/ghifari/modul2/petshop/tiger",NULL};
            execv("/bin/mkdir",argv);
        }
        
       DIR *dor;
        struct dirent *masuk;
        dor=opendir("/home/ghifari/modul2/petshop/");
        if (dor){
        while((masuk=readdir(dor))!=NULL){
            char file[100];
            memset(file,0,sizeof(file));
            strcpy(file, "/home/ghifari/modul2/petshop/");
            strcat(file,masuk->d_name);
            struct stat typestat;
            if (!stat(file,&typestat)){
                if ((typestat.st_mode&&S_IFREG)){
                    if (!stat(file,&typestat)){
                    if ((typestat.st_mode&&S_IFREG)){
                        if ((strstr(file, "betta")) && !(strstr(file,"_"))){
                            cid3=fork();
                            if  (cid3<0){exit(EXIT_FAILURE);}
                            if (cid3==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/betta",NULL};
                                execv("/bin/mv",argv);
                            }
                        }
                        
                         if ((strstr(file, "cat")) && !(strstr(file,"_"))){
                            cid4=fork();
                            if (cid4==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/cat",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                        
                        if ((strstr(file, "dog")) && !(strstr(file,"_"))){
                            cid5=fork();
                            if (cid5==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/dog",NULL};
                                execv("/bin/mv",argv);
                        } 
                        }
                        if ((strstr(file, "frog")) && !(strstr(file,"_"))){
                            cid5=fork();
                            if (cid5==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/frog",NULL};
                                execv("/bin/mv",argv);
                        } 
                        }
                         if ((strstr(file, "racoon")) && !(strstr(file,"_"))){
                            cid5=fork();
                            if (cid5==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/racoon",NULL};
                                execv("/bin/mv",argv);
                        } 
                        }
                         if ((strstr(file, "chicken")) && !(strstr(file,"_"))){
                            cid6=fork();
                            if (cid6==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/chicken",NULL};
                                execv("/bin/mv",argv);
                            }
                        }
                         
                         if ((strstr(file, "guinea pig")) && !(strstr(file,"_"))){
                            cid7=fork();
                            if (cid7==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/guinea pig",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         if ((strstr(file, "hamster")) && !(strstr(file,"_"))){
                            cid8=fork();
                            if (cid8==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/hamster",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         if ((strstr(file, "iguana")) && !(strstr(file,"_"))){
                            cid9=fork();
                            if (cid9==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/iguana",NULL};
                                execv("/bin/mv",argv);
                        }
                         }
                        if ((strstr(file, "ilama")) && !(strstr(file,"_"))){
                            cid10=fork();
                            if (cid10==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/ilama",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         if ((strstr(file, "otter")) && !(strstr(file,"_"))){
                            cid11=fork();
                            if (cid11==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/otter",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         if ((strstr(file, "parrot")) && !(strstr(file,"_"))){
                            cid12=fork();
                            if (cid12==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/parrot",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         
                         if ((strstr(file, "rabbit")) && !(strstr(file,"_"))){
                            cid13=fork();
                            if (cid13==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/rabbit",NULL};
                                execv("/bin/mv",argv);
                            }
                         }
                         if ((strstr(file, "sheep")) && !(strstr(file,"_"))){
                            cid14=fork();
                            if (cid14==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/sheep",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
                         
                         if ((strstr(file, "tiger")) && !(strstr(file,"_"))){
                            cid15=fork();
                            if (cid15==0){
                                char *argv[]={"mv",file,"/home/ghifari/modul2/petshop/tiger",NULL};
                                execv("/bin/mv",argv);
                        }
                        }
       }
        
            }
            
        }
                }
            }
            closedir(dor);
        }
        }
