
void bpsk(int *data, int len) {
  int i;
  for (i=0; i<len; i++) {
    if (data[i] == 1) {
      phase += M_PI;
    }
    if (phase > 2*M_PI) {
      phase -= 2*M_PI;
    }
  }
}
