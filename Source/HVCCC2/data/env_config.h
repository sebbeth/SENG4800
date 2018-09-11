#include <string>
#ifdef UE_BUILD_DEVELOPMENT
#define PROJECT_PATH std::string(TCHAR_TO_UTF8(*FPaths::ProjectDir()))
#else
#define PROJECT_PATH std::string("../")
#endif
#define XML_PATH PROJECT_PATH+"/XMLs"
#define BINARY_PATH PROJECT_PATH+"/BinaryDataFiles"