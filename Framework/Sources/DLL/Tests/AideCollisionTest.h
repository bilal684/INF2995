//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author Equipe 11
/// @date 2016-03-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <memory>


#include "Utilitaire.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudCompositeTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe FacadeModele
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class AideCollisionTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(AideCollisionTest);
		CPPUNIT_TEST(testIntersectionAvecSegment);
		CPPUNIT_TEST(testcalculerCollisionSegmentCirculaire);
		CPPUNIT_TEST(testCalculerCollisionCercle);
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

	/// Cas de test: permet de tester force en deux dimensions causée par la collision d'un objet
    /// circulaire avec un segment de droite. 
	void testIntersectionAvecSegment();

	/// Cas de test: permet de tester la collision en deux dimensions causée par la collision d'un objet
	/// circulaire avec un segment de droite. 
	void testcalculerCollisionSegmentCirculaire();

	/// Cas de test: permet de tester la collsion en deux dimensions causée par la collision d'un objet
	/// sphérique avec un segment de droite. 
	void testCalculerCollisionCercle();


private:



};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
