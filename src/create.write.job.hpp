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

#ifndef CREATE_WRITE_JOB_HPP
#define CREATE_WRITE_JOB_HPP

#include <string>
#include "r.objects.hpp"
#include "Rutilities.hpp"

using std::vector;

void createWriteJob(const Robject* x, std::vector<ColumnForWriting>& write_job, const bool writeRowNames);

#endif // CREATE_WRITE_JOB_HPP
