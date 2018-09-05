////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author Equipe 11
/// @date 2016-03-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TEST_PROJECTIONORTHOTESTS_H
#define _TEST_PROJECTIONORTHOTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include "ProjectionOrtho.h"
#include "VueOrtho.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement de
///        quelques méthodes de la classe ProjectionOrtho
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(ProjectionOrthoTest);
		CPPUNIT_TEST(testRedimensionnerFenetre);
		CPPUNIT_TEST(testZoom);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// Définissez ici les différents cas de tests...
	// =================================================================

	/// Cas de test:
	void testRedimensionnerFenetre();
	/// Cas de test:
	void testZoom();

private:

	int xMinCloture_;
	int xMaxCloture_;
	int yMinCloture_;
	int yMaxCloture_;
	double zAvant_; 
	double zArriere_;
	double zoomInMax_;
	double zoomOutMax_;
	double incrementZoom_;
	double xMinFenetre_;
	double xMaxFenetre_;
	double yMinFenetre_;
	double yMaxFenetre_;
	vue::ProjectionOrtho *projectionOrtho_;

};

#endif 
///////////////////////////////////////////////////////////////////////////////
