#pragma once
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")

#include "OpenGL.h"
#include "ArcBallNEHE.h"

namespace EllipseCfdMesh {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace ExtraLib;
	using namespace OpenGLForm;


	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			OpenGL1 = gcnew COpenGL(this->OpenGLpanel1, this->OpenGLpanel1->Width, this->OpenGLpanel1->Height);

			height = this->OpenGLpanel1->Height;
			width = this->OpenGLpanel1->Width;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			delete(OpenGL1);
			if (components)
			{
				delete components;
			}
		}
		void InitVars(void)
		{
			matrixLock = gcnew System::Object();
			arcBall = gcnew arcball(640.0f, 480.0f);
			matrix = gcnew array<float>(16);

			LastTransformation = gcnew Matrix4f();
			ThisTransformation = gcnew Matrix4f();
			N = Convert::ToInt32(this->IBCMesh->Text);
			if (Math::IEEERemainder(N, 4) != 0)
				N = N - int(Math::IEEERemainder(N, 4));
			this->IBCMesh->Text = Convert::ToString(N);
			Nf = Convert::ToInt32(this->NFar->Text);
			ibcx = gcnew array<double>(N);
			ibcy = gcnew array<double>(N);
			obcx = gcnew array<double>(N);
			obcy = gcnew array<double>(N);
			obcx_2 = gcnew array<double>(N);
			ibcx_2 = gcnew array<double>(N);
			ibcy_2 = gcnew array<double>(N);
			obcy_2 = gcnew array<double>(N);
			x = gcnew array<double, 2>(Nf, N);
			y = gcnew array<double, 2>(Nf, N);
			//dummyx = gcnew array<double,2>(Nf,N);
			//dummyy = gcnew array<double,2>(Nf,N);
			STP = gcnew array<double>(N);
			ARi = gcnew array<double, 2>(Nf, N);
			SARi = gcnew array<double, 2>(Nf, N);
			rhoi = gcnew array<double, 2>(Nf, N);
			ColLevel = 1000;
			red = gcnew array<float>(ColLevel);
			green = gcnew array<float>(ColLevel);
			blue = gcnew array<float>(ColLevel);
			this->makeColorGradient(2.0*Math::PI / ColLevel, 2.0*Math::PI / ColLevel, 2.0*Math::PI / ColLevel, 4.0*Math::PI / 3.0, 0.0, 2.0*Math::PI / 3, 0.5, 0.5, ColLevel);
		}

	public:
		COpenGL ^OpenGL1;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;


		System::Object ^matrixLock;
		array<float>^ matrix;
		array<double>^ ibcx;
		array<double>^ ibcy;
		array<double>^ obcx;
		array<double>^ obcy;
		array<double>^ obcx_2;
		array<double>^ obcy_2;
		array<double>^ ibcx_2;
		array<double>^ ibcy_2;
		array<double, 2>^ x;
		array<double, 2>^ y;
		array<double, 2>^ dummyx;
		array<double, 2>^ dummyy;
		array<double, 2>^ ARi;
		array<double, 2>^ SARi;
		array<double, 2>^ rhoi;
		Matrix4f ^LastTransformation;
		Matrix4f ^ThisTransformation;
		int plot_glList1, plot_glList2; // display list
		Int32 N, Nf;
		int width, height;
		array<float>^ red;
		array<float>^ green;
		array<float>^ blue;
		array<double>^ STP;

		double minAR;
		double maxAR;
		double minSAR;
		double maxSAR;
		double minr;
		double maxr;
		double d;
		int ColLevel;

		arcball ^arcBall;
		Point ^mouseStartDrag;
		static bool isLeftDrag = false;
		static bool isRightDrag = false;
		static bool isMiddleDrag = false;

		// lighting
		static array<float>^ LightAmbient = { 0.5f, 0.5f, 0.5f, 1.0f };
		static array<float>^ LightDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		static array<float>^ LightPosition = { 100.0f, 100.0f, 100.0f, 0.0f };
		static array<float>^ LightSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };

		static array<float>^ MaterialSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  MeshAll;


	private: System::Windows::Forms::TextBox^  ST_2;
	private: System::Windows::Forms::TextBox^  ST1;
	private: System::Windows::Forms::Label^  St2;
	private: System::Windows::Forms::Label^  ST;
	private: System::Windows::Forms::Label^  AllenScalinglabel;
	private: System::Windows::Forms::TextBox^  iters;
	private: System::Windows::Forms::Label^  Iter;
	private: System::Windows::Forms::Label^  SI_ch;
	private: System::Windows::Forms::TextBox^  S3;
	private: System::Windows::Forms::RadioButton^  Interpolate;
	private: System::Windows::Forms::RadioButton^  Scale;
	private: System::Windows::Forms::Label^  choice3;
	private: System::Windows::Forms::TextBox^  a;
	private: System::Windows::Forms::Label^  alpha;
	private: System::Windows::Forms::TextBox^  Q;
	private: System::Windows::Forms::TextBox^  P;
	private: System::Windows::Forms::Label^  RES_Q;
	private: System::Windows::Forms::Label^  RES_P;
	private: System::Windows::Forms::Label^  StretchLabel1_1;
	private: System::Windows::Forms::Label^  StretchLabel1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  RecH;
	private: System::Windows::Forms::TextBox^  RecW;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  MeshType;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  RotAng;
	private: System::Windows::Forms::TextBox^  MinAx;
	private: System::Windows::Forms::TextBox^  NFar;
	private: System::Windows::Forms::Label^  NFar_label;
	private: System::Windows::Forms::TextBox^  IBCMesh;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::CheckBox^  AppSmooth;
	private: System::Windows::Forms::Label^  ArThres;
	private: System::Windows::Forms::TextBox^  ARThreshold;

	private: System::Windows::Forms::Label^  Siter;
	private: System::Windows::Forms::TextBox^  SIters;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton4;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  S4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::RadioButton^  ProgGenOut;
	private: System::Windows::Forms::TextBox^  AL;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  D;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::RadioButton^  GenN;
	private: System::Windows::Forms::RadioButton^  EllN;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::SaveFileDialog^  saveImageDialog2;
	private: System::Windows::Forms::Panel^  OpenGLpanel1;
	private: System::Windows::Forms::TextBox^  CH;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::CheckBox^  CHcheck;
	private: System::Windows::Forms::Label^  label15;

	private: System::Windows::Forms::CheckBox^  Clustercheck;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  Mode;




	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::RadioButton^  radioButton7;
	private: System::Windows::Forms::Label^  label16;






			 static array<float>^ SurfaceShininess = { 96.0f };

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->MeshAll = (gcnew System::Windows::Forms::Button());
				 this->ST_2 = (gcnew System::Windows::Forms::TextBox());
				 this->ST1 = (gcnew System::Windows::Forms::TextBox());
				 this->St2 = (gcnew System::Windows::Forms::Label());
				 this->ST = (gcnew System::Windows::Forms::Label());
				 this->AllenScalinglabel = (gcnew System::Windows::Forms::Label());
				 this->iters = (gcnew System::Windows::Forms::TextBox());
				 this->Iter = (gcnew System::Windows::Forms::Label());
				 this->SI_ch = (gcnew System::Windows::Forms::Label());
				 this->S3 = (gcnew System::Windows::Forms::TextBox());
				 this->Interpolate = (gcnew System::Windows::Forms::RadioButton());
				 this->Scale = (gcnew System::Windows::Forms::RadioButton());
				 this->choice3 = (gcnew System::Windows::Forms::Label());
				 this->a = (gcnew System::Windows::Forms::TextBox());
				 this->alpha = (gcnew System::Windows::Forms::Label());
				 this->Q = (gcnew System::Windows::Forms::TextBox());
				 this->P = (gcnew System::Windows::Forms::TextBox());
				 this->RES_Q = (gcnew System::Windows::Forms::Label());
				 this->RES_P = (gcnew System::Windows::Forms::Label());
				 this->StretchLabel1_1 = (gcnew System::Windows::Forms::Label());
				 this->StretchLabel1 = (gcnew System::Windows::Forms::Label());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->RecH = (gcnew System::Windows::Forms::TextBox());
				 this->RecW = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->MeshType = (gcnew System::Windows::Forms::ComboBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->RotAng = (gcnew System::Windows::Forms::TextBox());
				 this->MinAx = (gcnew System::Windows::Forms::TextBox());
				 this->NFar = (gcnew System::Windows::Forms::TextBox());
				 this->NFar_label = (gcnew System::Windows::Forms::Label());
				 this->IBCMesh = (gcnew System::Windows::Forms::TextBox());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->AppSmooth = (gcnew System::Windows::Forms::CheckBox());
				 this->ArThres = (gcnew System::Windows::Forms::Label());
				 this->ARThreshold = (gcnew System::Windows::Forms::TextBox());
				 this->Siter = (gcnew System::Windows::Forms::Label());
				 this->SIters = (gcnew System::Windows::Forms::TextBox());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->button3 = (gcnew System::Windows::Forms::Button());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->S4 = (gcnew System::Windows::Forms::TextBox());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->ProgGenOut = (gcnew System::Windows::Forms::RadioButton());
				 this->AL = (gcnew System::Windows::Forms::TextBox());
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->D = (gcnew System::Windows::Forms::TextBox());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->EllN = (gcnew System::Windows::Forms::RadioButton());
				 this->GenN = (gcnew System::Windows::Forms::RadioButton());
				 this->button4 = (gcnew System::Windows::Forms::Button());
				 this->button5 = (gcnew System::Windows::Forms::Button());
				 this->saveImageDialog2 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->OpenGLpanel1 = (gcnew System::Windows::Forms::Panel());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->CH = (gcnew System::Windows::Forms::TextBox());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->label14 = (gcnew System::Windows::Forms::Label());
				 this->CHcheck = (gcnew System::Windows::Forms::CheckBox());
				 this->Clustercheck = (gcnew System::Windows::Forms::CheckBox());
				 this->label17 = (gcnew System::Windows::Forms::Label());
				 this->Mode = (gcnew System::Windows::Forms::TextBox());
				 this->label19 = (gcnew System::Windows::Forms::Label());
				 this->label18 = (gcnew System::Windows::Forms::Label());
				 this->label20 = (gcnew System::Windows::Forms::Label());
				 this->label21 = (gcnew System::Windows::Forms::Label());
				 this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
				 this->label16 = (gcnew System::Windows::Forms::Label());
				 this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
				 this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
				 this->groupBox1->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 this->groupBox3->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(354, 658);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(109, 25);
				 this->button1->TabIndex = 2;
				 this->button1->Text = L"Reset Camera";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
				 // 
				 // MeshAll
				 // 
				 this->MeshAll->Location = System::Drawing::Point(12, 618);
				 this->MeshAll->Name = L"MeshAll";
				 this->MeshAll->Size = System::Drawing::Size(109, 25);
				 this->MeshAll->TabIndex = 15;
				 this->MeshAll->Text = L"Mesh";
				 this->MeshAll->UseVisualStyleBackColor = true;
				 this->MeshAll->Visible = false;
				 this->MeshAll->Click += gcnew System::EventHandler(this, &Form1::MeshAll_Click);
				 // 
				 // ST_2
				 // 
				 this->ST_2->Location = System::Drawing::Point(306, 201);
				 this->ST_2->Name = L"ST_2";
				 this->ST_2->Size = System::Drawing::Size(47, 22);
				 this->ST_2->TabIndex = 108;
				 this->ST_2->Text = L"0.33";
				 this->ST_2->Visible = false;
				 // 
				 // ST1
				 // 
				 this->ST1->Location = System::Drawing::Point(204, 201);
				 this->ST1->Name = L"ST1";
				 this->ST1->Size = System::Drawing::Size(47, 22);
				 this->ST1->TabIndex = 106;
				 this->ST1->Text = L"3.0";
				 this->ST1->Visible = false;
				 // 
				 // St2
				 // 
				 this->St2->AutoSize = true;
				 this->St2->Location = System::Drawing::Point(267, 204);
				 this->St2->Name = L"St2";
				 this->St2->Size = System::Drawing::Size(33, 17);
				 this->St2->TabIndex = 107;
				 this->St2->Text = L"St2:";
				 this->St2->Visible = false;
				 // 
				 // ST
				 // 
				 this->ST->AutoSize = true;
				 this->ST->Location = System::Drawing::Point(173, 204);
				 this->ST->Name = L"ST";
				 this->ST->Size = System::Drawing::Size(25, 17);
				 this->ST->TabIndex = 105;
				 this->ST->Text = L"St:";
				 this->ST->Visible = false;
				 // 
				 // AllenScalinglabel
				 // 
				 this->AllenScalinglabel->AutoSize = true;
				 this->AllenScalinglabel->Location = System::Drawing::Point(45, 204);
				 this->AllenScalinglabel->Name = L"AllenScalinglabel";
				 this->AllenScalinglabel->Size = System::Drawing::Size(106, 17);
				 this->AllenScalinglabel->TabIndex = 104;
				 this->AllenScalinglabel->Text = L"Scaling Params";
				 this->AllenScalinglabel->Visible = false;
				 // 
				 // iters
				 // 
				 this->iters->Location = System::Drawing::Point(157, 201);
				 this->iters->Name = L"iters";
				 this->iters->Size = System::Drawing::Size(47, 22);
				 this->iters->TabIndex = 103;
				 this->iters->Text = L"1000";
				 this->iters->Visible = false;
				 // 
				 // Iter
				 // 
				 this->Iter->AutoSize = true;
				 this->Iter->Location = System::Drawing::Point(85, 204);
				 this->Iter->Name = L"Iter";
				 this->Iter->Size = System::Drawing::Size(66, 17);
				 this->Iter->TabIndex = 102;
				 this->Iter->Text = L"Iterations";
				 this->Iter->Visible = false;
				 // 
				 // SI_ch
				 // 
				 this->SI_ch->AutoSize = true;
				 this->SI_ch->Location = System::Drawing::Point(415, 251);
				 this->SI_ch->Name = L"SI_ch";
				 this->SI_ch->Size = System::Drawing::Size(0, 17);
				 this->SI_ch->TabIndex = 101;
				 // 
				 // S3
				 // 
				 this->S3->Location = System::Drawing::Point(362, 248);
				 this->S3->Name = L"S3";
				 this->S3->Size = System::Drawing::Size(47, 22);
				 this->S3->TabIndex = 100;
				 this->S3->Text = L"1.0";
				 this->S3->Visible = false;
				 this->S3->TextChanged += gcnew System::EventHandler(this, &Form1::S3_TextChanged);
				 // 
				 // Interpolate
				 // 
				 this->Interpolate->AutoSize = true;
				 this->Interpolate->Location = System::Drawing::Point(28, 278);
				 this->Interpolate->Name = L"Interpolate";
				 this->Interpolate->Size = System::Drawing::Size(141, 21);
				 this->Interpolate->TabIndex = 99;
				 this->Interpolate->Text = L"Interpolate Ellipse";
				 this->Interpolate->UseVisualStyleBackColor = true;
				 this->Interpolate->Visible = false;
				 this->Interpolate->CheckedChanged += gcnew System::EventHandler(this, &Form1::Interpolate_CheckedChanged_1);
				 // 
				 // Scale
				 // 
				 this->Scale->AutoSize = true;
				 this->Scale->Checked = true;
				 this->Scale->Location = System::Drawing::Point(28, 251);
				 this->Scale->Name = L"Scale";
				 this->Scale->Size = System::Drawing::Size(109, 21);
				 this->Scale->TabIndex = 98;
				 this->Scale->TabStop = true;
				 this->Scale->Text = L"Scale Ellipse";
				 this->Scale->UseVisualStyleBackColor = true;
				 this->Scale->Visible = false;
				 this->Scale->CheckedChanged += gcnew System::EventHandler(this, &Form1::Scale_CheckedChanged);
				 // 
				 // choice3
				 // 
				 this->choice3->AutoSize = true;
				 this->choice3->Location = System::Drawing::Point(180, 251);
				 this->choice3->Name = L"choice3";
				 this->choice3->Size = System::Drawing::Size(176, 17);
				 this->choice3->TabIndex = 97;
				 this->choice3->Text = L"Value (for Inner Boundary)";
				 this->choice3->Visible = false;
				 this->choice3->Click += gcnew System::EventHandler(this, &Form1::choice3_Click);
				 // 
				 // a
				 // 
				 this->a->Location = System::Drawing::Point(143, 201);
				 this->a->Name = L"a";
				 this->a->Size = System::Drawing::Size(45, 22);
				 this->a->TabIndex = 96;
				 this->a->Text = L"0.3";
				 this->a->Visible = false;
				 // 
				 // alpha
				 // 
				 this->alpha->AutoSize = true;
				 this->alpha->Location = System::Drawing::Point(85, 204);
				 this->alpha->Name = L"alpha";
				 this->alpha->Size = System::Drawing::Size(44, 17);
				 this->alpha->TabIndex = 95;
				 this->alpha->Text = L"Alpha";
				 this->alpha->Visible = false;
				 // 
				 // Q
				 // 
				 this->Q->Location = System::Drawing::Point(287, 201);
				 this->Q->Name = L"Q";
				 this->Q->Size = System::Drawing::Size(47, 22);
				 this->Q->TabIndex = 94;
				 this->Q->Text = L"2.0";
				 this->Q->Visible = false;
				 // 
				 // P
				 // 
				 this->P->Location = System::Drawing::Point(194, 201);
				 this->P->Name = L"P";
				 this->P->Size = System::Drawing::Size(47, 22);
				 this->P->TabIndex = 93;
				 this->P->Text = L"1.8";
				 this->P->Visible = false;
				 // 
				 // RES_Q
				 // 
				 this->RES_Q->AutoSize = true;
				 this->RES_Q->Location = System::Drawing::Point(258, 204);
				 this->RES_Q->Name = L"RES_Q";
				 this->RES_Q->Size = System::Drawing::Size(23, 17);
				 this->RES_Q->TabIndex = 92;
				 this->RES_Q->Text = L"Q:";
				 this->RES_Q->Visible = false;
				 // 
				 // RES_P
				 // 
				 this->RES_P->AutoSize = true;
				 this->RES_P->Location = System::Drawing::Point(167, 204);
				 this->RES_P->Name = L"RES_P";
				 this->RES_P->Size = System::Drawing::Size(21, 17);
				 this->RES_P->TabIndex = 91;
				 this->RES_P->Text = L"P:";
				 this->RES_P->Visible = false;
				 // 
				 // StretchLabel1_1
				 // 
				 this->StretchLabel1_1->AutoSize = true;
				 this->StretchLabel1_1->Location = System::Drawing::Point(20, 221);
				 this->StretchLabel1_1->Name = L"StretchLabel1_1";
				 this->StretchLabel1_1->Size = System::Drawing::Size(124, 17);
				 this->StretchLabel1_1->TabIndex = 90;
				 this->StretchLabel1_1->Text = L"Stretching Params";
				 this->StretchLabel1_1->Visible = false;
				 // 
				 // StretchLabel1
				 // 
				 this->StretchLabel1->AutoSize = true;
				 this->StretchLabel1->Location = System::Drawing::Point(20, 204);
				 this->StretchLabel1->Name = L"StretchLabel1";
				 this->StretchLabel1->Size = System::Drawing::Size(117, 17);
				 this->StretchLabel1->TabIndex = 89;
				 this->StretchLabel1->Text = L"Roberts-Eiseman";
				 this->StretchLabel1->Visible = false;
				 // 
				 // label8
				 // 
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(256, 93);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(53, 17);
				 this->label8->TabIndex = 88;
				 this->label8->Text = L"Hieght:";
				 // 
				 // label7
				 // 
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(140, 93);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(48, 17);
				 this->label7->TabIndex = 87;
				 this->label7->Text = L"Width:";
				 // 
				 // RecH
				 // 
				 this->RecH->Location = System::Drawing::Point(323, 90);
				 this->RecH->Name = L"RecH";
				 this->RecH->Size = System::Drawing::Size(56, 22);
				 this->RecH->TabIndex = 86;
				 this->RecH->Text = L"10";
				 // 
				 // RecW
				 // 
				 this->RecW->Location = System::Drawing::Point(194, 90);
				 this->RecW->Name = L"RecW";
				 this->RecW->Size = System::Drawing::Size(56, 22);
				 this->RecW->TabIndex = 85;
				 this->RecW->Text = L"10";
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(20, 93);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(109, 17);
				 this->label4->TabIndex = 84;
				 this->label4->Text = L"Outer Boundary";
				 // 
				 // MeshType
				 // 
				 this->MeshType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->MeshType->FormattingEnabled = true;
				 this->MeshType->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
					 L"Multi-Surface (2)", L"Multi-Surface (3)", L"Multi-Surface (4)",
						 L"Allen\'s TFI (1) (recommended)", L"Allen\'s TFI (2)", L"Elliptic PDE\'s"
				 });
				 this->MeshType->Location = System::Drawing::Point(140, 163);
				 this->MeshType->Name = L"MeshType";
				 this->MeshType->Size = System::Drawing::Size(208, 24);
				 this->MeshType->TabIndex = 83;
				 this->MeshType->SelectedValueChanged += gcnew System::EventHandler(this, &Form1::MeshType_SelectedValueChanged);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(18, 166);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(116, 17);
				 this->label1->TabIndex = 82;
				 this->label1->Text = L"Meshing Scheme";
				 // 
				 // RotAng
				 // 
				 this->RotAng->Location = System::Drawing::Point(356, 9);
				 this->RotAng->Name = L"RotAng";
				 this->RotAng->Size = System::Drawing::Size(53, 22);
				 this->RotAng->TabIndex = 81;
				 this->RotAng->Text = L"0";
				 // 
				 // MinAx
				 // 
				 this->MinAx->Location = System::Drawing::Point(143, 9);
				 this->MinAx->Name = L"MinAx";
				 this->MinAx->Size = System::Drawing::Size(53, 22);
				 this->MinAx->TabIndex = 80;
				 this->MinAx->Text = L"0.5";
				 // 
				 // NFar
				 // 
				 this->NFar->Location = System::Drawing::Point(247, 42);
				 this->NFar->Name = L"NFar";
				 this->NFar->Size = System::Drawing::Size(53, 22);
				 this->NFar->TabIndex = 79;
				 this->NFar->Text = L"100";
				 // 
				 // NFar_label
				 // 
				 this->NFar_label->AutoSize = true;
				 this->NFar_label->Location = System::Drawing::Point(202, 45);
				 this->NFar_label->Name = L"NFar_label";
				 this->NFar_label->Size = System::Drawing::Size(39, 17);
				 this->NFar_label->TabIndex = 78;
				 this->NFar_label->Text = L"NFar";
				 // 
				 // IBCMesh
				 // 
				 this->IBCMesh->Location = System::Drawing::Point(140, 42);
				 this->IBCMesh->Name = L"IBCMesh";
				 this->IBCMesh->Size = System::Drawing::Size(56, 22);
				 this->IBCMesh->TabIndex = 77;
				 this->IBCMesh->Text = L"300";
				 // 
				 // label6
				 // 
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(20, 62);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(73, 17);
				 this->label6->TabIndex = 76;
				 this->label6->Text = L"Mesh Size";
				 // 
				 // label5
				 // 
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(20, 45);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(114, 17);
				 this->label5->TabIndex = 75;
				 this->label5->Text = L"Ellipse Boundary";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(202, 12);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(146, 17);
				 this->label3->TabIndex = 74;
				 this->label3->Text = L"Ellipse Rotation Angle";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(20, 12);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(117, 17);
				 this->label2->TabIndex = 73;
				 this->label2->Text = L"Ellipse Minor Axis";
				 // 
				 // AppSmooth
				 // 
				 this->AppSmooth->AutoSize = true;
				 this->AppSmooth->Location = System::Drawing::Point(23, 396);
				 this->AppSmooth->Name = L"AppSmooth";
				 this->AppSmooth->Size = System::Drawing::Size(136, 21);
				 this->AppSmooth->TabIndex = 109;
				 this->AppSmooth->Text = L"Apply Smoothing";
				 this->AppSmooth->UseVisualStyleBackColor = true;
				 this->AppSmooth->CheckedChanged += gcnew System::EventHandler(this, &Form1::AppSmooth_CheckedChanged);
				 // 
				 // ArThres
				 // 
				 this->ArThres->AutoSize = true;
				 this->ArThres->Location = System::Drawing::Point(138, 18);
				 this->ArThres->Name = L"ArThres";
				 this->ArThres->Size = System::Drawing::Size(156, 17);
				 this->ArThres->TabIndex = 110;
				 this->ArThres->Text = L"Aspect Ratio Threshold";
				 this->ArThres->Visible = false;
				 // 
				 // ARThreshold
				 // 
				 this->ARThreshold->Location = System::Drawing::Point(300, 15);
				 this->ARThreshold->Name = L"ARThreshold";
				 this->ARThreshold->Size = System::Drawing::Size(47, 22);
				 this->ARThreshold->TabIndex = 111;
				 this->ARThreshold->Text = L"0.1";
				 this->ARThreshold->Visible = false;
				 // 
				 // Siter
				 // 
				 this->Siter->AutoSize = true;
				 this->Siter->Location = System::Drawing::Point(138, 46);
				 this->Siter->Name = L"Siter";
				 this->Siter->Size = System::Drawing::Size(137, 17);
				 this->Siter->TabIndex = 113;
				 this->Siter->Text = L"Smoothing Iterations";
				 this->Siter->Visible = false;
				 // 
				 // SIters
				 // 
				 this->SIters->Location = System::Drawing::Point(300, 43);
				 this->SIters->Name = L"SIters";
				 this->SIters->Size = System::Drawing::Size(47, 22);
				 this->SIters->TabIndex = 114;
				 this->SIters->Text = L"50";
				 this->SIters->Visible = false;
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(183, 618);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(109, 25);
				 this->button2->TabIndex = 116;
				 this->button2->Text = L"Export Results";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Visible = false;
				 this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
				 // 
				 // saveFileDialog1
				 // 
				 this->saveFileDialog1->DefaultExt = L"plt";
				 this->saveFileDialog1->FileName = L"rs0096_mesh.plt";
				 this->saveFileDialog1->Filter = L"Tecplot (*.plt)|*.plt";
				 this->saveFileDialog1->Title = L"Save Mesh As";
				 this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
				 // 
				 // button3
				 // 
				 this->button3->Location = System::Drawing::Point(12, 658);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(109, 25);
				 this->button3->TabIndex = 117;
				 this->button3->Text = L"Instructions";
				 this->button3->UseVisualStyleBackColor = true;
				 this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->radioButton4);
				 this->groupBox1->Controls->Add(this->radioButton3);
				 this->groupBox1->Controls->Add(this->radioButton2);
				 this->groupBox1->Controls->Add(this->radioButton1);
				 this->groupBox1->Location = System::Drawing::Point(23, 535);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(392, 65);
				 this->groupBox1->TabIndex = 119;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Mesh Quality Plots";
				 // 
				 // radioButton4
				 // 
				 this->radioButton4->AutoSize = true;
				 this->radioButton4->Location = System::Drawing::Point(116, 38);
				 this->radioButton4->Name = L"radioButton4";
				 this->radioButton4->Size = System::Drawing::Size(55, 21);
				 this->radioButton4->TabIndex = 3;
				 this->radioButton4->Text = L"Rho";
				 this->radioButton4->UseVisualStyleBackColor = true;
				 // 
				 // radioButton3
				 // 
				 this->radioButton3->AutoSize = true;
				 this->radioButton3->Location = System::Drawing::Point(327, 38);
				 this->radioButton3->Name = L"radioButton3";
				 this->radioButton3->Size = System::Drawing::Size(57, 21);
				 this->radioButton3->TabIndex = 2;
				 this->radioButton3->Text = L"SAR";
				 this->radioButton3->UseVisualStyleBackColor = true;
				 this->radioButton3->Visible = false;
				 // 
				 // radioButton2
				 // 
				 this->radioButton2->AutoSize = true;
				 this->radioButton2->Location = System::Drawing::Point(225, 38);
				 this->radioButton2->Name = L"radioButton2";
				 this->radioButton2->Size = System::Drawing::Size(48, 21);
				 this->radioButton2->TabIndex = 1;
				 this->radioButton2->Text = L"AR";
				 this->radioButton2->UseVisualStyleBackColor = true;
				 this->radioButton2->Visible = false;
				 this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton2_CheckedChanged);
				 // 
				 // radioButton1
				 // 
				 this->radioButton1->AutoSize = true;
				 this->radioButton1->Checked = true;
				 this->radioButton1->Location = System::Drawing::Point(6, 38);
				 this->radioButton1->Name = L"radioButton1";
				 this->radioButton1->Size = System::Drawing::Size(56, 21);
				 this->radioButton1->TabIndex = 0;
				 this->radioButton1->TabStop = true;
				 this->radioButton1->Text = L"Grid";
				 this->radioButton1->UseVisualStyleBackColor = true;
				 // 
				 // label10
				 // 
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(415, 278);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(0, 17);
				 this->label10->TabIndex = 123;
				 this->label10->Visible = false;
				 // 
				 // S4
				 // 
				 this->S4->Location = System::Drawing::Point(362, 275);
				 this->S4->Name = L"S4";
				 this->S4->Size = System::Drawing::Size(47, 22);
				 this->S4->TabIndex = 122;
				 this->S4->Text = L"1.0";
				 this->S4->Visible = false;
				 // 
				 // label11
				 // 
				 this->label11->AutoSize = true;
				 this->label11->Location = System::Drawing::Point(180, 278);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(180, 17);
				 this->label11->TabIndex = 121;
				 this->label11->Text = L"Value (for Outer Boundary)";
				 this->label11->Visible = false;
				 // 
				 // ProgGenOut
				 // 
				 this->ProgGenOut->AutoSize = true;
				 this->ProgGenOut->Location = System::Drawing::Point(28, 305);
				 this->ProgGenOut->Name = L"ProgGenOut";
				 this->ProgGenOut->Size = System::Drawing::Size(155, 21);
				 this->ProgGenOut->TabIndex = 124;
				 this->ProgGenOut->Text = L"Program Generated";
				 this->ProgGenOut->UseVisualStyleBackColor = true;
				 this->ProgGenOut->Visible = false;
				 this->ProgGenOut->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton5_CheckedChanged);
				 // 
				 // AL
				 // 
				 this->AL->Location = System::Drawing::Point(362, 303);
				 this->AL->Name = L"AL";
				 this->AL->Size = System::Drawing::Size(47, 22);
				 this->AL->TabIndex = 125;
				 this->AL->Text = L"0.55";
				 this->AL->Visible = false;
				 // 
				 // label12
				 // 
				 this->label12->AutoSize = true;
				 this->label12->Location = System::Drawing::Point(259, 306);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(96, 17);
				 this->label12->TabIndex = 126;
				 this->label12->Text = L"Parameter Aw";
				 this->label12->Visible = false;
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->Location = System::Drawing::Point(204, 21);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(123, 17);
				 this->label13->TabIndex = 127;
				 this->label13->Text = L"Normal Parameter";
				 this->label13->Visible = false;
				 // 
				 // D
				 // 
				 this->D->Location = System::Drawing::Point(333, 18);
				 this->D->Name = L"D";
				 this->D->Size = System::Drawing::Size(47, 22);
				 this->D->TabIndex = 128;
				 this->D->Text = L"1";
				 this->D->Visible = false;
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->EllN);
				 this->groupBox2->Controls->Add(this->GenN);
				 this->groupBox2->Controls->Add(this->D);
				 this->groupBox2->Controls->Add(this->label13);
				 this->groupBox2->Location = System::Drawing::Point(29, 332);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(394, 46);
				 this->groupBox2->TabIndex = 129;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Normal Type";
				 this->groupBox2->Visible = false;
				 // 
				 // EllN
				 // 
				 this->EllN->AutoSize = true;
				 this->EllN->Checked = true;
				 this->EllN->Location = System::Drawing::Point(95, 19);
				 this->EllN->Name = L"EllN";
				 this->EllN->Size = System::Drawing::Size(78, 21);
				 this->EllN->TabIndex = 130;
				 this->EllN->TabStop = true;
				 this->EllN->Text = L"Analytic";
				 this->EllN->UseVisualStyleBackColor = true;
				 // 
				 // GenN
				 // 
				 this->GenN->AutoSize = true;
				 this->GenN->Location = System::Drawing::Point(6, 19);
				 this->GenN->Name = L"GenN";
				 this->GenN->Size = System::Drawing::Size(81, 21);
				 this->GenN->TabIndex = 129;
				 this->GenN->Text = L"Numeric";
				 this->GenN->UseVisualStyleBackColor = true;
				 // 
				 // button4
				 // 
				 this->button4->Location = System::Drawing::Point(183, 658);
				 this->button4->Name = L"button4";
				 this->button4->Size = System::Drawing::Size(109, 25);
				 this->button4->TabIndex = 130;
				 this->button4->Text = L"Close";
				 this->button4->UseVisualStyleBackColor = true;
				 this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
				 // 
				 // button5
				 // 
				 this->button5->Location = System::Drawing::Point(354, 618);
				 this->button5->Name = L"button5";
				 this->button5->Size = System::Drawing::Size(109, 25);
				 this->button5->TabIndex = 131;
				 this->button5->Text = L"Save Image";
				 this->button5->UseVisualStyleBackColor = true;
				 this->button5->Visible = false;
				 this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
				 // 
				 // saveImageDialog2
				 // 
				 this->saveImageDialog2->FileName = L"rs0096_image01";
				 this->saveImageDialog2->Filter = L"BMP (*.bmp)|*.bmp|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif";
				 this->saveImageDialog2->Title = L"Save Image As";
				 this->saveImageDialog2->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveImageDialog2_FileOk);
				 // 
				 // OpenGLpanel1
				 // 
				 this->OpenGLpanel1->Location = System::Drawing::Point(490, 12);
				 this->OpenGLpanel1->Name = L"OpenGLpanel1";
				 this->OpenGLpanel1->Size = System::Drawing::Size(650, 650);
				 this->OpenGLpanel1->TabIndex = 132;
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->Location = System::Drawing::Point(487, 665);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(230, 17);
				 this->label15->TabIndex = 137;
				 this->label15->Text = L"Min Cell Hieght at Inner boundary : ";
				 // 
				 // CH
				 // 
				 this->CH->Location = System::Drawing::Point(356, 42);
				 this->CH->Name = L"CH";
				 this->CH->Size = System::Drawing::Size(53, 22);
				 this->CH->TabIndex = 133;
				 this->CH->Text = L"0.0001";
				 // 
				 // label9
				 // 
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(312, 45);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(31, 17);
				 this->label9->TabIndex = 134;
				 this->label9->Text = L"Cell";
				 // 
				 // label14
				 // 
				 this->label14->AutoSize = true;
				 this->label14->Location = System::Drawing::Point(312, 62);
				 this->label14->Name = L"label14";
				 this->label14->Size = System::Drawing::Size(49, 17);
				 this->label14->TabIndex = 135;
				 this->label14->Text = L"Height";
				 // 
				 // CHcheck
				 // 
				 this->CHcheck->AutoSize = true;
				 this->CHcheck->Checked = true;
				 this->CHcheck->CheckState = System::Windows::Forms::CheckState::Checked;
				 this->CHcheck->Location = System::Drawing::Point(415, 45);
				 this->CHcheck->Name = L"CHcheck";
				 this->CHcheck->Size = System::Drawing::Size(18, 17);
				 this->CHcheck->TabIndex = 136;
				 this->CHcheck->UseVisualStyleBackColor = true;
				 this->CHcheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::CHcheck_CheckedChanged);
				 // 
				 // Clustercheck
				 // 
				 this->Clustercheck->AutoSize = true;
				 this->Clustercheck->Location = System::Drawing::Point(23, 128);
				 this->Clustercheck->Name = L"Clustercheck";
				 this->Clustercheck->Size = System::Drawing::Size(93, 21);
				 this->Clustercheck->TabIndex = 137;
				 this->Clustercheck->Text = L"Clustering";
				 this->Clustercheck->UseVisualStyleBackColor = true;
				 this->Clustercheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::Clustercheck_CheckedChanged);
				 // 
				 // label17
				 // 
				 this->label17->AutoSize = true;
				 this->label17->Location = System::Drawing::Point(142, 129);
				 this->label17->Name = L"label17";
				 this->label17->Size = System::Drawing::Size(50, 17);
				 this->label17->TabIndex = 138;
				 this->label17->Text = L"Modes";
				 // 
				 // Mode
				 // 
				 this->Mode->Enabled = false;
				 this->Mode->Location = System::Drawing::Point(198, 126);
				 this->Mode->Name = L"Mode";
				 this->Mode->Size = System::Drawing::Size(53, 22);
				 this->Mode->TabIndex = 139;
				 this->Mode->Text = L"8";
				 // 
				 // label19
				 // 
				 this->label19->AutoSize = true;
				 this->label19->Location = System::Drawing::Point(259, 129);
				 this->label19->Name = L"label19";
				 this->label19->Size = System::Drawing::Size(89, 17);
				 this->label19->TabIndex = 143;
				 this->label19->Text = L"(Not Perfect)";
				 // 
				 // label18
				 // 
				 this->label18->AutoSize = true;
				 this->label18->Location = System::Drawing::Point(487, 682);
				 this->label18->Name = L"label18";
				 this->label18->Size = System::Drawing::Size(233, 17);
				 this->label18->TabIndex = 144;
				 this->label18->Text = L"Max Cell Hieght at Inner boundary : ";
				 // 
				 // label20
				 // 
				 this->label20->AutoSize = true;
				 this->label20->Location = System::Drawing::Point(1038, 682);
				 this->label20->Name = L"label20";
				 this->label20->Size = System::Drawing::Size(0, 17);
				 this->label20->TabIndex = 145;
				 // 
				 // label21
				 // 
				 this->label21->AutoSize = true;
				 this->label21->Location = System::Drawing::Point(986, 665);
				 this->label21->Name = L"label21";
				 this->label21->Size = System::Drawing::Size(106, 17);
				 this->label21->TabIndex = 146;
				 this->label21->Text = L"Total Iterations:";
				 // 
				 // groupBox3
				 // 
				 this->groupBox3->Controls->Add(this->label16);
				 this->groupBox3->Controls->Add(this->radioButton7);
				 this->groupBox3->Controls->Add(this->radioButton6);
				 this->groupBox3->Controls->Add(this->radioButton5);
				 this->groupBox3->Controls->Add(this->ArThres);
				 this->groupBox3->Controls->Add(this->ARThreshold);
				 this->groupBox3->Controls->Add(this->Siter);
				 this->groupBox3->Controls->Add(this->SIters);
				 this->groupBox3->Location = System::Drawing::Point(23, 423);
				 this->groupBox3->Name = L"groupBox3";
				 this->groupBox3->Size = System::Drawing::Size(392, 106);
				 this->groupBox3->TabIndex = 147;
				 this->groupBox3->TabStop = false;
				 this->groupBox3->Text = L"Smoothing";
				 this->groupBox3->Visible = false;
				 // 
				 // label16
				 // 
				 this->label16->AutoSize = true;
				 this->label16->Location = System::Drawing::Point(138, 77);
				 this->label16->Name = L"label16";
				 this->label16->Size = System::Drawing::Size(222, 17);
				 this->label16->TabIndex = 116;
				 this->label16->Text = L"Boundary Orthogonality not good.";
				 this->label16->Visible = false;
				 // 
				 // radioButton7
				 // 
				 this->radioButton7->AutoSize = true;
				 this->radioButton7->Location = System::Drawing::Point(6, 75);
				 this->radioButton7->Name = L"radioButton7";
				 this->radioButton7->Size = System::Drawing::Size(101, 21);
				 this->radioButton7->TabIndex = 115;
				 this->radioButton7->Text = L"8 Point Avg";
				 this->radioButton7->UseVisualStyleBackColor = true;
				 this->radioButton7->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton7_CheckedChanged);
				 // 
				 // radioButton6
				 // 
				 this->radioButton6->AutoSize = true;
				 this->radioButton6->Location = System::Drawing::Point(6, 48);
				 this->radioButton6->Name = L"radioButton6";
				 this->radioButton6->Size = System::Drawing::Size(101, 21);
				 this->radioButton6->TabIndex = 1;
				 this->radioButton6->Text = L"4 Point Avg";
				 this->radioButton6->UseVisualStyleBackColor = true;
				 this->radioButton6->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton6_CheckedChanged);
				 // 
				 // radioButton5
				 // 
				 this->radioButton5->AutoSize = true;
				 this->radioButton5->Checked = true;
				 this->radioButton5->Location = System::Drawing::Point(6, 21);
				 this->radioButton5->Name = L"radioButton5";
				 this->radioButton5->Size = System::Drawing::Size(92, 21);
				 this->radioButton5->TabIndex = 0;
				 this->radioButton5->TabStop = true;
				 this->radioButton5->Text = L"AR Based";
				 this->radioButton5->UseVisualStyleBackColor = true;
				 this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton5_CheckedChanged_1);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
				 this->ClientSize = System::Drawing::Size(1153, 704);
				 this->Controls->Add(this->groupBox3);
				 this->Controls->Add(this->label21);
				 this->Controls->Add(this->label20);
				 this->Controls->Add(this->label18);
				 this->Controls->Add(this->label19);
				 this->Controls->Add(this->label15);
				 this->Controls->Add(this->Mode);
				 this->Controls->Add(this->label17);
				 this->Controls->Add(this->Clustercheck);
				 this->Controls->Add(this->CHcheck);
				 this->Controls->Add(this->label9);
				 this->Controls->Add(this->label14);
				 this->Controls->Add(this->CH);
				 this->Controls->Add(this->OpenGLpanel1);
				 this->Controls->Add(this->button5);
				 this->Controls->Add(this->button4);
				 this->Controls->Add(this->groupBox2);
				 this->Controls->Add(this->label12);
				 this->Controls->Add(this->AL);
				 this->Controls->Add(this->ProgGenOut);
				 this->Controls->Add(this->label10);
				 this->Controls->Add(this->S4);
				 this->Controls->Add(this->label11);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->button3);
				 this->Controls->Add(this->button2);
				 this->Controls->Add(this->AppSmooth);
				 this->Controls->Add(this->SI_ch);
				 this->Controls->Add(this->S3);
				 this->Controls->Add(this->Interpolate);
				 this->Controls->Add(this->Scale);
				 this->Controls->Add(this->choice3);
				 this->Controls->Add(this->RES_Q);
				 this->Controls->Add(this->StretchLabel1_1);
				 this->Controls->Add(this->label8);
				 this->Controls->Add(this->label7);
				 this->Controls->Add(this->RecH);
				 this->Controls->Add(this->RecW);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->MeshType);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->RotAng);
				 this->Controls->Add(this->MinAx);
				 this->Controls->Add(this->NFar);
				 this->Controls->Add(this->NFar_label);
				 this->Controls->Add(this->IBCMesh);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->MeshAll);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->ST_2);
				 this->Controls->Add(this->St2);
				 this->Controls->Add(this->AllenScalinglabel);
				 this->Controls->Add(this->Iter);
				 this->Controls->Add(this->alpha);
				 this->Controls->Add(this->StretchLabel1);
				 this->Controls->Add(this->P);
				 this->Controls->Add(this->Q);
				 this->Controls->Add(this->ST1);
				 this->Controls->Add(this->a);
				 this->Controls->Add(this->RES_P);
				 this->Controls->Add(this->ST);
				 this->Controls->Add(this->iters);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
				 this->MaximizeBox = false;
				 this->Name = L"Form1";
				 this->Text = L"Grid Generation of Ellipse";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->SizeChanged += gcnew System::EventHandler(this, &Form1::Form1_SizeChanged);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->groupBox1->ResumeLayout(false);
				 this->groupBox1->PerformLayout();
				 this->groupBox2->ResumeLayout(false);
				 this->groupBox2->PerformLayout();
				 this->groupBox3->ResumeLayout(false);
				 this->groupBox3->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
			 void Ellipse()
			 {
				 double phi = Convert::ToDouble(this->RotAng->Text)*Math::PI / 180.0;
				 double phi2 = 0;
				 double centrex = 0;
				 double centrey = 0;
				 double m_axis = Convert::ToDouble(this->MinAx->Text);
				 double theta = -Math::PI / 4.0;
				 int i, mode;
				 bool clustering = true;
				 InitVars();

				 if (this->Clustercheck->Checked)
				 {
					 clustering = true;
					 mode = (int)Convert::ToDouble(this->Mode->Text);
				 }
				 else clustering = false;

				 plot_glList1 = glGenLists(1);						    // build a display list
				 glNewList(plot_glList1, GL_COMPILE);				// start loading into diplay list
				 glBegin(GL_LINE_LOOP);


				 for (i = 0; i < N; i++)
				 {
					 ibcx[i] = centrex + Math::Cos(theta - phi)*Math::Cos(phi) - m_axis*Math::Sin(theta - phi)*Math::Sin(phi);
					 ibcy[i] = centrey + Math::Cos(theta - phi)*Math::Sin(phi) + m_axis*Math::Sin(theta - phi)*Math::Cos(phi);
					 glColor3f(0.0f, 1.0f, 0.0f);
					 glVertex3d(ibcx[i], ibcy[i], 0.0f);
					 if (clustering)
						 theta += 4 * Math::PI / (N + 1)*Math::Pow(Math::Sin(mode*Math::PI*(i + 1) / (N + 1)), 2);
					 else theta += 2 * Math::PI / (N);
				 }

				 glEnd();

				 clustering = false;
				 double w = Convert::ToDouble(this->RecW->Text) / 2.0;
				 double h = Convert::ToDouble(this->RecH->Text) / 2.0;

				 glBegin(GL_LINE_LOOP);
				 int N1 = (int)(N / 4.0);
				 theta = -Math::PI / 4.0;
				 for (i = 0; i<N1; i++)
				 {
					 obcx[i] = w;
					 obcy[i] = h*Math::Tan(theta);
					 glColor3f(0.0f, 0.0f, 1.0f);
					 glVertex3d(obcx[i], obcy[i], 0.0f);
					 if (clustering)
						 theta += Math::PI / (N1)*Math::Pow(Math::Sin((mode*Math::PI)*(i + 1) / (N + 1)), 2);
					 else theta += Math::PI / (2.0*N1);
				 }

				 int N2 = (int)(N / 4.0);
				 for (; i<N2 + N1; i++)
				 {
					 obcy[i] = h;
					 obcx[i] = w*Math::Tan(Math::PI / 2.0 - theta);
					 glColor3f(0.0f, 0.0f, 1.0f);
					 glVertex3d(obcx[i], obcy[i], 0.0f);
					 if (clustering)
						 theta += Math::PI / (N2 + 1)*Math::Pow(Math::Sin((mode*Math::PI)*(i + 1) / (N + 1)), 2);
					 else theta += Math::PI / (2.0*N2);
				 }

				 int N3 = (int)(N / 4.0);
				 for (; i<N3 + N2 + N1; i++)
				 {
					 obcx[i] = -w;
					 obcy[i] = -h*Math::Tan(theta);
					 glColor3f(0.0f, 0.0f, 1.0f);
					 glVertex3d(obcx[i], obcy[i], 0.0f);
					 if (clustering)
						 theta += Math::PI / (N3 + 1)*Math::Pow(Math::Sin((mode*Math::PI)*(i + 1) / (N + 1)), 2);
					 else theta += Math::PI / (2.0*N3);
				 }

				 int N4 = (int)(N / 4.0);
				 for (; i<N4 + N3 + N2 + N1; i++)
				 {
					 obcy[i] = -h;
					 obcx[i] = -w*Math::Tan(Math::PI / 2.0 - theta);
					 glColor3f(0.0f, 0.0f, 1.0f);
					 glVertex3d(obcx[i], obcy[i], 0.0f);
					 if (clustering)
						 theta += Math::PI / (N4 + 1)*Math::Pow(Math::Sin((mode*Math::PI)*(i + 1) / (N + 1)), 2);
					 else theta += Math::PI / (2.0*N4);
				 }
				 glEnd();
			 }

			 void NormalIB()
			 {
				 // This actualy computes the next surface that would contain points lying on normal vector
				 int i;
				 double nx, ny;
				 double phi = Convert::ToDouble(this->RotAng->Text)*Math::PI / 180.0;
				 if (this->GenN->Checked)
				 {
					 i = 0;
					 nx = (ibcy[i + 1] - ibcy[N - 1]) / 2.0;
					 ny = -(ibcx[i + 1] - ibcx[N - 1]) / 2.0;
					 ibcx_2[i] = ibcx[i] + d*nx;
					 ibcy_2[i] = ibcy[i] + d*ny;
					 for (i = 1; i < N - 1; i++)
					 {
						 nx = (ibcy[i + 1] - ibcy[i - 1]) / 2.0;
						 ny = -(ibcx[i + 1] - ibcx[i - 1]) / 2.0;
						 ibcx_2[i] = ibcx[i] + d*nx;
						 ibcy_2[i] = ibcy[i] + d*ny;
					 }
					 i = N - 1;
					 nx = (ibcy[0] - ibcy[i - 1]) / 2.0;
					 ny = -(ibcx[0] - ibcx[i - 1]) / 2.0;
					 ibcx_2[i] = ibcx[i] + d*nx;
					 ibcy_2[i] = ibcy[i] + d*ny;
				 }
				 if (this->EllN->Checked)
				 {
					 double theta = -Math::PI / 4.0;
					 double b = Convert::ToDouble(this->MinAx->Text);
					 for (i = 0; i<N; i++)
					 {

						 ibcx_2[i] = d*(-Math::Sin(theta - phi)*Math::Sin(phi) + b*Math::Cos(theta - phi)*Math::Cos(phi)) + ibcx[i];
						 ibcy_2[i] = d*(Math::Sin(theta - phi)*Math::Cos(phi) + b*Math::Cos(theta - phi)*Math::Sin(phi)) + ibcy[i];
						 theta += 2.0*Math::PI / (N);
					 }
				 }
			 }

			 void Mesh()
			 {
				 int i, j, sw;
				 double n, s, phi0, phi1, phi2, phi3, phi4, phi5;
				 double sc, al, div;
				 double a1, b1, c1, d1;
				 double st, st2, dfn0x, dfn0y, dfn1x, dfn1y;
				 int choice = 0;
				 int k, iter = 0;;
				 array<double>^ h = gcnew array<double>(N);
				 double maxh = -1000;
				 double minh = 1000;
				 double hold = 0.0011234;
				 double p, q;

				 if (!String::Compare(this->MeshType->Text, "Multi-Surface (2)"))
				 {
					 sw = 1;
					 p = Convert::ToDouble(this->P->Text);
					 q = Convert::ToDouble(this->Q->Text);
					 if (this->CHcheck->Checked)
					 {
						 double dxdP, dydP, dhdP, targeth = Convert::ToDouble(this->CH->Text);


						 for (j = 0; j<N; j++)
						 {
							 minh = 1000;
							 p = 0.1;
							 while (Math::Abs(minh - targeth) >= 1E-14 && iter<5000)
							 {
								 n = double(1.0) / (Nf - 1.0);
								 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
								 x[1, j] = (1.0 - s)*ibcx[j] + s*obcx[j];
								 y[1, j] = (1.0 - s)*ibcy[j] + s*obcy[j];
								 h[j] = Math::Sqrt(Math::Pow(x[1, j] - ibcx[j], 2) + Math::Pow(y[1, j] - ibcy[j], 2));
								 dxdP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-ibcx[j] + obcx[j]);
								 dydP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-ibcy[j] + obcy[j]);
								 dhdP = (x[1, j] - ibcx[j])*dxdP / h[j] + (y[1, j] - ibcy[j])*dydP / h[j];
								 minh = h[j];
								 p = p - (h[j] - targeth) / dhdP;
								 STP[j] = p;
								 iter++;
							 }

						 }
						 this->label20->Text = Convert::ToString(iter);
						 this->P->Text = Convert::ToString(p);
					 }
				 }

				 if (!String::Compare(this->MeshType->Text, "Multi-Surface (3)"))
				 {
					 sw = 3;
					 p = Convert::ToDouble(this->P->Text);
					 q = Convert::ToDouble(this->Q->Text);
					 if (this->Scale->Checked)
						 choice = 0;
					 if (this->Interpolate->Checked)
						 choice = 1;
					 if (this->ProgGenOut->Checked)
						 choice = 2;
					 sc = Convert::ToDouble(this->S3->Text);
					 d = Convert::ToDouble(this->D->Text);
					 this->NormalIB();
					 if (this->CHcheck->Checked)
					 {
						 double dxdP, dydP, dhdP, targeth = Convert::ToDouble(this->CH->Text);

						 p = 0;

						 for (j = 0; j<N; j++)
						 {
							 p = 0.1;
							 minh = 1000;
							 if (choice == 0)
							 {
								 ibcx_2[j] = sc*ibcx[j];
								 ibcy_2[j] = sc*ibcy[j];
							 }
							 if (choice == 1)
							 {
								 ibcx_2[j] = sc*ibcx[j] + (1 - sc)*obcx[j];
								 ibcy_2[j] = sc*ibcy[j] + (1 - sc)*obcy[j];
							 }
							 if (choice == 2)
							 {
								 //
							 }
							 while (Math::Abs(minh - targeth) >= 1E-14 && iter<5000)
							 {
								 n = double(1.0) / (Nf - 1.0);
								 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
								 x[1, j] = ibcx[j] * (1 - s)*(1 - s) + 2 * s*(1 - s)*(ibcx_2[j]) + obcx[j] * s*s;
								 y[1, j] = ibcy[j] * (1 - s)*(1 - s) + 2 * s*(1 - s)*(ibcy_2[j]) + obcy[j] * s*s;
								 h[j] = Math::Sqrt(Math::Pow(x[1, j] - ibcx[j], 2) + Math::Pow(y[1, j] - ibcy[j], 2));
								 dxdP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-2 * (1 - s)*ibcx[j] + 2 * (1 - 2 * s)*ibcx_2[j] + 2 * s*obcx[j]);
								 dydP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-2 * (1 - s)*ibcy[j] + 2 * (1 - 2 * s)*ibcy_2[j] + 2 * s*obcy[j]);
								 dhdP = (x[1, j] - ibcx[j])*dxdP / h[j] + (y[1, j] - ibcy[j])*dydP / h[j];
								 minh = h[j];
								 p = p - (h[j] - targeth) / dhdP;
								 STP[j] = p;
								 iter++;
							 }
						 }
						 this->label20->Text = Convert::ToString(iter);
						 this->P->Text = Convert::ToString(p);
					 }
				 }

				 if (!String::Compare(this->MeshType->Text, "Elliptic PDE's"))
				 {
					 sw = 4;
					 p = Convert::ToDouble(this->P->Text);
					 q = Convert::ToDouble(this->Q->Text);
				 }

				 if (!String::Compare(this->MeshType->Text, "Allen's TFI (1) (recommended)"))
				 {
					 sw = 5;
					 st = Convert::ToDouble(this->ST1->Text);
					 st2 = Convert::ToDouble(this->ST_2->Text);
					 d = Convert::ToDouble(this->D->Text);
					 this->NormalIB();
					 if (this->CHcheck->Checked)
					 {
						 double dxdst, dydst, dhdst, targeth = Convert::ToDouble(this->CH->Text);

						 double d_phi0, d_phi1, d_phi2, d_phi3;
						 st = 0.6;

						 for (j = 0; j<N; j++)
						 {
							 st = 0.6;
							 minh = 1000;
							 while (Math::Abs(minh - targeth) >= 1E-14 && iter < 5000000)
							 {
								 n = double(1.0) / (Nf - 1.0);
								 phi0 = -Math::Tanh(st*(n - 1)) / Math::Tanh(st);
								 phi1 = 1 - phi0;
								 phi2 = Math::Pow(phi1, st2);
								 phi3 = 1 - phi2;
								 d_phi0 = -((1 - Math::Pow(Math::Tanh(st*(n - 1)), 2))*Math::Tanh(st) - (1 - Math::Pow(Math::Tanh(st), 2))*Math::Tanh(st*(n - 1))) / Math::Pow(Math::Tanh(st), 2);
								 d_phi1 = -d_phi0;
								 d_phi2 = st2*Math::Pow(phi1, st2 - 1)*d_phi1;
								 d_phi3 = -d_phi2;
								 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
								 dfn0x = ibcx[j] + (ibcx_2[j] - ibcx[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));
								 dfn0y = ibcy[j] + (ibcy_2[j] - ibcy[j])*div / Math::Sqrt(Math::Pow(ibcy_2[j] - ibcy[j], 2) + Math::Pow(ibcx_2[j] - ibcx[j], 2));
								 x[1, j] = phi0*ibcx[j] + phi1*(phi3*dfn0x + phi2*obcx[j]);
								 y[1, j] = phi0*ibcy[j] + phi1*(phi3*dfn0y + phi2*obcy[j]);
								 h[j] = Math::Sqrt(Math::Pow(x[1, j] - ibcx[j], 2) + Math::Pow(y[1, j] - ibcy[j], 2));
								 dxdst = d_phi0*ibcx[j] + d_phi1*(phi3*dfn0x + phi2*obcx[j]) + phi1*(d_phi3*dfn0x + d_phi2*obcx[j]);
								 dydst = d_phi0*ibcy[j] + d_phi1*(phi3*dfn0y + phi2*obcy[j]) + phi1*(d_phi3*dfn0y + d_phi2*obcy[j]);
								 dhdst = (x[1, j] - ibcx[j])*dxdst / h[j] + (y[1, j] - ibcy[j])*dydst / h[j];
								 minh = h[j];
								 st = st + (h[j] - targeth) / dhdst;
								 iter++;
								 STP[j] = st;
							 }
						 }
						 this->label20->Text = Convert::ToString(iter);
						 this->ST1->Text = Convert::ToString(st);
					 }
				 }
				 if (!String::Compare(this->MeshType->Text, "Allen's TFI (2)"))
				 {
					 sw = 6;
					 st = Convert::ToDouble(this->ST1->Text);
					 st2 = Convert::ToDouble(this->ST_2->Text);
					 d = Convert::ToDouble(this->D->Text);
					 this->NormalIB();
					 p = 1.0;
					 q = 2.0;

					 for (j = 0; j < N; j++)
					 {
						 n = double(Nf - 2.0) / (Nf - 1.0);
						 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
						 obcx_2[j] = (1.0 - s)*ibcx[j] + s*obcx[j];
						 obcy_2[j] = (1.0 - s)*ibcy[j] + s*obcy[j];
					 }

					 if (this->CHcheck->Checked)
					 {
						 double dxdst, dydst, dhdst, targeth = Convert::ToDouble(this->CH->Text);

						 double d_phi0, d_phi1, d_phi2, d_phi3, d_phi4, d_phi5;
						 st = 0.6;

						 for (j = 0; j<N; j++)
						 {
							 minh = 1000;
							 st = 0.6;
							 while (Math::Abs(minh - targeth) >= 1E-14 && iter<5000000)
							 {
								 n = double(1.0) / (Nf - 1.0);
								 phi0 = -Math::Tanh(st*(n - 1)) / Math::Tanh(st);
								 phi1 = 1 - phi0;
								 phi2 = Math::Pow(phi1, st2);
								 phi3 = 1 - phi2;
								 phi4 = 1 - phi1*phi1;
								 phi5 = 1 - phi4;
								 d_phi0 = -((1 - Math::Pow(Math::Tanh(st*(n - 1)), 2))*Math::Tanh(st) - (1 - Math::Pow(Math::Tanh(st), 2))*Math::Tanh(st*(n - 1))) / Math::Pow(Math::Tanh(st), 2);
								 d_phi1 = -d_phi0;
								 d_phi2 = st2*Math::Pow(phi1, st2 - 1)*d_phi1;
								 d_phi3 = -d_phi2;
								 d_phi4 = -2 * phi1*d_phi1;
								 d_phi5 = -d_phi4;

								 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
								 dfn0x = ibcx[j] + (ibcx_2[j] - ibcx[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));
								 dfn0y = ibcy[j] + (ibcy_2[j] - ibcy[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));

								 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
								 dfn1x = obcx[j] - (obcx[j] - obcx_2[j])*div / Math::Sqrt(Math::Pow(obcx[j] - obcx_2[j], 2) + Math::Pow(obcy[j] - obcy_2[j], 2));
								 dfn1y = obcy[j] - (obcy[j] - obcy_2[j])*div / Math::Sqrt(Math::Pow(obcx[j] - obcx_2[j], 2) + Math::Pow(obcy[j] - obcy_2[j], 2));

								 x[1, j] = phi4*(phi0*ibcx[j] + phi1*(phi3*dfn0x + phi2*obcx[j])) + phi5*(phi1*obcx[j] + phi0*(phi2*dfn1x + phi3*ibcx[j]));
								 y[1, j] = phi4*(phi0*ibcy[j] + phi1*(phi3*dfn0y + phi2*obcy[j])) + phi5*(phi1*obcy[j] + phi0*(phi2*dfn1y + phi3*ibcy[j]));;
								 h[j] = Math::Sqrt(Math::Pow(x[1, j] - ibcx[j], 2) + Math::Pow(y[1, j] - ibcy[j], 2));
								 dxdst = d_phi4*phi0*ibcx[j] + phi4*d_phi0*ibcx[j] + d_phi5*phi1*obcx[j] + phi5*d_phi1*obcx[j] + d_phi4*phi1*phi3*dfn0x + phi4*d_phi1*phi3*dfn0x + phi4*phi1*d_phi3*dfn0x + d_phi4*phi1*phi2*obcx[j] + phi4*d_phi1*phi2*obcx[j] + phi4*phi1*d_phi2*obcx[j] +
									 d_phi5*phi0*phi2*dfn1x + phi5*d_phi0*phi2*dfn1x + phi5*phi0*d_phi2*dfn1x + d_phi5*phi0*phi3*ibcx[j] + phi5*d_phi0*phi3*ibcx[j] + phi5*phi0*d_phi3*ibcx[j];
								 dydst = d_phi4*phi0*ibcy[j] + phi4*d_phi0*ibcy[j] + d_phi5*phi1*obcy[j] + phi5*d_phi1*obcy[j] + d_phi4*phi1*phi3*dfn0y + phi4*d_phi1*phi3*dfn0y + phi4*phi1*d_phi3*dfn0y + d_phi4*phi1*phi2*obcy[j] + phi4*d_phi1*phi2*obcy[j] + phi4*phi1*d_phi2*obcy[j] +
									 d_phi5*phi0*phi2*dfn1y + phi5*d_phi0*phi2*dfn1y + phi5*phi0*d_phi2*dfn1y + d_phi5*phi0*phi3*ibcy[j] + phi5*d_phi0*phi3*ibcy[j] + phi5*phi0*d_phi3*ibcy[j];
								 dhdst = (x[1, j] - ibcx[j])*dxdst / h[j] + (y[1, j] - ibcy[j])*dydst / h[j];
								 minh = h[j];
								 st = st + (h[j] - targeth) / dhdst;
								 iter++;
								 STP[j] = st;
							 }
						 }
						 this->label20->Text = Convert::ToString(iter);
						 this->ST1->Text = Convert::ToString(st);
					 }
				 }
				 if (!String::Compare(this->MeshType->Text, "Multi-Surface (4)"))
				 {
					 sw = 7;
					 p = Convert::ToDouble(this->P->Text);
					 q = Convert::ToDouble(this->Q->Text);
					 if (this->Scale->Checked)
						 choice = 0;
					 if (this->Interpolate->Checked)
						 choice = 1;
					 if (this->ProgGenOut->Checked)
						 choice = 2;
					 sc = Convert::ToDouble(this->S3->Text);
					 st = Convert::ToDouble(this->S4->Text);
					 al = Convert::ToDouble(this->AL->Text);
					 d = Convert::ToDouble(this->D->Text);
					 this->NormalIB();
					 if (this->CHcheck->Checked)
					 {
						 double dxdP, dydP, dhdP, targeth = Convert::ToDouble(this->CH->Text);

						 p = 2.0;

						 for (j = 0; j<N; j++)
						 {
							 minh = 1000;
							 p = 0.1;
							 if (choice == 0)
							 {
								 ibcx_2[j] = sc*ibcx[j];
								 ibcy_2[j] = sc*ibcy[j];
								 obcx_2[j] = st*obcx[j];
								 obcy_2[j] = st*obcy[j];
							 }
							 if (choice == 1)
							 {
								 ibcx_2[j] = sc*ibcx[j] + (1 - sc)*obcx[j];
								 ibcy_2[j] = sc*ibcy[j] + (1 - sc)*obcy[j];
								 obcx_2[j] = (1 - st)*ibcx[j] + st*obcx[j];
								 obcy_2[j] = (1 - st)*ibcy[j] + st*obcy[j];
							 }
							 if (choice == 2)
							 {
								 obcx_2[j] = (1 - 0.96)*ibcx[j] + 0.96*obcx[j];
								 obcy_2[j] = (1 - 0.96)*ibcy[j] + 0.96*obcy[j];
							 }
							 while (Math::Abs(minh - targeth) >= 1E-14 && iter<5000)
							 {
								 n = double(2.0 - 1.0) / (Nf - 1.0);
								 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
								 a1 = 2 / (3 * al - 1);
								 b1 = 2 / (2 - 3 * al);
								 x[1, j] = (1 - s)*(1 - s)*(1 - a1*s)*ibcx[j] + s*(1 - s)*(1 - s)*(a1 + 2)*ibcx_2[j] + s*s*(1 - s)*(b1 + 2)*obcx_2[j] + s*s*(1 - b1*(1 - s))*obcx[j];
								 y[1, j] = (1 - s)*(1 - s)*(1 - a1*s)*ibcy[j] + s*(1 - s)*(1 - s)*(a1 + 2)*ibcy_2[j] + s*s*(1 - s)*(b1 + 2)*obcy_2[j] + s*s*(1 - b1*(1 - s))*obcy[j];
								 h[j] = Math::Sqrt(Math::Pow(x[1, j] - ibcx[j], 2) + Math::Pow(y[1, j] - ibcy[j], 2));
								 dxdP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-2 * (1 - s)*(1 - a1*s)*ibcx[j] - (1 - s)*(1 - s)*a1*ibcx[j] + (1 - s)*(1 - s)*(a1 + 2)*ibcx_2[j] - 2 * s*(1 - s)*(a1 + 2)*ibcx_2[j] + (2 * s - 3 * s*s)*(b1 + 2)*obcx_2[j] + ((1 - b1) * 2 * s + 3 * b1*s*s)*obcx[j]);
								 dydP = (n - (1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q)))*(-2 * (1 - s)*(1 - a1*s)*ibcy[j] - (1 - s)*(1 - s)*a1*ibcy[j] + (1 - s)*(1 - s)*(a1 + 2)*ibcy_2[j] - 2 * s*(1 - s)*(a1 + 2)*ibcy_2[j] + (2 * s - 3 * s*s)*(b1 + 2)*obcy_2[j] + ((1 - b1) * 2 * s + 3 * b1*s*s)*obcy[j]);
								 dhdP = (x[1, j] - ibcx[j])*dxdP / h[j] + (y[1, j] - ibcy[j])*dydP / h[j];
								 minh = h[j];
								 p = p - (h[j] - targeth) / dhdP;
								 iter++;
								 STP[j] = p;
							 }
						 }

						 this->label20->Text = Convert::ToString(iter);
						 this->P->Text = Convert::ToString(p);
					 }
				 }

				 bool chchk = this->CHcheck->Checked;
				 if (chchk)
					 for (j = 0; j<N; j++)
					 {
						 if (sw == 1 || sw == 3 || sw == 7)
							 if (Math::Abs(STP[j])>1.90)
							 {
								 sw = 8;
								 break;
							 }

						 if (sw == 2 || sw == 5 || sw == 6)
							 if (iter == 5000000)
							 {
								 sw = 8;
								 break;
							 }
					 }


				 bool passed = true;
				 switch (sw)
				 {
				 case 1:
					 for (i = 1; i <= Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 p = (chchk ? STP[j] : p);
							 n = double(i - 1.0) / (Nf - 1.0);
							 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
							 x[i - 1, j] = (1.0 - s)*ibcx[j] + s*obcx[j];
							 y[i - 1, j] = (1.0 - s)*ibcy[j] + s*obcy[j];
						 }
					 }

					 break;
				 case 2:
					 break;
				 case 3: // Three surface
					 for (i = 0; i < Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 p = (chchk ? STP[j] : p);
							 n = double(i) / (Nf - 1.0);
							 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
							 if (choice == 0)
							 {
								 ibcx_2[j] = sc*ibcx[j];
								 ibcy_2[j] = sc*ibcy[j];
							 }
							 if (choice == 1)
							 {
								 ibcx_2[j] = sc*ibcx[j] + (1 - sc)*obcx[j];
								 ibcy_2[j] = sc*ibcy[j] + (1 - sc)*obcy[j];
							 }
							 if (choice == 2)
							 {
								 //
							 }

							 x[i, j] = ibcx[j] * (1 - s)*(1 - s) + 2 * s*(1 - s)*(ibcx_2[j]) + obcx[j] * s*s;
							 y[i, j] = ibcy[j] * (1 - s)*(1 - s) + 2 * s*(1 - s)*(ibcy_2[j]) + obcy[j] * s*s;
						 }
					 }
					 break;
				 case 4: // Elliptic PDE's
					 d = 0.05;
					 for (i = 0; i < Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 n = double(i - 1.0) / (Nf - 1.0);
							 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
							 x[i, j] = (1 - s)*ibcx[j] + s*obcx[j];
							 y[i, j] = (1 - s)*ibcy[j] + s*obcy[j];
						 }
					 }
					 for (k = 0; k <Convert::ToInt32(this->iters->Text); k++)
					 {
						 i = 0;
						 for (j = 0; j < N; j++)
						 {
							 x[i, j] = ibcx[j];
							 y[i, j] = ibcy[j];
						 }

						 for (i = 1; i < Nf - 1; i++)
						 {
							 j = 0;
							 a1 = 0.25*(Math::Pow(x[i, j + 1] - x[i, N - 1], 2) + Math::Pow(y[i, j + 1] - y[i, N - 1], 2));
							 b1 = 0.25*((x[i + 1, j] - x[i - 1, j])*(x[i, j + 1] - x[i, N - 1]) + (y[i + 1, j] - y[i - 1, j])*(y[i, j + 1] - y[i, N - 1]));
							 c1 = 0.25*(Math::Pow(x[i + 1, j] - x[i - 1, j], 2) + Math::Pow(y[i + 1, j] - y[i - 1, j], 2));
							 d1 = (1.0 / 16.0)*Math::Pow((x[i + 1, j] - x[i - 1, j])*(y[i, j + 1] - y[i, N - 1]) + (y[i + 1, j] - y[i - 1, j])*(x[i, j + 1] - x[i, N - 1]), 2);

							 x[i, j] = (a1*(x[i - 1, j] + x[i + 1, j]) - 0.5*b1*(x[i + 1, j + 1] - x[i - 1, j + 1] - x[i + 1, N - 1] + x[i + 1, j + 1]) + c1*(x[i, N - 1] + x[i, j + 1])) / (a1 + c1) / 2.0;
							 y[i, j] = (a1*(y[i - 1, j] + y[i + 1, j]) - 0.5*b1*(y[i + 1, j + 1] - y[i - 1, j + 1] - y[i + 1, N - 1] + y[i + 1, j + 1]) + c1*(y[i, N - 1] + y[i, j + 1])) / (a1 + c1) / 2.0;

							 //x[i,j] = ((x[i-1,j]+x[i+1,j]) + (x[i,N-1]+x[i,j+1]))/2.0;
							 //y[i,j] = ((y[i-1,j]+y[i+1,j]) + (y[i,N-1]+y[i,j+1]))/2.0;

							 for (j = 1; j < N - 1; j++)
							 {
								 a1 = 0.25*(Math::Pow(x[i, j + 1] - x[i, j - 1], 2) + Math::Pow(y[i, j + 1] - y[i, j - 1], 2));
								 b1 = 0.25*((x[i + 1, j] - x[i - 1, j])*(x[i, j + 1] - x[i, j - 1]) + (y[i + 1, j] - y[i - 1, j])*(y[i, j + 1] - y[i, j - 1]));
								 c1 = 0.25*(Math::Pow(x[i + 1, j] - x[i - 1, j], 2) + Math::Pow(y[i + 1, j] - y[i - 1, j], 2));
								 d1 = (1.0 / 16.0)*Math::Pow((x[i + 1, j] - x[i - 1, j])*(y[i, j + 1] - y[i, j - 1]) + (y[i + 1, j] - y[i - 1, j])*(x[i, j + 1] - x[i, j - 1]), 2);

								 x[i, j] = (a1*(x[i - 1, j] + x[i + 1, j]) - 0.5*b1*(x[i + 1, j + 1] - x[i - 1, j + 1] - x[i + 1, j - 1] + x[i + 1, j + 1]) + c1*(x[i, j - 1] + x[i, j + 1])) / (a1 + c1) / 2.0;
								 y[i, j] = (a1*(y[i - 1, j] + y[i + 1, j]) - 0.5*b1*(y[i + 1, j + 1] - y[i - 1, j + 1] - y[i + 1, j - 1] + y[i + 1, j + 1]) + c1*(y[i, j - 1] + y[i, j + 1])) / (a1 + c1) / 2.0;

								 //x[i,j] = ((x[i-1,j]+x[i+1,j]) + (x[i,j-1]+x[i,j+1]))/2.0;
								 //y[i,j] = ((y[i-1,j]+y[i+1,j]) + (y[i,j-1]+y[i,j+1]))/2.0;
							 }

							 j = N - 1;
							 a1 = 0.25*(Math::Pow(x[i, 0] - x[i, j - 1], 2) + Math::Pow(y[i, 0] - y[i, j - 1], 2));
							 b1 = 0.25*((x[i + 1, j] - x[i - 1, j])*(x[i, 0] - x[i, j - 1]) + (y[i + 1, j] - y[i - 1, j])*(y[i, 0] - y[i, j - 1]));
							 c1 = 0.25*(Math::Pow(x[i + 1, j] - x[i - 1, j], 2) + Math::Pow(y[i + 1, j] - y[i - 1, j], 2));
							 d1 = (1.0 / 16.0)*Math::Pow((x[i + 1, j] - x[i - 1, j])*(y[i, 0] - y[i, j - 1]) + (y[i + 1, j] - y[i - 1, j])*(x[i, 0] - x[i, j - 1]), 2);

							 x[i, j] = (a1*(x[i - 1, j] + x[i + 1, j]) - 0.5*b1*(x[i + 1, 0] - x[i - 1, 0] - x[i + 1, j - 1] + x[i + 1, 0]) + c1*(x[i, j - 1] + x[i, 0])) / (a1 + c1) / 2.0;
							 y[i, j] = (a1*(y[i - 1, j] + y[i + 1, j]) - 0.5*b1*(y[i + 1, 0] - y[i - 1, 0] - y[i + 1, j - 1] + y[i + 1, 0]) + c1*(y[i, j - 1] + y[i, 0])) / (a1 + c1) / 2.0;

							 //x[i,j] = ((x[i-1,j]+x[i+1,j]) + (x[i,j-1]+x[i,1]))/2.0;						
							 //y[i,j] = ((y[i-1,j]+y[i+1,j]) + (y[i,j-1]+y[i,1]))/2.0;
						 }
						 i = Nf - 1;
						 j = 0;
						 //a1 = 0.25*(Math::Pow(x[i,j+1]-x[i,N-2],2) + Math::Pow(y[i,j+1]-y[i,N-2],2));
						 //b1 = 0.25*((x[i+1,j]-x[i-1,j])*(x[i,j+1]-x[i,N-2]) + (y[i+1,j]-y[i-1,j])*(y[i,j+1]-y[i,N-2]));							
						 //c1 = 0.25*(Math::Pow(x[i+1,j]-x[i-1,j],2) + Math::Pow(y[i+1,j]-y[i-1,j],2));
						 //d1 = (1.0/16.0)*Math::Pow((x[i+1,j]-x[i-1,j])*(y[i,j+1]-y[i,N-2]) + (y[i+1,j]-y[i-1,j])*(x[i,j+1]-x[i,N-2]),2);

						 //x[i,j] = (a1*(x[i-1,j]+x[i+1,j]) -0.5*b1*(x[i+1,j+1]-x[i-1,j+1]-x[i+1,N-2]+x[i+1,j+1]) +c1*(x[i,N-2]+x[i,j+1]))/(a1+c1)/2.0;
						 //y[i,j] = (a1*(y[i-1,j]+y[i+1,j]) -0.5*b1*(y[i+1,j+1]-y[i-1,j+1]-y[i+1,N-2]+y[i+1,j+1]) +c1*(y[i,N-2]+y[i,j+1]))/(a1+c1)/2.0;

						 for (j = 0; j < N; j++)
						 {
							 //a1 = 0.25*(Math::Pow(obcx[j+1]-obcx[j-1],2) + Math::Pow(obcy[j+1]-obcy[j-1],2));
							 //b1 = 0.25*((obcx[j]-x[i-2,j])*(obcx[j+1]-obcx[j-1]) + (obcy[j]-y[i-2,j])*(y[i-1,j+1]-y[i-1,j-1]));							
							 //c1 = 0.25*(Math::Pow(obcx[j]-x[i-2,j],2) + Math::Pow(obcy[j]-y[i-2,j],2));
							 //d1 = (1.0/16.0)*Math::Pow((obcx[j]-x[i-2,j])*(obcy[j+1]-obcy[j-1]) + (obcy[j]-y[i-2,j])*(obcx[j+1]-obcx[j-1]),2);

							 //x[i,j] = (a1*(x[i-2,j]+obcx[j]) -0.5*b1*(obcx[j+1]-x[i-2,j+1]-obcx[j-1]+obcx[j+1]) +c1*(obcx[j-1]+obcx[j+1]))/(a1+c1)/2.0;
							 //y[i,j] = (a1*(y[i-2,j]+obcy[j]) -0.5*b1*(obcy[j+1]-y[i-2,j+1]-obcy[j-1]+obcy[j+1]) +c1*(obcy[j-1]+obcy[j+1]))/(a1+c1)/2.0;
							 x[i, j] = obcx[j];
							 y[i, j] = obcy[j];
						 }

						 j = N - 1;
						 //a1 = 0.25*(Math::Pow(x[i,1]-x[i,j-1],2) + Math::Pow(y[i,1]-y[i,j-1],2));
						 //b1 = 0.25*((x[i+1,j]-x[i-1,j])*(x[i,1]-x[i,j-1]) + (y[i+1,j]-y[i-1,j])*(y[i,1]-y[i,j-1]));							
						 //c1 = 0.25*(Math::Pow(x[i+1,j]-x[i-1,j],2) + Math::Pow(y[i+1,j]-y[i-1,j],2));
						 //d1 = (1.0/16.0)*Math::Pow((x[i+1,j]-x[i-1,j])*(y[i,1]-y[i,j-1]) + (y[i+1,j]-y[i-1,j])*(x[i,1]-x[i,j-1]),2);

						 //x[i,j] = (a1*(x[i-1,j]+x[i+1,j]) -0.5*b1*(x[i+1,1]-x[i-1,1]-x[i+1,j-1]+x[i+1,1]) +c1*(x[i,j-1]+x[i,1]))/(a1+c1)/2.0;
						 //y[i,j] = (a1*(y[i-1,j]+y[i+1,j]) -0.5*b1*(y[i+1,1]-y[i-1,1]-y[i+1,j-1]+y[i+1,1]) +c1*(y[i,j-1]+y[i,1]))/(a1+c1)/2.0;

					 }
					 break;
				 case 5: // Allen's TFI 1 ///3 Surface

					 for (i = 0; i < Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 st = (chchk ? STP[j] : st);
							 n = double(i) / (Nf - 1.0);
							 phi0 = -Math::Tanh(st*(n - 1)) / Math::Tanh(st);
							 phi1 = 1 - phi0;
							 phi2 = Math::Pow(phi1, st2);
							 phi3 = 1 - phi2;
							 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
							 dfn0x = ibcx[j] + (ibcx_2[j] - ibcx[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));
							 dfn0y = ibcy[j] + (ibcy_2[j] - ibcy[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));
							 x[i, j] = phi0*ibcx[j] + phi1*(phi3*dfn0x + phi2*obcx[j]);
							 y[i, j] = phi0*ibcy[j] + phi1*(phi3*dfn0y + phi2*obcy[j]);
						 }
					 }
					 break;
				 case 6: // Allen's TFI 2 ///4 surface

					 for (i = 0; i < Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 st = (chchk ? STP[j] : st);
							 n = double(i) / (Nf - 1.0);
							 phi0 = -Math::Tanh(st*(n - 1)) / Math::Tanh(st);
							 phi1 = 1 - phi0;
							 phi2 = Math::Pow(phi1, st2);
							 phi3 = 1 - phi2;
							 phi4 = 1 - phi1*phi1;
							 phi5 = 1 - phi4;

							 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
							 dfn0x = ibcx[j] + (ibcx_2[j] - ibcx[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));
							 dfn0y = ibcy[j] + (ibcy_2[j] - ibcy[j])*div / Math::Sqrt(Math::Pow(ibcx_2[j] - ibcx[j], 2) + Math::Pow(ibcy_2[j] - ibcy[j], 2));

							 div = Math::Sqrt(Math::Pow((obcx[j] - ibcx[j]), 2) + Math::Pow((obcy[j] - ibcy[j]), 2));
							 dfn1x = obcx[j] - (obcx[j] - obcx_2[j])*div / Math::Sqrt(Math::Pow(obcx[j] - obcx_2[j], 2) + Math::Pow(obcy[j] - obcy_2[j], 2));
							 dfn1y = obcy[j] - (obcy[j] - obcy_2[j])*div / Math::Sqrt(Math::Pow(obcx[j] - obcx_2[j], 2) + Math::Pow(obcy[j] - obcy_2[j], 2));

							 x[i, j] = phi4*(phi0*ibcx[j] + phi1*(phi3*dfn0x + phi2*obcx[j])) + phi5*(phi1*obcx[j] + phi0*(phi2*dfn1x + phi3*ibcx[j]));
							 y[i, j] = phi4*(phi0*ibcy[j] + phi1*(phi3*dfn0y + phi2*obcy[j])) + phi5*(phi1*obcy[j] + phi0*(phi2*dfn1y + phi3*ibcy[j]));;
						 }
					 }
					 break;
				 case 7: // Four surface
					 for (i = 0; i < Nf; i++)
					 {
						 for (j = 0; j < N; j++)
						 {
							 n = double(i) / (Nf - 1.0);
							 p = (chchk ? STP[j] : p);
							 s = p*n + (1 - p)*(1 - Math::Tanh(q*(1 - n)) / Math::Tanh(q));
							 if (choice == 0)
							 {
								 ibcx_2[j] = sc*ibcx[j];
								 ibcy_2[j] = sc*ibcy[j];
								 obcx_2[j] = st*obcx[j];
								 obcy_2[j] = st*obcy[j];
							 }
							 if (choice == 1)
							 {
								 ibcx_2[j] = sc*ibcx[j] + (1 - sc)*obcx[j];
								 ibcy_2[j] = sc*ibcy[j] + (1 - sc)*obcy[j];
								 obcx_2[j] = (1 - st)*ibcx[j] + st*obcx[j];
								 obcy_2[j] = (1 - st)*ibcy[j] + st*obcy[j];
							 }
							 if (choice == 2)
							 {
								 obcx_2[j] = (1 - 0.96)*ibcx[j] + 0.96*obcx[j];
								 obcy_2[j] = (1 - 0.96)*ibcy[j] + 0.96*obcy[j];
							 }
							 a1 = 2 / (3 * al - 1);
							 b1 = 2 / (2 - 3 * al);
							 x[i, j] = (1 - s)*(1 - s)*(1 - a1*s)*ibcx[j] + s*(1 - s)*(1 - s)*(a1 + 2)*ibcx_2[j] + s*s*(1 - s)*(b1 + 2)*obcx_2[j] + s*s*(1 - b1*(1 - s))*obcx[j];
							 y[i, j] = (1 - s)*(1 - s)*(1 - a1*s)*ibcy[j] + s*(1 - s)*(1 - s)*(a1 + 2)*ibcy_2[j] + s*s*(1 - s)*(b1 + 2)*obcy_2[j] + s*s*(1 - b1*(1 - s))*obcy[j];
						 }
					 }
					 break;
				 case 8:
					 passed = false;
					 System::Windows::Forms::MessageBox::Show("Unable to Mesh with the current Cell Height.\n" +
						 "Please choose lower value for Cell Height.",
						 "Cell Height Error", MessageBoxButtons::OK,
						 MessageBoxIcon::Error);
					 break;
				 }

				 if (passed)
				 {
					 if (this->AppSmooth->Checked)
						 Smooth();
					 this->Rho_Calc();
					 this->PlotMeshQ();
					 this->PlotGL();
					 double minh = 1000, maxh = -1000, h;
					 for (int i = 0; i<N; i++)
					 {
						 h = Math::Sqrt(Math::Pow(x[1, i] - ibcx[i], 2) + Math::Pow(y[1, i] - ibcy[i], 2));
						 if (h <= minh)
						 {
							 minh = h;
							 this->label15->Text = "Min Cell Height  at Inner Boundary : " + Convert::ToString(minh);
						 }
						 if (h >= maxh)
						 {
							 maxh = h;
							 this->label18->Text = "Max Cell Height at Inner Boundary : " + Convert::ToString(maxh);
						 }
					 }
					 this->button2->Visible = true;
					 this->button5->Visible = true;
				 }

			 }

			 void Rho_Calc()
			 {
				 // Calc Rho Vals
				 double rxip, rxim, ryip, ryim, rxkm, rykm, rxkp, rykp;
				 double rkp2, rkm2, rip2, rim2;
				 double r_ip_kp, r_ip_km, r_im_km, r_im_kp;
				 int i = 0;
				 int j = 0;
				 minr = 10000;
				 maxr = -10000;
				 rxip = x[i, j + 1] - x[i, j];
				 ryip = y[i, j + 1] - y[i, j];
				 rxim = x[i, N - 1] - x[i, j];//-x[i,j+1]+2*x[i,j];
				 ryim = y[i, N - 1] - y[i, j];//-y[i,j+1]+2*y[i,j];
				 rxkm = x[i, j] - x[i + 1, j];
				 rykm = y[i, j] - y[i + 1, j];
				 rxkp = x[i + 1, j] - x[i, j];
				 rykp = y[i + 1, j] - y[i, j];

				 rkp2 = rxkp*rxkp + rykp*rykp;
				 rkm2 = rxkm*rxkm + rykm*rykm;
				 rip2 = rxip*rxip + ryip*ryip;
				 rim2 = rxim*rxim + ryim*ryim;

				 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
				 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
				 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
				 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

				 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
				 minr = Math::Min(minr, rhoi[i, j]);
				 maxr = Math::Max(maxr, rhoi[i, j]);

				 for (j = 1; j <N - 1; j++)
				 {
					 rxip = x[i, j + 1] - x[i, j];
					 ryip = y[i, j + 1] - y[i, j];
					 rxim = x[i, j - 1] - x[i, j];
					 ryim = y[i, j - 1] - y[i, j];
					 rxkm = x[i, j] - x[i + 1, j];
					 rykm = y[i, j] - y[i + 1, j];
					 rxkp = x[i + 1, j] - x[i, j];
					 rykp = y[i + 1, j] - y[i, j];

					 rkp2 = rxkp*rxkp + rykp*rykp;
					 rkm2 = rxkm*rxkm + rykm*rykm;
					 rip2 = rxip*rxip + ryip*ryip;
					 rim2 = rxim*rxim + ryim*ryim;

					 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
					 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
					 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
					 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

					 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;

					 minr = Math::Min(minr, rhoi[i, j]);
					 maxr = Math::Max(maxr, rhoi[i, j]);
				 }
				 j = N - 1;
				 rxip = x[i, 0] - x[i, j];//-x[i,j-1]+2*x[i,j];
				 ryip = y[i, 0] - y[i, j];// -y[i,j-1]+2*y[i,j];
				 rxim = x[i, j - 1] - x[i, j];
				 ryim = y[i, j - 1] - y[i, j];
				 rxkm = x[i, j] - x[i + 1, j];
				 rykm = y[i, j] - y[i + 1, j];
				 rxkp = x[i + 1, j] - x[i, j];
				 rykp = y[i + 1, j] - y[i, j];

				 rkp2 = rxkp*rxkp + rykp*rykp;
				 rkm2 = rxkm*rxkm + rykm*rykm;
				 rip2 = rxip*rxip + ryip*ryip;
				 rim2 = rxim*rxim + ryim*ryim;

				 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
				 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
				 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
				 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

				 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
				 minr = Math::Min(minr, rhoi[i, j]);
				 maxr = Math::Max(maxr, rhoi[i, j]);

				 for (i = 1; i <Nf - 1; i++)
				 {
					 j = 0;
					 rxip = x[i, j + 1] - x[i, j];
					 ryip = y[i, j + 1] - y[i, j];
					 rxim = x[i, N - 1] - x[i, j];//-x[i,j+1]+2*x[i,j];
					 ryim = y[i, N - 1] - y[i, j];//-y[i,j+1]+2*y[i,j];
					 rxkm = x[i - 1, j] - x[i, j];
					 rykm = y[i - 1, j] - y[i, j];
					 rxkp = x[i + 1, j] - x[i, j];
					 rykp = y[i + 1, j] - y[i, j];

					 rkp2 = rxkp*rxkp + rykp*rykp;
					 rkm2 = rxkm*rxkm + rykm*rykm;
					 rip2 = rxip*rxip + ryip*ryip;
					 rim2 = rxim*rxim + ryim*ryim;

					 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
					 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
					 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
					 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

					 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
					 minr = Math::Min(minr, rhoi[i, j]);
					 maxr = Math::Max(maxr, rhoi[i, j]);

					 for (j = 1; j <N - 1; j++)
					 {
						 rxip = x[i, j + 1] - x[i, j];
						 ryip = y[i, j + 1] - y[i, j];
						 rxim = x[i, j - 1] - x[i, j];
						 ryim = y[i, j - 1] - y[i, j];
						 rxkm = x[i - 1, j] - x[i, j];
						 rykm = y[i - 1, j] - y[i, j];
						 rxkp = x[i + 1, j] - x[i, j];
						 rykp = y[i + 1, j] - y[i, j];

						 rkp2 = rxkp*rxkp + rykp*rykp;
						 rkm2 = rxkm*rxkm + rykm*rykm;
						 rip2 = rxip*rxip + ryip*ryip;
						 rim2 = rxim*rxim + ryim*ryim;

						 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
						 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
						 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
						 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

						 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
						 minr = Math::Min(minr, rhoi[i, j]);
						 maxr = Math::Max(maxr, rhoi[i, j]);
					 }
					 j = N - 1;
					 rxip = x[i, 0] - x[i, j];//-x[i,j-1]+2*x[i,j];
					 ryip = y[i, 0] - y[i, j];//-y[i,j-1]+2*y[i,j];
					 rxim = x[i, j - 1] - x[i, j];
					 ryim = y[i, j - 1] - y[i, j];
					 rxkm = x[i - 1, j] - x[i, j];
					 rykm = y[i - 1, j] - y[i, j];
					 rxkp = x[i + 1, j] - x[i, j];
					 rykp = y[i + 1, j] - y[i, j];

					 rkp2 = rxkp*rxkp + rykp*rykp;
					 rkm2 = rxkm*rxkm + rykm*rykm;
					 rip2 = rxip*rxip + ryip*ryip;
					 rim2 = rxim*rxim + ryim*ryim;

					 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
					 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
					 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
					 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

					 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
					 minr = Math::Min(minr, rhoi[i, j]);
					 maxr = Math::Max(maxr, rhoi[i, j]);
				 }
				 i = Nf - 1;
				 j = 0;
				 rxip = x[i, j + 1] - x[i, j];
				 ryip = y[i, j + 1] - y[i, j];
				 rxim = x[i, N - 1] - x[i, j];//-x[i,j+1]+2*x[i,j];
				 ryim = y[i, N - 1] - y[i, j];//-y[i,j+1]+2*y[i,j];
				 rxkm = x[i - 1, j] - x[i, j];
				 rykm = y[i - 1, j] - y[i, j];
				 rxkp = x[i, j] - x[i - 1, j];
				 rykp = y[i, j] - y[i - 1, j];

				 rkp2 = rxkp*rxkp + rykp*rykp;
				 rkm2 = rxkm*rxkm + rykm*rykm;
				 rip2 = rxip*rxip + ryip*ryip;
				 rim2 = rxim*rxim + ryim*ryim;

				 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
				 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
				 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
				 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

				 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
				 minr = Math::Min(minr, rhoi[i, j]);
				 maxr = Math::Max(maxr, rhoi[i, j]);

				 for (j = 1; j <N - 1; j++)
				 {
					 rxip = x[i, j + 1] - x[i, j];
					 ryip = y[i, j + 1] - y[i, j];
					 rxim = x[i, j - 1] - x[i, j];
					 ryim = y[i, j - 1] - y[i, j];
					 rxkm = x[i - 1, j] - x[i, j];
					 rykm = y[i - 1, j] - y[i, j];
					 rxkp = x[i, j] - x[i - 1, j];
					 rykp = y[i, j] - y[i - 1, j];

					 rkp2 = rxkp*rxkp + rykp*rykp;
					 rkm2 = rxkm*rxkm + rykm*rykm;
					 rip2 = rxip*rxip + ryip*ryip;
					 rim2 = rxim*rxim + ryim*ryim;

					 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
					 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
					 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
					 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

					 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.35;
					 minr = Math::Min(minr, rhoi[i, j]);
					 maxr = Math::Max(maxr, rhoi[i, j]);
				 }
				 j = N - 1;
				 rxip = x[i, 0] - x[i, j];//-x[i,j-1]+2*x[i,j];
				 ryip = y[i, 0] - y[i, j];//-y[i,j-1]+2*y[i,j];
				 rxim = x[i, j - 1] - x[i, j];
				 ryim = y[i, j - 1] - y[i, j];
				 rxkm = x[i - 1, j] - x[i, j];
				 rykm = y[i - 1, j] - y[i, j];
				 rxkp = x[i, j] - x[i - 1, j];
				 rykp = y[i, j] - y[i - 1, j];

				 rkp2 = rxkp*rxkp + rykp*rykp;
				 rkm2 = rxkm*rxkm + rykm*rykm;
				 rip2 = rxip*rxip + ryip*ryip;
				 rim2 = rxim*rxim + ryim*ryim;

				 r_ip_kp = Math::Pow(rxip*rxkp + ryip*rykp, 2);
				 r_im_km = Math::Pow(rxim*rxkm + ryim*rykm, 2);
				 r_im_kp = Math::Pow(rxim*rxkp + ryim*rykp, 2);
				 r_ip_km = Math::Pow(rxip*rxkm + ryip*rykm, 2);

				 rhoi[i, j] = (r_ip_kp / rkp2 / rip2 + r_im_km / rim2 / rkm2 + r_im_kp / rim2 / rkp2 + r_ip_km / rip2 / rkm2)*0.25;
				 minr = Math::Min(minr, rhoi[i, j]);
				 maxr = Math::Max(maxr, rhoi[i, j]);
			 }

			 void Smooth()
			 {
				 double rxip, rxim, ryip, ryim, rxkm, rykm;
				 double alpha = Convert::ToDouble(this->ARThreshold->Text);;
				 minAR = 100000;
				 maxAR = -100000;
				 minSAR = 100000;
				 maxSAR = -100000;
				 double a, b, c, d, e, f;
				 int i, j;

				 a = b = c = d = 0;
				 e = f = 6;
				 if (this->radioButton5->Checked)
				 {
					 for (int NS = 0; NS < Convert::ToInt32(this->SIters->Text); NS++)
					 {
						 i = 0;
						 for (j = 0; j<N; j++)
						 {
							 x[i, j] = ibcx[j];
							 y[i, j] = ibcy[j];
						 }
						 for (i = 1; i<Nf; i++)
						 {

							 j = 0;
							 a = b = c = d = 0;
							 e = f = 6;
							 rxip = x[i, j + 1] - x[i, j];
							 ryip = y[i, j + 1] - y[i, j];
							 rxim = x[i, N - 1] - x[i, j];//-x[i,j+1]+2*x[i,j];
							 ryim = y[i, N - 1] - y[i, j];//-y[i,j+1]+2*y[i,j];
							 rxkm = x[i - 1, j] - x[i, j];
							 rykm = y[i - 1, j] - y[i, j];

							 ARi[i, j] = Math::Sqrt(rxkm*rxkm + rykm*rykm) / Math::Min(Math::Sqrt(rxip*rxip + ryip*ryip), Math::Sqrt(rxim*rxim + ryim*ryim));
							 minAR = Math::Min(minAR, ARi[i, j]);
							 maxAR = Math::Max(maxAR, ARi[i, j]);
							 SARi[i, j] = Math::Sqrt(i)*(Math::Max(ARi[i, j], alpha) - alpha);
							 minSAR = Math::Min(minSAR, SARi[i, j]);
							 maxSAR = Math::Max(maxSAR, SARi[i, j]);
							 if (SARi[i, j] > NS)
							 {
								 a++; b++;
								 e += 2.0 + 2.0 / ARi[i, j];
								 f += 4.0 + 2.0 / ARi[i, j];
							 }
							 x[i, j] = (a*x[i, j + 1] + b*x[i, N - 1] + e*x[i, j]) / f;
							 y[i, j] = (a*y[i, j + 1] + b*y[i, N - 1] + e*y[i, j]) / f;

							 for (j = 1; j < N - 1; j++)
							 {
								 a = b = c = d = 0;
								 e = f = 6;

								 rxip = x[i, j + 1] - x[i, j];
								 ryip = y[i, j + 1] - y[i, j];
								 rxim = x[i, j - 1] - x[i, j];
								 ryim = y[i, j - 1] - y[i, j];
								 rxkm = x[i - 1, j] - x[i, j];
								 rykm = y[i - 1, j] - y[i, j];

								 ARi[i, j] = Math::Sqrt(rxkm*rxkm + rykm*rykm) / Math::Min(Math::Sqrt(rxip*rxip + ryip*ryip), Math::Sqrt(rxim*rxim + ryim*ryim));
								 minAR = Math::Min(minAR, ARi[i, j]);
								 maxAR = Math::Max(maxAR, ARi[i, j]);
								 SARi[i, j] = Math::Sqrt(i)*(Math::Max(ARi[i, j], alpha) - alpha);
								 minSAR = Math::Min(minSAR, SARi[i, j]);
								 maxSAR = Math::Max(maxSAR, SARi[i, j]);
								 if (SARi[i, j] > NS)
								 {
									 a++; b++;
									 e += 2.0 + 2.0 / ARi[i, j];
									 f += 4.0 + 2.0 / ARi[i, j];
								 }
								 x[i, j] = (a*x[i, j + 1] + b*x[i, j - 1] + e*x[i, j]) / f;
								 y[i, j] = (a*y[i, j + 1] + b*y[i, j - 1] + e*y[i, j]) / f;
							 }
							 j = N - 1;
							 a = b = c = d = 0;
							 e = f = 6;

							 rxip = x[i, 0] - x[i, j];
							 ryip = y[i, 0] - y[i, j];
							 rxim = x[i, j - 1] - x[i, j];
							 ryim = y[i, j - 1] - y[i, j];
							 rxkm = x[i - 1, j] - x[i, j];
							 rykm = y[i - 1, j] - y[i, j];

							 ARi[i, j] = Math::Sqrt(rxkm*rxkm + rykm*rykm) / Math::Min(Math::Sqrt(rxip*rxip + ryip*ryip), Math::Sqrt(rxim*rxim + ryim*ryim));
							 minAR = Math::Min(minAR, ARi[i, j]);
							 maxAR = Math::Max(maxAR, ARi[i, j]);
							 SARi[i, j] = Math::Sqrt(i)*(Math::Max(ARi[i, j], alpha) - alpha);
							 minSAR = Math::Min(minSAR, SARi[i, j]);
							 maxSAR = Math::Max(maxSAR, SARi[i, j]);
							 if (SARi[i, j] > NS)
							 {
								 a++; b++;
								 e += 2.0 + 2.0 / ARi[i, j];
								 f += 4.0 + 2.0 / ARi[i, j];
							 }
							 x[i, j] = (a*x[i, 0] + b*x[i, j - 1] + e*x[i, j]) / f;
							 y[i, j] = (a*y[i, 0] + b*y[i, j - 1] + e*y[i, j]) / f;
						 }
						 i = Nf - 1;
						 for (j = 0; j<N; j++)
						 {
							 x[i, j] = obcx[j];
							 y[i, j] = obcy[j];
						 }
					 }
				 }
				 if (this->radioButton6->Checked)
				 {
					 for (i = 1; i<Nf - 1; i++)
					 {
						 j = 0;
						 x[i, j] = 0.25*(x[i + 1, j] + x[i - 1, j] + x[i, j + 1] + x[i, N - 1]);
						 y[i, j] = 0.25*(y[i + 1, j] + y[i - 1, j] + y[i, j + 1] + y[i, N - 1]);
						 for (j = 1; j<N - 1; j++)
						 {
							 x[i, j] = 0.25*(x[i + 1, j] + x[i - 1, j] + x[i, j + 1] + x[i, j - 1]);
							 y[i, j] = 0.25*(y[i + 1, j] + y[i - 1, j] + y[i, j + 1] + y[i, j - 1]);
						 }
						 j = N - 1;
						 x[i, j] = 0.25*(x[i + 1, j] + x[i - 1, j] + x[i, 0] + x[i, j - 1]);
						 y[i, j] = 0.25*(y[i + 1, j] + y[i - 1, j] + y[i, 0] + y[i, j - 1]);
					 }
				 }
				 if (this->radioButton7->Checked)
				 {

					 for (i = 1; i<Nf - 1; i++)
					 {
						 j = 0;
						 x[i, j] = 0.125*(x[i + 1, j] + x[i - 1, j] + x[i, j + 1] + x[i, N - 1] + x[i + 1, j + 1] + x[i - 1, N - 1] + x[i + 1, N - 1] + x[i - 1, j + 1]);
						 y[i, j] = 0.125*(y[i + 1, j] + y[i - 1, j] + y[i, j + 1] + y[i, N - 1] + y[i + 1, j + 1] + y[i - 1, N - 1] + y[i + 1, N - 1] + y[i - 1, j + 1]);
						 for (j = 1; j<N - 1; j++)
						 {
							 x[i, j] = 0.125*(x[i + 1, j] + x[i - 1, j] + x[i, j + 1] + x[i, j - 1] + x[i + 1, j + 1] + x[i - 1, j - 1] + x[i + 1, j - 1] + x[i - 1, j + 1]);
							 y[i, j] = 0.125*(y[i + 1, j] + y[i - 1, j] + y[i, j + 1] + y[i, j - 1] + y[i + 1, j + 1] + y[i - 1, j - 1] + y[i + 1, j - 1] + y[i - 1, j + 1]);
						 }
						 j = N - 1;
						 x[i, j] = 0.125*(x[i + 1, j] + x[i - 1, j] + x[i, 0] + x[i, j - 1] + x[i + 1, 0] + x[i - 1, j - 1] + x[i + 1, j - 1] + x[i - 1, 0]);
						 y[i, j] = 0.125*(y[i + 1, j] + y[i - 1, j] + y[i, 0] + y[i, j - 1] + y[i + 1, 0] + y[i - 1, j - 1] + y[i + 1, j - 1] + y[i - 1, 0]);
					 }
				 }
			 }
			 float WavelengthToRGB(int colindex, float Wavelength)
			 {
				 float gamma = 0.80f;
				 float IntensityMax = 1.0;
				 float factor;
				 float r, g, b;

				 if (Wavelength >= 380 && Wavelength<440)
				 {
					 r = -(Wavelength - 440.0f) / (440.0f - 380.0f);
					 g = 0.0f;
					 b = 1.0f;
				 }
				 else if (Wavelength >= 440 && Wavelength<490)
				 {
					 r = 0.0f;
					 g = (Wavelength - 440.0f) / (490.0f - 440.0f);
					 b = 1.0f;
				 }
				 else if (Wavelength >= 490 && Wavelength<510)
				 {
					 r = 0.0f;
					 g = 1.0f;
					 b = -(Wavelength - 510.0f) / (510.0f - 490.0f);
				 }
				 else if (Wavelength >= 510 && Wavelength<580)
				 {
					 r = (Wavelength - 510.0f) / (580.0f - 510.0f);
					 g = 1.0f;
					 b = 0.0f;
				 }
				 else if (Wavelength >= 580 && Wavelength<645)
				 {
					 r = 1.0f;
					 g = -(Wavelength - 645.0f) / (645.0f - 580.0f);
					 b = 0.0f;
				 }
				 else if (Wavelength >= 645 && Wavelength<780)
				 {
					 r = 1.0f;
					 g = 0.0f;
					 b = 0.0f;
				 }
				 else
				 {
					 r = 0.0f;
					 g = 0.0f;
					 b = 0.0f;
				 }
				 if (Wavelength >= 380 && Wavelength<420)
					 factor = 0.3f + 0.7f*(Wavelength - 380.0f) / (420.0f - 380.0f);
				 else if (Wavelength >= 420 && Wavelength<701)
					 factor = 1.0f;
				 else if (Wavelength >= 701 && Wavelength <= 780)
					 factor = 0.3f + 0.7f*(780.0f - Wavelength) / (780.0f - 700.0f);
				 else factor = 0.0f;

				 switch (colindex)
				 {
				 case 1:
					 return Adjust(r, factor, IntensityMax, gamma);
					 break;
				 case 2:
					 return Adjust(g, factor, IntensityMax, gamma);
					 break;
				 case 3:
					 return Adjust(b, factor, IntensityMax, gamma);
					 break;
				 default:
					 return 0.0f;
					 break;
				 }
			 }
			 float Adjust(float col, float Factor, float IntensityMax, float Gamma)
			 {
				 if (col == 0.0)
					 return 0.0f;
				 else return (float)(IntensityMax * Math::Pow(col * Factor, Gamma));

			 }

			 void makeColorGradient(double frequency1, double frequency2, double frequency3,
				 double phase1, double phase2, double phase3,
				 double center, double width, double len)
			 {
				 int i = 0;
				 float w1 = 440.0, w2 = 645.0;
				 for (i = 0; i<len; i++)
				 {
					 red[i] = (float)this->WavelengthToRGB(1, w1 + i*(w2 - w1) / float(len));
					 green[i] = (float)this->WavelengthToRGB(2, w1 + i*(w2 - w1) / float(len));
					 blue[i] = (float)this->WavelengthToRGB(3, w1 + i*(w2 - w1) / float(len));
				 }
			 }



			 void PlotMeshQ()
			 {
				 int i, j, l;

				 if (this->radioButton1->Checked)
				 {
					 for (i = 1; i<Nf - 1; i++)
					 {
						 glBegin(GL_LINE_LOOP);
						 for (j = 0; j<N; j++)
						 {
							 glColor3f(1.0f, 0.0f, 0.0f);
							 glVertex3d(x[i, j], y[i, j], 0.0f);
						 }
						 glEnd();
					 }

					 for (j = 0; j<N; j++)
					 {
						 glBegin(GL_LINE_STRIP);
						 for (i = 0; i<Nf; i++)
						 {
							 glColor3f(1.0f, 0.0f, 0.0f);
							 glVertex3d(x[i, j], y[i, j], 0.0f);
						 }
						 glEnd();
					 }
				 }

				 if (this->radioButton4->Checked)
				 {
					 for (i = 0; i<Nf - 1; i++)
					 {
						 for (j = 0; j<N - 1; j++)
						 {
							 glBegin(GL_QUADS);

							 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i, j] - minr) / (maxr - minr));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j], y[i, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i + 1, j] - minr) / (maxr - minr));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i + 1, j + 1] - minr) / (maxr - minr));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j + 1], y[i + 1, j + 1], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i, j + 1] - minr) / (maxr - minr));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j + 1], y[i, j + 1], 0.0f);

							 glEnd();
						 }
						 j = N - 1;
						 glBegin(GL_QUADS);

						 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i, j] - minr) / (maxr - minr));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, j], y[i, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i + 1, j] - minr) / (maxr - minr));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i + 1, 0] - minr) / (maxr - minr));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, 0], y[i + 1, 0], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(rhoi[i, 0] - minr) / (maxr - minr));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, 0], y[i, 0], 0.0f);

						 glEnd();
					 }
				 }
				 if (this->radioButton2->Checked)
				 {
					 for (i = 0; i<Nf - 1; i++)
					 {
						 for (j = 0; j<N - 1; j++)
						 {
							 glBegin(GL_QUADS);

							 l = (int)Math::Abs((ColLevel - 1)*(ARi[i, j] - minAR) / (maxAR - minAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j], y[i, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(ARi[i + 1, j] - minAR) / (maxAR - minAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(ARi[i + 1, j + 1] - minAR) / (maxAR - minAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j + 1], y[i + 1, j + 1], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(ARi[i, j + 1] - minAR) / (maxAR - minAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j + 1], y[i, j + 1], 0.0f);

							 glEnd();
						 }
						 j = N - 1;
						 glBegin(GL_QUADS);

						 l = (int)Math::Abs((ColLevel - 1)*(ARi[i, j] - minAR) / (maxAR - minAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, j], y[i, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(ARi[i + 1, j] - minAR) / (maxAR - minAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(ARi[i + 1, 0] - minAR) / (maxAR - minAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, 0], y[i + 1, 0], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(ARi[i, 0] - minAR) / (maxAR - minAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, 0], y[i, 0], 0.0f);

						 glEnd();


					 }
				 }
				 if (this->radioButton3->Checked)
				 {
					 for (i = 0; i<Nf - 1; i++)
					 {
						 for (j = 0; j<N - 1; j++)
						 {
							 glBegin(GL_QUADS);

							 l = (int)Math::Abs((ColLevel - 1)*(SARi[i, j] - minSAR) / (maxSAR - minSAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j], y[i, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(SARi[i + 1, j] - minSAR) / (maxSAR - minSAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(SARi[i + 1, j + 1] - minSAR) / (maxSAR - minSAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i + 1, j + 1], y[i + 1, j + 1], 0.0f);

							 l = (int)Math::Abs((ColLevel - 1)*(SARi[i, j + 1] - minSAR) / (maxSAR - minSAR));
							 glColor3f(red[l], green[l], blue[l]);
							 glVertex3d(x[i, j + 1], y[i, j + 1], 0.0f);

							 glEnd();
						 }
						 j = N - 1;
						 glBegin(GL_QUADS);

						 l = (int)Math::Abs((ColLevel - 1)*(SARi[i, j] - minSAR) / (maxSAR - minSAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, j], y[i, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(SARi[i + 1, j] - minSAR) / (maxSAR - minSAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, j], y[i + 1, j], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(SARi[i + 1, 0] - minSAR) / (maxSAR - minSAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i + 1, 0], y[i + 1, 0], 0.0f);

						 l = (int)Math::Abs((ColLevel - 1)*(SARi[i, 0] - minSAR) / (maxSAR - minSAR));
						 glColor3f(red[l], green[l], blue[l]);
						 glVertex3d(x[i, 0], y[i, 0], 0.0f);

						 glEnd();
					 }
				 }
				 glEndList();
			 }

			 void PlotGL(void)
			 {
				 {
					 ThisTransformation->get_Renamed(matrix);
				 }
				 glClearColor(1.0, 1.0, 1.0, 1.0);
				 glShadeModel(GL_SMOOTH);								// enable smooth shading
				 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// nice perspective calculations
				 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear screen and DepthBuffer				
				 glEnable(GL_LINE_SMOOTH);
				 glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
				 glEnable(GL_BLEND);
				 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				 glLoadIdentity();

				 glPushMatrix();                  // NEW: Prepare Dynamic Transform
				 pin_ptr<GLfloat> p = &matrix[0];
				 glMultMatrixf(p);           // NEW: Apply Dynamic Transform

				 glPolygonMode(GL_FRONT, GL_FILL);
				 glColor3f(0.8f, 0.3f, 0.1f);
				 glCallList(plot_glList1); // plot using display list 

				 //glPolygonMode(GL_FRONT, GL_LINE);
				 glColor3f(0.5f, 0.5f, 0.9f);
				 glCallList(plot_glList2); // plot using display list 

				 glPopMatrix(); // NEW: Unapply Dynamic Transform
				 glFlush();     // Flush the GL Rendering Pipeline




				 //glViewport(0, 0, width, height);

				 glPushMatrix();
				 glMatrixMode(GL_PROJECTION);
				 glLoadIdentity();
				 gluPerspective(45.0, (double)width / (double)height, 1.0, 0.0);
				 glTranslatef(0.0f, 0.0f, -12.1f);
				 glMatrixMode(GL_MODELVIEW);
				 glPopMatrix();

				 this->OpenGL1->SwapOpenGLBuffers();

			 }

#pragma region Mouse Control
			 void startDrag(Point ^MousePt)
			 {
				 //lock (matrixLock)
				 {
					 LastTransformation->set_Renamed(ThisTransformation); // Set Last Static Rotation To Last Dynamic One
				 }
				 arcBall->click(*MousePt); // Update Start Vector And Prepare For Dragging

				 mouseStartDrag = *MousePt;

			 }

			 void drag(Point ^MousePt)
			 {
				 Quat4f ^ThisQuat = gcnew Quat4f();

				 arcBall->drag(*MousePt, ThisQuat); // Update End Vector And Get Rotation As Quaternion

				 //lock (matrixLock)
				 {
					 if (isRightDrag)
					 {
						 double len = Math::Sqrt(mouseStartDrag->X * mouseStartDrag->X + mouseStartDrag->Y * mouseStartDrag->Y)
							 / Math::Sqrt(MousePt->X * MousePt->X + MousePt->Y * MousePt->Y);

						 ThisTransformation->Scale = (float)len;
						 ThisTransformation->Pan = gcnew Vector3f(0, 0, 0);
						 ThisTransformation->Rotation = gcnew Quat4f();
						 ThisTransformation->MatrixMultiply(ThisTransformation, LastTransformation);// Accumulate Last Rotation Into This One
					 }
					 else if (isLeftDrag)
					 {
						 float x = 10 * (float)(MousePt->X - mouseStartDrag->X) / (float)this->OpenGLpanel1->Width;
						 float y = 10 * (float)(-MousePt->Y + mouseStartDrag->Y) / (float)this->OpenGLpanel1->Height;
						 float z = 0.0f;

						 ThisTransformation->Pan = gcnew Vector3f(x, y, z);
						 ThisTransformation->Scale = 1.0f;
						 ThisTransformation->Rotation = gcnew Quat4f();
						 ThisTransformation->MatrixMultiply(ThisTransformation, LastTransformation);
					 }
					 else if (isMiddleDrag)
					 {
						 ThisTransformation->Pan = gcnew Vector3f(0, 0, 0);
						 ThisTransformation->Scale = 1.0f;
						 ThisTransformation->Rotation = ThisQuat;
						 ThisTransformation->MatrixMultiply(ThisTransformation, LastTransformation);
					 }
				 }
			 }

			 void glOnLeftMouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Cursor->Current = Cursors::SizeAll;
				 isLeftDrag = true;
				 mouseStartDrag = gcnew Point(e->X, e->Y);
				 this->startDrag(*mouseStartDrag);
				 this->PlotGL();
			 }

			 /// end rotation
			 void glOnLeftMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 isLeftDrag = false;
			 }
			 void glOnMouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Point ^tempAux = gcnew Point(e->X, e->Y);

				 this->drag(*tempAux);
				 this->PlotGL();

			 }
			 void glOnRightMouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Cursor->Current = Cursors::SizeNS;
				 isRightDrag = true;
				 mouseStartDrag = gcnew Point(e->X, e->Y);
				 this->startDrag(*mouseStartDrag);
				 this->PlotGL();
			 }

			 /// end pan
			 void glOnRightMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Cursor->Current = Cursors::Default;
				 isRightDrag = false;
			 }

			 /// start zoom
			 void glOnMiddleMouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Cursor->Current = Cursors::NoMove2D;
				 isMiddleDrag = true;
				 mouseStartDrag = gcnew Point(e->X, e->Y);
				 this->startDrag(mouseStartDrag);
				 this->PlotGL();
			 }

			 /// end zoom
			 void glOnMiddleMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
			 {
				 Cursor->Current = Cursors::Default;

				 isMiddleDrag = false;
			 }
			 void reset()
			 {

				 //lock (matrixLock)
				 {
					 LastTransformation->SetIdentity();                                // Reset Rotation
					 ThisTransformation->SetIdentity();                                // Reset Rotation
				 }

				 this->PlotGL();
			 }
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		InitVars();
		this->OpenGL1->InitGL();
		this->OpenGL1->SwapOpenGLBuffers();
		LastTransformation->SetIdentity(); // Reset Rotation
		ThisTransformation->SetIdentity(); // Reset Rotation
		ThisTransformation->get_Renamed(matrix);

		this->OpenGLpanel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::glOnMouseMove);

