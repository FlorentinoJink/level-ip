#include "arp.h"
#include "util.h"

static struct arp_cache_entry arp_cache[ARP_CACHE_LEN];

void arp_init()
{
    memset(arp_cache, 0, ARP_CACHE_LEN * sizeof(struct arp_cache_entry));
}

void arp_incoming(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct arp_hdr *arphdr;
    struct arp_ipv4 *arp_payload;

    // int merge_flag = 0;

    arphdr = (struct arp_hdr *)hdr->payload;
    arphdr->hw_type = htons(arphdr->hw_type);
    arphdr->pro_type = htons(arphdr->pro_type);
    arphdr->opcode = htons(arphdr->opcode);

    if (arphdr->hw_type != ARP_ETHERNET)
    {
        eprint("Unsupported HW type\n");
        return;
    }
    if (arphdr->pro_type != ARP_IPV4)
    {
        eprint("Unsupported protocol type\n");
        return;
    }
    arp_payload = (struct arp_ipv4 *)arphdr->payload;

    update_arp_translation_table(arphdr, arp_payload);

    switch (arphdr->opcode)
    {
    case ARP_REQUEST:
        printf("ARP_REQUEST\n");
        break;
    default:
        eprint("Opcode not supported\n");
        break;
    }
}

int update_arp_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data)
{
    struct arp_cache_entry *entry;
    for (size_t i = 0; i < ARP_CACHE_LEN; ++i)
    {
        entry = &arp_cache[i];
        if (entry->state == ARP_FREE)
        {
            continue;
        }
        if (entry->hw_type == hdr->hw_type && entry->saddr == data->saddr)
        {
            memcpy(entry->smac, data->smac, 6);
            return 1;
        }
    }

    return 0;
}