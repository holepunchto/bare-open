#include <sys/types.h>
#include <unistd.h>

int
bare__open(const char *app, const char *arg) {
  pid_t pid = fork();

  if (pid < 0) return -1;

  if (pid == 0) execlp(app, arg, NULL);

  return 0;
}
