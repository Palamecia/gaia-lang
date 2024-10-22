#include <cstdlib>

#include <stream/filestream.h>
#include <parserstate.h>
#include <parser.h>
#include <lexer.h>

#include <compiler/testnodevisitor.h>
#include <compiler/buildnodevisitor.h>

int main(int argc, char** argv) {

	if (argc != 2) {
		fprintf(stderr, "wrong number of parameters\n");
		return EXIT_FAILURE;
	}

	FileStream stream(argv[1]);
	ParserState parser_state(std::make_unique<Lexer>(&stream));
	yy::parser parser(&parser_state);

	if (parser.parse() != 0) {
		fprintf(stderr, "parsing failed\n");
		return EXIT_FAILURE;
	}

	fprintf(stdout, "parsing succed\n");

	TestNodeVisitor tester;
	parser_state.get_ast()->accept(&tester);

	BuildNodeVisitor builder;
	parser_state.get_ast()->accept(&tester);

    return EXIT_SUCCESS;
}
