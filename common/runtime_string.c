typedef struct {
  unsigned int words[4];
} RuntimeString;

/* gk3/GK3R_rest.c */
extern int __thiscall destroy_runtime_string_impl(RuntimeString *string);

void __thiscall destroy_runtime_string(RuntimeString *string)
{
  destroy_runtime_string_impl(string);
}
