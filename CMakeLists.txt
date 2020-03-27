cmake_minimum_required(VERSION 3.14)
project(MAPD)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(include/google)
include_directories(include/google/sparsehash)
include_directories(include/sparsehash)
include_directories(include/sparsehash/internal)

add_executable(MAPD
        include/google/sparsehash/densehashtable.h
        include/google/sparsehash/hashtable-common.h
        include/google/sparsehash/libc_allocator_with_realloc.h
        include/google/sparsehash/sparsehashtable.h
        include/google/template_util.h
        include/google/type_traits.h
        include/sparsehash/internal/densehashtable.h
        include/sparsehash/internal/hashtable-common.h
        include/sparsehash/internal/libc_allocator_with_realloc.h
        include/sparsehash/internal/sparseconfig.h
        include/sparsehash/internal/sparsehashtable.h
        include/sparsehash/template_util.h
        include/sparsehash/type_traits.h
        include/Timer.hpp
        Agent.cpp
        Agent.h
        compute_heuristic.cpp
        compute_heuristic.h
        egraph_reader.cpp
        egraph_reader.h
        Endpoint.cpp
        Endpoint.h
        GA.cpp
        GA.h
        ICBSNode.cpp
        ICBSNode.h
        ICBSSearch.cpp
        ICBSSearch.h
        LLNode.cpp
        LLNode.h
        main.cpp
        map_loader.cpp
        map_loader.h
        MDD.cpp
        MDD.h
        node.cpp
        node.h
        Simulation.cpp
        Simulation.h
        SingleAgentICBS.cpp
        SingleAgentICBS.h
        SingleSearch.cpp
        SingleSearch.h)
