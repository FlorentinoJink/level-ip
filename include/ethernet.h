
struct eth_hdr
{
    unsigned char dmac[6];
    unsigned char smac[6];
    short ethertype;
    unsigned char payload[];
} __attribute__((packed));

struct eth_hdr *init_eth_hdr(char *buf);

void print_eth_hdr(struct eth_hdr *hdr);