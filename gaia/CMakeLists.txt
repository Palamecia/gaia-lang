project(gaia)

find_package(LLVM CONFIG REQUIRED)

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

add_executable(gaia)

target_sources(
	gaia
PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
	${CMAKE_CURRENT_BINARY_DIR}/parser.h
	compiler/build_node_visitor.cpp
	compiler/build_node_visitor.h
	compiler/test_node_visitor.cpp
	compiler/test_node_visitor.h
	lexer.cpp
	lexer.h
	main.cpp
	node/abstract_node_visitor.cpp
	node/abstract_node_visitor.h
	node/abstract_node.cpp
	node/abstract_node.h
	node/constant_node.cpp
	node/constant_node.h
	node/decl__node.cpp
	node/decl__node.h
	node/flow_node.cpp
	node/flow_node.h
	node/operator_node.cpp
	node/operator_node.h
	parser_state.cpp
	parser_state.h
	parser.y
	stream/document_stream.cpp
	stream/document_stream.h
	stream/file_stream.cpp
	stream/file_stream.h
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(gaia
	${llvm_libs}
)
