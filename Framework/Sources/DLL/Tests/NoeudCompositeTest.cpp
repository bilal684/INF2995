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
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
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
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
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
/// Cas de test: Permet de vérifier si le nombre de noeuds enfants d'un noeud est correct. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testObtenirNombreEnfants()
{

	// Cas 1: On vérifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Creation de deux noeuds poteaux 
	NoeudComposite* noeudPoteau1{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudComposite* noeudPoteau2{ new NoeudComposite{ ArbreRenduINF2990::NOM_POTEAU } };

	// Creation de deux noeuds murs 
	NoeudAbstrait* noeudMur1{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudMur2{ new NoeudMur{ ArbreRenduINF2990::NOM_MUR } };
	
	// Ajout d'un noeud mur à chaque noeud poteau 
	noeudPoteau1->ajouter(noeudMur1);
	noeudPoteau2->ajouter(noeudMur2);

	// Cas 2:  On ajoute deux noeuds poteaux au noeudComposite_
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);
		// Assurons-nous que la méthode obtenirNombreEnfants() et calculerProfondeur() se sont correctement exécutées
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

	// Cas 1: On vérifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	//Cas 2:  Ajout des noeuds au composite, la méthode ajout a déjà été testée 
	noeudPoteau1->ajouter(noeudMur1);
	noeudPoteau2->ajouter(noeudMur2);
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);

		// Assurons-nous que le noeud composite possède le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	 //Cas 3 : On vide le noeud
	noeudComposite_->vider();

		// Assurons-nous que le noeud composite possède le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est deja fait par la méthode vider()

}



