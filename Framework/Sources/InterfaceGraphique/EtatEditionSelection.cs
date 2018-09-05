///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionSelection.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.IO;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class EtatEditionSelection
    /// @brief Classe decrivant le comportement d'un objet lors de sa selection.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionSelection : EtatEdition
    {
        private int xDebut_ = 0;
        private int yDebut_ = 0;
        private int xFin_ = 0;
        private int yFin_ = 0;
        private bool rectangleAffiche_ = false;
        //private Keys modificateur_ = Keys.None;

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
            FonctionsNatives.tracerRectangleElastique(x, y);
            rectangleAffiche_ = true;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterClic(int x, int y, Keys k)
        ///
        /// Methode permettant le lancement d'algorithmes lors d'un clic d'une
        /// touche quelconque.
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
        public override void interpreterClic(int x, int y, Keys k)
        {
            // code pour la selection de l'objet au dessus du clic
            if (k == Keys.Control)
                FonctionsNatives.selectionObjet(x, y, false);
            else
                FonctionsNatives.selectionObjet(x, y, true);
            int nombreElementSelectionne = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
            bool aActiver = ( nombreElementSelectionne > 1 || 
                ( nombreElementSelectionne == 1 && !FonctionsNatives.noeudSelectionneEstFleche() ) );
            Program.edition.changerEtatOptionSupprimmer(aActiver);
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
            // code pour la selection de l'objet au dessus du clic
           // FonctionsNatives.terminerRectangleElastique(x, y);
            if ( rectangleAffiche_ )
            {
                FonctionsNatives.terminerRectangleElastique(x, y);
                bool estEnfonce = false;
                if (k == Keys.Control)
                {
                    estEnfonce = true; 
                }
                FonctionsNatives.selectRectElastique(xDebut_, yDebut_, x, y, estEnfonce);
            }
            else 
            {
                if (Math.Abs(x - xDebut_) <= 3 && Math.Abs(y - xDebut_) <= 3)
                    interpreterClic(x, y, k);
            }
            int nombreElementSelectionne = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
            bool aActiver = (nombreElementSelectionne > 1 ||
                (nombreElementSelectionne == 1 && !FonctionsNatives.noeudSelectionneEstFleche()));
            Program.edition.changerEtatOptionSupprimmer(aActiver);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public override void interpreterGlissement(int x, int y)
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
        public override void interpreterGlissement(int x, int y)
        {
            xFin_ = x;
            yFin_ = y;
            if ( x == xDebut_ || y == yDebut_ || ( Math.Abs(x - xDebut_) <= 3 && Math.Abs(y - xDebut_) <= 3 ) )
            {
                if ( rectangleAffiche_ )
                {
                    FonctionsNatives.tracerRectangleElastique(x, y);
                    FonctionsNatives.terminerRectangleElastique(x, y);
                    rectangleAffiche_ = false;
                }
            }
            else
            {
                if ( !rectangleAffiche_ )
                {
                    FonctionsNatives.tracerRectangleElastique(xDebut_, yDebut_);
                    rectangleAffiche_ = true;
                }
                FonctionsNatives.tracerRectangleElastique(x, y);
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
            if (rectangleAffiche_)
            {
                FonctionsNatives.terminerRectangleElastique(xFin_, yFin_);
                rectangleAffiche_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }


        /*public void updatePos(int x, int y)
        {
            xD = x;
            yMouseDown = y;
        }*/
    }

}