
#include "Form1.h"

namespace EllipseCfdMesh
{
	using namespace System;
	using namespace System::Windows::Forms;

	[System::Runtime::InteropServices::DllImport("user32.dll")]
	bool SetProcessDPIAware();

	[STAThreadAttribute]
	void Main(array<System::String ^> ^args)
	{
		OperatingSystem^ osv = Environment::OSVersion;
		Version^ ver = osv->Version;
		if (ver->Major >= 6)
			SetProcessDPIAware();

		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Form1 f1;
		Application::Run(% f1);
	}

}

