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
#include <sys/wait.h>

void killer(char mode[])
{
    FILE *fp;
    fp = fopen("killer.sh", "w");

    if (strcmp(mode, "-z") == 0)
    {
        fprintf(fp, "#!/bin/bash\nkillall soal3");
    }
    else if (strcmp(mode, "-x") == 0)
    {
        fprintf(fp, "#!/bin/bash\nkill %d", getpid());
    }

    fprintf(fp, "\nrm $0\n");

    fclose(fp);
}

void cipher(char text[], int key)
{
    char letter;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        letter = text[i];

        if (letter >= 'A' && letter <= 'Z')
        {
            letter = letter + key;

            if (letter > 'Z')
            {
                letter = letter - 'Z' + 'A' - 1;
            }

            text[i] = letter;
        } else if (letter >= 'a' && letter <= 'z')
        {
            letter = letter + key;

            if (letter > 'z')
            {
                letter = letter - 'z' + 'a' - 1;
            }

            text[i] = letter;
        }
    }
}

int main(int argc, char *argv[])
{
    pid_t pid, sid; // Variabel untuk menyimpan PID

    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    // if ((chdir("/")) < 0)
    // {
    //     exit(EXIT_FAILURE);
    // }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    killer(argv[1]);

    while (1)
    {
        pid_t child_id;
        int status;

        char path[] = "/home/hasna/sisop/praktikum2/";
        char rootPath[100];
        strcpy(rootPath, path);

        time_t rawtime = time(NULL);
        struct tm *tm_time = localtime(&rawtime);
        
        char now_folder[80];
        char now_folder_fix[80];

        // YYYY-mm-dd_HH:ii:ss].
        strftime(now_folder, 80, "%Y-%m-%d_%H:%M:%S", tm_time);
        strcpy(now_folder_fix, now_folder);

        strcat(path, now_folder); // path = ~/sisop/praktikum2/YYYY-MM-DD_HH:MM:SS

        child_id = fork();

        if (child_id < 0)
        {
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }

        if (child_id == 0)
        {
            if (fork() == 0)
            {
                char *argv[] = {"mkdir", path, NULL};
                execv("/bin/mkdir", argv);
            }
            else
            {
                while ((wait(&status)) > 0)
                    ;
                int count = 10;
                while (count)
                {
                    if (fork() == 0)
                    {

                        rawtime = time(NULL);
                        tm_time = localtime(&rawtime);
                        char now_pict[80];

                        // YYYY-mm-dd_HH:ii:ss].
                        strftime(now_pict, 80, "%Y-%m-%d_%H:%M:%S", tm_time);

                        char downloadLink[200];

                        sprintf(downloadLink, "https://picsum.photos/%ld", ((rawtime % 1000) + 100));

                        chdir(path);
                        char *argv[] = {"wget", "-qO", now_pict, downloadLink, NULL};
                        execv("/usr/bin/wget", argv);
                    }
                    count--;
                    sleep(5);
                }

                chdir(path);
                FILE *fp1 = fopen("status.txt", "w");
                char message[] = "Download Success";
                cipher(message, 5);
                fprintf(fp1, "%s", message);
                fclose(fp1);

                chdir(rootPath);
                char *argv[] = {"zip", "-rm", now_folder_fix, now_folder_fix, NULL};
                execv("/usr/bin/zip", argv);
            }
        }
        else
        {
            sleep(40);
        }
    }
}
