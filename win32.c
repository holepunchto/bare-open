#include <uv.h>

#include <shellapi.h> // Must be included after uv.h

int
bare__open(const char *app, const char *arg) {
  INT_PTR res = (INT_PTR) ShellExecute(NULL, "open", app, arg, NULL, 0);

  return res == 32 ? 0 : -1;
}
