#ifndef UTIL_H_
#define UTIL_H_

void panic(const char *);
void printk(const char *fmt, ...);
void memset(uchar *addr, uchar ch, uint n);
int min(int a, int b);
uint umin(uint a, uint b);

#endif
