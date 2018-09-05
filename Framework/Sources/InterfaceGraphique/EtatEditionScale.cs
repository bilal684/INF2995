///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionScale.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionScale
    /// @brief Classe decrivant le redimensionnement d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionScale : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        //private bool 
        private bool enScale_;
        int xDebut, yDebut;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void initialiserDebut(int x, int y)
        ///
        /// Methode permettant l'initialisation de certaines donnees lors d'un
        /// clic de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void initialiserDebut(int x, int y)
        {
            xDebut = x;
            yDebut = y;
            enScale_ = true;
            FonctionsNatives.initialiserScaleEnTraitement();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn  public override void interpreterGlissement( int x, int y )
        ///
        /// Methode permettant le lancement d'algorithme lors du deplacement de
        /// la souris avec un certain bouton enfonce.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement( int x, int y )
        {
            if (enScale_)
            {
                Program.edition.Cursor = Cursors.NoMoveVert;
                if (compteurDeplacement_ == 2)
                {
                    double facteurScale = 1.0 - (y - yDebut) / 60.0;

                    if (facteurScale <= 0.01)
                    {
                        facteurScale = 0.01;
                    }
                    FonctionsNatives.scaleSelection(facteurScale);

                    compteurDeplacement_ = 0;
                }
                else
                    compteurDeplacement_++;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterDepot(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors du relachement d'un
        /// bouton de souris.
        /// 
        /// @param[in] x : Position x de la souris en coordonnee de cloture.
        /// 
        /// @param[in] y : Position y de la souris en coordonnee de cloture.
        ///
        /// @param[in] k : Represente la touche appuyer.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterDepot(int x, int y, Keys k)
        {
            if (enScale_)
            {
                // code a executer quand le bouton est relaché
                Program.edition.Cursor = Cursors.Default;
                if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                {
                    //FonctionsNatives.retournerAuScaleInitiale();
                    FonctionsNatives.scaleSelection(1.0);
                }
                else
                    Program.edition.marquerModificationDansLaScene();
                enScale_ = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override bool interpreterEchap()
        ///
        /// Methode permettant le lancement d'algorithme lors de l'appui de la touche
        /// Echap.
        /// 
        /// @return True par defaut.
        ///
        ////////////////////////////////////////////////////////////////////////
        public override bool interpreterEchap()
        {
            if (enScale_)
            {
                Program.edition.Cursor = Cursors.Default;
                FonctionsNatives.scaleSelection(1.0);
                enScale_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
   }
}

