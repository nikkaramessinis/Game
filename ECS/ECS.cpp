#include "ECS.hpp"

void Entity::AddGroup(Group mGroup)
{
  groupBitSet[mGroup] = true;
  manager.AddToGroup(this, mGroup);
}
