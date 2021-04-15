#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int main() {
    pid_t child_id;
    int status;
    char add[] = "/home/meizee/Documents/SISOP/SHIFT 2";

    child_id = fork();

    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        pid_t child_id;
        int status2;
        child_id = fork();

        if(child_id < 0) {
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
        }

        if(child_id==0){
            id_t child_id;
            int status3;
            child_id = fork();

            if(child_id < 0) {
                exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
            }

            if(child_id==0){
                id_t child_id;
                int status4;
                child_id = fork();

                if(child_id < 0) {
                    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
                }

                if (child_id == 0){
                    pid_t child_id;
                    int status5;
                    child_id = fork();

                    if(child_id < 0) {
                        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
                    }

                    if(child_id==0){
                        pid_t child_id;
                        int status6;
                        child_id = fork(); 

                        if(child_id < 0) {
                            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
                        }

                        if(child_id==0){
                            pid_t child_id;
                            int status7;
                            child_id = fork(); 

                            if(child_id < 0) {
                                exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti)
                            }

                            if (child_id == 0){
                                //foto
                                char link[1000] = "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download";
                                char *argv[] = {"/usr/bin/wget", "--no-check-certificate", link, "-O", "Pyoto.zip",NULL};
                                execv("/usr/bin/wget", argv);
                            }
                            else{
                                while ((wait(&status7)) > 0);
                                sleep(2);
                                //musik
                                char link[1000] = "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download";
                                char *argv[] = {"/usr/bin/wget", "--no-check-certificate", link, "-O", "Musyik.zip",NULL};
                                execv("/usr/bin/wget", argv);
                            }
                        }
                        else{
                            while ((wait(&status6)) > 0);
                            sleep(2);
                            //dfilm
                            char link[1000] = "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download";
                            char *argv[] = {"/usr/bin/wget", "--no-check-certificate", link, "-O", "Fylm.zip",NULL};
                            execv("/usr/bin/wget", argv);
                        }
                    }
                    else{
                        while ((wait(&status5)) > 0);
                        sleep(2);
                        char *argv2[] = {"unzip", "-j", "/home/meizee/Documents/SISOP/SHIFT 2/Pyoto.zip", "-d", "/home/meizee/Documents/SISOP/SHIFT 2/Pyoto", NULL};
                        execv("/usr/bin/unzip", argv2);
                    }
                }
                else{
                    while ((wait(&status4)) > 0);
                    sleep(2);
                    char *argv2[] = {"unzip", "-j", "/home/meizee/Documents/SISOP/SHIFT 2/Musyik.zip", "-d", "/home/meizee/Documents/SISOP/SHIFT 2/Musyik", NULL};
                    execv("/usr/bin/unzip", argv2);
                }
            }
            else{
                while ((wait(&status3)) > 0);
                sleep(2);
                char *argv2[] = {"unzip", "-j", "/home/meizee/Documents/SISOP/SHIFT 2/Fylm.zip", "-d", "/home/meizee/Documents/SISOP/SHIFT 2/Fylm", NULL};
                execv("/usr/bin/unzip", argv2);
            }
        }
        
        else {
        // this is parent
            while ((wait(&status2)) > 0);
                sleep(2);
                //remove all zip
                char *argv2[] = {"/bin/rm", "Pyoto.zip", "Musyik.zip", "Fylm.zip", NULL};
                execv("/usr/bin/rm", argv2);
        }
    }

    else {
    // this is parent
        while ((wait(&status)) > 0);
        sleep(2);
        //zip semua
        char *argv2[] = {"/bin/zip", "-rm", "/home/meizee/Documents/SISOP/SHIFT 2/Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
        execv("/usr/bin/zip", argv2);
    }
}