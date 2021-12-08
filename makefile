frontEnd:
	g++ main.cpp testScanner.cpp scanner.cpp parser.cpp -o frontEnd

clean:
	rm frontEnd inputtestfile
