#include "ipv4.h"
#include "icmpv4.h"

void ipv4_incoming(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;
    iphdr->len = ntohs(iphdr->len);
    iphdr->id = ntohs(iphdr->id);
    iphdr->flags = ntohs(iphdr->flags);
    iphdr->csum = ntohs(iphdr->csum);
    iphdr->saddr = ntohs(iphdr->saddr);
    iphdr->daddr = ntohs(iphdr->daddr);
    
    if (iphdr->ihl < 5)
    {
        perror("IPv4 header length must be at least 5\n");
        return;
    }
    if (iphdr->ttl == 0)
    {
        perror("Time to live of datagram reached 0\n");
        return;
    }
    
    switch (iphdr->proto)
    {
    case ICMPV4:
        icmpv4_incoming(netdev, hdr);
        break;
    
    default:
        perror("Unknown IP header proto\n");
        break;
    }
    
}