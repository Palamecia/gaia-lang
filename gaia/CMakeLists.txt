project(gaia)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

find_package(BISON REQUIRED)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/parser.h ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
	COMMAND ${BISON_EXECUTABLE}
	ARGS -y ${CMAKE_CURRENT_SOURCE_DIR}/parser.y
	     --output=${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
		 --defines=${CMAKE_CURRENT_BINARY_DIR}/parser.h
		 -Wcounterexamples
		 -Wno-yacc
		 -L C++
		 -v
	COMMENT "Generating file parser.cpp"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(gaia
	${CMAKE_CURRENT_BINARY_DIR}/parser.h ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	compiler/buildnodevisitor.h compiler/buildnodevisitor.cpp
	compiler/testnodevisitor.h compiler/testnodevisitor.cpp
	lexer.h lexer.cpp
	main.cpp parser.y
	node/abstractnode.h node/abstractnode.cpp
	node/abstractnodevisitor.h node/abstractnodevisitor.cpp
	node/constantnode.h node/constantnode.cpp
	node/declnode.h node/declnode.cpp
	node/flownode.h node/flownode.cpp
	node/operatornode.h node/operatornode.cpp
	parserstate.h parserstate.cpp
	stream/documentstream.h stream/documentstream.cpp
	stream/filestream.h stream/filestream.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(gaia
	${llvm_libs}
)
