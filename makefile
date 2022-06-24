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

l1 =$(dir_o)/change_domain.o $(dir_o)/convolution.o $(dir_o)/base.o $(dir_o)/Image.o $(dir_o)/Vector.o
l2 =$(dir_o)/transformation.o $(dir_o)/segmentation.o $(dir_o)/file.o $(dir_o)/stack.o $(dir_o)/Complex.o
liste_objets =$(l1) $(l2)

Vector.o : $(src_lib)/Vector.c
	$(CC) -c $(src_lib)/Vector.c -o $(dir_o)/Vector.o $(CFLAGS)
	
Complex.o : $(src_lib)/Complex.c
	$(CC) -c $(src_lib)/Complex.c -o $(dir_o)/Complex.o $(CFLAGS)
	
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

stack.o : $(src_lib)/stack/stack.c
	$(CC) -c $(src_lib)//stack/stack.c -o $(dir_o)/stack.o $(CFLAGS)
	
# > les executables	
createImage : $(src_pg)/createImage.c
	$(CC) $(src_pg)/createImage.c -o $(dir_exec)/createBinaire 
	
main : $(liste_objets)  main.c
	$(CC) -c main.c -o $(dir_o)/main.o $(CFLAGS)
	$(CC) $(dir_o)/main.o $(liste_objets) -o $(dir_exec)/main $(CFLAGS)

histogramme :  $(liste_objets) $(src_pg)/histogramme.c
	$(CC) -c $(src_pg)/histogramme.c -o $(dir_o)/histogramme.o $(CFLAGS)
	$(CC) $(dir_o)/histogramme.o $(liste_objets) -o $(dir_exec)/histogramme $(CFLAGS)

	
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
	
	
drawDisque :   $(liste_objets) $(src_pg)/dessin/drawDisque.c
	$(CC) -c $(src_pg)/dessin/drawDisque.c -o $(dir_o)/drawDisque.o $(CFLAGS)
	$(CC) $(dir_o)/drawDisque.o $(liste_objets) -o $(dir_exec)/drawDisque $(CFLAGS)
	
drawLine :   $(liste_objets) $(src_pg)/dessin/drawLine.c 
	$(CC) -c $(src_pg)/dessin/drawLine.c -o $(dir_o)/drawLine.o $(CFLAGS)
	$(CC) $(dir_o)/drawLine.o $(liste_objets) -o $(dir_exec)/drawLine $(CFLAGS)
	
drawLines :   $(liste_objets) $(src_pg)/dessin/drawLines.c 
	$(CC) -c $(src_pg)/dessin/drawLines.c -o $(dir_o)/drawLines.o $(CFLAGS)
	$(CC) $(dir_o)/drawLines.o $(liste_objets) -o $(dir_exec)/drawLines $(CFLAGS)

drawRectangle :   $(liste_objets) $(src_pg)/dessin/drawRectangle.c 
	$(CC) -c $(src_pg)/dessin/drawRectangle.c -o $(dir_o)/drawRectangle.o $(CFLAGS)
	$(CC) $(dir_o)/drawRectangle.o $(liste_objets) -o $(dir_exec)/drawRectangle $(CFLAGS)
	
convoluerMedian :   $(liste_objets) $(src_pg)/convolution/convoluerMedian.c 
	$(CC) -c $(src_pg)/convolution/convoluerMedian.c -o $(dir_o)/convoluerMedian.o $(CFLAGS)
	$(CC) $(dir_o)/convoluerMedian.o $(liste_objets) -o $(dir_exec)/convoluerMedian $(CFLAGS)
	
convoluerGauss :   $(liste_objets) $(src_pg)/convolution/convoluerGauss.c 
	$(CC) -c $(src_pg)/convolution/convoluerGauss.c -o $(dir_o)/convoluerGauss.o $(CFLAGS)
	$(CC) $(dir_o)/convoluerGauss.o $(liste_objets) -o $(dir_exec)/convoluerGauss $(CFLAGS)
	
convoluerMoyenne :   $(liste_objets) $(src_pg)/convolution/convoluerMoyenne.c 
	$(CC) -c $(src_pg)/convolution/convoluerMoyenne.c -o $(dir_o)/convoluerMoyenne.o $(CFLAGS)
	$(CC) $(dir_o)/convoluerMoyenne.o $(liste_objets) -o $(dir_exec)/convoluerMoyenne $(CFLAGS)
	
