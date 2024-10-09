#ifndef TUNTAP_IF_H_
#define TUNTAP_IF_H_

// int set_if_route(char *dev, char *cidr);
// int set_if_address(char *dev, char *cidr);
// int set_if_up(char *dev);
// int tun_alloc(char *dev);

void tun_init(char *dev);
int tun_read(char* buf, int len);
int tun_write(char *buf, int len);

#endif // TUNTAP_IF_H_
