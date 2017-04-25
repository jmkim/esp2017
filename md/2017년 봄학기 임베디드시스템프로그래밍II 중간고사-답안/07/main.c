#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#define FILEPATH "sample.txt"
#define FILESIZE 10

int main(int argc, char *argv[])
{
    int fd;
    char *map;  /* mmapped array of char's */

    fd = open(FILEPATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(1);
    }

    /* 주소 공간에 파일 매핑 */
    map = mmap(NULL, FILESIZE, PROT_READ, MAP_PRIVATE, fd, 0);
    if(map == (void *) -1) {
        perror("Error mapping 10 chars");
    } else {
#if 0
        printf("Memory mapped at address %p\n", map);
        printf("%s\n", map);
#endif
        /* 포인터 변수 map 이용하여 처음 10개 문자 화면에 출력 */
        int i;
        for(i = 0; i < 10; ++i) {
            putchar(map[i]);
        }
        putchar('\n');
    }

    if (munmap(map, FILESIZE) == -1) {
        perror("Error un-mmapping the file");
    }
    close(fd);
    return 0;
}
