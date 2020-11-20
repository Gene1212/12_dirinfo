#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void printdirectory()
{
    DIR *d;
    d = opendir("./");
    struct dirent *entry;
    entry = readdir(d);

    struct stat b;
    stat("./", &b);

    printf("Statistics for directory: %s\n", entry->d_name);
    printf("Total Directory Size: %ld bytes\n", b.st_size);

    printf("Directories:\n");


    while (entry != NULL)
    {
        
        if (entry->d_type == DT_DIR)
        {
           printf("%s\n",entry->d_name);
        }
        entry = readdir(d);
    }

    printf("\n");
    rewinddir(d);
    entry= readdir(d);

    printf("Regular Files:\n");
    while (entry != NULL)
    {
        if (entry->d_type == DT_REG){
            printf("%s\n",entry->d_name);
        }
        entry=readdir(d);
    }
    

    closedir(d);
}

int main()
{

    printdirectory();
    return 0;
}