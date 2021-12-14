compfs:
	g++ main.cpp testScanner.cpp scanner.cpp parser.cpp -o compfs

clean:
	rm compfs inputtestfile