convoluer :   $(liste_objets) $(src_pg)/convolution/convoluer.c
	$(CC) -c $(src_pg)/convolution/convoluer.c -o $(dir_o)/convoluer.o $(CFLAGS)
	$(CC) $(dir_o)/convoluer.o $(liste_objets) -o $(dir_exec)/convoluer $(CFLAGS)

gradient :   $(liste_objets) $(src_pg)/convolution/gradient.c
	$(CC) -c $(src_pg)/convolution/gradient.c -o $(dir_o)/gradient.o $(CFLAGS)
	$(CC) $(dir_o)/gradient.o $(liste_objets) -o $(dir_exec)/gradient $(CFLAGS)
	
laplacien :   $(liste_objets) $(src_pg)/convolution/laplacien.c
	$(CC) -c $(src_pg)/convolution/laplacien.c -o $(dir_o)/laplacien.o $(CFLAGS)
	$(CC) $(dir_o)/laplacien.o $(liste_objets) -o $(dir_exec)/laplacien $(CFLAGS)

fourierTransform : $(liste_objets) $(src_pg)/transformation/fourierTransform.c
	$(CC) -c $(src_pg)/transformation/fourierTransform.c -o $(dir_o)/fourierTransform.o $(CFLAGS)
	$(CC) $(dir_o)/fourierTransform.o $(liste_objets) -o $(dir_exec)/fourierTransform $(CFLAGS)
	
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

interpolation_knn : $(liste_objets) $(src_pg)/transformation/interpolation_knn.c
	$(CC) -c $(src_pg)/transformation/interpolation_knn.c -o $(dir_o)/interpolation_knn.o $(CFLAGS)
	$(CC) $(dir_o)/interpolation_knn.o $(liste_objets) -o $(dir_exec)/interpolation_knn $(CFLAGS)
	
interpolation_bil : $(liste_objets) $(src_pg)/transformation/interpolation_bil.c
	$(CC) -c $(src_pg)/transformation/interpolation_bil.c -o $(dir_o)/interpolation_bil.o $(CFLAGS)
	$(CC) $(dir_o)/interpolation_bil.o $(liste_objets) -o $(dir_exec)/interpolation_bil $(CFLAGS)
	
kmeans : $(liste_objets) $(src_pg)/segmentation/kmeans.c
	$(CC) -c $(src_pg)/segmentation/kmeans.c -o $(dir_o)/kmeans.o $(CFLAGS)
	$(CC) $(dir_o)/kmeans.o $(liste_objets) -o $(dir_exec)/kmeans $(CFLAGS)

germe : $(liste_objets) $(src_pg)/segmentation/germe.c
	$(CC) -c $(src_pg)/segmentation/germe.c -o $(dir_o)/germe.o $(CFLAGS)
	$(CC) $(dir_o)/germe.o $(liste_objets) -o $(dir_exec)/germe $(CFLAGS)

seuillage_auto : $(liste_objets) $(src_pg)/segmentation/seuillage_auto.c
	$(CC) -c $(src_pg)/segmentation/seuillage_auto.c -o $(dir_o)/seuillage_auto.o $(CFLAGS)
	$(CC) $(dir_o)/seuillage_auto.o $(liste_objets) -o $(dir_exec)/seuillage_auto $(CFLAGS)

seuillage : $(liste_objets) $(src_pg)/segmentation/seuillage.c
	$(CC) -c $(src_pg)/segmentation/seuillage.c -o $(dir_o)/seuillage.o $(CFLAGS)
	$(CC) $(dir_o)/seuillage.o $(liste_objets) -o $(dir_exec)/seuillage $(CFLAGS)
	
seuillage_multiple : $(liste_objets) $(src_pg)/segmentation/seuillage_multiple.c
	$(CC) -c $(src_pg)/segmentation/seuillage_multiple.c -o $(dir_o)/seuillage_multiple.o $(CFLAGS)
	$(CC) $(dir_o)/seuillage_multiple.o $(liste_objets) -o $(dir_exec)/seuillage_multiple $(CFLAGS)
	
###########################
#                         #
#   OPERATIONS GLOBALES   #
#   -------------------   #
