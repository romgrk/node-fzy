#include "module-js.h"


napi_ref constructor;

napi_value ExportModule(napi_env env, napi_value exports)
{

  EXPORT(exports, "hasMatch",       HasMatch);
  EXPORT(exports, "match",          Match);
  EXPORT(exports, "matchPositions", MatchPositions);

  EXPORT(exports, "hasMatchMulti",       HasMatchMulti);
  EXPORT(exports, "matchMulti",          MatchMulti);
  EXPORT(exports, "matchPositionsMulti", MatchPositionsMulti);

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, ExportModule);
