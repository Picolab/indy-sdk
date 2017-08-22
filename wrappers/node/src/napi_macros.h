
#ifndef NAPI_CHECK_STATUS_VOID
#define NAPI_CHECK_STATUS_VOID(method) \
  if (status != napi_ok) { \
    printf("file %s, line %d\n", __FILE__, __LINE__); \
    napi_throw_error(env, method); \
    return; \
  }
#endif

#ifndef NAPI_CHECK_STATUS
#define NAPI_CHECK_STATUS(method) \
  if (status != napi_ok) { \
    printf("file %s, line %d\n", __FILE__, __LINE__); \
    napi_throw_error(env, method); \
    return NULL; \
  }
#endif

#ifndef NAPI_DEFINE_METHOD
#define NAPI_DEFINE_METHOD(name, function) \
  status = napi_create_function(env, name, function, NULL, &fn); \
  NAPI_CHECK_STATUS_VOID("napi_create_function"); \
  status = napi_set_named_property(env, exports, name, fn); \
  NAPI_CHECK_STATUS_VOID("napi_set_named_property");
#endif

#ifndef NAPI_EXPECTING_ARGS
#define NAPI_EXPECTING_ARGS(nargs) \
  napi_status status; \
  size_t argc = nargs; \
  napi_value argv[argc]; \
  napi_valuetype type; \
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL); \
  NAPI_CHECK_STATUS("napi_get_cb_info");
#endif

#ifndef NAPI_TYPEOF
#define NAPI_TYPEOF(value) \
  status = napi_typeof(env, value, &type); \
  NAPI_CHECK_STATUS("napi_typeof");
#endif

#ifndef NAPI_REQUIRED_STRING
#define NAPI_REQUIRED_STRING(value) \
  NAPI_TYPEOF(value); \
  if (type != napi_string) { \
    status = napi_throw_type_error(env, "Expected string"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_OPTIONAL_STRING
#define NAPI_OPTIONAL_STRING(value) \
  NAPI_TYPEOF(value); \
  if ( \
    !(type == napi_string || \
      type == napi_null || \
      type == napi_undefined) \
  ) { \
    status = napi_throw_type_error(env, "Expected string or null/undefined"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_REQUIRED_NUMBER
#define NAPI_REQUIRED_NUMBER(value) \
  NAPI_TYPEOF(value); \
  if (type != napi_number) { \
    status = napi_throw_type_error(env, "Expected number"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_OPTIONAL_NUMBER
#define NAPI_OPTIONAL_NUMBER(value) \
  NAPI_TYPEOF(value); \
  if ( \
    !(type == napi_number || \
      type == napi_null || \
      type == napi_undefined) \
  ) { \
    status = napi_throw_type_error(env, "Expected number or null/undefined"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_REQUIRED_FUNCTION
#define NAPI_REQUIRED_FUNCTION(value) \
  NAPI_TYPEOF(value); \
  if (type != napi_function) { \
    status = napi_throw_type_error(env, "Expected function"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_OPTIONAL_FUNCTION
#define NAPI_OPTIONAL_FUNCTION(value) \
  NAPI_TYPEOF(value); \
  if ( \
    !(type == napi_function || \
      type == napi_null || \
      type == napi_undefined) \
  ) { \
    status = napi_throw_type_error(env, "Expected function or null/undefined"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_REQUIRED_BOOLEAN
#define NAPI_REQUIRED_BOOLEAN(value) \
  NAPI_TYPEOF(value); \
  if (type != napi_boolean) { \
    status = napi_throw_type_error(env, "Expected boolean"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_OPTIONAL_BOOLEAN
#define NAPI_OPTIONAL_BOOLEAN(value) \
  NAPI_TYPEOF(value); \
  if ( \
    !(type == napi_boolean || \
      type == napi_null || \
      type == napi_undefined) \
  ) { \
    status = napi_throw_type_error(env, "Expected boolean or null/undefined"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

// TODO define the var inside macro
#ifndef NAPI_NUMBER_TO_INT32
#define NAPI_NUMBER_TO_INT32(number, i32) \
  NAPI_TYPEOF(number); \
  if (type != napi_number) { \
    i32 = -1; \
  } else { \
    status = napi_get_value_int32( \
      env, number, &i32 \
    ); \
    NAPI_CHECK_STATUS("napi_get_value_int32"); \
  }
#endif

#ifndef NAPI_STRING_TO_UTF8
#define NAPI_STRING_TO_UTF8(string, utf8) \
  NAPI_TYPEOF(string); \
  size_t length_##utf8 = napi_string_length(env, string); \
  char utf8[length_##utf8]; \
  if (type != napi_string) { \
    utf8[0] = '\0'; \
  } else { \
    status = napi_get_value_string_utf8(env, string, utf8, length_##utf8, NULL); \
    NAPI_CHECK_STATUS("napi_get_value_string_utf8"); \
  }
#endif

#ifndef NAPI_BOOLEAN_TO_BOOL
#define NAPI_BOOLEAN_TO_BOOL(boolean, c_bool) \
  NAPI_TYPEOF(boolean); \
  if (type != napi_boolean) { \
    c_bool = false; \
  } else { \
    status = napi_get_value_bool(env, boolean, &c_bool); \
    NAPI_CHECK_STATUS("napi_get_value_bool"); \
  }
#endif

#ifndef NAPI_DOUBLE_TO_NUMBER
#define NAPI_DOUBLE_TO_NUMBER(c_double, number) \
  status = napi_create_number(env, c_double, &number); \
  NAPI_CHECK_STATUS("napi_create_number");
#endif

#ifndef NAPI_ASYNC_CREATE
#define NAPI_ASYNC_CREATE(work, data) \
  napi_async_work work; \
  status = napi_create_async_work( \
    env, \
    execute, \
    complete, \
    data, \
    &work \
  ); \
  NAPI_CHECK_STATUS("napi_create_async_work");
#endif

#ifndef NAPI_ASYNC_CANCEL
#define NAPI_ASYNC_CANCEL(work) \
  status = napi_cancel_async_work(env, work); \
  if (status == napi_ok) { \
    NAPI_ASYNC_DELETE(work); \
    free_callback(callback->handle); \
  } else if (status == napi_generic_failure) { \
    std::lock_guard<std::mutex> lock(callback->mutex); \
    callback->cancelled = true; \
    callback->cv.notify_one(); \
  } else { \
    printf("file %s, line %d\n", __FILE__, __LINE__); \
    napi_throw_error(env, "napi_cancel_async_work"); \
    return NULL; \
  }
#endif

#ifndef NAPI_ASYNC_DELETE
#define NAPI_ASYNC_DELETE(work) \
  status = napi_delete_async_work(env, work); \
  NAPI_CHECK_STATUS("napi_delete_async_work");
#endif

#ifndef NAPI_ASYNC_START
#define NAPI_ASYNC_START(work) \
  status = napi_queue_async_work(env, work); \
  NAPI_CHECK_STATUS("napi_queue_async_work");
#endif