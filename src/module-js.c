#include "module-js.h"


#define BUFFER_SIZE 1024

napi_value HasMatch(napi_env env, napi_callback_info info)
{
  char *needle[BUFFER_SIZE];
  char *haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;

  // Get JS this and arguments
  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];

  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], &needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], &haystack, BUFFER_SIZE, &haystack_length));

  int result_value = has_match(needle, haystack);

  napi_value result;
  CALL(env, napi_create_double(env, result_value, &result));

  return result;
}

napi_value Match(napi_env env, napi_callback_info info)
{
  char *needle[BUFFER_SIZE];
  char *haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;

  // Get JS this and arguments
  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];

  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], &needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], &haystack, BUFFER_SIZE, &haystack_length));

  double score = match(needle, haystack);

  napi_value result;
  CALL(env, napi_create_double(env, score, &result));

  return result;
}

napi_value MatchPositions(napi_env env, napi_callback_info info)
{
  char *needle[BUFFER_SIZE];
  char *haystack[BUFFER_SIZE];
  size_t *positions[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;

  // Get JS this and arguments
  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];

  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], &needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], &haystack, BUFFER_SIZE, &haystack_length));

  double score = match_positions(needle, haystack, positions);

  napi_value js_result;
  napi_value js_score;
  napi_value js_positions;

  CALL(env, napi_create_double(env, score, &js_score));
  CALL(env, napi_create_array(env, &js_result));
  CALL(env, napi_create_array(env, &js_positions));


  for (size_t i = 0; i < needle_length; i++) {
    napi_value p;
    CALL(env, napi_create_int64(env, (int64_t)positions[i], &p));
    CALL(env, napi_set_element(env, js_positions, i, p));
  }

  CALL(env, napi_set_element(env, js_result, 0, js_score));
  CALL(env, napi_set_element(env, js_result, 1, js_positions));

  return js_result;
}

