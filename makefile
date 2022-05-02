histogramme :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/histogramme.c
	gcc -o execute/histogramme ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/histogramme.c -I. -lm
	
luminance :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/luminance.c
	gcc -o execute/luminance ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/luminance.c -I. -lm

contraste :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/contraste.c 
	gcc -o execute/contraste ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/contraste.c -I. -lm

main : ./library/source/Vector.c ./library/source/base.c  main.c
	gcc -o execute/main ./library/source/Vector.c ./library/source/base.c  main.c -I. -lm
	
inverse :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/inverse.c 
	gcc -o execute/inverse ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/inverse.c -I. -lm
	
info :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/info.c 
	gcc -o execute/info ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/info.c -I. -lm
	
binarisation :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/binarisation.c 
	gcc -o execute/binarisation ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/binarisation.c -I. -lm	
	
plus :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/plus.c 
	gcc -o execute/plus ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/plus.c -I. -lm
	
fois :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/fois.c 
	gcc -o execute/fois ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/fois.c -I. -lm

et :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/et.c 
	gcc -o execute/et ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/et.c -I. -lm
	
ou :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/ou.c 
	gcc -o execute/ou ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/ou.c -I. -lm
	
moins :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/moins.c 
	gcc -o execute/moins ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/moins.c -I. -lm

profilIntensite :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/profilIntensite.c 
	gcc -o execute/profilIntensite ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/profilIntensite.c -I. -lm
	
createImage : ./operation/createImage.c 
	gcc ./operation/createImage.c -o createBinaire 
	
drawDisque :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawDisque.c 
	gcc -o execute/drawDisque ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawDisque.c -I. -lm
	
drawLine :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawLine.c 
	gcc -o execute/drawLine ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawLine.c -I. -lm

drawRectangle :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawRectangle.c 
	gcc -o execute/drawRectangle ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/dessin/drawRectangle.c -I. -lm
	
convoluerMedian :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/convolution/convoluerMedian.c 
	gcc -o execute/convoluerMedian ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/convolution/convoluerMedian.c -I. -lm

convoluer :   ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/convolution/convoluer.c 
	gcc -o execute/convoluer ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c ./library/source/Image.c ./operation/convolution/convoluer.c -I. -lm
	
houghTransform :   
	gcc -o execute/houghTransform ./library/source/Vector.c ./library/source/base.c ./library/source/convolution.c ./library/source/change_domain.c  ./library/source/Image.c ./operation/transformation/houghTransform.c -I. -lm

