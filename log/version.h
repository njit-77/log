#pragma once

#define LOG_VER_MAJOR 1
#define LOG_VER_MINOR 2
#define LOG_VER_PATCH 0

#define NUM2STR(v) #v
#define VERSTR4NUM(ma, mi, pa, pb) NUM2STR(ma) "." NUM2STR(mi) "." NUM2STR(pa) "." NUM2STR(pb)
#define LOG_VERSION VERSTR4NUM(LOG_VER_MAJOR, LOG_VER_MINOR, LOG_VER_PATCH, 0)
