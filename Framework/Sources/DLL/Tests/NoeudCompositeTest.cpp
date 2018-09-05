////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author inf2990-11
/// @date 2016-03-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"
#include "../Arbre/Noeuds/NoeudTypes.h"


// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(NoeudCompositeTest);

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
void NoeudCompositeTest::setUp()
{
	noeudComposite_ = { new NoeudComposite{ ArbreRenduINF2990::NOM_TABLE } };
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
void NoeudCompositeTest::tearDown()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testObtenirNombreEnfants()
///
/// Cas de test: Permet de v�rifier si le nombre de noeuds enfants d'un noeud est correct. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testObtenirNombreEnfants()
{

	// Cas 1: On v�rifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Creation de deux noeuds poteaux 
	NoeudComposite* noeudPoteau1{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudComposite* noeudPoteau2{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };

	// Creation de deux noeuds murs 
	NoeudAbstrait* noeudMur1{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudMur2{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	
	// Ajout d'un noeud mur � chaque noeud poteau 
	noeudPoteau1->ajouter(noeudMur1);
	noeudPoteau2->ajouter(noeudMur2);

	// Cas 2:  On ajoute deux noeuds poteaux au noeudComposite_
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);
		// Assurons-nous que la m�thode obtenirNombreEnfants() et calculerProfondeur() se sont correctement ex�cut�es
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau1->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau1->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

	// Nettoyage
	delete noeudPoteau1;
	delete noeudPoteau2;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testVider()
///
/// Cas de test: permet de verifier que la suppression de noeuds enfants est fonctionnelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testVider()
{
	// Creation des noeuds qu'on va ajouter au composite 
	NoeudAbstrait* noeudPoteau1{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudPoteau2{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudMur1{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudMur2{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };

	// Cas 1: On v�rifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	//Cas 2:  Ajout des noeuds au composite, la m�thode ajout a d�j� �t� test�e 
	noeudPoteau1->ajouter(noeudMur1);
	noeudPoteau2->ajouter(noeudMur2);
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);

		// Assurons-nous que le noeud composite poss�de le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	 //Cas 3 : On vide le noeud
	noeudComposite_->vider();

		// Assurons-nous que le noeud composite poss�de le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est deja fait par la m�thode vider()

}



////////////////////////////////////////////////////////////////////////
///
/// @fn void void NoeudCompositeTest::testEffacer()
///
/// Cas de test: Permet de v�rifier si la suppression d'un noeud donn� est fonctionnelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacer()
{

	// Creation des noeuds qu'on va ajouter au noeud noeudComposite_
	NoeudComposite* noeudPoteau = new NoeudComposite(ArbreRenduINF2990::NOM_POTEAU);
	NoeudComposite* noeudMur1 = new NoeudComposite(ArbreRenduINF2990::NOM_MUR);
	NoeudComposite* noeudMur2 = new NoeudComposite(ArbreRenduINF2990::NOM_MUR);
	
	// Cas 1 : On v�rifie qu'initialement, le noeudComposite_ n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// ajout d'un mur au noeud poteau, la methode ajout() a d�j� �t� test�e 
	noeudPoteau->ajouter(noeudMur1);
	// ajout d'un poteau au noeudComposite_, la methode ajout() a d�j� �t� test�e 
	noeudComposite_->ajouter(noeudPoteau);

	// Cas 2 : On efface le noeud mur sous enfant de noeudComposite_
	noeudComposite_->effacer(noeudMur1);

		// Assurons-nous que le petit fils mur du noeud composite est bien effac�
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	// Cas 3 : On ajoute un nouveau noeud mur au poteau
	noeudPoteau->ajouter(noeudMur2);

	//On efface le noeud poteau enfant de noeudComposite_
	noeudComposite_->effacer(noeudPoteau);

		// Assurons-nous que le fils et petit fils du noeud composite sont bien effac�s
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est fait par la m�thode effacer()
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjouter()
///
/// Cas de test: Permet de v�rifier si l'ajout d'un noeud est fonctionnel.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjouter()
{
	// Cas 1 : On v�rifie qu'initialement, le noeudComposite_ n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Cas 2 : On ajoute un noeud mur au noeudComposite_
	NoeudAbstrait* noeudMur{ new NoeudConeCube{ ArbreRenduINF2990::NOM_MUR } };
	bool ajout{ noeudComposite_->ajouter(noeudMur) };

		// On v�rifie que l'ajout est un succ�s
	CPPUNIT_ASSERT(ajout == true);

		// Assurons-nous que le noeud poss�de un bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	// Cas 3 : On ajoute trois noeuds au noeudComposite_
	NoeudAbstrait* noeudPoteau{ new NoeudConeCube{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudMur2{ new NoeudConeCube{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudPoteau2{ new NoeudConeCube{ ArbreRenduINF2990::NOM_POTEAU } };
	noeudComposite_->ajouter(noeudPoteau);
	noeudComposite_->ajouter(noeudMur2);
	noeudComposite_->ajouter(noeudPoteau2);
		// Assurons-nous que le noeud poss�de un bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 4);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	// Nettoyage
	delete noeudMur;
	delete noeudPoteau;
	delete noeudMur2;
	delete noeudPoteau2;
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacerSelection()
///
/// Cas de test: Permet de v�rifier si la suppression de noeuds s�lectionn�s est fonctionnelle
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{
	// Creation des noeuds qu'on va ajouter au composite 
	NoeudComposite* noeudPoteau1{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudComposite* noeudPoteau2{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudMur1{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudMur2{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudMur3{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };

	// Cas 1 : On v�rifie qu'initialement, le noeudComposite_ n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Ajout de deux murs au poteau1
	noeudPoteau1->ajouter(noeudMur1);
	noeudPoteau1->ajouter(noeudMur2);
	// Ajout d'un mur au poteau2
	noeudPoteau2->ajouter(noeudMur3);
	// Ajout des deux poteaux au noeudComposite_
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);

	// Cas 2 : On s�lectionne un noeud petit enfant de noeudComposite_ 
	noeudMur1->assignerSelection(true);

		// Assurons-nous que les noeuds poss�dent le bon nombre d'enfants avant suppression
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau1->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudPoteau1->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

		// Suppression du noeud s�lectionn�
	noeudComposite_->effacerSelection();

		// Assurons-nous que les noeuds poss�dent le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau1->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau1->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

	// Cas 3 : On s�lectionne un noeud enfant de noeudComposite_ et puis on l'efface 
	noeudPoteau1->assignerSelection(true);
	noeudComposite_->effacerSelection();

		// Assurons-nous que les noeuds poss�dent le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

	// Cas 4 : On s�lectionne le dernier noeud enfant de noeudComposite_ et puis on l'efface. Autrement dit on vide l'arbre 
	noeudPoteau2->assignerSelection(true);
	noeudComposite_->effacerSelection();

		// Assurons-nous que le noeudComposite_ poss�de le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est fait par la m�thode effacerSelection()

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEstDansLaTableApresDeplacement()
///
/// Cas de test: Permet d'�valuer si un noeud est sur la table apr�s un d�placement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEstDansLaTableApresDeplacement()
{
	// La dimension de la table par rapport au centre est 48X24 

	// Cr�ation des noeuds qu'on va ajouter au composite 
	NoeudAbstrait* noeudPoteau1{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudPoteau2{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };

	// Ajout des noeuds au composite
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);

	// Cas 1 : On v�rifie que les noeuds sont sur la table
	CPPUNIT_ASSERT(noeudPoteau1->estDansLaTableApresDeplacement(glm::dvec3(0.0, 0.0, 0.0)) == true);
	CPPUNIT_ASSERT(noeudPoteau2->estDansLaTableApresDeplacement(glm::dvec3(0.0, 0.0, 0.0)) == true);

	// Cas 2 : On v�rifie que le poteau1 n'est plus sur la table apr�s un leger d�passement des abscisses
	CPPUNIT_ASSERT((noeudPoteau1->estDansLaTableApresDeplacement(glm::dvec3(49.0, 23.0, 0.0))) == false);

	// Cas 3 : On v�rifie que le poteau2 est encore sur la table � la position limite
	CPPUNIT_ASSERT((noeudPoteau2->estDansLaTableApresDeplacement(glm::dvec3(48.0, 24.0, 0.0))) == true);
	
	delete noeudPoteau1;
	delete noeudPoteau2;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// Cas de test: Permet de v�rifier si le noeud recherch� est le bon noeud. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher()
{
	// Cas 1 : On v�rifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Cr�ation des noeuds qu'on va ajouter au composite 
	NoeudAbstrait* noeudPoteau1{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudPoteau2{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudComposite* noeudMur{ new NoeudComposite{ ArbreRenduINF2990::NOM_MUR } };

	// Cas 2 : On s'assure que le noeud retourn� soit le premier noeud ajout�
		// Modification des attributs de s�lection des noeuds afin de les differencier 
		noeudPoteau2->assignerSelection(true);
	
		// Ajout d'un poteau au mur
		noeudMur->ajouter(noeudPoteau2);
		// Ajout d'un mur puis d'un poteau au composite. L'ordre est important
		noeudComposite_->ajouter(noeudMur);
		noeudComposite_->ajouter(noeudPoteau1);
		
		// R�cup�ration du noeud retourn� par la m�thode chercher()
		NoeudAbstrait* noeudTrouve = noeudComposite_->chercher(ArbreRenduINF2990::NOM_POTEAU);

		// Assurons-nous que le noeud retourn� par la mehtode chercher() est le premier noeud ajout�
		// Rappel: Dans l'arbre on a rajout� le poteau2 puis le poteau1
	CPPUNIT_ASSERT(noeudTrouve->estSelectionne() == true);

	// Nettoyage
	delete noeudMur;
	delete noeudPoteau1;

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
