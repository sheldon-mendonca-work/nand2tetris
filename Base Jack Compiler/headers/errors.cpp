#include "./errors.hpp"

std::string errors::FileHandlingException::what() {
	return _errMsg;
}

std::string errors::IllegalCallException::what() {
	return _errMsg;
}

std::string errors::SyntaxErrorException::what() {
	_errMsg = _errMsg + " at line: " + std::to_string(_lineNum) + ", at position: " + std::to_string(_pos) + ".\n";
    return _errMsg;
}
std::string errors::UndefinedSymbolException::what() {
	return _errMsg;
}