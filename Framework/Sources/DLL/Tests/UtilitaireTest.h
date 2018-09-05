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
///        quelques m�thodes de la classe Utilitaire
/// @author inf2990-11
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	// =================================================================
	CPPUNIT_TEST_SUITE(UtilitaireTest);
		CPPUNIT_TEST(testEGAL_ZERO);
		CPPUNIT_TEST(testDANS_LIMITESXY);
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

	/// Cas de test: permet de verifier si un nombre est �gal � z�ro.
	void testEGAL_ZERO();

	/// Cas de test: permet de v�rifier si un point 2d est dans un carr�.
	void testDANS_LIMITESXY();

};

#endif 


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
