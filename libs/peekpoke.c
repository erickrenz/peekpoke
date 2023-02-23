#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "peekpoke.h"

unsigned peek(unsigned addr)
{
    int fd;
    void *ptr;
    unsigned page_addr, page_offset;
    unsigned page_size = sysconf(_SC_PAGESIZE);

    fd = open("/dev/mem", O_RDONLY);
    if (fd < 1)
    {
        exit(-1);
    }

    page_addr = (addr & ~(page_size - 1));
    page_offset = addr - page_addr;

    ptr = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, (addr & ~(page_size - 1)));
    if ((int)ptr == -1)
    {
        exit(-1);
    }

    return *((unsigned *)(ptr + page_offset));
}

int poke(unsigned addr, unsigned value)
{
    int fd;
    void *ptr;
    unsigned page_addr, page_offset;
    unsigned page_size = sysconf(_SC_PAGESIZE);

    fd = open("/dev/mem", O_RDWR);
    if (fd < 1)
    {
        exit(-1);
    }

    page_addr = (addr & ~(page_size - 1));
    page_offset = addr - page_addr;

    ptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (addr & ~(page_size - 1)));
    if ((int)ptr == -1)
    {
        exit(-1);
    }

    *((unsigned *)(ptr + page_offset)) = value;
    return 0;
}