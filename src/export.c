#include "module-js.h"


napi_ref constructor;

napi_value ExportModule(napi_env env, napi_value exports)
{

  napi_value has_match;
  napi_value match;
  napi_value match_positions;

  CALL(env, napi_create_function(env, "hasMatch",       NAPI_AUTO_LENGTH, HasMatch,       NULL, &has_match));
  CALL(env, napi_create_function(env, "match",          NAPI_AUTO_LENGTH, Match,          NULL, &match));
  CALL(env, napi_create_function(env, "matchPositions", NAPI_AUTO_LENGTH, MatchPositions, NULL, &match_positions));

  // Export module
  CALL(env, napi_set_named_property(env, exports, "hasMatch", has_match));
  CALL(env, napi_set_named_property(env, exports, "match", match));
  CALL(env, napi_set_named_property(env, exports, "matchPositions", match_positions));

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, ExportModule);
