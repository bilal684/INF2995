///////////////////////////////////////////////////////////////////////////////
/// @file ConfigurationEdition.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Web.UI;
using System.Globalization;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    public partial class ConfigurationEdition : Form
    {
        private bool valide = false;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ConfigurationEdition()
        ///
        /// Constructeur.
        ///
        /// @param Aucun. 
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        public ConfigurationEdition ( double x, double y, double rotation, double echelle, bool type )
        {
            InitializeComponent();
            this.positionXTextBox.Text = x.ToString();
            this.positionYTextBox.Text = y.ToString();
            this.rotationTextBox.Text = rotation.ToString();
            this.echelleTextBox.Text = echelle.ToString();
            if (type)
                this.echelleTextBox.Enabled = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public bool estValide()
        ///
        /// verifie si valide.
        ///
        /// @param Aucun. 
        ///
        /// @return Vrai si valide, faux sinon.
        ///
        ////////////////////////////////////////////////////////////////////////
        public bool estValide()
        {
            return valide;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public double[,] lancerConfiguration(Form parent)
        ///
        /// 
        ///
        /// @param[in] parent: . 
        ///
        /// @return 
        ///
        ////////////////////////////////////////////////////////////////////////
        public double[,] lancerConfiguration(Form parent)
        {
            this.ShowDialog(parent);
            double[,] configuration = new double[5,2];
            if ( positionXTextBox.Text != "" )
            {
                configuration[0,0] = 1;
                configuration[0,1] = Convert.ToDouble(positionXTextBox.Text);
            }
            else
                configuration[0,0] = 0;

            if ( positionYTextBox.Text != "" )
            {
                configuration[1,0] = 1;
                configuration[1,1] = Convert.ToDouble(positionYTextBox.Text);
            }
            else
                configuration[1,0] = 0;
            
            if ( rotationTextBox.Text != "" )
            {
                configuration[2,0] = 1;
                configuration[2,1] = Convert.ToDouble(rotationTextBox.Text);
            }
            else
                configuration[2,0] = 0;
            
            if ( echelleTextBox.Text != "" )
            {
                configuration[3,0] = 1;
                configuration[3,1] = Convert.ToDouble(echelleTextBox.Text);
            }
            else
                configuration[3,0] = 0;
            
            return configuration;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OkButton_Click(object sender, EventArgs e)
        ///
        /// Action a executer apres le click sur le bouton ok.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OkButton_Click(object sender, EventArgs e)
        {
            valide = true;
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void AnnulerButton_Click(object sender, EventArgs e)
        ///
        /// Action a executer apres le click sur le bouton annuler.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void AnnulerButton_Click(object sender, EventArgs e)
        {
            valide = false;
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EffacerButton_Click(object sender, EventArgs e)
        ///
        /// Action a executer apres le click sur le bouton effacer.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EffacerButton_Click(object sender, EventArgs e)
        {
            positionXTextBox.Text = "";
            positionYTextBox.Text = "";
            rotationTextBox.Text = "";
            if ( echelleTextBox.Enabled == true )
                echelleTextBox.Text = "";
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        ///
        /// Action a executer apres le click sur la zone de texte de la boite.
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void textBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            char separateur = Convert.ToChar(CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator);
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&
                (e.KeyChar != separateur) && (e.KeyChar != '-'))
            {
                e.Handled = true;
            }

            if ( ( (e.KeyChar == separateur) && ( ( (sender as TextBox).Text.IndexOf(separateur) > -1) || ( (sender as TextBox).Text.Length == 0) ) )
            || ( (e.KeyChar == '-') && ( ( (sender as TextBox).Text.Length != 0) || sender == echelleTextBox ) ) )
            {
                e.Handled = true;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Configuration_Load(object sender, EventArgs e)
        ///
        /// 
        ///
        /// @param[in] sender : l'objet envoyant l'action.
        /// 
        /// @param[in] e : argument de l'evenement.
        ///
        /// @return Aucun.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Configuration_Load(object sender, EventArgs e)
        {
            this.Location = new Point(this.Owner.Location.X + 360, this.Owner.Location.Y + 103); 
        }
    }

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionXElementSelectionne();

	    [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirPositionYElementSelectionne();

	    [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirRotationElementSelectionne();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirEchelleElementSelectionne();
    }
}
