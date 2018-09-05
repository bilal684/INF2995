////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrthoTest.h
/// 
/// @date 2016-03-14
/// @version 1.0
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TEST_VUEORTHOTESTS_H
#define _TEST_VUEORTHOTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include "ProjectionOrtho.h"
#include "VueOrtho.h"

///////////////////////////////////////////////////////////////////////////
/// @class VueOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe VueOrtho
///
///////////////////////////////////////////////////////////////////////////
class VueOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(VueOrthoTest);
	CPPUNIT_TEST(testZoomerInElastique);
	CPPUNIT_TEST(testDeplacerFenetreVirtuelleClavier);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();


	// =================================================================
	// D�finissez ici les diff�rents cas de tests...
	// =================================================================

	/// Cas de test:
	void testZoomerInElastique();
	/// Cas de test:
	void testDeplacerFenetreVirtuelleClavier();

private:

	int xMinClotureTest_;
	int xMaxClotureTest_;
	int yMinClotureTest_;
	int yMaxClotureTest_;
	double zAvantTest_;
	double zArriereTest_;
	double zoomInMaxTest_;
	double zoomOutMaxTest_;
	double incrementZoomTest_;
	double xMinFenetreTest_;
	double xMaxFenetreTest_;
	double yMinFenetreTest_;
	double yMaxFenetreTest_;


	glm::dvec3 position_;
	glm::dvec3 pointVise_;
	glm::dvec3 directionHautCamera_;
	glm::dvec3 directionHautMonde_;
	vue::Camera *cameraTest_;
	vue::VueOrtho *vueOrthoTest_;

	vue::ProjectionOrtho *projectionOrthoTest_;

};

#endif 
///////////////////////////////////////////////////////////////////////////////
