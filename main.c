#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    char buffer[150];
    int check;
    DIR *d;
    char *remover;
    struct dirent *entry;

    if (argv[1] != NULL)
    {
        check = open(argv[1], O_RDONLY);
        if (check == -1)
        {
            printf("%s\n", strerror(errno));
            return 0;
        }

        else
        {
            d = opendir(argv[1]);
            entry = readdir(d);
            printf("Statistics for directory: %s\n", argv[1]);
        }
    }
    else
    {
        printf("Type in the directory: \n");
        fgets(buffer, sizeof(buffer), stdin);
        remover = strchr(buffer, '\n');
        if (remover != NULL)
        {
            *remover = '\0';
        }
        check = open(buffer, O_RDONLY);
        if (check == -1)
        {
            printf("%s\n", strerror(errno));
            return 0;
        }
        else
        {
            d = opendir(buffer);
            entry = readdir(d);
        }
    }

    struct stat b;

    if (argv[1] != NULL)
        stat(argv[1], &b);
    else
    {
        stat(buffer, &b);
    }

    printf("\n");
    if (argv[1] == NULL)
        printf("Statistics for directory: %s\n", buffer);
    printf("Total Directory Size: %ld bytes\n", b.st_size);

    printf("Directories:\n");

    while (entry != NULL)
    {

        if (entry->d_type == DT_DIR)
        {
            printf("%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    printf("\n");
    rewinddir(d);
    entry = readdir(d);

    printf("Regular Files:\n");
    while (entry != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            printf("%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    closedir(d);

    return 0;
}
