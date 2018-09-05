////////////////////////////////////////////////////////////////////////////////////
/// @file AideCollisionTest.cpp
/// @author inf2990-11
/// @date 2016-03-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "AideCollisionTest.h"
#include "Utilitaire.h"
#include "AideCollision.h"
#include "SegmentDroite2D.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION(AideCollisionTest);

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
void AideCollisionTest::setUp()
{

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
void AideCollisionTest::tearDown()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void AideCollisionTest::testIntersectionAvecSegment()
///
/// Cas de test: Permet de vérifier si deux segments se coupent
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void AideCollisionTest::testIntersectionAvecSegment()
{
	// Cas 1 : Intersection entre deux droites perpendiculaires
	 glm::dvec2 point1Segment1(-24.0, 0.0);
	 glm::dvec2 point2Segment1(24.0, 0.0);
	 glm::dvec2 point1Segment2(0.0, 48.0);
	 glm::dvec2 point2Segment2(0.0, -48.0);
	 math::SegmentDroite2D segment1(point1Segment1, point2Segment1);
		// On s'assure que les deux droites se coupent
	 CPPUNIT_ASSERT(segment1.intersectionAvecSegment(point1Segment2, point2Segment2) == true);

	 // Cas 2 : Intersection entre deux droites parallèles
	 point1Segment2.x = -24.0;
	 point1Segment2.y = 5.0;
	 point2Segment2.x = 24.0;
	 point2Segment2.y = 5.0;
		// On s'assure que les deux droites ne se coupent pas
	 CPPUNIT_ASSERT(segment1.intersectionAvecSegment(point1Segment2, point2Segment2) == false);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void AideCollisionTest::testcalculerCollisionSegmentCirculaire()
///
/// Cas de test: Permet de vérifier si la collision entre un segment et un cercle est fonctionnelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AideCollisionTest::testcalculerCollisionSegmentCirculaire()
{
	// Première extrémité du segment de droite.
	 glm::dvec2 point1(30.0, 0.0);
	// Seconde extrémité du segment de droite.
	 glm::dvec2 point2(-30.0, 0.0);
	/// position du centre du cercle.
	 glm::dvec2 point3(0.0, 30.0);
	/// rayon du cercle.
	double rayon = 0.0;
	/// collisionAvecPoints : Vrai si on veut les collisions avec les extrémités.
	bool collisionAvecPoints = true;

	
	// Cas 1 : Il n'y a aucune collision
		/// Calcule la collision d'un objet circulaire avec un segment de droite.
		aidecollision::DetailsCollision detailCollision_ = aidecollision::calculerCollisionSegment(point1, point2,
		point3, rayon, collisionAvecPoints);
		rayon = 15.0;
	CPPUNIT_ASSERT(detailCollision_.type == aidecollision::COLLISION_AUCUNE);

	// Cas 2 : Il y'a collision avec le premier point du segment
		point1.x = 0.0;
		point3.x = 30.0;
		point3.y = 0.0;
		rayon = 30.000000001; // collision obtenue avec une erreur de 0.000000001
		detailCollision_ = aidecollision::calculerCollisionSegment(point1, point2,
			point3, rayon, collisionAvecPoints);
	CPPUNIT_ASSERT(detailCollision_.type == aidecollision::COLLISION_SEGMENT_PREMIERPOINT);

	// Cas 3 : Il y'a collision avec le segment
	point1.x = 0.0;
	point3.x = 0.0;
	point3.y = 30.0;
	rayon = 31.0; 
	detailCollision_ = aidecollision::calculerCollisionSegment(point1, point2,
		point3, rayon, collisionAvecPoints);
	CPPUNIT_ASSERT(detailCollision_.type == aidecollision::COLLISION_SEGMENT);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void void AideCollisionTest::testCalculerCollisionCercle()
///
/// Cas de test: Permet de tester si la collision entre deux cercles est fonctionnelle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void AideCollisionTest::testCalculerCollisionCercle()
{
	
	// DetailsCollision calculerCollisionCercle(const glm::dvec2& centreCercle,double rayonCercle, const glm::dvec2& positionObjet,double rayonObjet);

	 glm::dvec2 centreCercle(-24.0, 0.0);
	double rayonCercle = 10.0;
	 glm::dvec2 positionObjet(24.0, 0.0);
	double rayonObjet = 10.0;
	// Cas 1 : Il n'y a aucune collision
		/// Evalue la collision d'un objet circulaire avec un cercle.
	aidecollision::DetailsCollision detailCollision_ = aidecollision::calculerCollisionCercle(centreCercle, rayonCercle, positionObjet, rayonObjet);
	CPPUNIT_ASSERT(detailCollision_.type == aidecollision::COLLISION_AUCUNE);
	// Cas 2 : Recherche de la tangente entre cercles est subtile 
		rayonCercle = 24.000000000000006; // Pour une marge de 0.000000000000005 aucune collision. Tandis qu'une marge de 0.000000000000006 entraine une collision sphérique
		rayonObjet = 24.0;
		detailCollision_ = aidecollision::calculerCollisionCercle(centreCercle, rayonCercle, positionObjet, rayonObjet);
	CPPUNIT_ASSERT(detailCollision_.type != aidecollision::COLLISION_ARC);
	
	// Cas 3 : La collision est une sphère
		rayonCercle = 25.0;
		detailCollision_ = aidecollision::calculerCollisionCercle(centreCercle, rayonCercle, positionObjet, rayonObjet);
	CPPUNIT_ASSERT(detailCollision_.type == aidecollision::COLLISION_SPHERE);

}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
