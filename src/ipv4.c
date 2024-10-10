#include "ipv4.h"

void ipv4_incoming(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;
    iphdr->len = ntohs(iphdr->len);
    iphdr->id = ntohs(iphdr->id);
    iphdr->flags = ntohs(iphdr->flags);
    iphdr->csum = ntohs(iphdr->csum);
    iphdr->saddr = ntohs(iphdr->saddr);
    iphdr->daddr = ntohs(iphdr->daddr);
    printf("ipv4 package len: %d\n", iphdr->len);
}