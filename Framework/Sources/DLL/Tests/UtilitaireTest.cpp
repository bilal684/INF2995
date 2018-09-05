////////////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.cpp
/// @author Equipe 11
/// @date 2016-03-17
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "UtilitaireTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(UtilitaireTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::setUp()
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
void UtilitaireTest::setUp()
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::tearDown()
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
void UtilitaireTest::tearDown()
{
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testEGAL_ZERO()
///
/// Cas de test: vérification de la nullité d'un nombre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testEGAL_ZERO()
{
	// Cas 1 : nullité pure
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(0) == true);
	// Cas 2 : non nullité
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(0.00000001)) == false);
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(-0.00000001)) == false);
	// Cas 3 : quasi nullité
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(0.000000001)) == true);
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(-0.000000001)) == true);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testDANS_LIMITESXY()
///
/// Cas de test: vérification de l'appartenance d'un point dans un carré.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testDANS_LIMITESXY()
{
	// Cas 1 : On s'assure que le point (1,1) est bien dans le carré spécifié
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 0.5, 2, 1, 0.5, 2)) == true);
	// Cas 2 : On vérifie que le point (1,1) n'est pas dans le carré spécifié 
			// l'abscisse 1 n'est pas dans la limite du carré
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 2.5, 3, 1, 0.5, 2)) == false);
	       // l'ordonnée 1 n'est pas dans la limite du carré
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 0.5, 2, 1, 4, 5)) == false);
	      // l'abscisse et l'ordonnée 1 ne sont pas dans la limite du carré
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 3.5, 4, 1, 4.5, 6)) == false);

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
