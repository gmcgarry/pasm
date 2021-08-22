void emitusage(void);
const char *emit_extension(const char *ftype);
const char *emit_desc_lookup(int num);
const char *emit_desc_to_name_lookup(const char *desc);
int emitopen(const char *file, const char *ftype, const char *arg);
void emitclose(void);
void emitaddr(unsigned long a);
void emitbyte(int b);
