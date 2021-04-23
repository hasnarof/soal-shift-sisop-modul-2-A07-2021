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
