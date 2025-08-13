add_library(cobalt SHARED cobalt.cc)

target_link_libraries(cobalt PUBLIC stdc++exp)

target_include_directories(cobalt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

add_library(sinsegye_ari_rt SHARED sinsegye_ari_rt.cc)
target_link_libraries(sinsegye_ari_rt PUBLIC stdc++exp cobalt)
target_include_directories(sinsegye_ari_rt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

