#include "Launcher.h"

void Launcher::Start(int argc, char* argv[]) {
    try {
        Parser parser(argc, argv);
        Image image;
        image.Read(parser.GetInputPath());
        Applier applier(parser.GetParameters());
        applier.ApplyFilters(image);
        image.Save(parser.GetOutputPath());
    } catch (std::runtime_error& e) {
        std::cout << e.what();
    } catch (std::logic_error& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Unidentified error";
    }
}
