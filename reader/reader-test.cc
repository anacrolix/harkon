#include <string>
#include <boost/lexical_cast.hpp>

#include "parser.hpp"


std::string pretty_print(harkon::prim_val const& v);


int main(int, char** argv) {


	typedef std::string::const_iterator iterator_type;

    harkon::sexpr_grammar<iterator_type> p;


    std::string str;

    std::cout << "> ";

    while (std::getline(std::cin, str))
    {

        if (str.empty())
            break;

        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();

        harkon::prim_val result;

        bool r = phrase_parse(iter, end, p, boost::spirit::ascii::space, result);

        if (r && iter == end)
        {
            std::cout << "Parsing succeeded: " << pretty_print(result) << "\n\n> ";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \": " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }

    std::cout << "exiting..." << std::endl;
    return 0;
}



struct pim_val_visitor : boost::static_visitor<std::string>
{
	std::string operator()(const int x) const {
		return boost::lexical_cast<std::string>(x);
	}

	std::string operator()(const std::vector<char> cv) const {
		std::stringstream ss;
		for (std::vector<char>::const_iterator it=cv.begin(); it != cv.end(); ++it)
			ss << *it;
		return ss.str();
	}

};

std::string pretty_print(harkon::prim_val const& v) {
	return boost::apply_visitor(pim_val_visitor(), v);
}

