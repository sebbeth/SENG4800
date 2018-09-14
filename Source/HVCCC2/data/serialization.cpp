#include "serialization.h"

serialisation_detail::serialisation_functor::serialisation_functor(bool &result, const std::string &destinationPath): result(result), destinationPath(destinationPath) {
};

serialisation_detail::deserialisation_functor::deserialisation_functor(bool &result, const std::string &sourcePath): result(result), sourcePath(sourcePath) {
};