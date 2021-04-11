/* gcc -Wall -o empty-dir empty-dir.c */
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int 
main(int argc, char const *argv[])
{
  char dir_path[1024];
  struct dirent *de;
  char *ptr;
  char buf[] = "a";
  DIR *d;
  int r;
  int fd;
  long pos;
  int count = 0;

  if (argc != 2)
    {
      fprintf(stderr, "usage: %s DIR", argv[0]);
      return 1;
    }

  snprintf(dir_path, sizeof(dir_path), "%s/empty-test.XXXXXX", argv[1]);

  ptr = mkdtemp(dir_path);
  assert(ptr != NULL);
  printf("Temp dir at %s\n", ptr);

  d = opendir(dir_path);
  assert(d != NULL);

  pos = telldir(d);

  fd = openat(dirfd(d), "a", O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC, 0666);
  assert(fd > 0);

  r = write(fd, buf, sizeof(buf));
  assert(r > 0);

  r = close(fd);
  assert(r == 0);

  rewinddir(d);

  while ((de = readdir (d)) != NULL)
    {

      if (!strcmp (de->d_name, ".") ||
          !strcmp (de->d_name, ".."))
        continue;

      count++;
      break;
    }

  r = closedir(d);
  assert(r == 0);

  printf("count: %d\n", count);

  return 0;
}