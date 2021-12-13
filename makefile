statSem:
	g++ main.cpp testScanner.cpp scanner.cpp parser.cpp -o statSem

clean:
	rm statSem inputtestfile
