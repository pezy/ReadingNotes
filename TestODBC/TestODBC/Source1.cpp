// SQLColumns_Function.cpp
// compile with: ODBC32.lib
#include <windows.h>
#include <sqlext.h>
#define STR_LEN 128 + 1
#define REM_LEN 254 + 1

// Declare buffers for result set data
SQLCHAR szSchema[STR_LEN];
SQLCHAR szCatalog[STR_LEN];
SQLCHAR szColumnName[STR_LEN];
SQLCHAR szTableName[STR_LEN];
SQLCHAR szTypeName[STR_LEN];
SQLCHAR szRemarks[REM_LEN];
SQLCHAR szColumnDefault[STR_LEN];
SQLCHAR szIsNullable[STR_LEN];

SQLINTEGER ColumnSize;
SQLINTEGER BufferLength;
SQLINTEGER CharOctetLength;
SQLINTEGER OrdinalPosition;

SQLSMALLINT DataType;
SQLSMALLINT DecimalDigits;
SQLSMALLINT NumPrecRadix;
SQLSMALLINT Nullable;
SQLSMALLINT SQLDataType;
SQLSMALLINT DatetimeSubtypeCode;

SQLHSTMT hstmt = NULL;

// Declare buffers for bytes available to return
SQLINTEGER cbCatalog;
SQLINTEGER cbSchema;
SQLINTEGER cbTableName;
SQLINTEGER cbColumnName;
SQLINTEGER cbDataType;
SQLINTEGER cbTypeName;
SQLINTEGER cbColumnSize;
SQLLEN cbBufferLength;
SQLINTEGER cbDecimalDigits;
SQLINTEGER cbNumPrecRadix;
SQLINTEGER cbNullable;
SQLINTEGER cbRemarks;
SQLINTEGER cbColumnDefault;
SQLINTEGER cbSQLDataType;
SQLINTEGER cbDatetimeSubtypeCode;
SQLINTEGER cbCharOctetLength;
SQLINTEGER cbOrdinalPosition;
SQLINTEGER cbIsNullable;

int main() {
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt = 0;
	SQLRETURN retcode;

	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	retcode = SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	retcode = SQLConnectA(hdbc, (SQLCHAR*) "Northwind", SQL_NTS, (SQLCHAR*)NULL, 0, NULL, 0);
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	retcode = SQLColumnsA(hstmt, NULL, 0, NULL, 0, (SQLCHAR*)"CUSTOMERS", SQL_NTS, NULL, 0);

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		// Bind columns in result set to buffers
		SQLBindCol(hstmt, 1, SQL_C_CHAR, szCatalog, STR_LEN, &cbCatalog);
		SQLBindCol(hstmt, 2, SQL_C_CHAR, szSchema, STR_LEN, &cbSchema);
		SQLBindCol(hstmt, 3, SQL_C_CHAR, szTableName, STR_LEN, &cbTableName);
		SQLBindCol(hstmt, 4, SQL_C_CHAR, szColumnName, STR_LEN, &cbColumnName);
		SQLBindCol(hstmt, 5, SQL_C_SSHORT, &DataType, 0, &cbDataType);
		SQLBindCol(hstmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, &cbTypeName);
		SQLBindCol(hstmt, 7, SQL_C_SLONG, &ColumnSize, 0, &cbColumnSize);
		SQLBindCol(hstmt, 8, SQL_C_SLONG, &BufferLength, 0, &cbBufferLength);
		SQLBindCol(hstmt, 9, SQL_C_SSHORT, &DecimalDigits, 0, &cbDecimalDigits);
		SQLBindCol(hstmt, 10, SQL_C_SSHORT, &NumPrecRadix, 0, &cbNumPrecRadix);
		SQLBindCol(hstmt, 11, SQL_C_SSHORT, &Nullable, 0, &cbNullable);
		SQLBindCol(hstmt, 12, SQL_C_CHAR, szRemarks, REM_LEN, &cbRemarks);
		SQLBindCol(hstmt, 13, SQL_C_CHAR, szColumnDefault, STR_LEN, &cbColumnDefault);
		SQLBindCol(hstmt, 14, SQL_C_SSHORT, &SQLDataType, 0, &cbSQLDataType);
		SQLBindCol(hstmt, 15, SQL_C_SSHORT, &DatetimeSubtypeCode, 0, &cbDatetimeSubtypeCode);
		SQLBindCol(hstmt, 16, SQL_C_SLONG, &CharOctetLength, 0, &cbCharOctetLength);
		SQLBindCol(hstmt, 17, SQL_C_SLONG, &OrdinalPosition, 0, &cbOrdinalPosition);
		SQLBindCol(hstmt, 18, SQL_C_CHAR, szIsNullable, STR_LEN, &cbIsNullable);

		while (SQL_SUCCESS == retcode) {
			retcode = SQLFetch(hstmt);
			/*
			if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
			0;   // show_error();
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			0;   // Process fetched data
			else
			break;
			*/
		}
	}
}