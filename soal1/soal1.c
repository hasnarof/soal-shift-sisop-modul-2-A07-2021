#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <dirent.h>

int main(){
    
pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if((chdir("/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1"))<0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    while(1){
        time_t currTime = time(NULL);
        int day = 9;
        int month = 4;
        int hour = 22;
        int min = 22;
        int entered = 0;
        int entered2 = 0;
        struct tm tmp = *localtime(&currTime);

        if(tmp.tm_mday == day && tmp.tm_mon+1 == month && tmp.tm_hour == hour-6 && tmp.tm_min == min && entered == 0){   

            char *folder[3] = {"Pyoto", "Musyik", "Fylm"};
            char *link[3] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
            char *zip[3] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
            char *tzip[3] = {"/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Pyoto.zip", "//home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Musyik.zip", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Fylm.zip"};
            char *tfolder[3] = {"/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Pyoto", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Musyik", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Fylm"}; 

            //mkdir
            pid_t child_id, wpid;
            int j;

            int status1=0;
            for(j=0; j<3; j++){
                
                if((child_id=fork())==0){
                    char *argv[] = {"mkdir", folder[j], NULL};
                    execv("/usr/bin/mkdir", argv);
                    exit(0);
                }
            }

            while((wpid==wait(&status1))>0);

            pid_t child_id2, wpid2;
            int k;
            int status2=0;
            for(k=0; k<3; k++){
                
                if((child_id2=fork())==0){
                    char *argv[] = {"wget", "-U", "firefox", "-q", "--no-check-certificate", link[k], "-O", zip[k], NULL};
                    execv("/usr/bin/wget", argv);
                    exit(0);
                }
                
            }
            while((wpid2==wait(&status2))>0);

            //unzip
            pid_t child_id3, wpid3;
            int i;
            int status3=0;
            for(i=0; i<3; i++){
                
                if((child_id3=fork())==0){
                    char *argv2[] = {"unzip", "-j", tzip[i], "-d", tfolder[i], NULL};
                    execv("/usr/bin/unzip", argv2);
                    exit(0);
                }
                //sleep(2);
            }
            while((wpid3==wait(&status3))>0);
            
            entered = 1;

        }

        else if(tmp.tm_mday == day && tmp.tm_mon+1 == month && tmp.tm_hour == hour && tmp.tm_min == min && entered2 ==0){
            char *argv2[] = {"/bin/zip", "-rm", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
            execv("/usr/bin/zip", argv2);
            entered2 = 1;
        }
        sleep(2);
    }
    
}