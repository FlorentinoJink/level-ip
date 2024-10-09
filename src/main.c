#include "syshead.h"
#include "basic.h"
#include "tuntap_if.h"
#include "util.h"
#include "ethernet.h"
#include "arp.h"
#include "netdev.h"

#define BUFFSIZE 100

void handle_frame(struct netdev *netdev, struct eth_hdr *hdr)
{
    switch (hdr->ethertype)
    {
    case ETH_P_ARP:
        arp_incoming(netdev, hdr);
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
    char buf[BUFFSIZE];
    char *dev = calloc(10, 1);
    struct netdev netdev;
    CLEAR(buf);
    tun_init(dev);
    netdev_init(&netdev, "10.0.0.4", "00:0c:29:6d:50:25");
    arp_init();
    while (1)
    {
        if (tun_read(buf, BUFFSIZE) < 0) {
            eprint("ERR: Read from tun_fd: %s\n", strerror(errno));
        }

        struct eth_hdr *eth_hdr = init_eth_hdr(buf);

        handle_frame(&netdev, eth_hdr);
    }

    free(dev);
}
