#include "dlfcn.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

int (*pimpl(const char* libname, const char* funcname))(int) {
  void* handle = dlopen(libname, RTLD_LAZY);
  if (NULL == handle) {
    return NULL;
  } else {
    return (int (*)(int))dlsym(handle, funcname);
  }
}

int main(int argc, char** argv) {
  printf("%d\n", pimpl(argv[1], argv[2])(atoi(argv[3])));
  return 0;
}
