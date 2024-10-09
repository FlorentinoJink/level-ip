#ifndef ARP_H_
#define ARP_H_
#include "syshead.h"
#include "ethernet.h"

#define ARP_ETHERNET    0x0001
#define ARP_IPV4        0x0800
#define ARP_REQUEST     0x0001

#define ARP_CACHE_LEN   32
#define ARP_FREE        0
#define ARP_WAITING     1
#define ARP_RESOLVED    2

struct arp_hdr 
{
    uint16_t hw_type;
    uint16_t pro_type;
    unsigned char hw_size;
    unsigned char pro_size;
    uint16_t opcode;
    unsigned char payload[];
} __attribute__((packed));

struct arp_ipv4
{
    unsigned char smac[6];
    unsigned char saddr[4];
    unsigned char dmac[6];
    unsigned char daddr[4];
} __attribute__((packed));


struct arp_cache_entry
{
    uint16_t hw_type;
    unsigned char saddr[4];
    unsigned char smac[6];
    unsigned int state;
} __attribute__((packed));

void arp_init();
void arp_incoming(int tun_fd, struct eth_hdr *hdr);
int update_arp_translation_table(struct arp_hdr *hdr, struct arp_ipv4* data);

#endif //ARP_H_