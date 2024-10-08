#ifndef UTILS_H_
#define UTILS_H_

#define CMDBUFLEN 100

int run_cmd(char *cmd, ...);
void hex_dump(char* str, size_t len);
void eprint(char* str, ...);

#endif // UTILS_H_