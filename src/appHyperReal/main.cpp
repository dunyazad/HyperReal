#include <iostream>

#include <HyperReal/libHyperReal.h>

int main(int argc, char** argv)
{
	libHyperReal::GetInstance().Initialize(1920, 1080);

	libHyperReal::GetInstance().Run();

	libHyperReal::GetInstance().Terminate();

	return 0;
}
