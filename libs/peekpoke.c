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
    unsigned page_addr, page_offset, result;
    unsigned page_size = sysconf(_SC_PAGESIZE);

    fd = open("/dev/mem", O_RDONLY);
    if (fd < 1) {
        perror("peekpoke: unable to open /dev/mem");
        exit(EXIT_FAILURE);
    }

    page_addr = (addr & ~(page_size - 1));
    page_offset = addr - page_addr;

    ptr = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, (addr & ~(page_size - 1)));
    if (ptr == (void*) -1) {
        perror("peekpoke: unable to map memory");
        exit(EXIT_FAILURE);
    }

    result = *((unsigned *)(ptr + page_offset));

    if (munmap(ptr, page_size) < 0) {
        perror("peekpoke: unable to unmap memory");
        exit(EXIT_FAILURE);
    }

    if (close(fd) < 0) {
        perror("peekpoke: unable to close /dev/mem");
        exit(EXIT_FAILURE);
    }

    return result;
}

void poke(unsigned addr, unsigned value)
{
    int fd;
    void *ptr;
    unsigned page_addr, page_offset;
    unsigned page_size = sysconf(_SC_PAGESIZE);

    fd = open("/dev/mem", O_RDWR);
    if (fd < 1) {
        perror("peekpoke: unable to open /dev/mem");
        exit(EXIT_FAILURE);
    }

    page_addr = (addr & ~(page_size - 1));
    page_offset = addr - page_addr;

    ptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (addr & ~(page_size - 1)));
    if (ptr == (void*) -1) {
        perror("peekpoke: unable to map memory");
        exit(EXIT_FAILURE);
    }

    *((unsigned *)(ptr + page_offset)) = value;

    if (munmap(ptr, page_size) < 0) {
        perror("peekpoke: unable to unmap memory");
        exit(EXIT_FAILURE);
    }

    if (close(fd) < 0) {
        perror("peekpoke: unable to close /dev/mem");
        exit(EXIT_FAILURE);
    }
}