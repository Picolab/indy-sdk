
#include <napi.h>

#include <indy_types.h>
#include <indy_core.h>

void init(
  napi_env env,
  napi_value exports,
  napi_value module,
  void* priv
) {
  printf("indy-sdk#init\n");
}

NAPI_MODULE(libindy, init);