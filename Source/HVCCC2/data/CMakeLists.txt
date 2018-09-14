project (TinyXML2Testing)
set (CMAKE_CXX_STANDARD 14)
set(TINYXML2
    tinyxml2/tinyxml2.h
    tinyxml2/tinyxml2.cpp
)

set(CEREAL
    cereal/access.hpp
    cereal/cereal.hpp
    cereal/macros.hpp
    cereal/archives/adapters.hpp
    cereal/archives/binary.hpp
    cereal/archives/json.hpp
    cereal/archives/portable_binary.hpp
    cereal/archives/xml.hpp
    cereal/details/helpers.hpp
    cereal/details/polymorphic_impl_fwd.hpp
    cereal/details/polymorphic_impl.hpp
    cereal/details/static_object.hpp
    cereal/details/traits.hpp
    cereal/details/util.hpp
    cereal/external/base64.hpp
    cereal/external/rapidjson
    cereal/external/rapidxml
    cereal/types/array.hpp
    cereal/types/base_class.hpp
    cereal/types/bitset.hpp
    cereal/types/boost_variant.hpp
    cereal/types/chrono.hpp
    cereal/types/common.hpp
    cereal/types/complex.hpp
    cereal/types/concepts
    cereal/types/deque.hpp
    cereal/types/forward_list.hpp
    cereal/types/functional.hpp
    cereal/types/list.hpp
    cereal/types/map.hpp
    cereal/types/memory.hpp
    cereal/types/polymorphic.hpp
    cereal/types/queue.hpp
    cereal/types/set.hpp
    cereal/types/stack.hpp
    cereal/types/string.hpp
    cereal/types/tuple.hpp
    cereal/types/unordered_map.hpp
    cereal/types/unordered_set.hpp
    cereal/types/utility.hpp
    cereal/types/valarray.hpp
    cereal/types/vector.hpp
)

include_directories(${CMAKE_SOURCE_DIR})

set(UTIL
    convertData.h
    convertData.cpp
    loadData.h
    loadData.cpp
    serialization.h
    serialization.cpp
        util.h)

set(CONFIG
    env_config.h
)

include(${CMAKE_CURRENT_SOURCE_DIR}/extraction/CMakeLists.txt)

add_executable(TINYXML2_TESTING
    ${TINYXML2}
    ${CEREAL}
    ${UTIL}
    ${CONFIG}
    ${GENERATED}
    TinyXML2Testing.cpp
)