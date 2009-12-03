#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <eikdoc.h> // CEikDocument

class CDocument : public CEikDocument
{
public:
	~CDocument();
	static CDocument* NewL(CEikApplication& aApp);
private:
	CDocument(CEikApplication& aApp);
private:
	CEikAppUi* CreateAppUiL();
};

#endif // DOCUMENT_H