#pragma region mouse handles
		MouseControl ^mouseControl = gcnew MouseControl(this->OpenGLpanel1);
		mouseControl->AddControl(OpenGLpanel1);
		mouseControl->LeftMouseDown += gcnew MouseEventHandler(this, &Form1::glOnLeftMouseDown);
		mouseControl->LeftMouseUp += gcnew MouseEventHandler(this, &Form1::glOnLeftMouseUp);
		mouseControl->RightMouseDown += gcnew MouseEventHandler(this, &Form1::glOnRightMouseDown);
		mouseControl->RightMouseUp += gcnew MouseEventHandler(this, &Form1::glOnRightMouseUp);
		mouseControl->MiddleMouseDown += gcnew MouseEventHandler(this, &Form1::glOnMiddleMouseDown);
		mouseControl->MiddleMouseUp += gcnew MouseEventHandler(this, &Form1::glOnMiddleMouseUp);

#pragma endregion

	}
	private: System::Void OpenGL1_Load(System::Object^  sender, System::EventArgs^  e) {
		this->PlotGL();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->reset();
	}

	private: System::Void Ellipse_MinAx_Scroll(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Ellipse_RotAng_Scroll(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MeshAll_Click(System::Object^  sender, System::EventArgs^  e) {

		this->Ellipse();
		this->Mesh();
	}

	private: System::Void MeshType_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
		this->StretchLabel1->Hide();
		this->StretchLabel1_1->Hide();
		this->RES_P->Hide();
		this->RES_Q->Hide();
		this->P->Hide();
		this->Q->Hide();
		this->choice3->Hide();
		this->Scale->Hide();
		this->Interpolate->Hide();
		this->StretchLabel1->Hide();
		this->StretchLabel1_1->Hide();
		this->RES_P->Hide();
		this->RES_Q->Hide();
		this->P->Hide();
		this->Q->Hide();
		this->S3->Hide();
		this->SI_ch->Hide();
		this->a->Hide();
		this->alpha->Hide();
		this->iters->Hide();
		this->Iter->Hide();
		this->AllenScalinglabel->Hide();
		this->ST->Hide();
		this->ST1->Hide();
		this->St2->Hide();
		this->ST_2->Hide();
		this->ProgGenOut->Hide();
		this->label12->Hide();
		this->AL->Hide();
		this->S4->Hide();
		this->label11->Hide();
		this->label13->Hide();
		this->D->Hide();
		this->groupBox2->Hide();
		this->label10->Hide();
		this->AppSmooth->Visible = true;
		this->CH->Enabled = true;
		this->CHcheck->Enabled = true;
		this->CHcheck->Checked = true;

		if (!String::Compare(this->MeshType->Text, "Multi-Surface (2)"))
		{
			this->StretchLabel1->Visible = true;
			this->StretchLabel1_1->Visible = true;
			this->RES_P->Visible = true;
			this->P->Text = "0.1";
			this->RES_Q->Visible = true;
			this->P->Visible = true;
			this->Q->Visible = true;
			this->MeshAll->Visible = true;
			//this->IBCMesh->Text = "300";
			//this->AppSmooth->Hide();
		}
		if (!String::Compare(this->MeshType->Text, "Multi-Surface (3)"))
		{
			this->StretchLabel1->Visible = true;
			this->StretchLabel1_1->Visible = true;
			this->RES_P->Visible = true;
			this->P->Text = "0.1";
			this->RES_Q->Visible = true;
			this->P->Visible = true;
			this->Q->Visible = true;
			this->choice3->Visible = true;
			this->Scale->Visible = true;
			this->Interpolate->Visible = true;
			this->S3->Visible = true;
			this->MeshAll->Visible = true;
			this->SI_ch->Visible = true;
			//this->IBCMesh->Text = "300";
			this->ProgGenOut->Visible = true;
			this->label13->Visible = true;
			this->D->Visible = true;
			this->ProgGenOut->Checked = true;
			this->D->Text = "1.0";
			this->groupBox2->Visible = true;
			//this->AppSmooth->Hide();
		}

		if (!String::Compare(this->MeshType->Text, "Elliptic PDE's"))
		{
			this->iters->Visible = true;
			this->Iter->Visible = true;
			this->MeshAll->Visible = true;
			this->IBCMesh->Text = "100";
			this->AppSmooth->Hide();
			this->AppSmooth->Checked = false;
			this->Siter->Hide();
			this->SIters->Hide();
			this->ArThres->Hide();
			this->ARThreshold->Hide();
			this->CH->Enabled = false;
			this->CHcheck->Checked = false;
			this->CHcheck->Enabled = false;
		}
		if (!String::Compare(this->MeshType->Text, "Allen's TFI (1) (recommended)") || !String::Compare(this->MeshType->Text, "Allen's TFI (2)"))
		{
			this->AllenScalinglabel->Visible = true;
			this->ST->Visible = true;
			this->ST1->Visible = true;
			this->St2->Visible = true;
			this->ST_2->Visible = true;
			this->MeshAll->Visible = true;
			//this->IBCMesh->Text = "300";
			this->D->Text = "1.0";
			this->label13->Visible = true;
			this->D->Visible = true;
			this->groupBox2->Visible = true;
		}
		if (!String::Compare(this->MeshType->Text, "Multi-Surface (4)"))
		{
			this->StretchLabel1->Visible = true;
			this->StretchLabel1_1->Visible = true;
			this->RES_P->Visible = true;
			this->RES_Q->Visible = true;
			this->P->Visible = true;
			this->Q->Visible = true;
			//this->choice3->Visible = true;
			this->Scale->Visible = true;
			this->Interpolate->Visible = true;
			//this->S3->Visible = true;
			this->MeshAll->Visible = true;
			//this->SI_ch->Visible = true;
			//this->IBCMesh->Text = "300";
			this->ProgGenOut->Visible = true;
			this->label12->Visible = true;
			this->label12->Text = "Parameter Aw";
			this->AL->Visible = true;
			//this->S4->Visible = true;
			//this->label11->Visible = true;
			this->label13->Visible = true;
			this->D->Visible = true;
			this->D->Text = "1.0";
			this->P->Text = "0.1";
			this->AL->Text = "0.65";
			this->ProgGenOut->Checked = true;
			this->groupBox2->Visible = true;
			//this->label10->Visible = true;
		}
	}

	private: System::Void Scale_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->SI_ch->Text = "> 1.0";
		this->S3->Text = "1.1";
		if (!String::Compare(this->MeshType->Text, "Multi-Surface (4) (recommended)"))
		{
			this->label10->Text = "< 1.0";
			this->S4->Text = "0.996";
		}
	}
	private: System::Void Interpolate_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
		this->SI_ch->Text = "< 1.0";
		this->S3->Text = "0.9";
		if (!String::Compare(this->MeshType->Text, "Multi-Surface (4) (recommended)"))
		{
			this->label10->Text = "< 1.0";
			this->S4->Text = "0.996";
		}
	}
	private: System::Void AppSmooth_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->AppSmooth->Checked)
		{
			this->ArThres->Visible = true;
			this->ARThreshold->Visible = true;
			this->Siter->Visible = true;
			this->SIters->Visible = true;
			this->radioButton2->Visible = true;
			this->radioButton3->Visible = true;
			this->groupBox3->Visible = true;
			this->radioButton5->Checked = true;
		}
		else
		{
			this->ArThres->Hide();
			this->ARThreshold->Hide();
			this->Siter->Hide();
			this->SIters->Hide();
			this->radioButton2->Hide();
			this->radioButton3->Hide();
			this->groupBox3->Hide();
		}

	}
	private: System::Void OpenGL1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {
		Drawing::Size ^s = this->OpenGLpanel1->Size;
		height = s->Height;
		width = s->Width;

		glShadeModel(GL_SMOOTH);								// enable smooth shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);					// black background
		glClearDepth(1.0f);										// depth buffer setup
		glEnable(GL_DEPTH_TEST);								// enables depth testing
		glDepthFunc(GL_LEQUAL);								// type of depth testing
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// nice perspective calculations

		glViewport(0, 0, width, height);

		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(25.0, (double)width / (double)height, 1.0, 15.0);
		glTranslatef(0.0f, 0.0f, -4.0f);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

#pragma region blending
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);							// Full Brightness.  50% Alpha
		glBlendFunc(GL_SRC_COLOR, GL_ONE);						// Set The Blending Function For Translucency
		glEnable(GL_BLEND);			// Turn Blending On
		glDisable(GL_DEPTH_TEST);		// Turn Depth Testing Off
