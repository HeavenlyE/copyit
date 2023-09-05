#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include <string.h>

int main(int argc, char **argv){

    int errnum;
    int readFile, writeFile, bytesRead, totalBytes;
    char *buffer = malloc(1000 * sizeof(char));

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

    //opening the two files and handling errors
    readFile = open(argv[1],O_RDONLY);
    if(readFile < 0){
        printf(openingErr, argv[0], argv[1], strerror(errno));
        exit(1);
    }
    printf("Read file opened %d\n", readFile);

    writeFile = open(argv[2], O_WRONLY);
    if(writeFile < 0){
        printf(openingErr, argv[0], argv[2], strerror(errno));
        exit(1);
    }
    printf("Write file opened %d\n",writeFile);

    do{
        if(bytesRead = read(readFile,buffer,1000) < 0){
            printf("%s: error reading from %s, %s\n", argv[0], argv[1],strerror(errno));
            exit(1);
        }
        printf("Read\n");

        if(write(0, buffer,bytesRead) < 0){
            printf("%s: error writing to %s, %s\n", argv[0], argv[2],strerror(errno));
            exit(1);
        }
        printf("Write\n");
    }while(bytesRead > 0);


    if(close(readFile) < 0){
        printf("copyit: couldn't close file: %s\n", strerror);
        exit(1);
    }else{
        printf("File %s closed successfully\n", argv[1]);
    }
    if(close(writeFile) < 0){
        printf("copyit: couldn't close file: %s\n", strerror);
        exit(1);
    }else{
        printf("File %s closed successfully\n", argv[2]);
    }


}