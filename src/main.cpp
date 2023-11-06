#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "scanner.h"
#include "token.h"

namespace next {

void run(const std::string& src) {
	scanner* sc = new scanner(src);
	try {
		std::vector<token> tokens = sc->scan_tokens();
		for (const auto& tk : tokens)
			std::cout << tk.to_string() << std::endl << std::endl;
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}
	delete sc;
}

void run_prompt() {
	std::string ln;
	for (;;) {
		std::cout << "> ";
		std::getline(std::cin, ln);
		if (ln == "quit.")
			break;
		run(ln);
	}
}

void run_file(const std::string& path) {
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string src = ss.str();
	run(src);
}

} // next

int main(int argc, char* argv[]) {
	if (argc > 2) {
		std::cout << "Usage: next [prog.nxt]" << std::endl;
		return 1;
	} else if (argc == 2) {
		next::run_file(argv[1]);
	} else {
		next::run_prompt();
	}
	return 0;
}