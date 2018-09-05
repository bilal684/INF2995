//////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
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

class NoeudComposite;

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCompositeTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe FacadeModele
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE(NoeudCompositeTest);
		CPPUNIT_TEST(testObtenirNombreEnfants);
		CPPUNIT_TEST(testVider);
		CPPUNIT_TEST(testEffacer);
		CPPUNIT_TEST(testAjouter);
		CPPUNIT_TEST(testEffacerSelection);
		CPPUNIT_TEST(testEstDansLaTableApresDeplacement);
		CPPUNIT_TEST(testChercher);
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

	/// Cas de test: permet d'obtenir le nombre d'enfants d'un noeud donn�
	void testObtenirNombreEnfants();

	/// Cas de test: permet vider l'arbre de rendu au complet 
	void testVider();

	/// Cas de test: permet de supprimer un noeud sp�cifique dans tout l'arbre de rendu 
	void testEffacer();

	/// Cas de test: permet de d'ajouter un noeud enfant au noeud pass� en param�tre
	void testAjouter();

	/// Cas de test: permet de supprimer les noeuds qui sont s�lectionn�s
	void testEffacerSelection();

	/// Cas de test: permet de verifier si le noeud est dans la table 
	void testEstDansLaTableApresDeplacement();

	/// Cas de test: permet de retourner le premier noeud ayant le m�me type
	void testChercher();


private:

	 NoeudComposite* noeudComposite_;
};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
