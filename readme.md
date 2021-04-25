# soal-shift-sisop-modul-2-A07-2021

Soal Shift Modul 2 |  Sistem Operasi 2021

1. Zahra Dyah Meilani 05111940000069
2. Ghifari Astaudi' Ukmullah 05111940000012
3. Fairuz Hasna Rofifah 05111940000003

## **1. Ulang Tahun Stevany**
> Source Code 
 > **[soal1.c](https://github.com/hasnarof/soal-shift-sisop-modul-2-A07-2021/blob/main/soal1/soal1.c)**
 
>"Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing sesuai extensi."

Karena di soal disebutkan bahwa semua proses di soal nomor 1 merupakan proses di latar belakang, maka permasalahan ini dapat diselesaikan dengan menggunakan Proses Daemon. 

```C
pid_t pid, sid;        // Variabel untuk menyimpan PID

pid = fork();     // Menyimpan PID dari Child Process
if (pid < 0) {
    exit(EXIT_FAILURE);
}
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
    
}
```

Di dalam iterasi `while` proses daemon, proses dibagi menjadi dua kondisi, yaitu 
1. Saat enam jam sebelum waktu ulang tahun Stevany (9 April 2021, 16:22) 
   
   Di dalam proses ini terjadi proses sebagai berikut secara berurutan:
   - Membuat folder Pyoto, Musyik, dan Fylm
   - Mendownload file zip sesuai link dengan wget
   - Jika kedua proses tersebut selesai, maka ditandai dengan `flag=1`, dan kemudian lanjut ke proses berikutnya
   - Jika `flag=1` maka proses akan lanjut untuk mengekstrak isi dari ZIP file tersebut dan memindahkannya sesuai format file ke folder Pyoto untuk .jpg, Musyik untuk .mp3, dan Fylm untuk .mp4.
   - Jika semua proses sudah selesai maka akan diberi flag `entered` diberi nilai 1.
2. Saat waktu ulang tahun Stevany (9 April 2021, 22:22) 
   
   Proses ini merupakan proses terakhir yaitu untuk mengkompres folder Pyoto, Musyik, dan Fylm menjadi satu file ZIP yang diberi nama Lopyu_Stevany.zip. Setelah dikompres, ketiga folder tersebut dihapus sehingga hanya menyisakan file ZIP saja.

Inisiasi variabel-variabel yang dibutuhkan sebagai waktu:

```C
time_t currTime = time(NULL);
int day = 9;
int month = 4;
int hour = 22;
int min = 22;
struct tm tmp = *localtime(&currTime);
```

Struktur proses berdasarkan dua kondisi waktu: 
```C
//6 jam sebelum ulang tahun Stevany
if(tmp.tm_mday == day && tmp.tm_mon+1 == month && tmp.tm_hour == (hour-6) && tmp.tm_min == min && entered == 0){
    //PROSES KONDISI 1
}

//ulang tahun Stevany
else if(tmp.tm_mday == day && tmp.tm_mon+1 == month && tmp.tm_hour == hour && tmp.tm_min == min && entered2 ==0){
    //PROSES KONDISI 2
}       
```               
### **Proses Kondisi 1:**
### **a. Membuat Folder**

>"Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg."

Untuk membuat folder bisa dilakukan dengan konsep fork dan exec dengan iterasi sebanyak 3 kali. Di child process akan melakukan pembuatan folder dengan `mkdir`. Setelah itu membuat iterasi lagi yang berfungsi untuk menunggu setiap child proccess selesai dengan fungsi `waitpid`. Berikut ini merupakan kodenya:


```C
pid_t child_id, wpid;
int j;

//nama folder yang akan dibuat
char *folder[3] = {"Pyoto", "Musyik", "Fylm"};

for(j=0; j<3; j++){
                    
    if((child_id=fork())==0){
        char *argv[] = {"mkdir", folder[j], NULL};
        execv("/usr/bin/mkdir", argv);
    }
}
for(j=0; j<3; j++){
    waitpid(-1, NULL, 0);
}
````

### **b. Men-download File ZIP**

>"Untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :)."

Untuk men-download file ZIP bisa dilakukan dengan konsep fork dan exec dengan iterasi sebanyak 3 kali. Di child process akan melakukan download file yang link-nya tersimpan di `char *link` dengan command `wget` dan beberapa argumen yang diperlukan. Hasil download akan disimpan dengan nama yang sudah ditentukan pada variabel `zip` Setelah itu membuat iterasi lagi yang berfungsi untuk menunggu setiap child proccess selesai dengan fungsi `waitpid`. Berikut ini merupakan kodenya:

```C
pid_t child_id2, wpid2;
int k;

//link
char *link[3] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};

