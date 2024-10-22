#include <cstdlib>
#include <print>

#include <span>
#include <stream/filestream.h>
#include <parserstate.h>
#include <parser.h>
#include <lexer.h>

#include <compiler/testnodevisitor.h>
#include <compiler/buildnodevisitor.h>

auto main(int argc, char** argv) -> int {

	auto args = std::span(argv, static_cast<std::size_t>(argc));

	if (args.size() != 2) {
		std::println(stderr, "wrong number of parameters");
		return EXIT_FAILURE;
	}

	auto stream = FileStream(args[1]);
	auto parser_state = ParserState(std::make_unique<Lexer>(&stream));
	auto parser = yy::parser(&parser_state);

	if (parser.parse() != 0) {
		std::println(stderr, "parsing failed");
		return EXIT_FAILURE;
	}

	std::println(stdout, "parsing succeeded");

	auto tester = TestNodeVisitor();
	parser_state.get_ast()->accept(tester);

	auto builder = BuildNodeVisitor();
	parser_state.get_ast()->accept(builder);

	return EXIT_SUCCESS;
}
