#include <HyperReal/Systems/CameraSystem.h>
#include <HyperReal/libHyperReal.h>

CameraSystem::CameraSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::Initialize()
{

}

void CameraSystem::Terminate()
{

}

void CameraSystem::Update(ui32 frameNo, f32 timeDelta)
{
	auto& registry = libHyperReal::GetInstance().GetRegistry();
	//{
	//	auto cameras = registry.view<Camera>(entt::exclude<Transform>);
	//	for (auto& camera : cameras)
	//	{
	//		camera.viewMatrix = 
	//	}
	//}
	{
		auto cameras = registry.view<Camera, Transform>();
		for (auto entity : cameras)
		{
			auto& camera = cameras.get<Camera>(entity);
			auto& transform = cameras.get<Transform>(entity);

			camera.viewMatrix = transform.transform.inverse();
		}
	}
}
