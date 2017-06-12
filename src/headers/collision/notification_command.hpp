#ifndef COLLISION_NOTIFICATIONC_COMMAND_H
#define COLLISION_NOTIFICATIONC_COMMAND_H
#include "patterns/command.hpp"
#include "collision/collider.hpp"
namespace Collision {
	class NotificationCommand : Command {
		public:
			NotificationCommand();
			virtual void execute();
			virtual void execute(Collider*, Collider*);
			virtual ~NotificationCommand();


	};
} // namespace Collision
#endif
