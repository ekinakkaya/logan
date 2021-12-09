## logan

A small logger tool for your C projects.


### Usage:
```c
#include <stdio.h>
#include <stdlib.h>

#include "logan.h"

int main() {
    logan_s logger;
    logan(&logger, "logfile.txt");

    logan_log(&logger, "Hello!!!");

    logan_free(&logger);

    return 0;
}
```

### Design Goals:
- Small
- Fast
- Thread Safe: Uses mutex locks.
- Easy: Fairly easy to remember syntax and function names.

