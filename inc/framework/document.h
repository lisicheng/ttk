#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <eikdoc.h> // CEikDocument

class CDocument : public CEikDocument
{
public:
	CDocument(CEikApplication& aApp);
	~CDocument();
private:
	CEikAppUi* CreateAppUiL();
};

#endif // DOCUMENT_H
