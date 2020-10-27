#ifndef MACROS_H
#define MACROS_H

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


#define EXPORT(obj, name, fn)                                    \
  do {                                                           \
    napi_value __value;                                          \
    CALL(env, napi_create_function(                              \
          env, name, NAPI_AUTO_LENGTH, fn, NULL, &__value));     \
    CALL(env, napi_set_named_property(env, obj, name, __value)); \
  } while(0);




#endif /* !MACROS_H */
