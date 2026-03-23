@echo on

set revfile="%~dp0version.h"

for /f "delims=+ " %%a in ('git rev-parse HEAD') do @set HEAD=%%a

echo //Auto generate file version > %revfile%

echo #define NUM2STR(v) #v	>> %revfile%
echo #define VERSTR4NUM(ma, mi, pa, pb) NUM2STR(ma) "." NUM2STR(mi) "." NUM2STR(pa) "." NUM2STR(pb)	>> %revfile%
echo
echo #define LOG_VER_MAJOR 1	>> %revfile%
echo #define LOG_VER_MINOR 3	>> %revfile%
echo #define LOG_VER_PATCH 1	>> %revfile%

echo #define LOG_VERSION VERSTR4NUM(LOG_VER_MAJOR, LOG_VER_MINOR, LOG_VER_PATCH, 0)	>> %revfile%
echo #define LOG_ASSEMBLY_VERSION LOG_VERSION " + %HEAD%"	>> %revfile%