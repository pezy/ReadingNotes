#import "C:\Program files\Common Files\System\Ado\msado27.tlb" \
	no_namespace rename("EOF", "EndOfFile")

#include <oledb.h>
#include <stdio.h>
#include <conio.h>
#include <icrsint.h>

void TESTHR(HRESULT _hr) { if FAILED(_hr) throw(_hr); }

void PrintProviderError(_ConnectionPtr pConnection) {
	// Print Provider Errors from Connection object.
	// pErr is a record object in the Connection's Error collection.
	ErrorPtr pErr = NULL;

	if ((pConnection->Errors->Count) > 0) {
		long nCount = pConnection->Errors->Count;
		// Collection ranges from 0 to nCount -1.
		for (long i = 0; i < nCount; i++) {
			pErr = pConnection->Errors->GetItem(i);
			printf("\t Error number: %x\t%s", pErr->Number, pErr->Description);
		}
	}
}

void PrintComError(_com_error &e) {
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	// Print COM errors. 
	printf("Error\n");
	printf("\tCode = %08lx\n", e.Error());
	printf("\tCode meaning = %s\n", e.ErrorMessage());
	printf("\tSource = %s\n", (LPCSTR)bstrSource);
	printf("\tDescription = %s\n", (LPCSTR)bstrDescription);
}

void OpenX() {
	_ConnectionPtr pConnection = NULL;
	_RecordsetPtr pRstDBName = NULL;
	_RecordsetPtr pRstValue = NULL;
	_bstr_t strCnn("Provider='sqloledb'; Data Source='WIN2000';");
	//Initial Catalog='MAINLOGSQL_NEW';

	try {
		// open connection and record set
		TESTHR(pConnection.CreateInstance(__uuidof(Connection)));
		pConnection->Open(strCnn, "sa", "sa", adConnectUnspecified);

		TESTHR(pRstDBName.CreateInstance(__uuidof(Recordset)));
		pRstDBName->Open("EXEC sp_databases", _variant_t((IDispatch *)pConnection, true),
			adOpenStatic, adLockReadOnly, adCmdText);

		while (!(pRstDBName->EndOfFile)) {
			// Convert variant string to convertable string type.
			_bstr_t  bstrDBName = pRstDBName->Fields->GetItem("DATABASE_NAME")->Value;
			printf("\t%s\n", (LPCSTR)bstrDBName);

			pRstDBName->MoveNext();
		}

		pConnection->DefaultDatabase = "MAINLOGSQL_NEW";
		TESTHR(pRstValue.CreateInstance(__uuidof(Recordset)));
		pRstValue->Open("SELECT TOP 1 * FROM GTB WHERE(WID = 'q74')",
			_variant_t((IDispatch *)pConnection, true),
			adOpenStatic, adLockReadOnly, adCmdText);

		while (!(pRstValue->EndOfFile)) {
			// Convert variant string to convertable string type.
			_bstr_t  bstrValue = pRstValue->Fields->GetItem("DATE")->Value;
			printf("\t%s\n", (LPCSTR)bstrValue);

			pRstValue->MoveNext();
		}

	}
	catch (_com_error &e) {
		// Display errors, if any. Pass a connection pointer accessed from the Connection.
		PrintProviderError(pConnection);
		PrintComError(e);
	}

	if (pRstDBName)
		if (pRstDBName->State == adStateOpen)
			pRstDBName->Close();
	if (pRstValue)
		if (pRstValue->State == adStateOpen)
			pRstValue->Close();
	if (pConnection)
		if (pConnection->State == adStateOpen)
			pConnection->Close();
}

int main() {
	if (FAILED(::CoInitialize(NULL)))
		return -1;

	OpenX();
	::CoUninitialize();
}