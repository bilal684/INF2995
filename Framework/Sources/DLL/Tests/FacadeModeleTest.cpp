////////////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.cpp
/// @author Equipe 11
/// @date 2016-03-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "FacadeModeleTest.h"

#include "../Arbre/ArbreRenduINF2990.h"


// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(FacadeModeleTest);

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::setUp()
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
void FacadeModeleTest::setUp()
{
	HWND handle = nullptr;
	facade_ = FacadeModele::obtenirInstance();
	facade_->initialiserOpenGL(handle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstraitTest::tearDown()
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
void FacadeModeleTest::tearDown()
{
	facade_->libererOpenGL();
	facade_->libererInstance();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testAjouterNoeudSimple()
///
/// Cas de test: Permet de tester si l'ajout d'un noeud donné est fonctionnel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testAjouterNoeudSimple()
{
	// On sait que lors de la création de facade_, l'arbre est initialisé avec 5 éléments : 4 murs invisibles et une flèche
	 
	// Cas 1 : Vidons la table 
		facade_->obtenirArbreRenduINF2990()->chercher("table")->vider();

		// Vérifions que la table est vide 
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau") == nullptr);
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur") == nullptr);

	// Cas 2 : Ajout de noeuds enfants 
		//ajout d'un Poteau 
		char* nomPoteau = "poteau";
		int positionX = 0;
		int positionY = 0;
		facade_->ajouterNoeudSimple(nomPoteau, positionX, positionY);
		
		// Assurons-nous que le poteau a été rattaché à la table
			NoeudAbstrait* noeudTrouvePoteau = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau");
			// le poteau est placé au pixel (0,0), cela équivaut au point (-1,1) en coordonnées de clôture
			CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirPositionRelative().x == -1);
			CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirPositionRelative().y == 1);
			CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau") != nullptr);
			CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau")->obtenirType() == "poteau");
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->obtenirNombreEnfants() == 1);

		// ajout d'un mur 
		char* nomMur = "mur";
	    positionX = 48;
		positionY = 24;
		facade_->ajouterNoeudSimple(nomMur, positionX, positionY);
		// Assurons-nous que le mur a été rattaché à la table
		NoeudAbstrait* noeudTrouveMur = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur");
		// le mur est toujours placé  en (0,0) en coordonnées de clôture 
		CPPUNIT_ASSERT(noeudTrouveMur->obtenirPositionRelative().x == 0);
		CPPUNIT_ASSERT(noeudTrouveMur->obtenirPositionRelative().y == 0);
		CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur") != nullptr);
		CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur")->obtenirType() == "mur");
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->obtenirNombreEnfants() == 2);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testRotationObjetSelectionne()
///
/// Cas de test: Permet de vérifier si les modifications de rotation sont établies.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testRotationObjetSelectionne()
{

	int positionX = 0;
	int positionY = 0;
	char* nomPoteau = "poteau";
	float angleRotation = 20.0;
	
	// Vidons la table
	facade_->obtenirArbreRenduINF2990()->chercher("table")->vider();
	// ajout du poteau à l'arbre
	facade_->ajouterNoeudSimple(nomPoteau, positionX, positionY);
	
	NoeudAbstrait* noeudTrouvePoteau = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau");
	// Cas 1 : On vérifie qu'initialement, aucun angle de rotation n'est appliqué au poteau
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == ANGLE_INITIAL);
	
	// Cas 2 : On sélectionne le poteau et le tourne
		noeudTrouvePoteau->assignerSelection(true);
		facade_->assignerRotationPourObjetSelectionne(angleRotation);
		// S'assurer que le noeud rajouté est tourné suivant son centre
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == angleRotation);

	// Cas 3 : On désélectionne le poteau et le tourne
		noeudTrouvePoteau->assignerSelection(false);
		facade_->assignerRotationPourObjetSelectionne(30.0);
		// S'assurer que le noeud n'a pas été tourné sur son centre
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == angleRotation);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

