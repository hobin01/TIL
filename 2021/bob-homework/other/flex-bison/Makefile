hw: 	hw.l hw.y
	bison -d hw.y
	flex hw.l
	gcc -o $@ hw.tab.c lex.yy.c -lfl

