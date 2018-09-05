///////////////////////////////////////////////////////////////////////////////
/// @file Edition.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Web.UI;
using System.Xml;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Edition
    /// @brief Classe correspondant au formulaire principale du mode edition.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    public partial class Edition : Form
    {
        //public static Object unLock = new Object();
        //public static bool peutAfficher = true;
        
        //private const int NB_IMAGES_PAR_SECONDE = 60;
        //private bool curseurDansLaZoneDeDessin = false;
        private static int hauteurZoneDeDessin_ = 0;
        private static int largeurZoneDeDessin_ = 0;
        private int compteurDeplacement_ = 0;

        private int xMouseDown_;
        private int yMouseDown_;
        private Keys modificateur_ = Keys.None;
        private bool boutonGauchePresse_ = false;
        public bool boutonDroitePresse_ = false;
        private bool sourisEstEnZoneDeClic_ = false;
        private bool initialisationEnvoyee_ = false;

        private Aide aide_ = null;
        public static bool aideEnPremierPlan_ = false;

        private bool enEdition_ = false;
        public static bool enTrace_ = false;
       // private static Edition edition;
        /*private static TimeSpan dernierTemps;
        private static TimeSpan tempsAccumule;
        private static Stopwatch chrono = Stopwatch.StartNew();
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);*/
        
        private static EtatEdition etat_ = null;
        private static System.Windows.Forms.ToolStripButton boutonSelectionne_ = null;
        private static System.Windows.Forms.ToolStripMenuItem itemSelectionne_ = null;
        private string nomFichierOuvert_ = null;
        private string nomCompletFichierParDefaut_; 
        private static bool sceneModifiee_ = false;
        private bool openGLLibere_ = false;
        //private bool nouvelleScene = true;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public Edition()
        ///
        /// Constructeur par defaut.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public Edition()
        {
            sceneModifiee_ = false;
            this.KeyPreview = true;
            this.BackColor = Color.Black;
            //this.KeyPress += new KeyPressEventHandler(Edition_KeyPress);
            //this.KeyDown += new KeyEventHandler(Edition_KeyDown);
            InitializeComponent();
            FonctionsNatives.changerModeApplication('E');
            InitialiserAnimation();
            //chrono.Start();
            etat_ = null;
            Program.peutAfficher = true;
            orthographiqueToolStripMenuItem.BackColor = Color.LightSkyBlue;
            FonctionsNatives.chargerZoneDeSimulation("zones/default.xml");
            FileInfo f = new FileInfo("zones/default.xml");
            string nomComplet = f.FullName;
            nomCompletFichierParDefaut_ = nomComplet;
            nomFichierOuvert_ = nomComplet;
            this.Text = "Edition : default";
            supprimerToolStripButton.Enabled = false;
            supprimerToolStripMenuItem.Enabled = false;
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn ~Edition()
        ///
        /// Destructeur
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        ~Edition()
        {
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void marquerModificationDansLaScene()
        ///
        /// Methode permettant l'indication de modifications dans la scene
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void marquerModificationDansLaScene()
        {
            sceneModifiee_ = true;
            enregistrerToolStripButton.Enabled = true;
            enregistrerToolStripMenuItem.Enabled = true;
            if (!this.Text.EndsWith("*"))
                this.Text = this.Text + "*";
        }
        public void changerEtatOptionSupprimmer(bool aActiver)
        {
            if (aActiver)
            {
                supprimerToolStripButton.Enabled = true;
                supprimerToolStripMenuItem.Enabled = true;
            }
            else
            {
                supprimerToolStripButton.Enabled = false;
                supprimerToolStripMenuItem.Enabled = false;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void retournerEtatInitial()
        ///
        /// Methode permettant de retourner à l'état initial (où tous les 
        /// boutons sont désactivés)
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void retournerEtatInitial()
        {
            etat_ = null;
            boutonSelectionne_.Checked = false;
            boutonSelectionne_ = null;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void lancerEdition()
        ///
        /// Methode permettant le lancement du mode edition
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void lancerEdition()
        {
            this.ShowDialog();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public static  int obtenirHauteur()
        ///
        /// Methode permettant l'obtention de la hauteur de la zone de dessin 
        /// en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public static  int obtenirHauteur()
        {
            return hauteurZoneDeDessin_;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public static int obtenirLargeur()
        ///
        /// Methode permettant l'obtention de la largeur de la zone de dessin 
        /// en coordonnee de cloture.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public static int obtenirLargeur()
        {
            return largeurZoneDeDessin_;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void InitialiserAnimation()
        ///
        /// Methode permettant l'initialisation d'OpenGL et du dessin OpenGL
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            FonctionsNatives.initialiserOpenGL(zoneDeDessin.Handle);
            openGLLibere_ = false;
            FonctionsNatives.dessinerOpenGL(0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void MettreAJour(double tempsInterAffichage)
        ///
        /// Methode permettant la mise a jour de la zone de dessin.
        /// 
        /// @param[in] tempsInterAffichage : intervalle de temps entre chaque image
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    int screenWidth = Screen.PrimaryScreen.Bounds.Width;
                    int screenHeight = Screen.PrimaryScreen.Bounds.Height;
                    FonctionsNatives.dessinerOpenGL(tempsInterAffichage);
                });
            }
            catch (Exception)
            {
            }
        }


        //*********************** Evenement du Clavier ***********************//
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        ///
        /// Methode permettant la capture d'evenement et l'execution d'algorithme associee
        /// aux dit evenements.
        /// 
        /// @param[in] sender : Represente la touche relier a l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Left:
                    FonctionsNatives.deplacerDroite();
                    break;
                case Keys.Right:
                    FonctionsNatives.deplacerGauche();
                    break;
                case Keys.Up:
                    FonctionsNatives.deplacerBas();
                    break;
                case Keys.Down:
                    FonctionsNatives.deplacerHaut();
                    break;
                case Keys.Add:
                case Keys.Oemplus:
                    FonctionsNatives.zoomIn();
                    break;
                case Keys.Subtract:
                case Keys.OemMinus:
                    FonctionsNatives.zoomOut();
                    break;
                case Keys.Escape:
                    if (boutonSelectionne_ != null)
                    {
                        bool aRetourner = false;
                        if (etat_ != null)
                            aRetourner = etat_.interpreterEchap();
                        if (aRetourner)
                        {
                            retournerEtatInitial();
                        }
                    }
                    break;
                case Keys.Delete:
                    supprimerToolStripButton_Click(supprimerToolStripButton, e);
                    break;
                case Keys.D:
                    deplacementToolStripButton_Click(deplacementToolStripButton, null);
                    break;
                case Keys.S :
                    if (e.Control)
                        enregistrerToolStripButton_Click(enregistrerToolStripButton, null);
                    else
                        selectionToolStripButton_Click(selectionToolStripButton, null);
                    break;
                case Keys.R:
                    rotationToolStripButton_Click(rotationToolStripButton, null);
                    break;
                case Keys.E:
                    miseAEchelleToolStripButton_Click(miseAEchelleToolStripButton, null);
                    break;
                case Keys.C:
                    duplicationToolStripButton_Click(duplicationToolStripButton, null);
                    break;
                case Keys.Z:
                    zoomToolStripButton_Click(zoomToolStripButton, null);
                    break;
                case Keys.N:
                    if (e.Control)
                        nouveauToolStripButton_Click(nouveauToolStripButton, null);
                    break;
                case Keys.O:
                    if (e.Control)
                        ouvrirToolStripMenuItem_Click(ouvrirToolStripButton, null);
                    break;
                case Keys.Q:
                    if (e.Control)
                        this.Close();
                    break;
                case Keys.D1:
                case Keys.NumPad1:
                    orthographiqueToolStripMenuItem_Click(null, null);
                    break;
                case Keys.D2:
                case Keys.NumPad2:
                    orbiteToolStripMenuItem_Click(null, null);
                    break;
                case Keys.T:
                    modeTestToolStripMenuItem_Click(null, null);
                    break;
                default:
                    break;
            }
        }

        private void Edition_KeyDown(object sender, KeyEventArgs e)
        {
            /*switch (e.KeyCode)
            {
                case Keys.D1:
                    Console.WriteLine("1");
                    orthographiqueToolStripMenuItem_Click(orthographiqueToolStripMenuItem, null);
                    break;
                case Keys.D2:
                    Console.WriteLine("2");
                    orbiteToolStripMenuItem_Click(orbiteToolStripMenuItem, null);
                    break;
                default:
                    break;
            }*/
        }

        //*********************** Evenements de la souris ***********************//

        /**
         * Definie les actions a executer quand on appuie sur le bouton gauche 
         * de la souris
         */

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseDown(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement d'appui d'un bouton de
        /// la souris.
        /// 
        /// @param[in] sender : Represente la touche relier a l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                modificateur_ = ModifierKeys;
                xMouseDown_ = e.Location.X;
                yMouseDown_ = e.Location.Y;
                sourisEstEnZoneDeClic_ = true;
                boutonGauchePresse_ = true;
                initialisationEnvoyee_ = false;
            }
            else
            {
                if (e.Button == System.Windows.Forms.MouseButtons.Right && !enTrace_)
                {
                    //xMouseDown_ = e.Location.X;
                    //yMouseDown_ = e.Location.Y;
                    FonctionsNatives.sauverPositionSouris(e.Location.X, e.Location.Y);
                    Program.edition.Cursor = Cursors.SizeAll;
                    boutonDroitePresse_ = true;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseUp(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de relachement d'un bouton de
        /// la souris.
        /// 
        /// @param[in] sender : Represente la touche relier a l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                boutonGauchePresse_ = false;
                if (etat_ != null)
                {
                    if (modificateur_ != ModifierKeys)
                        modificateur_ = Keys.None;
                    if (sourisEstEnZoneDeClic_)
                        etat_.interpreterClic(e.X, e.Y, modificateur_);
                    else
                        etat_.interpreterDepot(e.X, e.Y, modificateur_);
                }
            }
            else
            {
                if (e.Button == System.Windows.Forms.MouseButtons.Right && !enTrace_)
                { 
                    FonctionsNatives.deplacerFenetreVirtuelleSouris(e.Location.X, e.Location.Y);
                    Program.edition.Cursor = Cursors.Default;
                    boutonDroitePresse_ = false;
                }
            }
        }

        /**
         * Definie les actions a executer quand on tourne la roulette de la souris
         */

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseWheel(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement provenant de roulette de
        /// la souris
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseWheel(object sender, MouseEventArgs e)
        {
            int nombreDeZoom = e.Delta / 120;
            for (int i = 0; i < Math.Abs(nombreDeZoom); i++)
            {
                if (nombreDeZoom < 0)
                    FonctionsNatives.zoomOut();
                else
                    FonctionsNatives.zoomIn();
            }
         }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseMove(object sender, MouseEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement provenant du deplacement
        /// de la souris.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseMove(object sender, MouseEventArgs e)
        {
            if ( !boutonDroitePresse_ )
            {
                if (etat_ == null)
                    return;

                if ( !etat_.verifierCurseur(e.Location.X, e.Location.Y) && enEdition_ )
                    Cursor = Cursors.No;
                else
                    Cursor = Cursors.Default;

                if (!sourisEstEnZoneDeClic_)
                {
                    if (boutonGauchePresse_)
                    {
                        if (!initialisationEnvoyee_)
                        {
                            etat_.initialiserDebut(xMouseDown_, yMouseDown_);
                            initialisationEnvoyee_ = true;
                        }
                        etat_.interpreterGlissement(e.X, e.Y);
                    }
                    else
                        etat_.interpreterDeplacement(e.X, e.Y);
                }
                else
                {
                    if (e.Location.X > xMouseDown_ + 3 || e.Location.X < xMouseDown_ - 3 || e.Location.Y > yMouseDown_ + 3 || e.Location.Y < yMouseDown_ - 3)
                        sourisEstEnZoneDeClic_ = false;
                }
            }
            else
            {
                if (compteurDeplacement_ == 2)
                {
                    FonctionsNatives.deplacerFenetreVirtuelleSouris(e.Location.X, e.Location.Y);
                    compteurDeplacement_ = 0;
                }
                else
                    compteurDeplacement_++;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton quitter
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Edition_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic le bouton de fermeture
        /// de la fenetre
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Edition_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (sceneModifiee_)
            {
                MessageBoxButtons boite = MessageBoxButtons.YesNoCancel;
                DialogResult resultat = MessageBox.Show(" La scène ouverte n'est pas encore enregistrée, \n voulez vous l'enregistrer avant de fermer?",
                    "Scène non enregistrée", boite, MessageBoxIcon.Warning);
                if (resultat == DialogResult.Yes)
                {
                    if (nomFichierOuvert_ == null)
                    {
                        enregistrerSousToolStripMenuItem_Click(enregistrerSousToolStripMenuItem, e);
                        if (nomFichierOuvert_ == null)
                            return;
                    }
                    else
                        enregistrerToolStripButton_Click(enregistrerToolStripButton, e);
                }
                else
                {
                    if (resultat == DialogResult.Cancel)
                    {
                        e.Cancel = true;
                        return;
                    }
                }
            }
                        
            lock(Program.unLock)
            {
                if (!openGLLibere_)
                    FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la generation d'une nouvelle zone de dessin
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            nouveauToolStripButton_Click(nouveauToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nouveauToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la generation d'une nouvelle zone de dessin
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nouveauToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            if ( sceneModifiee_ )
            {
                MessageBoxButtons boite = MessageBoxButtons.YesNoCancel;
                DialogResult resultat = MessageBox.Show(" La scène ouverte n'est pas encore enregistrée, \n voulez vous l'enregistrer avant de commencer\n une nouvelle?",
                    "Scène non enregistrée", boite, MessageBoxIcon.Warning);
                if (resultat == DialogResult.Yes)
                {
                    if (nomFichierOuvert_ == null)
                    {
                        enregistrerSousToolStripMenuItem_Click(enregistrerSousToolStripMenuItem, e);
                        if (nomFichierOuvert_ == null)
                            return;
                    }
                    else
                        enregistrerToolStripButton_Click(enregistrerToolStripButton, e);
                }
                else
                {
                    if ( resultat == DialogResult.Cancel )
                        return;
                }
            }
            
            FonctionsNatives.reInitialiserScene();
            //FonctionsNatives.redimensionnerFenetre(zoneDeDessin.Width, zoneDeDessin.Height);
            nomFichierOuvert_ = null;
            this.Text = "Edition : nouvelle scene";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'ouverture d'un nouveau fichier xml
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ouvrirtoolStripButton_Click(ouvrirToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ouvrirtoolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'ouverture d'un nouveau fichier xml
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ouvrirtoolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            openFileDialog.Filter = "Fichier XML (*.xml)|*.xml";
            openFileDialog.InitialDirectory = Path.Combine(Application.StartupPath, @"zones");
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                nomFichierOuvert_ = openFileDialog.FileName;
                if (nomCompletFichierParDefaut_ == nomFichierOuvert_)
                    this.Text = "Edition : default"; 
                else
                    this.Text = "Edition : " + nomFichierOuvert_; 
                FonctionsNatives.chargerZoneDeSimulation(nomFichierOuvert_);
                sceneModifiee_ = false;

                enregistrerToolStripButton.Enabled = false;
                enregistrerToolStripMenuItem.Enabled = false;

            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la sauvegarde de la zone de dessin dans un fichier xml
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            if (nomFichierOuvert_ == nomCompletFichierParDefaut_ || nomFichierOuvert_ == null)
                enregistrerSousToolStripMenuItem_Click(enregistrerSousToolStripMenuItem, e);
            else
            {
                if (sceneModifiee_)
                {
                    FonctionsNatives.enregistrerZoneDeSimulation(nomFichierOuvert_);
                    this.Text = "Edition : " + nomFichierOuvert_;
                    sceneModifiee_ = false;
                    enregistrerToolStripButton.Enabled = false;
                    enregistrerToolStripMenuItem.Enabled = false;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la sauvegarde de la zone de dessin dans un fichier xml
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            enregistrerToolStripButton_Click(enregistrerToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void enregistrerToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la sauvegarde de la zone de dessin dans un fichier xml
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog.Filter = "Fichier XML (*.xml)|*.xml";
            saveFileDialog.InitialDirectory = Path.Combine(Application.StartupPath, @"zones");
            saveFileDialog.RestoreDirectory = true;

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog.FileName.ToString() != nomCompletFichierParDefaut_)
                {
                    nomFichierOuvert_ = saveFileDialog.FileName.ToString();
                    this.Text = "Edition : " + nomFichierOuvert_;
                    FonctionsNatives.enregistrerZoneDeSimulation(nomFichierOuvert_);
                    sceneModifiee_ = false;
                    //enregistrerToolStripButton.Enabled = false;
                    //enregistrerToolStripMenuItem.Enabled = false;
                }
                else 
                {
                    MessageBox.Show("Vous pouvez pas modifier le fichier default.xml.\nChoisissez un autre nom ou un autre repertoire",
                        "Fichier protégé", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectionToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant d'initialiser le mode selection d'objet
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void selectionToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(selectionToolStripButton);
            basculerItem(selectionToolStripMenuItem);
            if (selectionToolStripButton.Checked == true)
                etat_ = new EtatEditionSelection();
            else
                etat_ = null;
            enEdition_ = false;
            boutonGauchePresse_ = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void selectionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant d'initialiser le mode selection d'objet
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void selectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            selectionToolStripButton_Click(selectionToolStripButton, e);
        }

        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void deplacementToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant d'initialiser le mode deplacement des objets dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////

        private void deplacementToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(deplacementToolStripButton);
            basculerItem(deplacementToolStripMenuItem);
            if (deplacementToolStripButton.Checked == true)
                etat_ = new EtatEditionDeplacement();
            else
                etat_ = null;
            enEdition_ = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void deplacementToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant d'initialiser le mode deplacement des objets dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void deplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            deplacementToolStripButton_Click(deplacementToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton de zoom
        /// avec rectangle elastique afin d'effectuer un zoom in ou zoom out avec 
        /// ce dernier.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(zoomToolStripButton);
            basculerItem(zoomToolStripMenuItem);
            if (zoomToolStripButton.Checked == true)
                etat_ = new EtatEditionZoom();
            else
                etat_ = null;
            enEdition_ = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton de zoom
        /// avec rectangle elastique afin d'effectuer un zoom in ou zoom out avec 
        /// ce dernier.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            zoomToolStripButton_Click(zoomToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomInToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton de zoom
        /// in.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomInToolStripButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomIn();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoomOutToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton de zoom
        /// out.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoomOutToolStripButton_Click(object sender, EventArgs e)
        {
            FonctionsNatives.zoomOut();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void poteauToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant le placement de poteau dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void poteauToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(poteauToolStripButton);
            basculerItem(poteauToolStripMenuItem);
            if (poteauToolStripButton.Checked == true)
            {
                etat_ = new EtatEditionPoteau();
                enEdition_ = true;
            }
            else
            {
                etat_ = null;
                enEdition_ = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void poteauToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant le placement de mur dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void murToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(murToolStripButton);
            basculerItem(murToolStripMenuItem);
            if (murToolStripButton.Checked == true)
            {
                etat_ = new EtatEditionMur();
                enEdition_ = true;
            }
            else
            {
                etat_ = null;
                enEdition_ = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ligneToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant le placement de ligne dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ligneToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(ligneToolStripButton);
            basculerItem(ligneNoireToolStripMenuItem);
            if (ligneToolStripButton.Checked == true)
            {
                etat_ = new EtatEditionLigne();
                enEdition_ = true;
            }
            else
            {
                etat_ = null;
                enEdition_ = false;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ligneToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la supression de l'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void supprimerToolStripButton_Click(object sender, EventArgs e)
        {
            if (FonctionsNatives.obtenirNombreNoeudsSelectionnes() != 0)
            {
                if (boutonSelectionne_ != null)
                {
                    boutonSelectionne_.Checked = false;
                    boutonSelectionne_ = null;
                }
                if (itemSelectionne_ != null)
                {
                    itemSelectionne_.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                    itemSelectionne_ = null;
                }
                FonctionsNatives.supprimerSelection();
                marquerModificationDansLaScene();
                changerEtatOptionSupprimmer(false);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ligneToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la supression de l'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            supprimerToolStripButton_Click(supprimerToolStripButton, e);
        }
        

        /*private void zoneDeDessin_Resize(object sender, EventArgs e) //POURQUOI
        {
            FonctionsNatives.redimensionnerFenetre(zoneDeDessin.Width, zoneDeDessin.Height);
        }*/


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de CTRL-Q afin de
        /// quitter l'application.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void menuPrincipalCtrlQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur l'option poteau
        /// pour l'ajouter a la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void poteauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            poteauToolStripButton_Click(poteauToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void murToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur l'option mur
        /// pour l'ajouter a la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void murToolStripMenuItem_Click(object sender, EventArgs e)
        {
            murToolStripButton_Click(murToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur l'option ligne
        /// pour l'ajouter a la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ligneNoireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ligneToolStripButton_Click(ligneToolStripButton, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void basculerBouton(ToolStripButton bouton)
        ///
        /// Methode permettant la bascule de la selection d'un bouton et le changement
        /// de la variable boutonSelectionne
        /// 
        /// @param[in] bouton : Represente l'objet bouton en question
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void basculerBouton(ToolStripButton bouton)
        {
            if (bouton.Checked == true)
            {
                bouton.Checked = false;
                boutonSelectionne_ = null;
            }
            else
            {
                bouton.Checked = true;
                if (boutonSelectionne_ != null)
                    boutonSelectionne_.Checked = false;
                boutonSelectionne_ = bouton;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void basculerItem(ToolStripMenuItem item)
        ///
        /// Methode permettant la bascule de la selection d'un item du menu et 
        /// le changement de la variable itemSelectionne
        /// 
        /// @param[in] item : Represente l'objet en question
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void basculerItem(ToolStripMenuItem item)
        {
            if (item == itemSelectionne_)
            {
                item.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                itemSelectionne_ = null;
            }
            else
            {
                item.BackColor = Color.LightSkyBlue;
                if (itemSelectionne_ != null)
                    itemSelectionne_.BackColor = System.Windows.Forms.Control.DefaultBackColor;
               
                itemSelectionne_ = item;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la rotation de l'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////      
        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            rotationToolStripButton_Click(rotationToolStripButton, null);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void miseAEchelleToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la mise a l'echelle de l'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////     
        private void miseAEchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            miseAEchelleToolStripButton_Click(miseAEchelleToolStripButton, null);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant la duplication de l'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////    
        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            duplicationToolStripButton_Click(duplicationToolStripButton, null);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'activation de la vue orthographique
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////    
        private void orthographiqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (orthographiqueToolStripMenuItem.BackColor == System.Windows.Forms.Control.DefaultBackColor)
            {
                orthographiqueToolStripMenuItem.BackColor = Color.LightSkyBlue;
                orbiteToolStripMenuItem.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                FonctionsNatives.activerVueOrthographique();
                zoomToolStripButton.Enabled = true;
                FonctionsNatives.redimensionnerFenetre(zoneDeDessin.Width, zoneDeDessin.Height);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'activation de la vue en orbite
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (orbiteToolStripMenuItem.BackColor == System.Windows.Forms.Control.DefaultBackColor)
            {
                orbiteToolStripMenuItem.BackColor = Color.LightSkyBlue;
                orthographiqueToolStripMenuItem.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                FonctionsNatives.activerVueOrbite();
                zoomToolStripButton.Enabled = false;
                FonctionsNatives.redimensionnerFenetre(zoneDeDessin.Width, zoneDeDessin.Height);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de clic sur le bouton
        /// permettant l'ouverture d'une fenetre d'aide a un usager.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void orbiteToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de redimensionnement de 
        /// la fenetre d'edition.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Edition_Resize(object sender, EventArgs e)
        {
            largeurZoneDeDessin_ = zoneDeDessin.Width;
            hauteurZoneDeDessin_ = zoneDeDessin.Height;
            FonctionsNatives.redimensionnerFenetre(zoneDeDessin.Width, zoneDeDessin.Height);
            Program.executerMiseAJour();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseLeave(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement de deplacement hors de
        /// la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseLeave(object sender, EventArgs e)
        {
            Cursor = Cursors.Default;
            //curseurDansLaZoneDeDessin = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void zoneDeDessin_MouseEnter(object sender, EventArgs e)
        ///
        /// Methode permettant la capture de l'evenement d'entrer de la souris
        /// dans la zone de dessin.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void zoneDeDessin_MouseEnter(object sender, EventArgs e)
        {
            if ( !aideEnPremierPlan_ )
            {
                zoneDeDessin.Focus();
                //curseurDansLaZoneDeDessin = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void configurationToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant la configuration d'un et un unique objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void configurationToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
            {
                etat_.interpreterEchap();
                etat_ = null;
            }
            int nombreElementSelectionnes = FonctionsNatives.obtenirNombreNoeudsSelectionnes();
            if ( nombreElementSelectionnes == 1 )
            {
                basculerBouton(configurationToolStripButton);
                
                double x = FonctionsNatives.obtenirPositionXElementSelectionne();
                double y = FonctionsNatives.obtenirPositionYElementSelectionne();
                double rotation = FonctionsNatives.obtenirRotationElementSelectionne();
                double echelle = FonctionsNatives.obtenirEchelleElementSelectionne();
                bool type = FonctionsNatives.noeudSelectionneEstFleche()
                    || FonctionsNatives.noeudSelectionneEstLigne();
                ConfigurationEdition configuration = new ConfigurationEdition( Math.Round(x, 2),
                    Math.Round(y, 2), Math.Round(rotation, 2)%360, Math.Round( echelle, 2),
                    type );
                
                double[,] informationConfiguration = configuration.lancerConfiguration(this);
                if ( configuration.estValide() )
                {
                    FonctionsNatives.initialiserEnTraitement();
                    bool configure = true;
                    if (informationConfiguration[0, 0] != 0 && informationConfiguration[1, 0] != 0
                        && !FonctionsNatives.assignerPositionPourObjetSelectionne(informationConfiguration[0, 1], informationConfiguration[1, 1], 0))
                    {
                        configure = false;
                        etat_ = null;
                    }
                    else
                    {
                        configure = true;
                    }

                    if ( configure == true )
                    {
                        if (informationConfiguration[2, 0] != 0)
                        {
                            FonctionsNatives.PivoterObjetSelectionne(2 * ( informationConfiguration[2, 1] - rotation));
                            if ( !FonctionsNatives.objetsSelectionnesSurLaTable() )
                            {
                                FonctionsNatives.PivoterObjetSelectionne(2 * ( - informationConfiguration[2, 1] + rotation));
                                configure = false;
                                FonctionsNatives.assignerPositionPourObjetSelectionne(x, y, 0);
                            }
                        }
                        if ( configure == true && informationConfiguration[3, 0] != 0 && 
                            !FonctionsNatives.changerScalePourObjetSelectionne(informationConfiguration[3, 1] / echelle))
                        {
                            FonctionsNatives.PivoterObjetSelectionne(2 * (-informationConfiguration[2, 1] + rotation));
                            configure = false;
                            FonctionsNatives.assignerPositionPourObjetSelectionne(x, y, 0);
                        }
                    }
                    if ( configure == false )
                        MessageBox.Show("La combinaison des paramétres choisis fait sortir l'objet de la table",
                            "Configuration échouée", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    else
                        Program.edition.marquerModificationDansLaScene();
                }
                configurationToolStripButton.Checked = false;
                boutonSelectionne_ = null;
                if (itemSelectionne_ != null)
                {
                    itemSelectionne_.BackColor = System.Windows.Forms.Control.DefaultBackColor;
                    itemSelectionne_ = null;
                }
            }
            else
            {
                if ( nombreElementSelectionnes == 0 )
                    MessageBox.Show("Aucun élément n'est sélectionné",
                        "Opération non autorisée", MessageBoxButtons.OK, MessageBoxIcon.Information);
                else
                    MessageBox.Show(nombreElementSelectionnes + " éléments sont sélectionnés.\nSélectionnez un seul élement",
                        "Opération non autorisée", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void rotationToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant la rotation d'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void rotationToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(rotationToolStripButton);
            basculerItem(rotationToolStripMenuItem);
            if (rotationToolStripButton.Checked == true)
                etat_ = new EtatEditionRotation();
            else
                etat_ = null;
            enEdition_ = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void rotationToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant la mise a l'echelle d'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void miseAEchelleToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(miseAEchelleToolStripButton);
            basculerItem(miseAEchelleToolStripMenuItem);
            if (miseAEchelleToolStripButton.Checked == true)
                etat_ = new EtatEditionScale();
            else
                etat_ = null;
            enEdition_ = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void duplicationToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant la duplication d'objet selectionne.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void duplicationToolStripButton_Click(object sender, EventArgs e)
        {
            if (etat_ != null)
                etat_.interpreterEchap();
            basculerBouton(duplicationToolStripButton);
            basculerItem(duplicationToolStripMenuItem);
            if (duplicationToolStripButton.Checked == true)
                etat_ = new EtatEditionDuplication();
            else
                etat_ = null;
            enEdition_ = false;

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void duplicationToolStripButton_Click(object sender, EventArgs e)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant l'affichage d'une fenetre d'aide a l'usager.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void aideToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (aide_ == null) 
            {
                aide_ = new Aide();
                aide_.FormClosed += fermetureAide;
            }
            aideEnPremierPlan_ = true;
            aide_.Show();
            aide_.Activate();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn void fermetureAide(object sender, FormClosedEventArgs args)
        ///
        /// Methode permettant la detection d'un clic de souris sur le bouton 
        /// permettant la fermeture de la fenetre d'aide
        /// 
        /// @param[in] args : Evenement relier a la fermeture de la fenetre
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        void fermetureAide(object sender, FormClosedEventArgs args)
        {
            aide_.FormClosed -= fermetureAide;
            aide_ = null;
            aideEnPremierPlan_ = false;
        }

        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.enregistrerZoneDeSimulation("temp");
            this.Hide();
            Program.simulation = new Simulation(false);
            bool retourPrincipale = Program.simulation.lancerSimulation("temp");
            openGLLibere_ = true;
            Program.simulation = null;
            if (!retourPrincipale)
            {
                FonctionsNatives.changerModeApplication('E');
                InitialiserAnimation();
                Program.peutAfficher = true;
                FonctionsNatives.chargerZoneDeSimulation("temp");
                if ( orbiteToolStripMenuItem.BackColor == Color.LightSkyBlue )
                    FonctionsNatives.activerVueOrbite();
                Edition_Resize(null, null);
                this.Show();
            }
            else
                menuPrincipalCtrlQToolStripMenuItem_Click(null, null);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// @class FonctionsNatives
    /// @brief Classe contenant des fonction externe implementer au niveau du
    /// noyau de l'application.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL(double temps);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerHaut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerBas();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerDroite();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerGauche();

        // Test(Samir)
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerFenetreVirtuelleSouris(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauverPositionSouris(int x, int y);

        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void enregistrerZoneDeSimulation(string nomFichier);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerZoneDeSimulation(string nomFichier);//(string nomFichier);

        

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
       // public static extern void zoomInRectangle(int xMin, int yMin, int xMax, int yMax);
        public static extern void zoomInRectangle(int xMin, int xMax, int yMin, int yMax);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOutRectangle(int xMin, int xMax, int yMin, int yMax);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void selectRectElastique(int X_debut, int Y_debut, int X_fin, int Y_fin, bool estEnfonce);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerSelection();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool assignerPositionPourObjetSelectionne(double x, double y, double z);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerRotationPourObjetSelectionne(double rotation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool changerScalePourObjetSelectionne(double scale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void scaleSelection(double facteurScale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PivoterObjetSelectionne(double deltaY);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PivoterObjetsMultiples(double rotation);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool tournerObjetSelectionne(double angle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void annulerRotationSelection();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreNoeudsSelectionnes();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void debuterSimulation();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerModeApplication(char mode);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool noeudSelectionneEstFleche();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool noeudSelectionneEstLigne();
        //
    }
}
