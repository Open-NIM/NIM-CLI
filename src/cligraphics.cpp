/* Copyright (C) 2022 Alluringbits */
#include "cligraphics.h"

std::string text_wrap(std::string  t, uint8_t length) noexcept{
	size_t endlinesN{t.size()/length};
	if(!(t.size()%length)) endlinesN--;
	for(size_t i{1}; i<=endlinesN; ++i) t.insert(length*i+(i-1), "\n");
	size_t remaining{(endlinesN+1)*(length+1)-t.size()};
	for(size_t i{}; i<remaining; ++i) t += ' ';
	return t;
}

std::string& text_remove_endl(std::string & t) noexcept{
	/* for(auto & i : t) if(i == '\n' && *(&i+1) != '\n') i = ' '; */
	for(auto & i : t) if(i == '\n') i = ' ';
	return t;
}

//This is so stupid and inefficient, overengineering textual aesthetics. it works anyway
std::string text_box(std::string  t, const char corner = 'O') noexcept{
	t.insert(0, "|");
	size_t width{(t.find("\n") != std::string::npos) ? t.find("\n") : t.size()-1};
	size_t endlinesN{t.size()/width-1};
	for(size_t i{1}; i<=endlinesN; ++i){
		t.insert(width*i+2*i-2, "|");
		t.insert(width*i+2*i,"|");
	}
	t.insert(t.end()-1, 1, '|');
	++width;
	t.insert(0,width,'-');
	t.insert(width, "\n");
	if(*(t.end()-1) != '\n') t.append("\n");
	t.append(width, '-');
	t.append("\n");
	/* t.insert(t.size(), "\n"); */
	t[0] = corner;
	t[width-1] = corner;
	t[t.size()-width-1] = corner;
	t[t.size()-2] = corner;
	size_t Ncount{};
	size_t tmpS{t.size()};
	t.insert(0, "   ");
	for(size_t i{}; i<tmpS; ++i) if( t[i+Ncount] == '\n'){
		t.insert(i+Ncount+1, "   ");
		Ncount++;
	}
	return t;
}

void print_header() noexcept{
	std::stringstream h{};
	size_t wdt{38};
	h << std::setw(wdt/2) << std::left << "NIM-CLI" << std::setw(wdt*3/2) << std::right << "CLI software for the NIM modules interface\n";
	h << std::setw(wdt) << std::left << "Version 0.1" << std::setw(wdt) << std::right << "https:://opennim.com\n";
	h << std::setw(wdt) << std::left << "Copyright (C) 2022 Open-NIM" << std::setw(wdt)  << std::right << "https://github.com/Open-NIM\n";
	h << std::setw(wdt) << std::left << "Conception: Alluringbits" << std::setw(wdt) << std::right << "https://github.com/Alluringbits\n";
	h << std::setw(wdt*3/2) << std::left << "Useful commands: help, list, credits, quit" << std::setw(wdt/2) << std::right << "\n";
	h << std::setw(wdt*2) << "\n";
	h << std::setw(wdt*2-1) << std::left << "This program comes with ABSOLUTELY NO WARRANTY; for details use the command" << "\n";
	h << std::setw(wdt*2-1) << std::left << " 'license'. This is free software, and you are welcome to redistribute it" << "\n";
	h << std::setw(wdt*2-1) << std::left << "      under certain conditions; use command 'conditions' for details." << "\n";
	std::cout << "\n" << text_box(h.str()) << "\n";
}


