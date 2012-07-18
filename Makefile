example: main.cpp nfont.c nfont.h
	convert font.png -depth 2 gray:font_data
	ld -r -b binary -o font_data.o font_data
	g++ main.cpp nfont.c font_data.o -o example -lSDL

clean:
	rm example
