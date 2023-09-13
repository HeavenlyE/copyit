

void handler(int signum){
    printf("copyit: is still copying...\n");
    alarm(1);
}

int main(int argc, char **argv){

    signal(SIGALRM,handler);
    alarm(1);
    int errnum;
    int readDir, writeDir, bytesRead, totalBytes;
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

}