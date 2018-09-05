///////////////////////////////////////////////////////////////////////////////
/// @file EtatEditionRotation.cs
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
    /// @class EtatEditionRotation
    /// @brief Classe decrivant l'etat de rotation d'un objet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    class EtatEditionRotation : EtatEdition
    {
        private int xDebut_ = 0;
        private int yDebut_ = 0;
        int nbreObjetsSelectionnes = 0;
        double rotation_;
        int ancienY = 0;
        bool enRotation_;
       // private int compteurDeplacement_ = 0;
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
            ancienY = yDebut_;
            enRotation_ = true;
            nbreObjetsSelectionnes = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
            FonctionsNatives.initialiserEnTraitement();
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
            if (enRotation_)
            {
                Program.edition.Cursor = Cursors.Default;
                if (!FonctionsNatives.objetsSelectionnesSurLaTable())
                {
                    FonctionsNatives.annulerRotationSelection();
                }
                else
                    Program.edition.marquerModificationDansLaScene();
                enRotation_ = false;
            }
           
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
        ///native
        ////////////////////////////////////////////////////////////////////////
        public override void interpreterGlissement(int x, int y)
        {
            if (enRotation_)
            {
                double deltaY = 0;
                Program.edition.Cursor = Cursors.NoMoveVert;

                deltaY = y - ancienY;
                rotation_ = deltaY;
                if (nbreObjetsSelectionnes == 1)
                {
                    FonctionsNatives.PivoterObjetSelectionne(deltaY);
                }
                else
                {
                    FonctionsNatives.PivoterObjetsMultiples(deltaY);
                }
                ancienY = y;
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
            if (enRotation_)
            {
                Program.edition.Cursor = Cursors.Default;
                FonctionsNatives.annulerRotationSelection();
                enRotation_ = false;
                return false;
            }
            else
            {
                return true;
            }
        }
        
    }

}
