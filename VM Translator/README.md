To build the translator from main directory:

g++-12 ./VM\ Translator/translator.cpp -o ./VM\ Translator/translator ./VM\ Translator/headers/parser.cpp ./VM\ Translator/headers/errors.cpp ./VM\ Translator/headers/code.cpp ./VM\ Translator/headers/ioFileHandler.cpp

To run the VM Translator, two arguments are provided. Example:

./VM\ Translator/translator ./projects/07/MemoryAccess/BasicTest/BasicTest.vm