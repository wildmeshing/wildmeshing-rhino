################################################################################
include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
    set(WILDMESHING_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
    set(WILDMESHING_EXTRA_OPTIONS "")
endif()

# Shortcut function
function(wildmeshing_download_project name)
    download_project(
        PROJ         ${name}
        SOURCE_DIR   ${WILDMESHING_EXTERNAL}/${name}
        DOWNLOAD_DIR ${WILDMESHING_EXTERNAL}/.cache/${name}
        QUIET
        ${WILDMESHING_EXTRA_OPTIONS}
        ${ARGN}
    )
endfunction()

################################################################################

# data
function(wildmeshing_download_bindings)
    wildmeshing_download_project(bindings
        GIT_REPOSITORY https://github.com/wildmeshing/wildmeshing-python.git
        GIT_TAG        6a41901c31c60c02a58ca78e4e93bcfa89a59198
    )
endfunction()


function(wildmeshing_download_triwild)
    wildmeshing_download_project(triwild
        GIT_REPOSITORY  https://github.com/wildmeshing/TriWild
        GIT_TAG         a69ef125e5c6e336f1bd982afadefbc87a92398e
    )
endfunction()

function(wildmeshing_download_tetwild)
    wildmeshing_download_project(tetwild
        GIT_REPOSITORY  https://github.com/wildmeshing/fTetWild
        GIT_TAG         9ce357a936f7bade5a96fb2cbb43ed34a99d40a6
    )
endfunction()