//////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobotTest.h
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDROBOTTEST_H
#define _TESTS_NOEUDROBOTTEST_H
#define DIMENSION_INITIAL 3
#define FACTEUR 4

#include <cppunit\extensions\HelperMacros.h>

#include "../Arbre/Noeuds/NoeudTypes.h"
///////////////////////////////////////////////////////////////////////////
/// @class NoeudPoteauTest
/// @brief Classe qui effectue des tests sur les noeuds poteaux.
///
///
/// @author INF2990 Eq.11
/// @date 2016-02-15
///////////////////////////////////////////////////////////////////////////
class NoeudPoteauTest : public CppUnit::TestFixture
{
	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudPoteauTest);
	 	CPPUNIT_TEST(testChangerScale);
		CPPUNIT_TEST(testEstDansLaTable);
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

	/// Cas de test: permet d'obtenir le nombre de senseurs actifs
	void testChangerScale();

	// Cas de test : permet de verifier qu'un noeudPoteau est bel et bien a l'interieur de la table. 
	void testEstDansLaTable();

private:

	NoeudPoteau* noeudPoteau_; 

};

#endif // _TESTS_NOEUDROBOTTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////