#pragma endregion 

		arcBall->setBounds((float)width, (float)height); // Update mouse bounds for arcball
		this->PlotGL();
	}
	private: System::Void Form1_SizeChanged(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void progressBar1_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->saveFileDialog1->ShowDialog();
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		System::Windows::Forms::MessageBox::Show("Grid Generation of Ellipse:\n\n" +
			"Meshhing is done using Multi Surface Methods, Transfinite  Interpolation\n" +
			"and by  Solving  Elliptic PDE's.  You  must  first  specify the scheme in the\n" +
			"drop down menu strip and also edit the values as per your choice or you\n" +
			"can retain the default ones. Clustering is not perfect.\n\n" +
			"Using Mouse in Graphics Window:\n\n" +
			"1. Pan      : Hold down the Left Mouse Button and drag the mouse.\n" +
			"2. Zoom  : Hold down the Right Mouse Button and drag the mouse.\n" +
			"3. Rotate : Hold down the Middle Mouse Button and drag the mouse.\n\n\n\n" +
			"Made By:\n\tRavinder Singh, ravi_29_12@hotmail.com\n\n"+
			"Licensing : Apache License Version 2.0"
			, "Instructions on using this software");
		//System::Windows::Forms::Form ^f = gcnew System::Windows::Forms::Form;
		//f->FormBorderStyle = 
		//f->ShowDialog();
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		System::String^ fname = saveFileDialog1->FileName;
		StreamWriter^ pwriter = gcnew StreamWriter(fname);
		pwriter->WriteLine("TITLE = \"RS0096 Mesh Quality File\"");
		pwriter->WriteLine("VARIABLES = \"X\" \"Y\" \"Rho\"" + (this->AppSmooth->Checked ? " \"AR\" \"SAR\"" : "\n"));
		pwriter->WriteLine("ZONE");
		pwriter->WriteLine("I = " + Convert::ToString(N + 1) + ", J = " + Convert::ToString(Nf));//k=1
		pwriter->WriteLine("DATAPACKING = POINT");

		int i, j;
		for (i = 0; i<Nf; i++)
		{
			for (j = 0; j<N; j++)
				pwriter->WriteLine(Convert::ToString(x[i, j]) + " " + Convert::ToString(y[i, j]) + " " + Convert::ToString(rhoi[i, j]) + (this->AppSmooth->Checked ? " " + Convert::ToString(ARi[i, j]) + " " + Convert::ToString(SARi[i, j]) : "\n"));
			pwriter->WriteLine(Convert::ToString(x[i, 0]) + " " + Convert::ToString(y[i, 0]) + " " + Convert::ToString(rhoi[i, 0]) + (this->AppSmooth->Checked ? " " + Convert::ToString(ARi[i, 0]) + " " + Convert::ToString(SARi[i, 0]) : "\n"));
		}


		pwriter->Close();
	}
	private: System::Void choice3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void S3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void radioButton5_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->ProgGenOut->Checked)
		{
			this->choice3->Hide();
			this->label11->Hide();
			this->label10->Hide();
			this->S3->Hide();
			this->S4->Hide();
			this->SI_ch->Hide();
			this->groupBox2->Visible = true;
		}
		else
		{
			this->choice3->Visible = true;
			this->S3->Visible = true;
			this->SI_ch->Visible = true;
			this->groupBox2->Hide();
			if (!String::Compare(this->MeshType->Text, "Multi-Surface (4) (recommended)"))
			{
				this->label11->Visible = true;
				this->S4->Visible = true;
				this->label10->Visible = true;
			}

		}
	}
	private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void simpleOpenGlControl1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		this->saveImageDialog2->ShowDialog();
	}
	private: System::Void saveImageDialog2_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		System::Drawing::Bitmap^ bmp = gcnew System::Drawing::Bitmap(this->OpenGLpanel1->Width, this->OpenGLpanel1->Height, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
		System::Drawing::Rectangle^ r = gcnew System::Drawing::Rectangle(0, 0, this->OpenGLpanel1->Width, this->OpenGLpanel1->Height);
		System::Drawing::Imaging::BitmapData^ data;
		System::IO::FileStream ^ fs;
		fs = (System::IO::FileStream ^)this->saveImageDialog2->OpenFile();
		System::String ^fname = this->saveImageDialog2->FileName;
		data = bmp->LockBits(*r, System::Drawing::Imaging::ImageLockMode::WriteOnly, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
		glReadPixels(0, 0, this->OpenGLpanel1->Width, this->OpenGLpanel1->Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, (void*)data->Scan0);
		bmp->UnlockBits(data);
		bmp->RotateFlip(RotateFlipType::RotateNoneFlipY);
		switch (saveImageDialog2->FilterIndex)
		{
		case 1:
			bmp->Save(fs, System::Drawing::Imaging::ImageFormat::Bmp);
			break;
		case 2:
			bmp->Save(fs, System::Drawing::Imaging::ImageFormat::Jpeg);
			break;
		case 3:
			bmp->Save(fs, System::Drawing::Imaging::ImageFormat::Gif);
			break;
		}

		fs->Close();
		//delete(fs);
		delete(bmp);
	}
	private: System::Void OpenGL1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
		this->Cursor = Cursors::Cross;
	}
	private: System::Void OpenGL1_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
		this->Cursor = Cursors::Default;
	}
	private: System::Void CHcheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->CHcheck->Checked)
		{
			this->CH->Enabled = true;
		}
		else
		{
			this->CH->Enabled = false;
		}
	}
	private: System::Void Clustercheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->Clustercheck->Checked)
		{
			this->Mode->Enabled = true;
		}
		else
		{
			this->Mode->Enabled = false;
		}
	}
	private: System::Void radioButton5_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
		if (this->radioButton5->Checked)
		{
			this->ArThres->Visible = true;
			this->ArThres->Text = "Aspect Ratio Threshold";
			this->Siter->Visible = true;
			this->ARThreshold->Visible = true;
			this->ARThreshold->Text = "0.1";
			this->SIters->Visible = true;
		}
		else
		{
			this->ArThres->Hide();
			this->Siter->Hide();
			this->ARThreshold->Hide();
			this->SIters->Hide();
		}
	}
	private: System::Void radioButton6_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->radioButton6->Checked)
		{
			this->radioButton2->Hide();
			this->radioButton3->Hide();
			this->label16->Visible = true;
		}
		else
		{
			this->radioButton2->Visible = true;
			this->radioButton3->Visible = true;
			this->label16->Hide();
		}
	}

	private: System::Void radioButton7_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->radioButton7->Checked)
		{
			this->radioButton2->Hide();
			this->radioButton3->Hide();
			this->label16->Visible = true;
		}
		else
		{
			this->radioButton2->Visible = true;
			this->radioButton3->Visible = true;
			this->label16->Hide();
		}
	}
	};
}

