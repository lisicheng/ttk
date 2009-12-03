#ifndef APPLICATION_H
#define APPLICATION_H

#include <eikapp.h> // CEikApplication

class CApplication : public CEikApplication
{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
};

#endif // APPLICATION_H
