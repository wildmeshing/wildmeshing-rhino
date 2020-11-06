################################################################################
cmake_minimum_required(VERSION 3.1)
project(WildMeshingRhino)
################################################################################


set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Prepend function
# include(PrependCurrentPath)

# Use C++11/14
include(CXXFeatures)

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################


set(WILDMESHING_EXTERNAL ${THIRD_PARTY_DIR})

# Download and update 3rdparty libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
include(DownloadExternal)

wildmeshing_download_bindings()
add_subdirectory(${THIRD_PARTY_DIR}/bindings)
# add_subdirectory(${THIRD_PARTY_DIR}/bindings/3rdparty/tetwild)


################################################################################
# Subdirectories
################################################################################
add_library(wildmeshing-rhino SHARED
	${THIRD_PARTY_DIR}/bindings/src/Utils.cpp ${THIRD_PARTY_DIR}/bindings/src/Utils.hpp

	# ${THIRD_PARTY_DIR}/bindings/src/triangulate_data.hpp ${THIRD_PARTY_DIR}/bindings/src/triangulate_data.cpp
	# ${THIRD_PARTY_DIR}/bindings/src/triangulate.cpp ${THIRD_PARTY_DIR}/bindings/src/triangulate.hpp

	${THIRD_PARTY_DIR}/bindings/src/tetrahedralize.cpp ${THIRD_PARTY_DIR}/bindings/src/tetrahedralize.hpp)

target_sources(wildmeshing-rhino PRIVATE src/Rhino-Binding.cpp)

target_include_directories(wildmeshing-rhino PRIVATE ${THIRD_PARTY_DIR}/bindings/src)
# target_include_directories(wildmeshing-rhino PRIVATE ${THIRD_PARTY_DIR}/bindings/triwild/src)

target_compile_features(wildmeshing-rhino PUBLIC cxx_std_14)
target_compile_definitions(wildmeshing-rhino PUBLIC WILDMESHING_SKIP_BINDINGS)


# target_link_libraries(wildmeshing-rhino PRIVATE triwild_lib)
target_link_libraries(wildmeshing-rhino PRIVATE FloatTetwild)




