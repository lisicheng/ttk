#include "framework/application.h"
#include "framework/document.h"
#include "common.h"

TUid CApplication::AppDllUid() const
{
	return KApplicationUid;
}

CApaDocument* CApplication::CreateDocumentL()
{
	return new(ELeave) CDocument(*this);
}

