///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2009  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "postgres.column.factory.hpp"
#include "postgres.oid.hpp"
#include "postgres.results.column.hpp"

using std::cout;
using std::cerr;
using std::endl;
using namespace postgres;

PostgresColumnFactory::PostgresColumnFactory(const PGresult *res): res_(res) {}

PostgresResultColumn* PostgresColumnFactory::createColumn(const int i) const {
  //cout << "OID number: " << PQftype(res_,i) << endl;
  
  // first switch is for text representation
  if(PQfformat(res_,i) == 0) {
    switch(static_cast<pg_oidT>(PQftype(res_,i))) {
    case INT4OID:
    case INT8OID:
    case OIDOID:
      return new int_char(res_, i);
    case FLOAT4OID:
    case FLOAT8OID:
      return new float_char(res_, i);
    case DATEOID:
      return new date_char(res_, i);
    case VARCHAROID:
    case TEXTOID:
    case CHAROID:
    case BPCHAROID:
      return new text_char(res_, i);
    case TIMESTAMPOID:
      return new TIMESTAMPOID_char(res_, i);
    case BOOLOID:
      return new BOOLOID_char(res_, i);
    default:
      cerr << "conversion not supported using null conversion for column number: " << i << endl;
      cerr << "native oid value: " << PQftype(res_,i) << endl;
      return new defaultResultColumn(res_, i);
    }
  } else {
    switch(static_cast<pg_oidT>(PQftype(res_,i))) {
    case INT4OID:
      return new INT4OID_binary(res_,i);
    case DATEOID:
      return new DATEOID_binary(res_,i);
    case FLOAT8OID:
      return new FLOAT8OID_binary(res_,i);
    case BOOLOID:
      return new BOOLOID_binary(res_,i);
    case VARCHAROID:
    case TEXTOID:
    case CHAROID:
    case BPCHAROID:
      return new text_char(res_, i);
    case TIMESTAMPOID:
    case TIMESTAMPTZOID:
      return new TIMESTAMPOID_binary(res_, i);
    default:
      cerr << "conversion not supported using null conversion for column number: " << i << endl;
      cerr << "native oid value: " << PQftype(res_,i) << endl;
      return new defaultResultColumn(res_, i);
    }
  }
}

void PostgresColumnFactory::init(std::vector<QueryResultColumn*>& ans) const {
  const int ncols = PQnfields(res_);
  for(int i = 0; i < ncols; i++) {
    //cout << "PostgresColumnFactory: init column: " << i << endl;
    ans.push_back(createColumn(i));
  }
}

