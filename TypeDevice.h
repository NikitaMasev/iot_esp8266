typedef enum { ups,
               lamp,
               rgba,
               unknown,
} TypeDevice;

const static struct {
  TypeDevice val;
  const char *str;
} conversion[] = {
  { ups, "ups" },
  { lamp, "lamp" },
  { rgba, "rgba" },
  { unknown, "unknown" },
};

TypeDevice str2enum(const char *str) {
  int j;
  for (j = 0; j < sizeof(conversion) / sizeof(conversion[0]); ++j) {
    if (!strcmp(str, conversion[j].str)) {
      return conversion[j].val;
    }
  }
  return unknown;
}