//nama file output hasil download
char *zip[3] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};

for(k=0; k<3; k++){                    
    if((child_id2=fork())==0){
        char *argv[] = {"wget", "-U", "firefox", "-q", "--no-check-certificate", link[k], "-O", zip[k], NULL};
        execv("/usr/bin/wget", argv);
    }
}

for(k=0; k<3; k++){
    waitpid(-1, NULL, 0);
}
```

Screenshot:
![1ab](Screenshot/ss%20soal1/1ab.png)

### **c dan d. Ekstrak ZIP dan Memindahkannya**

>"Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload serta memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan)."

Untuk mengekstrak dan memindahkan file ZIP bisa dilakukan dengan konsep fork dan exec dengan iterasi sebanyak 3 kali. Di child process akan melakukan ekstraksi dengan `unzip` dan beberapa argumen lain. Argumen `-j` berfungsi untuk mengekstrak zip tanpa membuat direktori baru (atau mengabaikan direktori di dalam file zip tersebut). Selanjutnya, `-d` berfungsi untuk menyimpannya di path folder yang diinginkan (path tiga folder yang tadi sudah dibuat). Setelah itu membuat iterasi lagi yang berfungsi untuk menunggu setiap child proccess selesai dengan fungsi `waitpid`. Berikut ini merupakan kodenya:

```C
pid_t child_id3;
int i;

//path dari file zip yang akan di-unzip
char *tzip[3] = {"/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Foto_for_Stevany.zip", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Musik_for_Stevany.zip", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Film_for_Stevany.zip"};

