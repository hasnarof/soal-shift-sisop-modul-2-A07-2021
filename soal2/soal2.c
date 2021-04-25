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
int main(){
    int status1,status2,status;
   char *argv[]={"unzip", "-q","/home/ghifari/modul2/petshop/pets.zip","-d", "/home/ghifari/modul2/petshop", NULL};
   ardu("/usr/bin/unzip", argv);
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
        
        DIR *diiir;
        struct dirent *eeentry;
        diiir=opendir("/home/ghifari/modul2/petshop");
        if (diiir){
           while ((eeentry=readdir(diiir))!=NULL){
           char file2[100]="";
           strcpy(file2,eeentry->d_name);
           if (strcmp(eeentry->d_name, ".") != 0 && strcmp(eeentry->d_name, "..") != 0){
               int adaa=0;
               if(strstr(file2,".jpg") && !(strstr(file2,"_"))){
                   char nama[100],halu[100],ada[100],settingan[100],halu2[100],ada2[100],settingan2[100],halu3[100],halu4[100],ada3[100],settingan3[100]="";
                   strcpy(nama,file2);
                   strtok(nama,";");
                   int i,ii;
                   strcpy(halu,nama);
                   strcat(halu,";");
                   int ext=strlen(halu);
                   strcpy(ada,&file2[ext]);
                   //printf("%s\n",ada);
                   strcpy(settingan,ada);
                   strtok(settingan,";");
                  // printf("%s\n",settingan);
                   strcpy(halu2,settingan);
                   strcat(halu2,";");
                   int ext2=strlen(halu2);
                    strcpy(ada2,&ada[ext2]);
                    //printf("%s\n",ada2);
                    
                    strcpy(settingan2,ada2);
                    //strtok(settingan2, "_");
                    strtok(settingan2, "j");
                    if (settingan2[strlen(settingan2) - 1] == '.')
                    {
                    settingan2[strlen(settingan2) - 1] = '\0';
                    }
                    printf("%s\n",settingan2);
                    while((wait(&status))>0);

                    int status, status2;
                    
                    char rekor[400], muri[400],hbd[400],adalah[400];
                    strcpy(hbd,"/home/ghifari/modul2/petshop/");
                    strcat(hbd,eeentry->d_name);
                        sprintf(rekor, "%s", hbd);
                        sprintf(muri, "/home/ghifari/modul2/petshop/%s/%s.jpg", nama, settingan);
                        char *arg[] = {"cp", "-r", rekor, muri, NULL};
                        ardu("/bin/cp", arg);
            
                        while(wait(&status) > 0);
                        char susah[400];
                        sprintf(susah, "/home/ghifari/modul2/petshop/%s/keterangan.txt", nama);
                        FILE *angel=fopen(susah, "a+");
                        fprintf(angel, "nama : %s\n", settingan);
                        fprintf(angel, "umur : %s tahun\n\n", settingan2);
                        fclose(angel);
               }
                    
                     if(strstr(file2,".jpg") && (strstr(file2,"_"))){
                         char name[100],hantu2[100],really[100],setting[100],hantu5[100],really2[100],setting2[100],hantu3[100],hantu4[100],really3[100],setting4[100]="";
                         char hantu6[100],hantu7[100];
                         char setting3[100],setting6[100],setting5[100];
                         char really4[100],really6[100],really7[100],really5[100];
                 strcpy(name,file2);
                   strtok(name,";");
                   int i,ii;
                   strcpy(hantu2,name);
                   strcat(hantu2,";");
                   int xet=strlen(hantu2);
                   strcpy(really,&file2[xet]);
                //   printf("%s\n",really);
                   strcpy(setting,really);
                   strtok(setting,";");
                 //  printf("%s\n",setting);
                   strcpy(hantu3,setting);
                   strcat(hantu3,";");
                   int xet2=strlen(hantu3);
                    strcpy(really2,&really[xet2]);
                 //   printf("%s\n",really2);
                    strcpy(setting2,really2);
                    strtok(setting2, "_");
                  //  printf("%s\n",setting2);
                    strcpy(hantu4,setting2);
                    strcat(hantu4,"_");

                     int xet3=strlen(hantu4);
                    strcpy(really3,&really2[xet3]);
                   // printf("%s\n",really3);
                     strcpy(setting3,really3);
                    strtok(setting3, ";");
                   // printf("%s\n",setting3);
                    strcpy(hantu5,setting3);
                    strcat(hantu5,"_");

                    int xet4=strlen(hantu5);
                    strcpy(really4,&really3[xet4]);
                   // printf("%s\n",really4);
                    
                    strcpy(setting4,really4);
                    strtok(setting4, ";");
                    printf("%s\n",setting4);
                    strcpy(hantu6,setting4);
                    strcat(hantu6,";");
                    int xet5=strlen(hantu6);
                    strcpy(really5,&really4[xet5]);
                    //printf("%s\n",really5);
                    
                   strcpy(setting5,really5);
                    strtok(setting5, "j");
                    if (setting5[strlen(setting5) - 1] == '.')
                    {
                    setting5[strlen(setting5) - 1] = '\0';
                    }
                            
                   while((wait(&status))>0);
                    char rekor[400], muri[400],hbd[400],adalah[400],sapi[400],kucing[400];
                    strcpy(hbd,"/home/ghifari/modul2/petshop/");
                    strcat(hbd,eeentry->d_name);
                    sprintf(rekor, "%s", hbd);
                    sprintf(muri, "/home/ghifari/modul2/petshop/%s/%s.jpg", name, setting);
                    char *arg[] = {"cp", "-r", rekor, muri, NULL};
                    ardu("/bin/cp", arg);
            
                while(wait(&status2) > 0);
                    sprintf(sapi, "/home/ghifari/modul2/petshop/%s/%s.jpg", setting3, setting4);
                    char *argvv[] = {"cp", "-r", rekor, sapi, NULL};
                    ardu("/bin/cp", argvv);
       
                //soal e
                while(wait(&status2) > 0);
                char terang[300];
                sprintf(terang, "/home/ghifari/modul2/petshop/%s/keterangan.txt", name);
                FILE *terangkanlah;
                terangkanlah = fopen(terang, "a+");
                fprintf(terangkanlah, "nama : %s\n", setting);
                fprintf(terangkanlah, "umur : %s tahun\n\n", setting3);
                fclose(terangkanlah);
                while(wait(&status2) > 0);
                sprintf(terang, "/home/ghifari/modul2/petshop/%s/keterangan.txt", setting3);
                terangkanlah = fopen(terang, "a+");
                fprintf(terangkanlah, "nama : %s\n", setting4);
                fprintf(terangkanlah, "umur : %s tahun\n\n", setting5);
                fclose(terangkanlah);
                  }
         }
           
           }
           closedir(diir);
}
}
