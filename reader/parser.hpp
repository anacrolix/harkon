#pragma once

#define BOOST_SPIRIT_UNICODE

#include <boost/spirit/include/qi.hpp>


namespace harkon
{
	using boost::spirit::qi::rule;
	using boost::spirit::qi::grammar;
	using boost::spirit::qi::space;
	using boost::spirit::qi::char_;
	using boost::spirit::qi::alnum;
	using boost::spirit::qi::int_;
	using boost::spirit::qi::eol;
	using boost::spirit::qi::lexeme;
	namespace ascii = boost::spirit::ascii;

	typedef std::vector<char> symbol;
	typedef boost::variant<int, symbol> prim_val;

	template <typename Iterator>
	struct sexpr_grammar : grammar<Iterator, ascii::space_type, prim_val()>
	{
		sexpr_grammar() : sexpr_grammar::base_type(start_)
		{
			start_ %= int_ | symbol_;
			symbol_ %= lexeme[+(char_ - space - ')' - '(')];
		}


		rule<Iterator, ascii::space_type, prim_val()> start_;
		rule<Iterator, ascii::space_type, symbol() > symbol_;

	};

}


