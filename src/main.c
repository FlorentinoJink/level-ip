#include "syshead.h"
#include "basic.h"
#include "tuntap_if.h"
#include "util.h"
#include "ethernet.h"
#include "arp.h"

#define BUFFSIZE 100

void handle_frame(struct eth_hdr *hdr)
{
    switch (hdr->ethertype)
    {
    case ETH_P_ARP:
        arp_incoming(hdr);
        break;
    case ETH_P_IP:
        printf("Found Ipv4\n");
        break;
    case ETH_P_IPV6:
        printf("Found Ipv6\n");
        break;
    default:
        printf("Unrecongnized ethertype: %x\n",hdr->ethertype);
        break;
    }
}

int main(int argc, char **argv)
{
    int tun_fd;
    char buf[BUFFSIZE];
    char *dev = calloc(10, 1);
    CLEAR(buf);
    tun_fd = tun_alloc(dev);

    if (set_if_up(dev) != 0)
    {
        eprint("ERROR when setting up if\n");
    }

    // if (set_if_address(dev, "10.0.0.5/24") != 0) {
    //     eprint("ERROR when setting address for if\n");
    // };

    if (set_if_route(dev, "10.0.0.0/24") != 0)
    {
        eprint("ERROR when setting route for if\n");
    }
    while (1)
    {
        read(tun_fd, buf, BUFFSIZE);
        hex_dump(buf, BUFFSIZE);
        struct eth_hdr *eth_hdr = init_eth_hdr(buf);
        handle_frame(eth_hdr);
        // print_eth_hdr(eth_hdr);
    }

    free(dev);
}
