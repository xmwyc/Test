#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
static void getMemInfo()
{
    char buffer[1024];
    size_t numFound = 0;

    int fd = open("/proc/meminfo", O_RDONLY | O_CLOEXEC);

    if (fd < 0) {
        printf("Unable to open /proc/meminfo: %s\n", strerror(errno));
        return;
    }

    int len = read(fd, buffer, sizeof(buffer)-1);
    close(fd);

    if (len < 0) {
        printf("Empty /proc/meminfo");
        return;
    }
    buffer[len] = 0;

    static const char* const tags[] = {
            "MemTotal:",
            "MemFree:",
            NULL
    };
    static const int tagsLen[] = {
            9,
            8,
            0
    };
    long mem[] = { 0, 0, 0 };

    char* p = buffer;
    while (*p && numFound < (sizeof(tagsLen) / sizeof(tagsLen[0]))) {
        int i = 0;
        while (tags[i]) {
            if (strncmp(p, tags[i], tagsLen[i]) == 0) {
                p += tagsLen[i];
                while (*p == ' ') p++;
                char* num = p;
                while (*p >= '0' && *p <= '9') p++;
                if (*p != 0) {
                    *p = 0;
                    p++;
                }
                mem[i] = atoll(num);
                numFound++;
                break;
            }
            i++;
        }
        while (*p && *p != '\n') {
            p++;
        }
        if (*p) p++;
    }
	printf("MemTotal: %10ld KB\nMemFree:  %10ld KB\n",mem[0],mem[1]);
}

int main(){
	getMemInfo();
	return 0;
}
