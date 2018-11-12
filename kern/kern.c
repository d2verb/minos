void main(void) {
  unsigned short *screen = (unsigned short *)0xb8000;

  char *msg = "Starting Minos!";
  char ch;
  char attr = 0x0f;

  while (ch = *msg++) {
    *screen++ = ((attr) << 8) | ch;
  }
  return;
}