//path folder yang akan diisi oleh konten dari hasil unzip
char *tfolder[3] = {"/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Pyoto", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Musyik", "/home/meizee/Documents/git_env/soal-shift-sisop-modul-2-A07-2021/soal1/Fylm"}; 

for(i=0; i<3; i++){
    if((child_id3=fork())==0){
    char *argv2[] = {"unzip", "-j", tzip[i], "-d", tfolder[i], NULL};
    execv("/usr/bin/unzip", argv2);
    }
}

for(i=0; i<3; i++){
    waitpid(-1, NULL, 0);
}
```

Screenshot:
![1cd](Screenshot/ss%20soal1/1cd.png)

Isi dari folder-folder:
> [Pyoto](Screenshot/ss%20soal1/isi%20pyoto.png)

> [Musyik](Screenshot/ss%20soal1/isi%20pyoto.png)

> [Fylm](Screenshot/ss%20soal1/isi%20fylm.png)

### **Proses Kondisi 2:**
### **e. dan f. Otomatisasi Program dan ZIP Semua Folder**

>"Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany. Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete (sehingga hanya menyisakan .zip)."

Untuk membuat zip dari ketiga folder tadi digunakan command `zip`. Argumen `-rm` berfungsi untuk menghapus ketiga folder yang telah di zip.


```C
else if(tmp.tm_mday == day && tmp.tm_mon+1 == month && tmp.tm_hour == hour && tmp.tm_min == min && entered2 ==0){
    char *argv2[] = {"/bin/zip", "-rm", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv2);
}
```

Screenshot:
![1f](Screenshot/ss%20soal1/1ef%20(2).png)

Isi ZIP:
![isizip](Screenshot/ss%20soal1/isi%20lopyu%20stevany.png)

### **Kendala**
- Sempat mengalami error tidak bisa mendownload file dengan wget. Di awal berpikir jika codingan salah, ternyata codingan tidak salah, tetapi memang sepertinya perintah download ditolak oleh server, setelah dicoba langsung di terminal menggunakan command wget tersebut juga tidak bisa mendownload karena ERROR 403: Forbidden. Akhirnya saya mencari cara mengatasinya yaitu dengan menambahkan argumen `"-U", "firefox"`.
  
  ![error](Screenshot/ss%20soal1/error%20(2).jpeg)

- Sempat error karena lupa belum memberi fungsi `waitpid` supaya parent process menunggu semua child process selesai.
  
- Date di Linux tidak mau berubah, ternyata butuh konfigurasi di OS Host (Windows) sebelum mengubah date di Virtual Machine dengan `sudo date --set`.

### **Referensi**
- https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
- https://stackoverflow.com/questions/23204128/waiting-for-all-children-with-waitpid-option-wall
- https://stackoverflow.com/questions/19461744/how-to-make-parent-wait-for-all-child-processes-to-finish
- https://www.linuxquestions.org/questions/linux-software-2/wget-error-403-can-i-get-around-this-606755/
- https://unix.stackexchange.com/questions/72838/unzip-file-contents-but-without-creating-archive-folder
- https://www.unix.com/shell-programming-and-scripting/169967-zip-files-deleting-originals.html
- https://askubuntu.com/questions/35566/how-do-i-manually-set-the-system-time-in-virtualbox/331871#331871

## Soal No.2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.


Jawab:
Pada persoalan nomer 2a, diminta untuk mengunzip file pets.zip, untuk menjawab persoalan ini menggunakan ```fork x exec``` dengan menggunakan fungsi ardu sebagai berikut
```
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
```
Fungsi ardu ini digunakan untuk memanggil  ```fork x exec ``` berkali-kali. Selanjutnya, untuk mengunzipnya sebagai berikut:
```
  char *argv[]={"unzip", "-q","/home/ghifari/modul2/petshop/pets.zip","-d", "/home/ghifari/modul2/petshop", NULL};
   ardu("/usr/bin/unzip", argv);
```
Karena terdapat folder yang tidak penting maka kita harus menghapus folder tersebut, maka harus bisa membedakan yang mana file dan folder. Sebelum itu, digunakan fungsi wait() untuk menunggu proses unzipnya benar-benar selesai. 
```while((wait(&status))>0);;
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
```
## Penjelasan souce code diatas
Pertama yang dilakukan adalah membuka directory yang akan di tuju yaitu  “/home/[user]/modul2/petshop”, kemudian menggunakan ```struct stat``` untuk mengetahui tentang file atau folder, untuk melacak folder maka menggunakan ```(S_ISDIR(statbuf.st_mode))```, setelah itu inisiasi sub foldernya dan buka sub folder tersebut. Kemudian, kita hapus menggunakan fungsi remove(), dan tutup sub directorynya menggunakan fungsi closedir, karena file di sub directory kosong maka kita dapat menghapus folder menggunakan fungsi rmdir(), dan menutup directorynya.

b. Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.

```
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
```
### Penjelasan source codenya
Pertama yang dilakukan adalah menunggu proses menghapus folder sampai selesai menggunakan fungsi wait, kemudian membuka directory yang akan di tuju yaitu  “/home/[user]/modul2/petshop”, kemudian mencari file yang hanya ```.jpg``` menggunakan strstr(), kemudian menggunakan strstok() unutk membagi string menjadi beberapa bagian yang dibatasi oleh karakter ";", sehingga didapatkan string yang berisi nama2 hewan, string tersebut akan dibuatkan folder dengan menggunakan fungsi ardu untuk memanggil fork x exec dan menggunakan mkdir, kemudian menutup directorynya.

c. Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
        while(wait(&status2) > 0);
```       
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
			...
``` 
### Penjelasan Source code
Untuk menjawab soal nomer c ini, pertama program akan membuka directory ``` “/home/[user]/modul2/petshop”```, kemudian mengcopy nama string file atau foleder menggunakan ``` strcpy(file2,eeentry->d_name)```, selanjutnya adalah mencari file2 dengan format ``` jpg```  dan bukan ``` _ ``` menggunakan strstr.  Lalu, membagi filenya ke dalam beberapa string secara manual dengan menggunakan strtok,strcat dan strcpy sampai selesai, untuk pembagian string ini terdiri atas jenis hewan, nama hewan, dan umur. Selanjutnya, file akan di copy ke folder jenis hewan, dengan format namahewan.jpg

d. Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. 
     while(wait(&status) > 0);
               
```        ...             
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
		    ...
           
           }
           closedir(diir);
}
}
```
### Penjelasan Program
Setelah menjalankan program no c, selanjutnya program akan mencari mencari file2 dengan format ``` jpg```  dan ``` _ ``` menggunakan strstr, Lalu, membagi filenya ke dalam beberapa string secara manual dengan menggunakan strtok,strcat dan strcpy, untuk pembagian string ini terdiri atas jenis hewan, nama hewan, dan umur, jenis hewan2, nama2, dan umur2. Selanjutnya, file akan di copy ke folder jenis hewan1 dan jenis hewam2, dengan format namahewan1.jpg dan namahewan2.jpg

e. Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
```         	char susah[400];
                sprintf(susah, "/home/ghifari/modul2/petshop/%s/keterangan.txt", nama);
                FILE *angel=fopen(susah, "a+");
                fprintf(angel, "nama : %s\n", settingan);
                fprintf(angel, "umur : %s tahun\n\n", settingan2);
                fclose(angel);
