#include <assert.h>
#include <bare.h>
#include <js.h>
#include <stdlib.h>
#include <utf.h>

int
bare__open(const char *app, const char *arg);

static js_value_t *
bare_open(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  size_t app_len;
  err = js_get_value_string_utf8(env, argv[0], NULL, 0, &app_len);
  assert(err == 0);

  app_len += 1 /* NULL */;

  utf8_t *app = malloc(app_len);
  err = js_get_value_string_utf8(env, argv[0], app, app_len, NULL);
  assert(err == 0);

  utf8_t *arg = NULL;

  if (argc == 2) {
    size_t arg_len;
    err = js_get_value_string_utf8(env, argv[1], NULL, 0, &arg_len);
    assert(err == 0);

    arg_len += 1 /* NULL */;

    arg = malloc(arg_len);
    err = js_get_value_string_utf8(env, argv[1], arg, arg_len, NULL);
    assert(err == 0);
  }

  err = bare__open((char *) app, (char *) arg);

  free(app);
  free(arg);

  if (err < 0) {
    err = js_throw_error(env, NULL, "Failed to launch application");
    assert(err == 0);
  }

  return NULL;
}

static js_value_t *
bare_open_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("open", bare_open)
#undef V

  return exports;
}

BARE_MODULE(bare_open, bare_open_exports)
