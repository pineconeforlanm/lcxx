//
// Created by lanm on 2025/8/11.
//

#include "sinsegye_ari_rt.h"

#include <dlfcn.h>

#include <ylt/easylog.hpp>

namespace rt {

static thread_local bool t_hook_enable = false;

#define HOOK_FUN(XX) \
  XX(rt_create_task) \
  XX(rt_delete_task)

void hook_init() {
  static bool is_inited = false;
  if (is_inited) {
    return;
  }
#define XX(name) name##_f = (name##_fun)dlsym(RTLD_NEXT, #name);
  HOOK_FUN(XX);
#undef XX
}

bool is_hook_enable() { return t_hook_enable; }

void set_hook_enable(const bool flag) { t_hook_enable = flag; }

extern "C" {
#define XX(name) name##_fun name##_f = nullptr;
HOOK_FUN(XX);
#undef XX

void rt_create_task(int argc, const char **argv) {
  if (!t_hook_enable) {
    return rt_create_task_f(argc, argv);
  }
  ELOGI << "Creating task in Sinsegye ARI RT";
  rt_create_task_f(argc, argv);
}

void rt_delete_task() {
  if (!t_hook_enable) {
    return rt_delete_task_f();
  }
  ELOGI << "Deleting task in Sinsegye ARI RT";
  rt_delete_task_f();
}
}

#undef HOOK_FUN

}  // namespace rt