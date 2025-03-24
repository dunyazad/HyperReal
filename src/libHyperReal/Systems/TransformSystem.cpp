#include <HyperReal/Systems/TransformSystem.h>
#include <HyperReal/libHyperReal.h>

TransformSystem::TransformSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::Initialize()
{

}

void TransformSystem::Terminate()
{

}

void TransformSystem::Update(ui32 frameNo, f32 timeDelta)
{
	auto& registry = libHyperReal::GetInstance().GetRegistry();
	auto transformEntities = registry.view<Transform>();
	for (auto& entity : transformEntities)
	{
		auto& transform = transformEntities.get<Transform>(entity);
		if (transform.parent)
		{
			transform.absoluteTransform = transform.parent->absoluteTransform * transform.transform;
		}
		else
		{
			transform.absoluteTransform = transform.transform;
		}
	}
}
