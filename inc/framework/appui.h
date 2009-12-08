#ifndef APPUI_H
#define APPUI_H

#include <eikappui.h> // CEikAppUi

class CWsClient;

class CAppUi : public CEikAppUi
{
public:
	virtual ~CAppUi();
private:
	void ConstructL();
private: /* from CEikAppUi */
	void HandleCommandL(TInt aCommand);
private:
	CWsClient* iClient;
	CWidget* iRoot;
};

#endif // APPUI_H
