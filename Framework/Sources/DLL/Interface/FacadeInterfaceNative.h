////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990 Eq.11
/// @date   2016-02-15
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

extern "C" {

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL(double temps);
	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void animer(double temps);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();
	__declspec(dllexport) void deplacerHaut();
	__declspec(dllexport) void deplacerBas();
	__declspec(dllexport) void deplacerGauche();
	__declspec(dllexport) void deplacerDroite();
	__declspec(dllexport) void deplacerFenetreVirtuelleSouris(int x, int y);
	__declspec(dllexport) void sauverPositionSouris(int x, int y);
	__declspec(dllexport)  int obtenirAffichagesParSeconde();
	__declspec(dllexport) bool executerTests();
	__declspec(dllexport)  int obtenirVue();
	__declspec(dllexport) void ajouterNoeudSimple(char* nom, int x, int y);
	__declspec(dllexport) void ajouterNoeudAvecScale(char* nom, int x1, int y1, int x2, int y2, bool estConcret);
	__declspec(dllexport) void supprimerDernierNoeud();
	__declspec(dllexport) void supprimerDerniereLigne();
	__declspec(dllexport) bool verifierPositionCurseur(int x, int y);
	__declspec(dllexport) bool verifierCurseurPoteau(int x, int y);
	__declspec(dllexport) bool verifierCurseurFinMur(int xDebut, int yDebut, int xFin, int yFin);
	__declspec(dllexport) bool verifierCurseurFinLigne(int xDebut, int yDebut, int xFin, int yFin);
	__declspec(dllexport) void enregistrerZoneDeSimulation(char* nomFichier);
	__declspec(dllexport) void chargerZoneDeSimulation(char* nomFichier);
	__declspec(dllexport) void tracerRectangleElastique(int x, int y);
	__declspec(dllexport) void terminerRectangleElastique(int x, int y);
	__declspec(dllexport) void zoomInRectangle(int xMin, int xMax, int yMin, int yMax);
	__declspec(dllexport) void zoomOutRectangle(int xMin, int xMax, int yMin, int yMax);
	__declspec(dllexport) void reInitialiserScene();

	//Selection

	__declspec(dllexport) void deplacerSelection(int xDebut, int yDebut, int xFin, int yFin);
	__declspec(dllexport) void scaleSelection(double facteurScale);
	__declspec(dllexport) int obtenirNmbreNoeudsSelectionnes();

	__declspec(dllexport) void selectionObjet(int mouseX, int mouseY, bool selectionUnique);
	__declspec(dllexport) void selectRectElastique(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce);

	//rotation d'un seul objet
	__declspec(dllexport) void PivoterObjetSelectionne(double deltaY);
	//rotation de plusieurs objets selectionnes
	__declspec(dllexport) void PivoterObjetsMultiples(double rotation);

	//Supression de la selection
	__declspec(dllexport) void supprimerSelection();

	__declspec(dllexport) bool assignerPositionPourObjetSelectionne(double x, double y, double z);
	__declspec(dllexport) void assignerRotationPourObjetSelectionne(double rotation);
	__declspec(dllexport) bool changerScalePourObjetSelectionne(double scale);
	__declspec(dllexport) void initialiserEnTraitement();
	__declspec(dllexport) void initialiserScaleEnTraitement();
	

	//Duplication de noeuds selectionnes
	__declspec(dllexport) bool dupliquerObjetsSelectionnes(int x, int y, bool estFantome);
	//Suppression de noeuds dupliques
	__declspec(dllexport) void supprimerNoeudsDupliques();

	__declspec(dllexport) bool objetsSelectionnesSurLaTable();
	__declspec(dllexport) bool tournerObjetSelectionne(double angle);
	__declspec(dllexport) void annulerRotationSelection();
	
	__declspec(dllexport) int obtenirNombreElementsSelectionns();
	__declspec(dllexport) void retournerAuScaleInitiale();


	__declspec(dllexport) void initialiserRobot(bool vuePremierePersonne);
	__declspec(dllexport) void arreterRobot();
	__declspec(dllexport) void actionnerRobot(double rapportVitesseGauche, double rapportVitesseDroit, bool sensDirect);

	__declspec(dllexport) void stopperModeAutomatique();
	__declspec(dllexport) void actionnerModeAutomatique();

	//test suiveurligne
	__declspec(dllexport) void debuterSimulation();

	__declspec(dllexport) void chargerProfilRobot(char* nomProfil);

	__declspec(dllexport) void libererRobot();

	__declspec(dllexport) void basculerActivationLumiereAmbiante();
	__declspec(dllexport) void basculerActivationLumiereDirectionnelle();
	__declspec(dllexport) void basculerActivationSpots();
	__declspec(dllexport) void basculerActivationDebougage();

	//
	__declspec(dllexport) double obtenirPositionXElementSelectionne();
	__declspec(dllexport) double obtenirPositionYElementSelectionne();
	__declspec(dllexport) double obtenirRotationElementSelectionne();
	__declspec(dllexport) double obtenirEchelleElementSelectionne();
	__declspec(dllexport) bool noeudSelectionneEstFleche();
	__declspec(dllexport) bool noeudSelectionneEstLigne();
		
	// camera orbite, orthographique 
	__declspec(dllexport) void activerVueOrbite();
	__declspec(dllexport) void activerVueOrthographique();
	__declspec(dllexport) void activerVuePremierePersonne();
	__declspec(dllexport) void changerModeApplication(char mode);
	
	//Son
	__declspec(dllexport) void __cdecl jouerMusiqueSimulation();
	//initialiserSonEditeur
	__declspec(dllexport) void __cdecl initialiserSonEditeur();
	__declspec(dllexport) void __cdecl libererFmod();
	__declspec(dllexport) void __cdecl pauseSonSimulation();
	__declspec(dllexport) void __cdecl UnPauseSonSimulation();
}

#endif // __FACADE_INTERFACE_NATIVE_H__
