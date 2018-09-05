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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test: v�rification de la nullit� d'un nombre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testEGAL_ZERO()
{
	// Cas 1 : nullit� pure
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(0) == true);
	// Cas 2 : non nullit�
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(0.00000001)) == false);
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(-0.00000001)) == false);
	// Cas 3 : quasi nullit�
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(0.000000001)) == true);
	CPPUNIT_ASSERT((utilitaire::EGAL_ZERO(-0.000000001)) == true);

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testDANS_LIMITESXY()
///
/// Cas de test: v�rification de l'appartenance d'un point dans un carr�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testDANS_LIMITESXY()
{
	// Cas 1 : On s'assure que le point (1,1) est bien dans le carr� sp�cifi�
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 0.5, 2, 1, 0.5, 2)) == true);
	// Cas 2 : On v�rifie que le point (1,1) n'est pas dans le carr� sp�cifi� 
			// l'abscisse 1 n'est pas dans la limite du carr�
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 2.5, 3, 1, 0.5, 2)) == false);
	       // l'ordonn�e 1 n'est pas dans la limite du carr�
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 0.5, 2, 1, 4, 5)) == false);
	      // l'abscisse et l'ordonn�e 1 ne sont pas dans la limite du carr�
	CPPUNIT_ASSERT((utilitaire::DANS_LIMITESXY(1, 3.5, 4, 1, 4.5, 6)) == false);

}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
