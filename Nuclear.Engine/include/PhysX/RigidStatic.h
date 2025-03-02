#pragma once
#include <NE_Common.h>

namespace physx { class PxRigidStatic; }

namespace Nuclear
{
	namespace PhysX
	{
		//Wraps around physx::PxRigidStatic
		//Also known as collider
		class NEAPI RigidStatic
		{
		public:
			RigidStatic();
			~RigidStatic();


			physx::PxRigidStatic* mPtr;
		};
	}
}