#include <HyperReal/Systems/RenderSystem.h>
#include <HyperReal/libHyperReal.h>

RenderSystem::RenderSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{

}

void RenderSystem::Terminate()
{

}

void RenderSystem::Update(ui32 frameNo, f32 timeDelta)
{
	glViewport(0, 0,
		libHyperReal::GetInstance().GetHyperRealWindow()->GetWidth(),
		libHyperReal::GetInstance().GetHyperRealWindow()->GetHeight());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
