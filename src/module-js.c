#include <ctype.h>

#include "module-js.h"


#define BUFFER_SIZE 1024

static int has_uppercase(const char *src) {
  for (;*src;++src) {
    if (isalpha(*src) && *src == toupper(*src))
      return 1;
  }
  return 0;
}

napi_value HasMatch(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  bool is_case_sensitive;

  size_t argc = 3;
  napi_value jsthis;
  napi_value argv[3];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], (char *)&needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], (char *)&haystack, BUFFER_SIZE, &haystack_length));
  CALL(env, napi_get_value_bool(
    env, argv[2], &is_case_sensitive));

  int result = has_match(needle, haystack, (int)is_case_sensitive);

  napi_value js_result;
  CALL(env, napi_get_boolean(env, result, &js_result));

  return js_result;
}

napi_value Match(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  bool is_case_sensitive;

  size_t argc = 3;
  napi_value jsthis;
  napi_value argv[3];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], (char *)&needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], (char *)&haystack, BUFFER_SIZE, &haystack_length));
  CALL(env, napi_get_value_bool(
    env, argv[2], &is_case_sensitive));

  double score = match(needle, haystack, (int)is_case_sensitive);

  napi_value result;
  CALL(env, napi_create_double(env, score, &result));

  return result;
}

napi_value MatchPositions(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t positions[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  bool is_case_sensitive;

  size_t argc = 3;
  napi_value jsthis;
  napi_value argv[3];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  CALL(env, napi_get_value_string_utf8(
    env, argv[0], (char *)&needle, BUFFER_SIZE, &needle_length));
  CALL(env, napi_get_value_string_utf8(
    env, argv[1], (char *)&haystack, BUFFER_SIZE, &haystack_length));
  CALL(env, napi_get_value_bool(
    env, argv[2], &is_case_sensitive));

  double score = match_positions(needle, haystack, positions, (int)is_case_sensitive);

  napi_value js_result;
  napi_value js_score;
  napi_value js_positions;

  CALL(env, napi_create_double(env, score, &js_score));
  CALL(env, napi_create_array(env, &js_result));
  CALL(env, napi_create_array_with_length(env, needle_length, &js_positions));


  for (size_t i = 0; i < needle_length; i++) {
    napi_value p;
    CALL(env, napi_create_int64(env, (int64_t)positions[i], &p));
    CALL(env, napi_set_element(env, js_positions, i, p));
  }

  CALL(env, napi_set_element(env, js_result, 0, js_score));
  CALL(env, napi_set_element(env, js_result, 1, js_positions));

  return js_result;
}


napi_value HasMatchMulti(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  int is_case_sensitive = 0;

  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  napi_value js_needle = argv[0];
  napi_value js_haystacks = argv[1];

  CALL(env, napi_get_value_string_utf8(
    env, js_needle, (char *)&needle, BUFFER_SIZE, &needle_length));

  is_case_sensitive = has_uppercase(needle);

  uint32_t length;
  CALL(env, napi_get_array_length(env, js_haystacks, &length));

  napi_value js_results;
  CALL(env, napi_create_array_with_length(env, length, &js_results));


  for (uint32_t i = 0; i < length; i++) {
    napi_value js_haystack;
    CALL(env, napi_get_element(env, js_haystacks, i, &js_haystack));
    CALL(env, napi_get_value_string_utf8(
      env, js_haystack, (char *)&haystack, BUFFER_SIZE, &haystack_length));

    int result = has_match(needle, haystack, (int)is_case_sensitive);

    napi_value js_result;
    CALL(env, napi_get_boolean(env, (bool)result, &js_result));

    CALL(env, napi_set_element(env, js_results, i, js_result));
  }

  return js_results;
}

napi_value MatchMulti(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  int is_case_sensitive;

  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  napi_value js_needle = argv[0];
  napi_value js_haystacks = argv[1];

  CALL(env, napi_get_value_string_utf8(
    env, js_needle, (char *)&needle, BUFFER_SIZE, &needle_length));

  is_case_sensitive = has_uppercase(needle);

  uint32_t length;
  CALL(env, napi_get_array_length(env, js_haystacks, &length));

  napi_value js_results;
  CALL(env, napi_create_array_with_length(env, length, &js_results));


  for (uint32_t i = 0; i < length; i++) {
    napi_value js_haystack;
    CALL(env, napi_get_element(env, js_haystacks, i, &js_haystack));
    CALL(env, napi_get_value_string_utf8(
      env, js_haystack, (char *)&haystack, BUFFER_SIZE, &haystack_length));

    double score = match(needle, haystack, (int)is_case_sensitive);

    napi_value js_result;
    CALL(env, napi_create_double(env, score, &js_result));

    CALL(env, napi_set_element(env, js_results, i, js_result));
  }

  return js_results;
}

napi_value MatchPositionsMulti(napi_env env, napi_callback_info info)
{
  char needle[BUFFER_SIZE];
  char haystack[BUFFER_SIZE];
  size_t positions[BUFFER_SIZE];
  size_t needle_length;
  size_t haystack_length;
  int is_case_sensitive;

  size_t argc = 2;
  napi_value jsthis;
  napi_value argv[2];
  CALL(env, napi_get_cb_info(env, info, &argc, argv, &jsthis, NULL));

  napi_value js_needle = argv[0];
  napi_value js_haystacks = argv[1];

  CALL(env, napi_get_value_string_utf8(
    env, js_needle, (char *)&needle, BUFFER_SIZE, &needle_length));

  is_case_sensitive = has_uppercase(needle);

  uint32_t length;
  CALL(env, napi_get_array_length(env, js_haystacks, &length));

  napi_value js_results;
  CALL(env, napi_create_array_with_length(env, length, &js_results));


  for (uint32_t i = 0; i < length; i++) {
    napi_value js_haystack;
    CALL(env, napi_get_element(env, js_haystacks, i, &js_haystack));
    CALL(env, napi_get_value_string_utf8(
      env, js_haystack, (char *)&haystack, BUFFER_SIZE, &haystack_length));

    double score = match_positions(needle, haystack, (size_t *)positions, (int)is_case_sensitive);

    napi_value js_result;
    napi_value js_score;
    napi_value js_positions;

    CALL(env, napi_create_double(env, score, &js_score));
    CALL(env, napi_create_array(env, &js_result));
    CALL(env, napi_create_array_with_length(env, needle_length, &js_positions));


    for (size_t i = 0; i < needle_length; i++) {
      napi_value p;
      CALL(env, napi_create_int64(env, (int64_t)positions[i], &p));
      CALL(env, napi_set_element(env, js_positions, i, p));
    }

    CALL(env, napi_set_element(env, js_result, 0, js_score));
    CALL(env, napi_set_element(env, js_result, 1, js_positions));

    CALL(env, napi_set_element(env, js_results, i, js_result));
  }

  return js_results;
}

