###########################
#                         #
#   VARIABLES GENERALES   #
#   -------------------   #

# => de compilation
# compilateur $(CC)
CC = gcc
# parametres du compilateur
CFLAGS = -W -Wall -lm

# => des dossiers utiles
# dossier des fichiers sources de librairies
src_lib = library/source
# dossier des fichiers sources de programme
src_pg = operation
# dossier des fichiers d'extension .o
dir_o = execute/objets
# dossier des executables
dir_exec = execute/executables


#############################
#                           #
#   CIBLES DE COMPILATION   #
#   ---------------------   #

# > les objets de librairies

liste_objets =$(dir_o)/change_domain.o $(dir_o)/convolution.o $(dir_o)/base.o $(dir_o)/Image.o $(dir_o)/Vector.o $(dir_o)/transformation.o $(dir_o)/segmentation.o $(dir_o)/file.o

Vector.o : $(src_lib)/Vector.c
	$(CC) -c $(src_lib)/Vector.c -o $(dir_o)/Vector.o $(CFLAGS)
	
Image.o : $(src_lib)/Image.c
	$(CC) -c $(src_lib)/Image.c -o $(dir_o)/Image.o $(CFLAGS)
	
base.o : $(src_lib)/base.c
	$(CC) -c $(src_lib)/base.c -o $(dir_o)/base.o $(CFLAGS)
	
convolution.o : $(src_lib)/convolution.c
	$(CC) -c $(src_lib)/convolution.c -o $(dir_o)/convolution.o $(CFLAGS)

change_domain.o : $(src_lib)/change_domain.c
	$(CC) -c $(src_lib)/change_domain.c -o $(dir_o)/change_domain.o $(CFLAGS)
	
transformation.o : $(src_lib)/transformation.c
	$(CC) -c $(src_lib)/transformation.c -o $(dir_o)/transformation.o $(CFLAGS)

segmentation.o : $(src_lib)/segmentation.c
	$(CC) -c $(src_lib)/segmentation.c -o $(dir_o)/segmentation.o $(CFLAGS)
	
file.o : $(src_lib)/file.c
	$(CC) -c $(src_lib)/file.c -o $(dir_o)/file.o $(CFLAGS)
	
# > les executables	

histogramme :  $(liste_objets) $(src_pg)/histogramme.c
	$(CC) -c $(src_pg)/histogramme.c -o $(dir_o)/histogramme.o $(CFLAGS)
	$(CC) $(dir_o)/histogramme.o $(liste_objets) -o $(dir_exec)/histogramme $(CFLAGS)
	
luminance :   $(liste_objets) $(src_pg)/luminance.c
	$(CC) -c $(src_pg)/luminance.c -o $(dir_o)/luminance.o $(CFLAGS)
	$(CC) $(dir_o)/luminance.o $(liste_objets) -o $(dir_exec)/luminance $(CFLAGS)

contraste :   $(liste_objets) $(src_pg)/contraste.c 
	$(CC) -c $(src_pg)/contraste.c -o $(dir_o)/contraste.o $(CFLAGS)
	$(CC) $(dir_o)/contraste.o $(liste_objets) -o $(dir_exec)/contraste $(CFLAGS)

main : $(liste_objets)  main.c
	$(CC) -c main.c -o $(dir_o)/main.o $(CFLAGS)
	$(CC) $(dir_o)/main.o $(liste_objets) -o $(dir_exec)/main $(CFLAGS)
	
inverse :   $(liste_objets) $(src_pg)/inverse.c
	$(CC) -c $(src_pg)/inverse.c -o $(dir_o)/inverse.o $(CFLAGS)
	$(CC) $(dir_o)/inverse.o $(liste_objets) -o $(dir_exec)/inverse $(CFLAGS)
	
info :   $(liste_objets) $(src_pg)/info.c 
	$(CC) -c $(src_pg)/info.c -o $(dir_o)/info.o $(CFLAGS)
	$(CC) $(dir_o)/info.o $(liste_objets) -o $(dir_exec)/info $(CFLAGS)
	
binarisation :   $(liste_objets) $(src_pg)/binarisation.c 
	$(CC) -c $(src_pg)/binarisation.c -o $(dir_o)/binarisation.o $(CFLAGS)
	$(CC) $(dir_o)/binarisation.o $(liste_objets) -o $(dir_exec)/binarisation $(CFLAGS)	
	
plus :   $(liste_objets) $(src_pg)/plus.c
	$(CC) -c $(src_pg)/plus.c -o $(dir_o)/plus.o $(CFLAGS)
	$(CC) $(dir_o)/plus.o $(liste_objets) -o $(dir_exec)/plus $(CFLAGS)
	
fois :   $(liste_objets) $(src_pg)/fois.c 
	$(CC) -c $(src_pg)/fois.c -o $(dir_o)/fois.o $(CFLAGS)
	$(CC) $(dir_o)/fois.o $(liste_objets) -o $(dir_exec)/fois $(CFLAGS)

et :   $(liste_objets) $(src_pg)/et.c
	$(CC) -c $(src_pg)/et.c -o $(dir_o)/et.o $(CFLAGS)
	$(CC) $(dir_o)/et.o $(liste_objets) -o $(dir_exec)/et $(CFLAGS)
	
ou :   $(liste_objets) $(src_pg)/ou.c 
	$(CC) -c $(src_pg)/ou.c -o $(dir_o)/ou.o $(CFLAGS)
	$(CC) $(dir_o)/ou.o $(liste_objets) -o $(dir_exec)/ou $(CFLAGS)
	
