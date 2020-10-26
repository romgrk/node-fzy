#ifndef WRAP_MODULE_JS_H_
#define WRAP_MODULE_JS_H_

#include <assert.h>
#include <stdlib.h>
#include <node_api.h>
#include "fzy/match.h"

#define DECLARE_NAPI_METHOD(name, func)     \
  {                                         \
    name, 0, func, 0, 0, 0, napi_default, 0 \
  }

#define ASSERT(env, test, msg)        \
  if (!(test)) {                      \
    napi_throw_error(env, NULL, msg); \
    return NULL;                      \
  }

#define CALL(env, call)                                           \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending) {                                          \
        const char* message = (error_info->error_message == NULL) \
            ? "empty error message"                               \
            : error_info->error_message;                          \
        napi_throw_error((env), NULL, message);                   \
        return NULL;                                              \
      }                                                           \
    }                                                             \
  } while(0)

napi_value HasMatch(napi_env env, napi_callback_info info);
napi_value Match(napi_env env, napi_callback_info info);
napi_value MatchPositions(napi_env env, napi_callback_info info);

#endif // WRAP_MODULE_JS_H_
