﻿///////////////////////////////////////////////////////////////////////////////
/// @file Program.cs
/// @author INF2990 Eq.11
/// @date 2016-02-15
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Program
    /// @brief Classe representant le main du projet.
    ///
    /// @author INF2990 Eq.11
    /// @date 2016-02-15
    ///////////////////////////////////////////////////////////////////////////
    static class Program
    {
        /// constante qui enregistre le nombre d'image par seconde souhaite
        private const int NB_IMAGES_PAR_SECONDE = 60;
        /// un lock pour avoir l'acces exclusif a peutAfficher
        public static Object unLock = new Object();
        /// Enregistre si on peutafficher l'image sans probleme
        public static bool peutAfficher = true;
        /// instance pour la fenetre Edition
        public static Edition edition;
        /// instance pour la fenetre de la simulation
        public static Simulation simulation;
        /// instance du menu Principale
        public static MenuPrincipale menuPrincipale;
        /// enregistre le dernier temps de l'affichege
        private static TimeSpan dernierTemps;
        /// enregistre le temps ecoule depuis le dernier affichage
        private static TimeSpan tempsAccumule;
        /// instance Stopwach pour surveiller le temps
        private static Stopwatch chrono = Stopwatch.StartNew();
        /// le temps ecoulé souhaite entre deux affichage successives
        public static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / NB_IMAGES_PAR_SECONDE);

        /// <summary>
        /// Point d'entrée principal de l'application.
        /// </summary>
        [STAThread]
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static void Main(string[] args)
        ///
        /// Le point d'entree principal de l'application.
        /// 
        /// @param[in] args : Arguments d'entrer de l'application.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        static void Main(string[] args)
        {
           /* if (args.Length != 0)
                if (args[0] == "testsC++")
                {
                    if (FonctionsNatives.executerTests())
                        System.Console.WriteLine("Échec d'un ou plusieurs tests.");
                    else
                        System.Console.WriteLine("Tests réussis.");

                    return;
                }
            */

            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            menuPrincipale = new MenuPrincipale();
            Application.Run(menuPrincipale);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static void ExecuterQuandInactif(object sender, EventArgs e)
        ///
        /// Methode fourni dans le cadre du cadriciel.
        /// 
        /// @param[in] sender : Represente l'objet generant l'evenement.
        /// 
        /// @param[in] e : Represente l'evenement.
        ///
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;
            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
               executerMiseAJour();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn static public void executerMiseAJour()
        ///
        /// Methode permettant l'execution de la mise a jour de l'image sur les
        /// deux fenetre Simulation et edition si l'un des deux est actif 
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        static public void executerMiseAJour()
        {
            TimeSpan currentTime = chrono.Elapsed;
            TimeSpan elapsedTime = currentTime - dernierTemps;
            dernierTemps = currentTime;
            tempsAccumule += elapsedTime;

            if (tempsAccumule >= tempsEcouleVoulu)
            {
                lock (unLock)
                {

                    if (edition != null && peutAfficher)
                        edition.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                    else if (simulation != null && peutAfficher)
                        simulation.MettreAJour((double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond);
                }
                tempsAccumule = TimeSpan.Zero;
            }
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
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint Msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint Time;
            public System.Drawing.Point Point;
        }

        [DllImport("User32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool executerTests();
    }
}
