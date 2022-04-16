histogramme :  ./library/source/Image.c ./operation/histogramme.c
	gcc -o histogramme ./library/source/Image.c ./operation/histogramme.c -I. -lm
	
luminance :  ./library/source/Image.c ./operation/luminance.c
	gcc -o luminance ./library/source/Image.c ./operation/luminance.c -I. -lm

contraste :  ./library/source/Image.c ./operation/contraste.c
	gcc -o contraste ./library/source/Image.c ./operation/contraste.c -I. -lm