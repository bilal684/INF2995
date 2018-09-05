////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// 
/// @date 2016-03-14
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////

#include "vueOrthoTest.h"
#include "Utilitaire.h"

using namespace vue;

CPPUNIT_TEST_SUITE_REGISTRATION(VueOrthoTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void VueOrthoTest::setUp()
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
void VueOrthoTest::setUp()
{
	//initialisation tiree de FacadeModele.cpp
	xMinClotureTest_ = 0;
	xMaxClotureTest_ = 500;
	yMinClotureTest_ = 0;
	yMaxClotureTest_ = 500;
	zAvantTest_ = 1;
	zArriereTest_ = 1000;
	zoomInMaxTest_ = 1;
	zoomOutMaxTest_ = 1000;
	incrementZoomTest_ = 1.25;
	xMinFenetreTest_ = -25;
	xMaxFenetreTest_ = 25;
	yMinFenetreTest_ = -25;
	yMaxFenetreTest_ = 25;

	//initialisation tiree de Camera.cpp
	glm::dvec3& position_ = glm::dvec3(0, 0, 200);
	pointVise_ = glm::dvec3(0, 29, 0);
	directionHautCamera_ = glm::dvec3(0, 1, 0);
	directionHautMonde_ = glm::dvec3(0, 1, 0);

	projectionOrthoTest_ = new ProjectionOrtho(xMinClotureTest_, xMaxClotureTest_, yMinClotureTest_, yMaxClotureTest_,
		zAvantTest_, zArriereTest_, zoomInMaxTest_, zoomOutMaxTest_,
		incrementZoomTest_, xMinFenetreTest_, xMaxFenetreTest_,
		yMinFenetreTest_, yMaxFenetreTest_);
	cameraTest_ = new Camera(position_, pointVise_, directionHautCamera_, directionHautMonde_);
	vueOrthoTest_ = new VueOrtho(*cameraTest_, *projectionOrthoTest_);
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
void VueOrthoTest::tearDown()
{
	delete projectionOrthoTest_;
	delete cameraTest_;
	delete vueOrthoTest_;
	projectionOrthoTest_ = 0;
	cameraTest_ = 0;
	vueOrthoTest_ = 0;
}


/// Permet de faire un zoom in sur un rectangle déterminé par deux coins.
/// Ainsi la région délimitée par le rectangle deviendra la fenêtre
/// virtuelle.  La fenêtre résultante est ajustée pour respecter le rapport
/// d'aspect.
////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testRedimentionnementDeLaFenetre()
///
/// pour tester si la fonction fait le bon zoom in sur un rectangle déterminé par deux coins 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VueOrthoTest::testZoomerInElastique()
{
	std::cout << "     VUE_ORTHO_testZoomerInElastique" << std::endl;
	/* Cas 1 : On vérifie que la région délimitée par le rectangle devient la fenêtre virtuelle
	int rapportClotureBase = (xMaxClotureTest_ - xMinClotureTest_) / (yMaxClotureTest_ - yMinClotureTest_);
	vueOrthoTest_->zoomerInElastique(glm::ivec2(-10, -20), glm::ivec2(30, 50));
	int xMinCloture, xMaxCloture, yMinCoture, yMaxCloture;
	projectionOrthoTest_->obtenirCoordonneesCloture(xMinCloture, xMaxCloture, yMinCoture, yMaxCloture);
	int rapportCloture = (xMaxCloture - xMinCloture) / (yMaxCloture - yMinCoture);
	CPPUNIT_ASSERT(rapportClotureBase == rapportCloture);
	// Cas 2 : Le rapport d'aspect est respecté
	double xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre;
	projectionOrthoTest_->obtenirCoordonneesFenetreVirtuelle(xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre);
	int rapportFenetre = (int)(xMaxFenetre - xMinFenetre) / (int)(yMaxFenetre - yMinFenetre);
	//std::cout << xMaxFenetre << std::endl;
	CPPUNIT_ASSERT(rapportCloture == rapportFenetre);*/
	std::cout << "pbm avec openGL" << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testDeplacerFenetreVirtuelleClavier()
///
/// Permet le deplacement de la fenetre virtuelle a l'aide de la touche haut au bas du clavier
///
/// @return Aucune.
///
void VueOrthoTest::testDeplacerFenetreVirtuelleClavier()
{
	std::cout << "     VUE_ORTHO_testDeplacerFenetreVirtuelleClavier" << std::endl;
	int xMin, xMax, yMin, yMax;
	projectionOrthoTest_->obtenirCoordonneesCloture(xMin, xMax, yMin, yMax);
	std::cout << "pbm avec openGL" << std::endl;
	
}
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////