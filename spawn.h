

#ifndef _SPAWN_H
#define _SPAWN_H

int spawn(const char* file, char* const* argv, char* const* envv,
    const char* cwd, int outfd);

#endif
