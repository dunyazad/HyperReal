#include <HyperReal/Systems/ImmediateRenderSystem.h>
#include <HyperReal/libHyperReal.h>

ImmediateRenderSystem::ImmediateRenderSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

ImmediateRenderSystem::~ImmediateRenderSystem()
{
}

void ImmediateRenderSystem::Initialize()
{

}

void ImmediateRenderSystem::Terminate()
{

}

void ImmediateRenderSystem::Update(ui32 frameNo, f32 timeDelta)
{
	glUseProgram(0);

	glViewport(0, 0,
		libHyperReal::GetInstance().GetHyperRealWindow()->GetWidth(),
		libHyperReal::GetInstance().GetHyperRealWindow()->GetHeight());

	glPointSize(10.0f);
	glLineWidth(2.0f);

	glClear(GL_DEPTH_BUFFER_BIT);

	// Enable anti-aliasing for smoother lines
	//glEnable(GL_LINE_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth test if needed
	glEnable(GL_DEPTH_TEST);

	auto activeCamera = libHyperReal::GetInstance().GetActiveCamera();
	if (nullptr != activeCamera)
	{
		const auto& projection = activeCamera->projectionMatrix;
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(projection.data());

		const auto& view = activeCamera->viewMatrix;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(view.data());

		Eigen::Matrix4f worldTransform = view.inverse();
		Eigen::Vector3f origin = worldTransform.block<3, 1>(0, 3);

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(origin.x(), origin.y(), origin.z());
		glEnd();
	}

	//auto cameras = Feather.GetInstances<PerspectiveCamera>();
	//for (auto& camera : cameras)
	//{
	//	if (nullptr != camera)
	//	{
	//		const auto& projection = camera->GetProjectionMatrix();
	//		glMatrixMode(GL_PROJECTION);
	//		glLoadMatrixf((float*)projection.m);

	//		const auto& view = camera->GetViewMatrix();
	//		auto target = camera->GetTarget();
	//		glMatrixMode(GL_MODELVIEW);
	//		glLoadMatrixf((float*)view.m);

	//		glColor3f(1.0f, 0.0f, 0.0f);
	//		glBegin(GL_POINTS);
	//		glVertex3f(target.x, target.y, target.z);
	//		glEnd();
	//	}
	//}

	// Draw X-axis (Red)
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	// Draw Y-axis (Green)
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	// Draw Z-axis (Blue)
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
}
