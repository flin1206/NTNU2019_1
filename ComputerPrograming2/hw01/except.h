#pragma once

#include <setjmp.h>

#define TRYBUF(x) jmp_buf try_buf_##x
#define SIGTRY(x) switch( sigsetjmp(try_buf_##x, 1)) {case 0: 
#define SIGCATCH(y) break; case y: 
#define SIGFINALLY break; default:
#define SIGETRY break; }

#define SIGTHROW(x, y) siglongjmp(try_buf_##x, y)