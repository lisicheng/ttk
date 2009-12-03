#include "framework/application.h"

EXPORT_C CApaApplication* NewApplication()
{
	return new CApplication();
}

#ifdef EKA2
#else
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
{
	return KErrNone;
}
#endif
