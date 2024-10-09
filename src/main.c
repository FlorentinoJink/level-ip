#include "syshead.h"
#include "basic.h"
#include "tuntap_if.h"
#include "util.h"

#define BUFFSIZE 100

int main(int argc, char** argv) {
    int tun_fd;
    char buf[BUFFSIZE];
    char *dev = calloc(10, 1);
    CLEAR(buf);
    tun_fd = tun_alloc(dev);

    if (set_if_up(dev) != 0) {
        eprint("ERROR when setting up if\n");
    }

    // if (set_if_address(dev, "10.0.0.5/24") != 0) {
    //     eprint("ERROR when setting address for if\n");
    // };

    if (set_if_route(dev, "10.0.0.0/24") != 0) {
        eprint("ERROR when setting route for if\n");
    }

    while (1)
    {
        read(tun_fd, buf, BUFFSIZE);
        hex_dump(buf, BUFFSIZE);
    }
    
    free(dev);
}