```
```
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
```
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
			...
``` 
### Penjelasan Source code
Untuk menjawab soal nomer c ini, pertama program akan membuka directory ``` “/home/[user]/modul2/petshop”```, kemudian mengcopy nama string file atau foleder menggunakan ``` strcpy(file2,eeentry->d_name)```, selanjutnya adalah mencari file2 dengan format ``` jpg```  dan bukan ``` _ ``` menggunakan strstr.  Lalu, membagi filenya ke dalam beberapa string secara manual dengan menggunakan strtok,strcat dan strcpy sampai selesai, untuk pembagian string ini terdiri atas jenis hewan, nama hewan, dan umur. Selanjutnya, file akan di copy ke folder jenis hewan, dengan format namahewan.jpg

d. Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. 
     while(wait(&status) > 0);
               
```        ...             
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
		    ...
           
           }
           closedir(diir);
}
}
```
### Penjelasan Program
Setelah menjalankan program no c, selanjutnya program akan mencari mencari file2 dengan format ``` jpg```  dan ``` _ ``` menggunakan strstr, Lalu, membagi filenya ke dalam beberapa string secara manual dengan menggunakan strtok,strcat dan strcpy, untuk pembagian string ini terdiri atas jenis hewan, nama hewan, dan umur, jenis hewan2, nama2, dan umur2. Selanjutnya, file akan di copy ke folder jenis hewan1 dan jenis hewam2, dengan format namahewan1.jpg dan namahewan2.jpg

e. Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut. Format harus sesuai contoh.
## 1
```		...
		if(strstr(file2,".jpg") && !(strstr(file2,"_"))){
		...
		char susah[400];
                sprintf(susah, "/home/ghifari/modul2/petshop/%s/keterangan.txt", nama);
                FILE *angel=fopen(susah, "a+");
                fprintf(angel, "nama : %s\n", settingan);
                fprintf(angel, "umur : %s tahun\n\n", settingan2);
                fclose(angel);
		...
```
## 2
```
		...
		if(strstr(file2,".jpg") && (strstr(file2,"_"))){
		...
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
```
### Penjelasan Program

Untuk program diatas, pertama membuat keterangan.txt di folder hewan, kemudian membuka keterangan.txt sekaligus menambahkan keterangan berupa nama dan umurnya dengan fungsi ```fopen(const char *filename,a+)``` dan  ```fprintf() ``` untuk menambahkan keterangan. Untuk program pertama, untuk file yang tanpa char ``` _``` 
dan program kedua file yang tanpa char ``` _``` maka dibutuhkan dua kali inisiasi untuk jenis hewan yang berbeda.

### Kendala
Program c harus berada di file petshop, kemudian tidak dapat menghapus file ``.jpg`` karena program c berada di file tersebut dengan error segmentation fault core dumped.

### Referensi
- https://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c
- https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

## **Soal No 3: Pekerjaan Magang Ranora**

> Source Code  **[soal3.c](https://github.com/hasnarof/soal-shift-sisop-modul-2-A07-2021/blob/main/soal3/soal3.c)**
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini

    sleep(30);
  }
}
```
Code di atas adalah langkah-langkah untuk membuat daemon.
```c
		pid_t child_id;
        int status;

        char path[] = "/home/hasna/sisop/praktikum2/";
        char rootPath[100];
        strcpy(rootPath, path);

        time_t rawtime = time(NULL);
        struct tm *tm_time = localtime(&rawtime);
