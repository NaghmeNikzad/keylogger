namespace Server
{
    partial class mainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.networkLogsTxt = new System.Windows.Forms.RichTextBox();
            this.loggerTxt = new System.Windows.Forms.RichTextBox();
            this.exportBtn = new System.Windows.Forms.Button();
            this.clearLogsBtn = new System.Windows.Forms.Button();
            this.clearKeylogsBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // networkLogsTxt
            // 
            this.networkLogsTxt.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(64)))));
            this.networkLogsTxt.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.networkLogsTxt.ForeColor = System.Drawing.Color.Lime;
            this.networkLogsTxt.Location = new System.Drawing.Point(12, 12);
            this.networkLogsTxt.Name = "networkLogsTxt";
            this.networkLogsTxt.ReadOnly = true;
            this.networkLogsTxt.Size = new System.Drawing.Size(226, 434);
            this.networkLogsTxt.TabIndex = 0;
            this.networkLogsTxt.Text = "";
            // 
            // loggerTxt
            // 
            this.loggerTxt.AutoWordSelection = true;
            this.loggerTxt.BackColor = System.Drawing.SystemColors.Desktop;
            this.loggerTxt.ForeColor = System.Drawing.SystemColors.Window;
            this.loggerTxt.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.loggerTxt.Location = new System.Drawing.Point(244, 12);
            this.loggerTxt.Name = "loggerTxt";
            this.loggerTxt.ReadOnly = true;
            this.loggerTxt.Size = new System.Drawing.Size(531, 434);
            this.loggerTxt.TabIndex = 1;
            this.loggerTxt.Text = "";
            // 
            // exportBtn
            // 
            this.exportBtn.Location = new System.Drawing.Point(619, 452);
            this.exportBtn.Name = "exportBtn";
            this.exportBtn.Size = new System.Drawing.Size(75, 23);
            this.exportBtn.TabIndex = 2;
            this.exportBtn.Text = "Export";
            this.exportBtn.UseVisualStyleBackColor = true;
            this.exportBtn.Click += new System.EventHandler(this.exportBtn_Click);
            // 
            // clearLogsBtn
            // 
            this.clearLogsBtn.Location = new System.Drawing.Point(163, 452);
            this.clearLogsBtn.Name = "clearLogsBtn";
            this.clearLogsBtn.Size = new System.Drawing.Size(75, 23);
            this.clearLogsBtn.TabIndex = 3;
            this.clearLogsBtn.Text = "Clear ";
            this.clearLogsBtn.UseVisualStyleBackColor = true;
            this.clearLogsBtn.Click += new System.EventHandler(this.clearLogsBtn_Click);
            // 
            // clearKeylogsBtn
            // 
            this.clearKeylogsBtn.Location = new System.Drawing.Point(700, 452);
            this.clearKeylogsBtn.Name = "clearKeylogsBtn";
            this.clearKeylogsBtn.Size = new System.Drawing.Size(75, 23);
            this.clearKeylogsBtn.TabIndex = 4;
            this.clearKeylogsBtn.Text = "Clear";
            this.clearKeylogsBtn.UseVisualStyleBackColor = true;
            this.clearKeylogsBtn.Click += new System.EventHandler(this.clearKeylogsBtn_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(785, 483);
            this.Controls.Add(this.clearKeylogsBtn);
            this.Controls.Add(this.clearLogsBtn);
            this.Controls.Add(this.exportBtn);
            this.Controls.Add(this.loggerTxt);
            this.Controls.Add(this.networkLogsTxt);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimizeBox = false;
            this.Name = "mainForm";
            this.Text = "Server";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.mainForm_FormClosed);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox networkLogsTxt;
        private System.Windows.Forms.RichTextBox loggerTxt;
        private System.Windows.Forms.Button exportBtn;
        private System.Windows.Forms.Button clearLogsBtn;
        private System.Windows.Forms.Button clearKeylogsBtn;
    }
}

