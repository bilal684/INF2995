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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test: Permet de tester si l'ajout d'un noeud donn� est fonctionnel
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testAjouterNoeudSimple()
{
	// On sait que lors de la cr�ation de facade_, l'arbre est initialis� avec 5 �l�ments : 4 murs invisibles et une fl�che
	 
	// Cas 1 : Vidons la table 
		facade_->obtenirArbreRenduINF2990()->chercher("table")->vider();

		// V�rifions que la table est vide 
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau") == nullptr);
	CPPUNIT_ASSERT(facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur") == nullptr);

	// Cas 2 : Ajout de noeuds enfants 
		//ajout d'un Poteau 
		char* nomPoteau = "poteau";
		int positionX = 0;
		int positionY = 0;
		facade_->ajouterNoeudSimple(nomPoteau, positionX, positionY);
		
		// Assurons-nous que le poteau a �t� rattach� � la table
			NoeudAbstrait* noeudTrouvePoteau = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau");
			// le poteau est plac� au pixel (0,0), cela �quivaut au point (-1,1) en coordonn�es de cl�ture
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
		// Assurons-nous que le mur a �t� rattach� � la table
		NoeudAbstrait* noeudTrouveMur = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("mur");
		// le mur est toujours plac�  en (0,0) en coordonn�es de cl�ture 
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
/// Cas de test: Permet de v�rifier si les modifications de rotation sont �tablies.
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
	// ajout du poteau � l'arbre
	facade_->ajouterNoeudSimple(nomPoteau, positionX, positionY);
	
	NoeudAbstrait* noeudTrouvePoteau = facade_->obtenirArbreRenduINF2990()->chercher("table")->chercher("poteau");
	// Cas 1 : On v�rifie qu'initialement, aucun angle de rotation n'est appliqu� au poteau
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == ANGLE_INITIAL);
	
	// Cas 2 : On s�lectionne le poteau et le tourne
		noeudTrouvePoteau->assignerSelection(true);
		facade_->assignerRotationPourObjetSelectionne(angleRotation);
		// S'assurer que le noeud rajout� est tourn� suivant son centre
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == angleRotation);

	// Cas 3 : On d�s�lectionne le poteau et le tourne
		noeudTrouvePoteau->assignerSelection(false);
		facade_->assignerRotationPourObjetSelectionne(30.0);
		// S'assurer que le noeud n'a pas �t� tourn� sur son centre
	CPPUNIT_ASSERT(noeudTrouvePoteau->obtenirRotationRelative().x == angleRotation);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