////////////////////////////////////////////////////////////////////////
///
/// @fn void void NoeudCompositeTest::testEffacer()
///
/// Cas de test: Permet de vérifier si la suppression d'un noeud donné est fonctionnelle
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
	
	// Cas 1 : On vérifie qu'initialement, le noeudComposite_ n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// ajout d'un mur au noeud poteau, la methode ajout() a déjà été testée 
	noeudPoteau->ajouter(noeudMur1);
	// ajout d'un poteau au noeudComposite_, la methode ajout() a déjà été testée 
	noeudComposite_->ajouter(noeudPoteau);

	// Cas 2 : On efface le noeud mur sous enfant de noeudComposite_
	noeudComposite_->effacer(noeudMur1);

		// Assurons-nous que le petit fils mur du noeud composite est bien effacé
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	// Cas 3 : On ajoute un nouveau noeud mur au poteau
	noeudPoteau->ajouter(noeudMur2);

	//On efface le noeud poteau enfant de noeudComposite_
	noeudComposite_->effacer(noeudPoteau);

		// Assurons-nous que le fils et petit fils du noeud composite sont bien effacés
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est fait par la méthode effacer()
	
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testAjouter()
///
/// Cas de test: Permet de vérifier si l'ajout d'un noeud est fonctionnel.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testAjouter()
{
	// Cas 1 : On vérifie qu'initialement, le noeudComposite_ n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Cas 2 : On ajoute un noeud mur au noeudComposite_
	NoeudAbstrait* noeudMur{ new NoeudConeCube{ ArbreRenduINF2990::NOM_MUR } };
	bool ajout{ noeudComposite_->ajouter(noeudMur) };

		// On vérifie que l'ajout est un succès
	CPPUNIT_ASSERT(ajout == true);

		// Assurons-nous que le noeud possède un bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 2);

	// Cas 3 : On ajoute trois noeuds au noeudComposite_
	NoeudAbstrait* noeudPoteau{ new NoeudConeCube{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudMur2{ new NoeudConeCube{ ArbreRenduINF2990::NOM_MUR } };
	NoeudAbstrait* noeudPoteau2{ new NoeudConeCube{ ArbreRenduINF2990::NOM_POTEAU } };
	noeudComposite_->ajouter(noeudPoteau);
	noeudComposite_->ajouter(noeudMur2);
	noeudComposite_->ajouter(noeudPoteau2);
		// Assurons-nous que le noeud possède un bon nombre d'enfants
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
/// Cas de test: Permet de vérifier si la suppression de noeuds sélectionnés est fonctionnelle
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

	// Cas 1 : On vérifie qu'initialement, le noeudComposite_ n'a pas d'enfants
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

	// Cas 2 : On sélectionne un noeud petit enfant de noeudComposite_ 
	noeudMur1->assignerSelection(true);

		// Assurons-nous que les noeuds possèdent le bon nombre d'enfants avant suppression
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau1->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudPoteau1->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

		// Suppression du noeud sélectionné
	noeudComposite_->effacerSelection();

		// Assurons-nous que les noeuds possèdent le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 2);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau1->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau1->calculerProfondeur() == 2);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

	// Cas 3 : On sélectionne un noeud enfant de noeudComposite_ et puis on l'efface 
	noeudPoteau1->assignerSelection(true);
	noeudComposite_->effacerSelection();

		// Assurons-nous que les noeuds possèdent le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 3);
	CPPUNIT_ASSERT(noeudPoteau2->obtenirNombreEnfants() == 1);
	CPPUNIT_ASSERT(noeudPoteau2->calculerProfondeur() == 2);

	// Cas 4 : On sélectionne le dernier noeud enfant de noeudComposite_ et puis on l'efface. Autrement dit on vide l'arbre 
	noeudPoteau2->assignerSelection(true);
	noeudComposite_->effacerSelection();

		// Assurons-nous que le noeudComposite_ possède le bon nombre d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Nettoyage : le nettoyage est fait par la méthode effacerSelection()

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEstDansLaTableApresDeplacement()
///
/// Cas de test: Permet d'évaluer si un noeud est sur la table après un déplacement
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEstDansLaTableApresDeplacement()
{
	// La dimension de la table par rapport au centre est 48X24 

	// Création des noeuds qu'on va ajouter au composite 
	NoeudAbstrait* noeudPoteau1{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudPoteau2{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };

	// Ajout des noeuds au composite
	noeudComposite_->ajouter(noeudPoteau1);
	noeudComposite_->ajouter(noeudPoteau2);

	// Cas 1 : On vérifie que les noeuds sont sur la table
	CPPUNIT_ASSERT(noeudPoteau1->estDansLaTableApresDeplacement(glm::dvec3(0.0, 0.0, 0.0)) == true);
	CPPUNIT_ASSERT(noeudPoteau2->estDansLaTableApresDeplacement(glm::dvec3(0.0, 0.0, 0.0)) == true);

	// Cas 2 : On vérifie que le poteau1 n'est plus sur la table après un leger dépassement des abscisses
	CPPUNIT_ASSERT((noeudPoteau1->estDansLaTableApresDeplacement(glm::dvec3(49.0, 23.0, 0.0))) == false);

	// Cas 3 : On vérifie que le poteau2 est encore sur la table à la position limite
	CPPUNIT_ASSERT((noeudPoteau2->estDansLaTableApresDeplacement(glm::dvec3(48.0, 24.0, 0.0))) == true);
	
	delete noeudPoteau1;
	delete noeudPoteau2;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// Cas de test: Permet de vérifier si le noeud recherché est le bon noeud. 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher()
{
	// Cas 1 : On vérifie qu'initialement, le noeud n'a pas d'enfants
	CPPUNIT_ASSERT(noeudComposite_->obtenirNombreEnfants() == 0);
	CPPUNIT_ASSERT(noeudComposite_->calculerProfondeur() == 1);

	// Création des noeuds qu'on va ajouter au composite 
	NoeudAbstrait* noeudPoteau1{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudAbstrait* noeudPoteau2{ new NoeudPoteau{ ArbreRenduINF2990::NOM_POTEAU } };
	NoeudComposite* noeudMur{ new NoeudComposite{ ArbreRenduINF2990::NOM_MUR } };

	// Cas 2 : On s'assure que le noeud retourné soit le premier noeud ajouté
		// Modification des attributs de sélection des noeuds afin de les differencier 
		noeudPoteau2->assignerSelection(true);
	
		// Ajout d'un poteau au mur
		noeudMur->ajouter(noeudPoteau2);
		// Ajout d'un mur puis d'un poteau au composite. L'ordre est important
		noeudComposite_->ajouter(noeudMur);
		noeudComposite_->ajouter(noeudPoteau1);
		
		// Récupération du noeud retourné par la méthode chercher()
		NoeudAbstrait* noeudTrouve = noeudComposite_->chercher(ArbreRenduINF2990::NOM_POTEAU);

		// Assurons-nous que le noeud retourné par la mehtode chercher() est le premier noeud ajouté
		// Rappel: Dans l'arbre on a rajouté le poteau2 puis le poteau1
	CPPUNIT_ASSERT(noeudTrouve->estSelectionne() == true);

	// Nettoyage
	delete noeudMur;
	delete noeudPoteau1;

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
