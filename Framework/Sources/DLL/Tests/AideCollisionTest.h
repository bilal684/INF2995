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
///        m�thodes de la classe FacadeModele
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class AideCollisionTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(AideCollisionTest);
		CPPUNIT_TEST(testIntersectionAvecSegment);
		CPPUNIT_TEST(testcalculerCollisionSegmentCirculaire);
		CPPUNIT_TEST(testCalculerCollisionCercle);
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

	/// Cas de test: permet de tester force en deux dimensions caus�e par la collision d'un objet
    /// circulaire avec un segment de droite. 
	void testIntersectionAvecSegment();

	/// Cas de test: permet de tester la collision en deux dimensions caus�e par la collision d'un objet
	/// circulaire avec un segment de droite. 
	void testcalculerCollisionSegmentCirculaire();

	/// Cas de test: permet de tester la collsion en deux dimensions caus�e par la collision d'un objet
	/// sph�rique avec un segment de droite. 
	void testCalculerCollisionCercle();


private:



};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
