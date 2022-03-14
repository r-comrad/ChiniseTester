#ifndef DATABASE_HPP
#define DATABASE_HPP

//--------------------------------------------------------------------------------
//						SQLLITE INTERFACE DECLARATION
//--------------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <vector>

#include "sqllite/sqlite3.h"

#include "domain/domain.hpp"
#include "domain/my_strings.hpp"
#include "domain/errors.hpp"
#include "domain/pair.hpp"

//--------------------------------------------------------------------------------

typedef sqlite3 Base;
typedef sqlite3_stmt Statement;

class Database
{
public:
	Database(str_const_ref aPath);
	virtual ~Database();

	//----------------------------------------------------------------------------
	//							DATABASE QUERY FUNCTIONS
	//----------------------------------------------------------------------------

	/*
	\brief Prepare the sqlite SELECT statement.
	\param aTableName The name of the table for data selection.
	\param aColum The names of the columns to be selected. 
	If empty, select all columns.
	\param aConditon Specifies the conditions for the selection request. 
	If empty, then no conditions are used.
	\param aStatementID Number of statment array cell to use. 
	To simultaneously execute multiple queries, you must use 
	different cells for each query.
	If empty, the first cell (#0) is used.
	*/
	void select(str_const_ref aTableName, str_val aColum = "", 
		str_val aConditon = "", int aStatementID = 0);

	/*
	\brief Prepare the sqlite UPDATE statement.
	\param aTableName The name of the table for data update.
	\param aValue New value for the sqlite table cell.
	\param aConditon Specifies the conditions for data update.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use 
	different cells for each query.
	If empty, the first cell (#0) is used.
	*/
	void update(str_const_ref aTableName, str_const_ref aValue, 
		str_const_ref aConditon, int aStatementID = 0);

	/*
	\brief Close the selected statment.
	\param aStatementID The number of the statment array cell 
	that should be closed.
	If empty, the first cell (#0) is used.
	*/
	void closeStatment(int aStatementID = 0);

	/*
	\brief Make a step for the selected statment.
	\param aStatementID The number of the statment array cell
	that should make a step.
	If empty, the first cell (#0) is used.
	\return SQLLite step status.
	*/
	int	step(int aStatementID = 0);

	//----------------------------------------------------------------------------
	//						INFORMATION RECEIVING FUNCTIONS
	//----------------------------------------------------------------------------

	/*
	\brief Gets UTF-8 string from colum of current row. The current line 
	defined by the statement step.
	\param aColumNumber The number of the column with string to get.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use
	different cells for each query.
	If empty, the first cell (#0) is used.
	\return Pointer to unt-8 string from specidied cell.
	*/
	const unsigned char* getTextFromRow(int aColumNumber, int aStatementID = 0);

	/*
	\brief Gets UTF-16 string from colum of current row. The current line
	defined by the statement step.
	\param aColumNumber The number of the column with string to get.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use
	different cells for each query.
	If empty, the first cell (#0) is used.
	\return Pointer to unt-8 string from specidied cell.
	*/
	const void* getText16FromRow(int aColumNumber, int aStatementID = 0);

	/*
	\brief Gets integer from colum of current row. The current line
	defined by the statement step.
	\param aColumNumber The number of the column with number to get.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use
	different cells for each query.
	If empty, the first cell (#0) is used.
	\return Number from specidied cell.
	*/
	int getIntFromRow(int aColumNumber, int aStatementID = 0);

	/*
	\brief Gets large nteger from colum of current row. The current line
	defined by the statement step.
	\param aColumNumber The number of the column with number to get.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use
	different cells for each query.
	If empty, the first cell (#0) is used.
	\return Number from specidied cell.
	*/
	sint_64 getInt64FromRow(int aColumNumber, int aStatementID = 0);

	//----------------------------------------------------------------------------

	/*
	\brief Gets Integer from colum of current row. The current line
	defined by the statement step.
	\param aColumNumber The number of the column with number to get.
	\param aStatementID Number of statment array cell to use.
	To simultaneously execute multiple queries, you must use
	different cells for each query.
	If empty, the first cell (#0) is used.
	\return Number from specidied cell.
	*/
	char* toAscii(const unsigned char* input);

private:
	Base* mBase;
	std::vector<Statement*> mStatement;

	void prepare(str_const_ref aStatment, int aStatementID);
};

//--------------------------------------------------------------------------------

#endif // !DATABASE_HPP