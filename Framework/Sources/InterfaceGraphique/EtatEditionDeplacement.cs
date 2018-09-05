///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionDeplacement.cs
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
    /// @class EtatEditionDeplacement
    /// @brief Classe decrivant l'etat de deplacement d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionDeplacement : EtatEdition
    {
        private int compteurDeplacement_ = 0;
        private bool enDeplacement_; 

        private int xDebut_, yDebut_;

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
            xDebut_ = x;
            yDebut_ = y;
            FonctionsNatives.initialiserEnTraitement();
            enDeplacement_ = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement( int x, int y )
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
            if (enDeplacement_)
            {
                Program.edition.Cursor = Cursors.SizeAll;
                if (compteurDeplacement_ == 2)
                {
                    FonctionsNatives.deplacerSelection(xDebut_, yDebut_, x, y);
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
        /// Methode permettant le lancement d'algorithme lors du relachement d'un
        /// bouton de la souris.
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
            if (enDeplacement_)
            {
                Program.edition.Cursor = Cursors.Default;
                if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                {
                    FonctionsNatives.deplacerSelection(xDebut_, yDebut_, xDebut_, yDebut_);
                }
                else
                    Program.edition.marquerModificationDansLaScene();
                enDeplacement_ = false;
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
            if ( enDeplacement_ )
            {
                Program.edition.Cursor = Cursors.Default;
                FonctionsNatives.deplacerSelection(xDebut_, yDebut_, xDebut_, yDebut_);
                enDeplacement_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
   }
}
