#include "files/FileProvider.hpp"
#include "window/MainWindow.hpp"



int main(int argc, char* argv[])
{
    FileProvider provider(argv[0]);

	const char title[] = "World 3D";
    const int width = 800;
    const int height = 600;

	MainWindow app;
	int retCode = -1;

	if (app.create(title, width, height))
		retCode = app.run();

    return retCode;
}