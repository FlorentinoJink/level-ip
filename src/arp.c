#include "arp.h"
#include "util.h"

static struct arp_cache_entry arp_cache[ARP_CACHE_LEN];

static int insert_arp_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data)
{
    struct arp_cache_entry *entry;
    for (size_t i = 0; i < ARP_CACHE_LEN; ++i)
    {
        entry = &arp_cache[i];
        if (entry->state == ARP_FREE)
        {
            entry->state = ARP_RESOLVED;
            entry->hw_type = hdr->hwtype;
            entry->sip = data->sip;
            memcpy(entry->smac, data->smac, sizeof(data->smac));
            return 0;
        }
    }
    return -1;
}

static int update_arp_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data)
{
    struct arp_cache_entry *entry;
    for (size_t i = 0; i < ARP_CACHE_LEN; ++i)
    {
        entry = &arp_cache[i];
        if (entry->state == ARP_FREE)
        {
            continue;
        }
        if (entry->hw_type == hdr->hwtype && entry->sip == data->sip)
        {
            memcpy(entry->smac, data->smac, 6);
            return 1;
        }
    }

    return 0;
}

void arp_init()
{
    memset(arp_cache, 0, ARP_CACHE_LEN * sizeof(struct arp_cache_entry));
}

void arp_incoming(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct arp_hdr *arphdr;
    struct arp_ipv4 *arpdata;

    int merge = 0;

    arphdr = (struct arp_hdr *)hdr->payload;
    arphdr->hwtype = ntohs(arphdr->hwtype);
    arphdr->protype = ntohs(arphdr->protype);
    arphdr->opcode = ntohs(arphdr->opcode);

    if (arphdr->hwtype != ARP_ETHERNET)
    {
        eprint("Unsupported HW type\n");
        return;
    }
    if (arphdr->protype != ARP_IPV4)
    {
        eprint("Unsupported protocol\n");
        return;
    }
    arpdata = (struct arp_ipv4 *)arphdr->data;

    merge = update_arp_translation_table(arphdr, arpdata);

    if (netdev->addr != arpdata->dip)
    {
        printf("ARP was not for us\n");
    }
    
    if (!merge && insert_arp_translation_table(arphdr, arpdata) != 0)
    {
       perror("ERR: No free space in ARP translation table\n"); 
    }

    switch (arphdr->opcode)
    {
    case ARP_REQUEST:
        break;
    default:
        eprint("Opcode not supported\n");
        break;
    }
}