void print_license(bool full) noexcept{
	std::cout << text_box("The following is the GNU GPLv3 License associated with this program and the libNIM library.\n", 'L') << "\n";
	if(full){
		std::cout <<
"This program is free software: you can redistribute it and/or modify it\nunder the terms of the GNU General Public License as published by the Free\nSoftware Foundation, either version 3 of the License, or (at your option)\nany later version.\n\nThis program is distributed in the hope that it will be useful, but WITHOUT\nANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or\nFITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for\nmore details.\n\nYou should have received a copy of the GNU General Public License along with\nthis program.  If not, see <http://www.gnu.org/licenses/>.\n\nTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\nAPPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\nHOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\nOF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\nTHE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\nPURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\nIS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\nALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n";
	}
	else if(std::ifstream GPLv3{"LICENSE", std::ios::binary | std::ios::ate}){
		std::streamoff size{GPLv3.tellg()};
		std::string lic(size, '\0');
		GPLv3.seekg(0);
		if(GPLv3.read(&lic[0],size-2676)){
			std::cout << lic << "\n";
		}
	}	
	else{
		std::cout << "***WARNING***\nThe License file for this program is missing, therefore rendering this program and every\nright given by such license void to the user. Please install the program again following\nthe instructions at https://github.com/Open-NIM/NIM-CLI\n";
	}
	std::cout << text_box("The following is the MIT License associated with this program and the serial library.\n", 'L') << "\n";
	if(std::ifstream MIT{"libNIM/include/serial/LICENSE", std::ios::binary | std::ios::ate}){
		auto size{MIT.tellg()};
		std::string lic(size, '\0');
		MIT.seekg(0);
		if(MIT.read(&lic[0], size)){
			std::cout << lic << "\n";
			/* std::cout << text_box(text_wrap(text_remove_endl(lic),72), 'L') << "\n"; */
		}
	}	
	else{
		std::cout << "***WARNING***\nThe License file for the serial library is missing, therefore rendering this program and every\nright given by such license void to the user. Please install the program again following\nthe instructions at https://github.com/Open-NIM/NIM-CLI\n";
	}
}

void print_credits() noexcept{
	std::stringstream a{};
	size_t wdt{76};
	a << std::setw(wdt/2+4) << std::right << "Credits:" << std::setw(wdt/2-4) << std::right<< "\n";
	a << std::setw(wdt -1) << std::left << "Name: Alluringbits" << "\n";
	a << std::setw(wdt-1) << std::left << "Link: https://github.com/Alluringbits" << "\n";
	a << std::setw(wdt-1) << std::left << "Main conception and entirety of the program." << "\n" << std::setw(wdt) << std::right << "\n";
	std::cout << text_box(a.str(), 'A') << "\n";
}

void print_help() noexcept{
	std::stringstream h{};
	size_t wdt{75};
	h << std::setw(wdt) << std::left  << "NIM-CLI help page and quick commands list." << "\n";
	h << std::setw(wdt) << std::left  << "Syntax: command [<arg1>...]" << "\n";
	h << std::setw(wdt+1) << std::right  << "\n";
	h << std::setw(wdt) << std::left  << "COMMANDS" << "\n";
       	h << std::setw(wdt) << std::left  << "    help" <<  std::right << "\n";
	h << std::setw(wdt) << std::right << "Prints the quick help page." << "\n";
	h << std::setw(wdt) << std::left  << "    credits" << "\n";
	h << std::setw(wdt) << std::right << "Prints the credits and authors of the program." << "\n";
	h << std::setw(wdt) << std::left  << "    license" << "\n";
	h << std::setw(wdt) << std::right << "Prints the license conditions implied with the program." << "\n";
	h << std::setw(wdt) << std::left << "    conditions" << "\n";	
	h << std::setw(wdt) << std::right << "Prints the entirety of the licenses used by this program." << "\n";
	h << std::setw(wdt) << std::left << "    list [all]" << "\n";
	h << std::setw(wdt) << std::right <<"Lists the available modules that could be found." << "\n";
	h << std::setw(wdt) << std::right << "The [all] option makes it list every single serial device found." << "\n";
	h << std::setw(wdt) << std::left << "    history" << "\n";
	h << std::setw(wdt) << std::right << "Shows the history of the commands used in this session." << "\n"; 
	
	h << std::setw(wdt) << std::left << "    q, quit" << "\n";
	h << std::setw(wdt) << std::right << "Exists the program." << "\n";

	std::cout << text_box(h.str(), 'H') << "\n";
}



