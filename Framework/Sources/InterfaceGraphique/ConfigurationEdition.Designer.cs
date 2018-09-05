namespace InterfaceGraphique
{
    partial class ConfigurationEdition
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.AnnulerButton = new System.Windows.Forms.Button();
            this.OkButton = new System.Windows.Forms.Button();
            this.positionLabel = new System.Windows.Forms.Label();
            this.rotationLabel = new System.Windows.Forms.Label();
            this.positionXTextBox = new System.Windows.Forms.TextBox();
            this.rotationTextBox = new System.Windows.Forms.TextBox();
            this.xLabel = new System.Windows.Forms.Label();
            this.yLabel = new System.Windows.Forms.Label();
            this.positionYTextBox = new System.Windows.Forms.TextBox();
            this.echelleLabel = new System.Windows.Forms.Label();
            this.echelleTextBox = new System.Windows.Forms.TextBox();
            this.effacerButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // AnnulerButton
            // 
            this.AnnulerButton.Location = new System.Drawing.Point(49, 135);
            this.AnnulerButton.Name = "AnnulerButton";
            this.AnnulerButton.Size = new System.Drawing.Size(67, 23);
            this.AnnulerButton.TabIndex = 0;
            this.AnnulerButton.Text = "Annuler";
            this.AnnulerButton.UseVisualStyleBackColor = true;
            this.AnnulerButton.Click += new System.EventHandler(this.AnnulerButton_Click);
            // 
            // OkButton
            // 
            this.OkButton.Location = new System.Drawing.Point(187, 135);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(67, 23);
            this.OkButton.TabIndex = 1;
            this.OkButton.Text = "OK";
            this.OkButton.UseVisualStyleBackColor = true;
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // positionLabel
            // 
            this.positionLabel.AutoSize = true;
            this.positionLabel.Location = new System.Drawing.Point(30, 49);
            this.positionLabel.Name = "positionLabel";
            this.positionLabel.Size = new System.Drawing.Size(50, 13);
            this.positionLabel.TabIndex = 2;
            this.positionLabel.Text = "Position :";
            // 
            // rotationLabel
            // 
            this.rotationLabel.AutoSize = true;
            this.rotationLabel.Location = new System.Drawing.Point(30, 79);
            this.rotationLabel.Name = "rotationLabel";
            this.rotationLabel.Size = new System.Drawing.Size(53, 13);
            this.rotationLabel.TabIndex = 3;
            this.rotationLabel.Text = "Rotation :";
            // 
            // positionXTextBox
            // 
            this.positionXTextBox.AcceptsReturn = true;
            this.positionXTextBox.Location = new System.Drawing.Point(152, 46);
            this.positionXTextBox.Name = "positionXTextBox";
            this.positionXTextBox.Size = new System.Drawing.Size(37, 20);
            this.positionXTextBox.TabIndex = 4;
            this.positionXTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // rotationTextBox
            // 
            this.rotationTextBox.Location = new System.Drawing.Point(151, 72);
            this.rotationTextBox.Name = "rotationTextBox";
            this.rotationTextBox.Size = new System.Drawing.Size(103, 20);
            this.rotationTextBox.TabIndex = 5;
            this.rotationTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // xLabel
            // 
            this.xLabel.AutoSize = true;
            this.xLabel.Location = new System.Drawing.Point(135, 49);
            this.xLabel.Name = "xLabel";
            this.xLabel.Size = new System.Drawing.Size(15, 13);
            this.xLabel.TabIndex = 2;
            this.xLabel.Text = "x:";
            // 
            // yLabel
            // 
            this.yLabel.AutoSize = true;
            this.yLabel.Location = new System.Drawing.Point(197, 49);
            this.yLabel.Name = "yLabel";
            this.yLabel.Size = new System.Drawing.Size(15, 13);
            this.yLabel.TabIndex = 2;
            this.yLabel.Text = "y:";
            // 
            // positionYTextBox
            // 
            this.positionYTextBox.Location = new System.Drawing.Point(215, 46);
            this.positionYTextBox.Name = "positionYTextBox";
            this.positionYTextBox.Size = new System.Drawing.Size(37, 20);
            this.positionYTextBox.TabIndex = 4;
            this.positionYTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // echelleLabel
            // 
            this.echelleLabel.AutoSize = true;
            this.echelleLabel.Location = new System.Drawing.Point(30, 105);
            this.echelleLabel.Name = "echelleLabel";
            this.echelleLabel.Size = new System.Drawing.Size(48, 13);
            this.echelleLabel.TabIndex = 3;
            this.echelleLabel.Text = "Echelle :";
            // 
            // echelleTextBox
            // 
            this.echelleTextBox.Location = new System.Drawing.Point(151, 98);
            this.echelleTextBox.Name = "echelleTextBox";
            this.echelleTextBox.Size = new System.Drawing.Size(103, 20);
            this.echelleTextBox.TabIndex = 5;
            this.echelleTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox_KeyPress);
            // 
            // effacerButton
            // 
            this.effacerButton.Location = new System.Drawing.Point(118, 135);
            this.effacerButton.Name = "effacerButton";
            this.effacerButton.Size = new System.Drawing.Size(67, 23);
            this.effacerButton.TabIndex = 0;
            this.effacerButton.Text = "Effacer";
            this.effacerButton.UseVisualStyleBackColor = true;
            this.effacerButton.Click += new System.EventHandler(this.EffacerButton_Click);
            // 
            // Configuration
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 170);
            this.Controls.Add(this.echelleTextBox);
            this.Controls.Add(this.rotationTextBox);
            this.Controls.Add(this.positionYTextBox);
            this.Controls.Add(this.positionXTextBox);
            this.Controls.Add(this.echelleLabel);
            this.Controls.Add(this.yLabel);
            this.Controls.Add(this.rotationLabel);
            this.Controls.Add(this.xLabel);
            this.Controls.Add(this.positionLabel);
            this.Controls.Add(this.OkButton);
            this.Controls.Add(this.effacerButton);
            this.Controls.Add(this.AnnulerButton);
            this.Name = "Configuration";
            this.Text = "Configuration";
            this.Load += new System.EventHandler(this.Configuration_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button AnnulerButton;
        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Label positionLabel;
        private System.Windows.Forms.Label rotationLabel;
        private System.Windows.Forms.TextBox positionXTextBox;
        private System.Windows.Forms.TextBox rotationTextBox;
        private System.Windows.Forms.Label xLabel;
        private System.Windows.Forms.Label yLabel;
        private System.Windows.Forms.TextBox positionYTextBox;
        private System.Windows.Forms.Label echelleLabel;
        private System.Windows.Forms.TextBox echelleTextBox;
        private System.Windows.Forms.Button effacerButton;
    }
}