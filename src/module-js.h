#ifndef WRAP_MODULE_JS_H_
#define WRAP_MODULE_JS_H_

#include <assert.h>
#include <stdlib.h>
#include <node_api.h>

#include "macros.h"
#include "fzy/match.h"

/*
 * Definitions
 */

napi_value HasMatch(napi_env env, napi_callback_info info);
napi_value Match(napi_env env, napi_callback_info info);
napi_value MatchPositions(napi_env env, napi_callback_info info);

napi_value HasMatchMulti(napi_env env, napi_callback_info info);
napi_value MatchMulti(napi_env env, napi_callback_info info);
napi_value MatchPositionsMulti(napi_env env, napi_callback_info info);


#endif // WRAP_MODULE_JS_H_
