#include "framework/document.h"
#include "framework/appui.h"

CDocument::CDocument(CEikApplication& aApp)
		: CEikDocument(aApp)
{
}

CEikAppUi* CDocument::CreateAppUiL()
{
	return new(ELeave) CAppUi();
}

CDocument::~CDocument()
{
}

