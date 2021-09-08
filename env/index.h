#ifndef GLOBAL_H
#define GLOBAL_H

#include "../partitions/index.h"
#include "../users/index.h"
#include "string"
#include <deque>

using namespace std;

struct User : UserCommandsProps {
  bool logged;
  string uid;
  string gid;
};

extern deque<MountedPartition> mounted_partitions;
extern struct User global_user;

#endif // GLOBAL_H