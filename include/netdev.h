#ifndef NETDEV_H_
#define NETDEV_H_

#include "syshead.h"

struct netdev
{
    uint32_t addr;
    unsigned char hwaddr[6];
};

void netdev_init(struct netdev *dev, char *addr, char *hwaddr);

#endif // NETDEV_H_