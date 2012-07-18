example_linux: main.cpp nfont.c nfont.h
	convert font.png -depth 2 gray:font_data
	ld -r -b binary -o font_data.o font_data
	g++ main.cpp nfont.c font_data.o -o example -lSDL

example_mac: 
	cp font_data _binary_font_data_start
	xxd -i _binary_font_data_start > font_data.h
	g++ main.cpp nfont.c -o example -lSDL  -L/usr/local/lib -lSDLmain -framework Cocoa


clean:
	rm example
