#include "Application.h"

Application::Application(int argc, char **argv)
{
    if (argc > 1)
    {
        this->argc = argc;
        this->argv = argv;
    }
}
void Application::run()
{
    try
    {
        findMode();
        processMode();

        hasher.hashString(this->text);
        cout << text << endl;
        cout << hasher.getHashed() << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
void Application::openFile(std::ifstream &open_f, string file_name)
{
    open_f.open(file_name);
    if (open_f.fail())
        throw std::invalid_argument("File \"" + file_name + "\" not found");
}

void Application::readFile(string file_name)
{
    std::ifstream file;
    openFile(file, file_name);

    std::stringstream fileText;
    fileText << file.rdbuf();
    this->text = fileText.str();
}
void Application::processMode()
{
    switch (this->mode)
    {
    case AppMode::GenFile:
        if (this->argc != 4)
            throw std::invalid_argument("Invalid argument: -genFile used incorrectly");
        Generator gen;
        gen.genFile(argv[2], std::atoi(argv[3]));
        exit(0);
        break;
    case AppMode::HashFile:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: -hashFile used incorrectly");
        readFile(argv[2]);
        break;
    case AppMode::HashLine:
        if (this->argc != 3)
            throw std::invalid_argument("Invalid argument: -hashLine used incorrectly");
        this->text = argv[2];
        break;

    default:
        break;
    }
}

void Application::findMode()
{
    string modeArg = argv[1];
    if (modeArg == "")
    {
        throw std::invalid_argument("Invalid command line argument");
        return;
    }

    if (modeArg == "-genFile")
    {
        this->mode = AppMode::GenFile;
        return;
    }

    if (modeArg == "-hashFile")
    {
        this->mode = AppMode::HashFile;
        return;
    }
    if (modeArg == "-hashLine")
    {
        this->mode = AppMode::HashLine;
        return;
    }
    throw std::invalid_argument("Mode not found");
}