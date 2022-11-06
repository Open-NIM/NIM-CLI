/*
 * libNIM a cross platform library for the Open-NIM modules.
 * Copyright (C) 2022 Alluringbits
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
 * APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
 * HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
 * IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
 * ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 */
#include "libNIM.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "cligraphics.h"


int main(int argc, char** argv){
	print_header();
	std::vector<std::string> hist{};
	
	std::string cmdbuff{};
	static uint32_t cmdN{};
	while(true){
		std::cout << "NIM [" << cmdN++ << "]: ";
		std::cin >> cmdbuff;
		hist.push_back(cmdbuff);
		if(!cmdbuff.compare("help")) print_help();
		else if(!cmdbuff.compare("list")){
			std::cin >> cmdbuff;
			if(!cmdbuff.compare("all")){
				hist.back().append(" "+cmdbuff);
			}
			auto ls{NIM::listAvailableModules()};
			for(auto i : ls) std::cout << i->getSerialNumber() << "\n";
		}
		else if(!cmdbuff.compare("quit") || !cmdbuff.compare("q")) std::exit(EXIT_SUCCESS);
		else if(!cmdbuff.compare("history")) for(const auto & i: hist) std::cout<< i << "\n";
		else if(!cmdbuff.compare("license")) print_license(1);
		else if(!cmdbuff.compare("conditions")) print_license(1);
		else if(!cmdbuff.compare("credits")) print_credits();
		else{
			std::cout << "Unrecognised command \"" << cmdbuff << "\".\n";
			print_help();
		}
	}


	/* auto ls{NIM::listAvailableModules()}; */
	/* for(auto i : ls) std::cout << i->getSerialNumber() << "\n"; */

	return 0;
}






