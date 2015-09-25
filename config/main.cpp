#include <LXQt/Application>
#include "config.h"

int main(int argc, char *argv[])
{
    LXQt::Application app(argc, argv);
    Config conf;
    conf.show();
    return app.exec();
}
