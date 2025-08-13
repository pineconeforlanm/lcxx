//
// Created by lanm on 2025/8/11.
//
#pragma once
#ifndef LCXX_SINSEGYE_ARI_RT_H
#define LCXX_SINSEGYE_ARI_RT_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdint>
#include <ctime>
#include <unistd.h>
#include <cobalt.h>

namespace rt {
bool is_hook_enable();
void set_hook_enable(bool flag);
void hook_init();
}

extern "C" {
  typedef void (*rt_create_task_fun)(int argc, const char **argv);
  extern rt_create_task_fun rt_create_task_f;

  typedef void (*rt_delete_task_fun)();
  extern rt_delete_task_fun rt_delete_task_f;
}

#endif  // LCXX_SINSEGYE_ARI_RT_H
