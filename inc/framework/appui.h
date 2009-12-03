#ifndef APPUI_H
#define APPUI_H

#include <eikappui.h> // CEikAppUi

class CWsClient;

class CAppUi : public CEikAppUi
{
public:
	~CAppUi();
private:
	void ConstructL();
private:
	void HandleCommandL(TInt aCommand);
private:
	CWsClient* iClient;
};

#endif // APPUI_H
