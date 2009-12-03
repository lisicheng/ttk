#ifndef APPLICATION_H
#define APPLICATION_H

#include <eikapp.h> // CEikApplication

class CApplication : public CEikApplication
{
private:
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
};

#endif // APPLICATION_H
