//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.h
/// @author Equipe 11
/// @date 2016-03-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_FACADEMODELETEST_H
#define _TESTS_FACADEMODELETEST_H
#define ANGLE_INITIAL 0
#include <cppunit/extensions/HelperMacros.h>
#include <memory>


#include "../Application/FacadeModele.h"

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModeleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe FacadeModele
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE(FacadeModeleTest);
		/*CPPUNIT_TEST(testAjouterNoeudSimple);
		CPPUNIT_TEST(testRotationObjetSelectionne);*/
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

	/// Cas de test: Permet l'ajout d'un noeud
	void testAjouterNoeudSimple();

	/// Méthode permettant de valider la rotation d'un objet
	void testRotationObjetSelectionne();

private:
	/// Instance de FacadeModele

	FacadeModele* facade_;
	
};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