```
Pertama, kita ingin membuat folder dengan nama folder adalah timestamp. Fungsi `time()` mereturn banyak waktu sejak 00:00:00 UTC, January 1, 1970 (Unix timestamp) dalam detik dan disimpan pada `rawtime`. Kemudian, kita format waktu `rawtime` menjadi jam lokal yang biasa kita lihat dengan fungsi `localtime()`. `struct tm` ini memudahkan kita untuk memformat jam sesuai keinginan kita.
```c        
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
```
Kemudian, kita taruh hasil timestamp pada string `now_folder`. Sehingga nama folder adalah timestamp. Kemudian, gabungkan string `now_folder` ke string `path`. String `path` ini untuk membuat folder dengan dengan **mkdir**.

Tambahan: `now_folder_fix` ini akan dipakai nanti, karena `now_folder` nilainya sudah berubah setelah `strcat` ke `path`.

Kemudian kita membuat **child process**. Karena child berjalan duluan, maka child kita gunakan untuk mengeksekusi `mkdir`. Bisa dilihat di sini kita `fork()` dua kali karena kita butuh beberapa cabang untuk melaksanakan beberapa eksekusi **execv** (sehabis `execv`, process akan selesai, oleh karena itu membutuhkan child untuk program tetap berjalan sesuai keinginan kita). Proses child ditandai jika hasil return `fork()` adalah 0.
```c
            else
            {
                while ((wait(&status)) > 0)
                    ;
```
`while  ((wait(&status))  >  0)` agar proses mendownload gambar tidak berjalan duluan sebelum membuat direktori.
```c
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
```
Kemudian kita mendownload 10 gambar untuk setiap 1 direktori. Buat waktu lagi seperti cara sebelumnya untuk nama file gambar.
```c
                        char downloadLink[200];

                        sprintf(downloadLink, "https://picsum.photos/%ld", ((rawtime % 1000) + 100));
```
Taruh link download pada `downloadLink`. Tambah juga `((rawtime % 1000) + 100))` pada `downloadLink` karena kita ingin mendownload gambar dengan ukuran sebesar `((rawtime % 1000) + 100))` pixel. rawtime adalah banyak waktu dalam Unix timestamp.
```c
                        chdir(path);
                        char *argv[] = {"wget", "-qO", now_pict, downloadLink, NULL};
                        execv("/usr/bin/wget", argv);
                    }
                    count--;
                    sleep(5);
                }
```

Kemudian `execv` `wget`. Argumen `-q0` untuk menamai hasil downloadan dengan nama `now_pict`. `sleep(5)` untuk agar mendownload setiap 5 detik.

```c

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
```
Setelah download gambar, **chdir** ke folder direktori yang berisi 10 gambar itu, dan buat status.txt berisi "Download Success" yang sudah dienkripsi memakai fungsi `cipher`. Kemudian, eksekusi `execv zip`.
```c
        }
        else
        {
            sleep(40);
        }
```
`sleep(40)` untuk membuat direktori setiap 40 detik.
```c
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
```
Ini adalah fungsi untuk mengenkripsi dengan sandi cipher. Setiap huruf digeser sebanyak `key` ke depan. Jika sudah melewati batas Z atau z, balik lagi dari A atau a.
```c
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
```
Ini adalah fungsi killer yang cara memanggilnya seperti berikut (line 95).
```c
killer(argv[1]);
```
Jadi misal ketika menjalankan hasil compile-an program dengan argumen `-z` maka akan membuat script shell `killall soal3` yang artinya memberhentikan semua proses dari compile soal3, jika argumennya `-x` akan membuat script shell `kill < pid >` , yaitu pid yang sekarang, sehingga dapat melanjutkan proses parent nya (melanjutkan proses sampai selesai zip dan menghapus direktori). `fprintf(fp,  "\nrm $0\n");`agar setelah menjalankan bash, shell script akan terhapus sendiri.
### Kendala
- saat zip mengalami kendala tidak bisa zip. Ternyata typo code `execv("/user/bin/zip", argv);`
- saat wget mengalami kendala tidak dapat mendownload dengan pixel yang diinginkan. Setelah dicoba-coba, sepertinya masalahnya ada di argumen yang memakai variabel `now_folder` yang telah berubah value nya. Jadi diakali dengan `chdir` saja.
### Screenshot
#### 3a
![3a](Screenshot/ss-soal-3/3a.png)
#### 3b
![3b](Screenshot/ss-soal-3/3b.png)
#### 3c
![3c](Screenshot/ss-soal-3/3c.png)
#### 3d
![3d](Screenshot/ss-soal-3/3d.png)
#### 3e
![3e](Screenshot/ss-soal-3/3e.png)