moins :   $(liste_objets) $(src_pg)/moins.c 
	$(CC) -c $(src_pg)/moins.c -o $(dir_o)/moins.o $(CFLAGS)
	$(CC) $(dir_o)/moins.o $(liste_objets) -o $(dir_exec)/moins $(CFLAGS)

profilIntensite :   $(liste_objets) $(src_pg)/profilIntensite.c
	$(CC) -c $(src_pg)/profilIntensite.c -o $(dir_o)/profilIntensite.o $(CFLAGS)
	$(CC) $(dir_o)/profilIntensite.o $(liste_objets) -o $(dir_exec)/profilIntensite $(CFLAGS)
	
createImage : $(src_pg)/createImage.c
	$(CC) $(src_pg)/createImage.c -o $(dir_exec)/createBinaire 
	
drawDisque :   $(liste_objets) $(src_pg)/dessin/drawDisque.c
	$(CC) -c $(src_pg)/dessin/drawDisque.c -o $(dir_o)/drawDisque.o $(CFLAGS)
	$(CC) $(dir_o)/drawDisque.o $(liste_objets) -o $(dir_exec)/drawDisque $(CFLAGS)
	
drawLine :   $(liste_objets) $(src_pg)/dessin/drawLine.c 
	$(CC) -c $(src_pg)/dessin/drawLine.c -o $(dir_o)/drawLine.o $(CFLAGS)
	$(CC) $(dir_o)/drawLine.o $(liste_objets) -o $(dir_exec)/drawLine $(CFLAGS)

drawRectangle :   $(liste_objets) $(src_pg)/dessin/drawRectangle.c 
	$(CC) -c $(src_pg)/dessin/drawRectangle.c -o $(dir_o)/drawRectangle.o $(CFLAGS)
	$(CC) $(dir_o)/drawRectangle.o $(liste_objets) -o $(dir_exec)/drawRectangle $(CFLAGS)
	
convoluerMedian :   $(liste_objets) $(src_pg)/convolution/convoluerMedian.c 
	$(CC) -c $(src_pg)/convolution/convoluerMedian.c -o $(dir_o)/convoluerMedian.o $(CFLAGS)
	$(CC) $(dir_o)/convoluerMedian.o $(liste_objets) -o $(dir_exec)/convoluerMedian $(CFLAGS)

convoluer :   $(liste_objets) $(src_pg)/convolution/convoluer.c
	$(CC) -c $(src_pg)/convolution/convoluer.c -o $(dir_o)/convoluer.o $(CFLAGS)
	$(CC) $(dir_o)/convoluer.o $(liste_objets) -o $(dir_exec)/convoluer $(CFLAGS)
	
houghTransform : $(liste_objets) $(src_pg)/transformation/houghTransform.c
	$(CC) -c $(src_pg)/transformation/houghTransform.c -o $(dir_o)/houghTransform.o $(CFLAGS)
	$(CC) $(dir_o)/houghTransform.o $(liste_objets) -o $(dir_exec)/houghTransform $(CFLAGS)
	
egalizeur_hist : $(liste_objets) $(src_pg)/transformation/egalizeur_hist.c
	$(CC) -c $(src_pg)/transformation/egalizeur_hist.c -o $(dir_o)/egalizeur_hist.o $(CFLAGS)
	$(CC) $(dir_o)/egalizeur_hist.o $(liste_objets) -o $(dir_exec)/egalizeur_hist $(CFLAGS)
	
transformation_lineaire : $(liste_objets) $(src_pg)/transformation/transformation_lineaire.c
	$(CC) -c $(src_pg)/transformation/transformation_lineaire.c -o $(dir_o)/transformation_lineaire.o $(CFLAGS)
	$(CC) $(dir_o)/transformation_lineaire.o $(liste_objets) -o $(dir_exec)/transformation_lineaire $(CFLAGS)

transformation_lineaire_satur : $(liste_objets) $(src_pg)/transformation/transformation_lineaire_satur.c
	$(CC) -c $(src_pg)/transformation/transformation_lineaire_satur.c -o $(dir_o)/transformation_lineaire_satur.o $(CFLAGS)
	$(CC) $(dir_o)/transformation_lineaire_satur.o $(liste_objets) -o $(dir_exec)/transformation_lineaire_satur $(CFLAGS)
	
transformation_lineaire_morceau : $(liste_objets) $(src_pg)/transformation/transformation_lineaire_morceau.c
	$(CC) -c $(src_pg)/transformation/transformation_lineaire_morceau.c -o $(dir_o)/transformation_lineaire_morceau.o $(CFLAGS)
	$(CC) $(dir_o)/transformation_lineaire_morceau.o $(liste_objets) -o $(dir_exec)/transformation_lineaire_morceau $(CFLAGS)

kmeans : $(liste_objets) $(src_pg)/segmentation/kmeans.c
	$(CC) -c $(src_pg)/segmentation/kmeans.c -o $(dir_o)/kmeans.o $(CFLAGS)
	$(CC) $(dir_o)/kmeans.o $(liste_objets) -o $(dir_exec)/kmeans $(CFLAGS)

germe : $(liste_objets) $(src_pg)/segmentation/germe.c
	$(CC) -c $(src_pg)/segmentation/germe.c -o $(dir_o)/germe.o $(CFLAGS)
	$(CC) $(dir_o)/germe.o $(liste_objets) -o $(dir_exec)/germe $(CFLAGS)
	
###########################
#                         #
#   OPERATIONS GLOBALES   #
#   -------------------   #
