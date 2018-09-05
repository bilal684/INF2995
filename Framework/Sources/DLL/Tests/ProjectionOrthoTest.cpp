////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// @author Equipe 11
/// @date 2016-03-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "projectionOrthoTest.h"
#include "Utilitaire.h"

using namespace vue;

CPPUNIT_TEST_SUITE_REGISTRATION(ProjectionOrthoTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::setUp()
{
	//initialisation inspirée de FacadeModele.cpp
	xMinCloture_ = 0;
	xMaxCloture_ = 500;
	yMinCloture_ = 0;
	yMaxCloture_ = 500;
	zAvant_ = 1;
	zArriere_ = 1000;
	zoomInMax_ = 1;
	zoomOutMax_ = 1000;
	incrementZoom_ = 1.25;
	xMinFenetre_ = -25;
	xMaxFenetre_ = 25;
	yMinFenetre_ = -25;
	yMaxFenetre_ = 25;
	projectionOrtho_ = new ProjectionOrtho(xMinCloture_, xMaxCloture_, yMinCloture_, yMaxCloture_,
		zAvant_, zArriere_, zoomInMax_, zoomOutMax_,
		incrementZoom_, xMinFenetre_, xMaxFenetre_,
		yMinFenetre_, yMaxFenetre_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::tearDown()
{
	delete projectionOrtho_;
	projectionOrtho_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testRedimentionnementDeLaFenetre()
///
/// pour tester si la fonction fait le bon redimentionnement de la fenêtre 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testRedimensionnerFenetre()
{
	// Cas 1 : On vérifie qu'initialement, le rapport d'aspect est respecté
	int xMinCloture, xMaxCloture, yMinCoture, yMaxCloture;
	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrtho_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);
	projectionOrtho_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
	int rapportCloture = (xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture);
	int rapportFenetre = (int)(xMaxFenetre - xMinFenetre) / (int)(yMaxFenetre - yMinFenetre);
			// Rapport d'aspect respecté
	CPPUNIT_ASSERT(rapportCloture == rapportFenetre);
	// Cas 2 : On redimensionne la fenêtre, puis vérifie si le rapport d'aspect est respecté
	projectionOrtho_->redimensionnerFenetre(glm::ivec2(0, 0), (glm::ivec2(2500,3000)));
	projectionOrtho_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);
	projectionOrtho_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
	rapportCloture = (xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture);
	rapportFenetre = (int)(xMaxFenetre - xMinFenetre) / (int)(yMaxFenetre - yMinFenetre);
			// Rapport d'aspect respecté
	CPPUNIT_ASSERT(rapportCloture == rapportFenetre);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testZoomIn()
///
/// pour tester si la fonction fait le bon zoom avant ou arrière
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testZoom()
{
	// Cas 1 : On vérifie qu'initialement, aucun zoom n'est appliqué. Autrement dit le facteur de zoom est unitaire
	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrtho_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
	double zoom1 = yMaxFenetre_ / yMaxFenetre;
	double zoom2 = yMinFenetre_ / yMinFenetre;
	double zoom3 = xMaxFenetre_ / xMaxFenetre;
	double zoom4 = xMinFenetre_ / xMinFenetre;
	CPPUNIT_ASSERT(zoom1 == FACTEUR_ZOOM_UNITAIRE && zoom2 == FACTEUR_ZOOM_UNITAIRE && zoom3 == FACTEUR_ZOOM_UNITAIRE && zoom4 == FACTEUR_ZOOM_UNITAIRE);
	// Cas 2 : On applique un zoomIn
	projectionOrtho_->zoomerIn();
	projectionOrtho_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
			// Le zoomIn diminue les bornes supérieures en X et Y de la fenêtre virtuelle
	CPPUNIT_ASSERT(xMaxFenetre < xMaxFenetre_ && yMaxFenetre < yMaxFenetre_);
	        // Le zoomIn agrandit les bornes inférieures en X et Y de la fenêtre virtuelle
	CPPUNIT_ASSERT(xMinFenetre_ < xMinFenetre && yMinFenetre_ < yMinFenetre);
	// Cas 3 : Le zoomIn se fait selon l'incrément de zoom : incrementZoomTest_.
	zoom1 = yMaxFenetre_ / yMaxFenetre;
	zoom2 = yMinFenetre_ / yMinFenetre;
	zoom3 = xMaxFenetre_ / xMaxFenetre;
	zoom4 = xMinFenetre_ / xMinFenetre;
	CPPUNIT_ASSERT(zoom1 == incrementZoom_ && zoom2 == incrementZoom_ && zoom3 == incrementZoom_ && zoom4 == incrementZoom_);
	// Cas 4 : On applique un nombre égal de zooms avant et arrière. Autrement dit le facteur de zoom serait unitaire
	projectionOrtho_->zoomerOut(); // pour annihiler le premier zoomIn()
	projectionOrtho_->zoomerIn();
	projectionOrtho_->zoomerIn();
	projectionOrtho_->zoomerIn();
	projectionOrtho_->zoomerOut();
	projectionOrtho_->zoomerOut();
	projectionOrtho_->zoomerOut();
	projectionOrtho_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
	zoom1 = yMaxFenetre_ / yMaxFenetre;
	zoom2 = yMinFenetre_ / yMinFenetre;
	zoom3 = xMaxFenetre_ / xMaxFenetre;
	zoom4 = xMinFenetre_ / xMinFenetre;
	CPPUNIT_ASSERT(zoom1 == FACTEUR_ZOOM_UNITAIRE && zoom2 == FACTEUR_ZOOM_UNITAIRE && zoom3 == FACTEUR_ZOOM_UNITAIRE && zoom4 == FACTEUR_ZOOM_UNITAIRE);

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////