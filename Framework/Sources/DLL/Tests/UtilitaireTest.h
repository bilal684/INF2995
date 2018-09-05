////////////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author Equipe 11
/// @date 2016-03-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_UTILITAIRETEST_H
#define _TESTS_UTILITAIRETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "../Arbre/Noeuds/NoeudTypes.h"


///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement de
///        quelques méthodes de la classe Utilitaire
/// @author inf2990-11
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
		CPPUNIT_TEST(testEGAL_ZERO);
		CPPUNIT_TEST(testDANS_LIMITESXY);
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

	/// Cas de test: permet de verifier si un nombre est égal à zéro.
	void testEGAL_ZERO();

	/// Cas de test: permet de vérifier si un point 2d est dans un carré.
	void testDANS_LIMITESXY();

};

#endif 


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
