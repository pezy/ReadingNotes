// SQLTables.cpp
// compile with: user32.lib odbc32.lib
#include <windows.h>
#include <sqlext.h>
#include <strsafe.h>

// simple helper functions
int MySQLSuccess(SQLRETURN rc) {
	return (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO);
}

struct DataBinding {
	SQLSMALLINT TargetType;
	SQLPOINTER TargetValuePtr;
	SQLINTEGER BufferLength;
	SQLLEN StrLen_or_Ind;
};

void printCatalog(const struct DataBinding* catalogResult) {
	if (catalogResult[0].StrLen_or_Ind != SQL_NULL_DATA)
		printf("Catalog Name = %s\n", (char *)catalogResult[0].TargetValuePtr);
}

void printTables(const struct DataBinding* catalogResult) {
	if (catalogResult[2].StrLen_or_Ind != SQL_NULL_DATA)
		printf("Table Name = %s\n", (char *)catalogResult[2].TargetValuePtr);
}

void printColumns(const struct DataBinding* catalogResult) {
	if (catalogResult[3].StrLen_or_Ind != SQL_NULL_DATA)
		printf("Columns Name = %s\n", (char *)catalogResult[3].TargetValuePtr);
}

// remember to disconnect and free memory, and free statements and handles
int main() {
	int bufferSize = 1024, i, numCols = 5;
	struct DataBinding* catalogResult = (struct DataBinding*) malloc(numCols * sizeof(struct DataBinding));
	wchar_t* dbName = (wchar_t *)malloc(sizeof(wchar_t)*bufferSize);
	wchar_t* userName = (wchar_t *)malloc(sizeof(wchar_t)*bufferSize);

	// declare and initialize the environment, connection, statement handles
	SQLHENV henv = NULL;   // Environment   
	SQLHDBC hdbc = NULL;   // Connection handle
	SQLHSTMT hstmt = NULL;   // Statement handle

	SQLRETURN retCode;
	HWND desktopHandle = GetDesktopWindow();   // desktop's window handle
	SQLWCHAR connStrbuffer[1024];
	SQLSMALLINT connStrBufferLen;

	retCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	retCode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, -1);
	retCode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	retCode = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)10, 0);
	retCode = SQLDriverConnectA(hdbc, desktopHandle, (SQLCHAR*)"DSN=CPS;UID=sa;PWD=sa", SQL_NTS, (SQLCHAR*)connStrbuffer, 1024 + 1, &connStrBufferLen, SQL_DRIVER_COMPLETE);
	retCode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	retCode = SQLGetInfo(hdbc, SQL_DATABASE_NAME, dbName, (SQLSMALLINT)bufferSize, (SQLSMALLINT *)&bufferSize);
	retCode = SQLGetInfo(hdbc, SQL_USER_NAME, userName, (SQLSMALLINT)bufferSize, (SQLSMALLINT *)&bufferSize);

	bufferSize = 1024;

	// allocate memory for the binding
	// free this memory when done
	for (i = 0; i < numCols; i++) {
		catalogResult[i].TargetType = SQL_C_CHAR;
		catalogResult[i].BufferLength = (bufferSize + 1);
		catalogResult[i].TargetValuePtr = malloc(sizeof(unsigned char)*catalogResult[i].BufferLength);
	}

	// setup the binding (can be used even if the statement is closed by closeStatementHandle)
	for (i = 0; i < numCols; i++)
		retCode = SQLBindCol(hstmt, (SQLUSMALLINT)i + 1, catalogResult[i].TargetType, catalogResult[i].TargetValuePtr, catalogResult[i].BufferLength, &(catalogResult[i].StrLen_or_Ind));

	// all catalogs query
	/*printf("A list of names of all catalogs\n");
	retCode = SQLTablesA(hstmt, (SQLCHAR*)SQL_ALL_CATALOGS, SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS);
	for (retCode = SQLFetch(hstmt); MySQLSuccess(retCode); retCode = SQLFetch(hstmt))
		printCatalog(catalogResult);*/
	
	printf("A list of names of all Tables\n");
	retCode = SQLTables(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
	for (retCode = SQLFetch(hstmt); MySQLSuccess(retCode); retCode = SQLFetch(hstmt)) {
		printTables(catalogResult);
	}

	/*printf("A list of names of all Columns\n");
	retCode = SQLColumns(hstmt, NULL, 0, NULL, 0, (SQLWCHAR*)L"BITR", SQL_NTS, NULL, 0);
	for (retCode = SQLFetch(hstmt); MySQLSuccess(retCode); retCode = SQLFetch(hstmt))
		printColumns(catalogResult);*/
}