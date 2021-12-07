parser:
	g++ main.cpp testScanner.cpp scanner.cpp parser.cpp -o parser

clean:
	rm parser inputtestfile
