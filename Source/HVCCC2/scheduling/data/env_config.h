#include <string>
#define PROJECT_PATH std::string(TCHAR_TO_UTF8(*FPaths::GameDir()))
#define XML_PATH PROJECT_PATH+"Resources/XMLs"
#define BINARY_PATH PROJECT_PATH+"Resources/BinaryDataFiles"
//#define BINARY_PATH std::getenv("BINARY_PATH")