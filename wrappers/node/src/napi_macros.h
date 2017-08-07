
#ifndef NAPI_CHECK_STATUS_VOID
#define NAPI_CHECK_STATUS_VOID(method) \
  if (status != napi_ok) { \
    napi_throw_error(env, method); \
    return; \
  }
#endif

#ifndef NAPI_CHECK_STATUS
#define NAPI_CHECK_STATUS(method) \
  if (status != napi_ok) { \
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

#ifndef NAPI_ENSURE_STRING
#define NAPI_ENSURE_STRING(value) \
  status = napi_typeof(env, value, &type); \
  NAPI_CHECK_STATUS("napi_typeof"); \
  if (type != napi_string) { \
    status = napi_throw_type_error(env, "Expected string"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_ENSURE_NUMBER
#define NAPI_ENSURE_NUMBER(value) \
  status = napi_typeof(env, value, &type); \
  NAPI_CHECK_STATUS("napi_typeof"); \
  if (type != napi_number) { \
    status = napi_throw_type_error(env, "Expected number"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
#endif

#ifndef NAPI_ENSURE_FUNCTION
#define NAPI_ENSURE_FUNCTION(value) \
  status = napi_typeof(env, value, &type); \
  NAPI_CHECK_STATUS("napi_typeof"); \
  if (type != napi_function) { \
    status = napi_throw_type_error(env, "Expected function"); \
    NAPI_CHECK_STATUS("napi_throw_type_error"); \
    return NULL; \
  }
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

#ifndef NAPI_NUMBER_TO_INT32
#define NAPI_NUMBER_TO_INT32(number, i32) \
  status = napi_get_value_int32(env, number, &i32); \
  NAPI_CHECK_STATUS("napi_get_value_int32");
#endif

#ifndef NAPI_STRING_TO_UTF8
#define NAPI_STRING_TO_UTF8(string, utf8) \
  status = napi_get_value_string_utf8(env, string, NULL, 0, &string_length); \
  NAPI_CHECK_STATUS("napi_get_value_string_utf8"); \
  status = napi_get_value_string_utf8(env, string, utf8, string_length, &written); \
  NAPI_CHECK_STATUS("napi_get_value_string_utf8");
#endif

#ifndef NAPI_DOUBLE_TO_NUMBER
#define NAPI_DOUBLE_TO_NUMBER(c_double, number) \
  status = napi_create_number(env, c_double, &number); \
  NAPI_CHECK_STATUS("napi_create_number");
#endif