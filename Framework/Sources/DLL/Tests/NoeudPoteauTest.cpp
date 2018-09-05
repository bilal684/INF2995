////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteauTest.cpp
/// @author Equipe 11
/// @date 2016-03-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudPoteauTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudPoteauTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::setUp()
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

void NoeudPoteauTest::setUp()
{
	noeudPoteau_ = { new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	noeudPoteau_->assignerRedimensionnementRelative(glm::dvec3(DIMENSION_INITIAL, DIMENSION_INITIAL, DIMENSION_INITIAL));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobotTest::tearDown()
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
void NoeudPoteauTest::tearDown()
{
	delete noeudPoteau_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteauTest::testChangerScale()
///
/// Cas de test: Permet de verifier si le scale d'un noeud poteau est conforme aux requis
//
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudPoteauTest::testChangerScale()
{
	// Cas 1 : On vérifie qu'initialement, le facteur initial est appliqué au noeud 
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().x == DIMENSION_INITIAL);
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().y == DIMENSION_INITIAL);
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().z == DIMENSION_INITIAL);

	// Cas 2 : On applique le facteur final au poteau
	noeudPoteau_->changerScale(FACTEUR);
	// Assurons-nous que le rayon du noeud est FACTEUR_FINAL *  FACTEUR_INITIAL
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().x == FACTEUR *  DIMENSION_INITIAL);
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().y == FACTEUR *  DIMENSION_INITIAL);
	// Assurons-nous que la hauteur du noeud est conservé
	CPPUNIT_ASSERT(noeudPoteau_->obtenirRedimensionnementRelative().z == DIMENSION_INITIAL);


}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteauTest::testEstDansLaTable()
///
/// Cas de test: Permet de verifier si le noeud est sur la table
//
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudPoteauTest::testEstDansLaTable()
{
	// Dimension table 48*24
	// Cas 1: On s'assure qu'initialement le noeud est sur la table
	noeudPoteau_->assignerPositionRelative(glm::dvec3(0.0, 0.0, 0.0));
	CPPUNIT_ASSERT(noeudPoteau_->estDansLaTable() == true);
	// Cas 2: On s'assure que le noeud est limite sur la table, 
	noeudPoteau_->assignerPositionRelative(glm::dvec3(45.0, 21.0, 0.0));
	CPPUNIT_ASSERT(noeudPoteau_->estDansLaTable() == true);
	// Cas 3: On s'assure que le noeud déborde
	noeudPoteau_->assignerPositionRelative(glm::dvec3(48.0, 24.0, 0.0));
	CPPUNIT_ASSERT(noeudPoteau_->estDansLaTable() == false);

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////