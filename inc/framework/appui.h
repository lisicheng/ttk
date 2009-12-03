#ifndef APPUI_H
#define APPUI_H

#include <eikappui.h> // CEikAppUi

class CWsClient;

class CAppUi : public CEikAppUi
{
public:
	void ConstructL();
	~CAppUi();
private:
	void HandleCommandL(TInt aCommand);
private:
	CWsClient* iClient;
};

#endif // APPUI_H
