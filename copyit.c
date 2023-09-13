#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

void handler(int signum){
    printf("copyit: is still copying...\n");
    alarm(1);
}

int main(int argc, char **argv){
    
    signal(SIGALRM,handler);
    alarm(1);
    int errnum;
    int readFile, writeFile, bytesRead, totalBytes;
    char* buffer = (char*) malloc(1000 * sizeof(char));

    static char usage[] = "usage: %s <SourceFile> <TargetFile>\n";
    static char openingErr[] = "%s: couldn't open %s: %s\n";

    //checking is program is being called properyly
    if(argc < 3){
        printf("%s: Too little arguments!\n", argv[0]);
        printf(usage, argv[0]);
        exit(1);
    }else if (argc > 3){
        printf("%s: Too many arguments!\n", argv[0]);
        printf(usage, argv[0]);
        exit(1);
    }

    //opening the two files + error handling
    readFile = open(argv[1],O_RDONLY);
    if(readFile < 0){
        printf(openingErr, argv[0], argv[1], strerror(errno));
        exit(1);
    }

    //If the file does not exist if it is created then 0666 will give everyone permission to read and write.
    //0666 is the same as using "S_IRWXO | S_IRWXU | S_IRWXG"
    writeFile = open(argv[2], O_CREAT | O_RDWR, 0666);
    if(writeFile < 0){
        printf(openingErr, argv[0], argv[2], strerror(errno));
        exit(1);
    }

    //read-write loop and set total bytes read to 0 + error handling
    totalBytes = 0;
    do{
        bytesRead = read(readFile,buffer,1000);
        if(bytesRead < 0){
            printf("%s: error reading from %s, %s\n", argv[0], argv[1],strerror(errno));
            exit(1);
        }
        buffer[bytesRead] = '\0';

        if(write(writeFile, buffer, bytesRead) < 0){
            printf("%s: error writing to %s, %s\n", argv[0], argv[2],strerror(errno));
            exit(1);
        }
        totalBytes += bytesRead;
    }while(bytesRead > 0);

    //close the read and write files + error handling
    if(close(readFile) < 0){
        printf("copyit: couldn't close file: %s\n", strerror);
        exit(1);
    }
    if(close(writeFile) < 0){
        printf("copyit: couldn't close file: %s\n", strerror);
        exit(1);
    }

    printf("Bytes read: %d\n", totalBytes);


}