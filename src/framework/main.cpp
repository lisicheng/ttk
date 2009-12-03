#include "framework/application.h"

EXPORT_C CApaApplication* NewApplication()
{
	return new CApplication();
}

GLDEF_C TInt E32Dll(TDllReason)
{
	return KErrNone;
}

