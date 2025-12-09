#include "include/parser/table.h"

Table::Table()
: axiom({"Program", Symbol::Type::NonTerminal}),
  action_table({
  	{0, {
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(4)},
  		{{"LeftBrace", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{1, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Rules", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"LeftAngle", Symbol::Type::Terminal}, Shift(7)}
  	}},

  	{2, {
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(9)}
  	}},

  	{3, {
  		{{"EOF", Symbol::Type::Terminal}, Accept{}}
  	}},

  	{4, {
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"Comma", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)}
  	}},

  	{5, {
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"Comma", Symbol::Type::Terminal}, Shift(10)}
  	}},

  	{6, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Rules", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"LeftAngle", Symbol::Type::Terminal}, Shift(7)}
  	}},

  	{7, {
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(13)}
  	}},

  	{8, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Program", Symbol::Type::NonTerminal},
  			{{"Declaration", Symbol::Type::NonTerminal}, {"Rules", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{9, {
  		{{"RightBrace", Symbol::Type::Terminal}, Shift(14)}
  	}},

  	{10, {
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(4)},
  		{{"LeftBrace", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{11, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Declaration", Symbol::Type::NonTerminal},
  			{{"NonterminalDecl", Symbol::Type::NonTerminal}, {"Declaration1", Symbol::Type::NonTerminal}}
  		)},
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"Declaration", Symbol::Type::NonTerminal},
  			{{"NonterminalDecl", Symbol::Type::NonTerminal}, {"Declaration1", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{12, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Rules", Symbol::Type::NonTerminal},
  			{{"Rule", Symbol::Type::NonTerminal}, {"Rules", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{13, {
  		{{"Colon", Symbol::Type::Terminal}, Shift(18)}
  	}},

  	{14, {
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"LeftBrace", Symbol::Type::Terminal}, {"NonTerminal", Symbol::Type::Terminal}, {"RightBrace", Symbol::Type::Terminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"LeftBrace", Symbol::Type::Terminal}, {"NonTerminal", Symbol::Type::Terminal}, {"RightBrace", Symbol::Type::Terminal}}
  		)},
  		{{"Comma", Symbol::Type::Terminal}, Reduce(
  			{"NonterminalDecl", Symbol::Type::NonTerminal},
  			{{"LeftBrace", Symbol::Type::Terminal}, {"NonTerminal", Symbol::Type::Terminal}, {"RightBrace", Symbol::Type::Terminal}}
  		)}
  	}},

  	{15, {
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"Comma", Symbol::Type::Terminal}, Shift(10)}
  	}},

  	{16, {
  		{{"RightAngle", Symbol::Type::Terminal}, Shift(20)}
  	}},

  	{17, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Alternatives1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Shift(18)}
  	}},

  	{18, {
  		{{"Eps", Symbol::Type::Terminal}, Shift(26)},
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(25)},
  		{{"Terminal", Symbol::Type::Terminal}, Shift(24)}
  	}},

  	{19, {
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{{"Comma", Symbol::Type::Terminal}, {"NonterminalDecl", Symbol::Type::NonTerminal}, {"Declaration1", Symbol::Type::NonTerminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Declaration1", Symbol::Type::NonTerminal},
  			{{"Comma", Symbol::Type::Terminal}, {"NonterminalDecl", Symbol::Type::NonTerminal}, {"Declaration1", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{20, {
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"Rule", Symbol::Type::NonTerminal},
  			{{"LeftAngle", Symbol::Type::Terminal}, {"NonTerminal", Symbol::Type::Terminal}, {"Alternatives", Symbol::Type::NonTerminal}, {"RightAngle", Symbol::Type::Terminal}}
  		)},
  		{{"LeftAngle", Symbol::Type::Terminal}, Reduce(
  			{"Rule", Symbol::Type::NonTerminal},
  			{{"LeftAngle", Symbol::Type::Terminal}, {"NonTerminal", Symbol::Type::Terminal}, {"Alternatives", Symbol::Type::NonTerminal}, {"RightAngle", Symbol::Type::Terminal}}
  		)}
  	}},

  	{21, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Alternatives1", Symbol::Type::NonTerminal},
  			{{"Alternatives", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{22, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Alternatives", Symbol::Type::NonTerminal},
  			{{"Alternative", Symbol::Type::NonTerminal}, {"Alternatives1", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{23, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Terms1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Terms1", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"Eps", Symbol::Type::Terminal}, Shift(26)},
  		{{"Terminal", Symbol::Type::Terminal}, Shift(24)},
  		{{"NonTerminal", Symbol::Type::Terminal}, Shift(25)}
  	}},

  	{24, {
  		{{"Terminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Terminal", Symbol::Type::Terminal}}
  		)},
  		{{"NonTerminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Terminal", Symbol::Type::Terminal}}
  		)},
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Terminal", Symbol::Type::Terminal}}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Terminal", Symbol::Type::Terminal}}
  		)},
  		{{"Eps", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Terminal", Symbol::Type::Terminal}}
  		)}
  	}},

  	{25, {
  		{{"Terminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"NonTerminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)},
  		{{"Eps", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"NonTerminal", Symbol::Type::Terminal}}
  		)}
  	}},

  	{26, {
  		{{"Terminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Eps", Symbol::Type::Terminal}}
  		)},
  		{{"NonTerminal", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Eps", Symbol::Type::Terminal}}
  		)},
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Eps", Symbol::Type::Terminal}}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Eps", Symbol::Type::Terminal}}
  		)},
  		{{"Eps", Symbol::Type::Terminal}, Reduce(
  			{"Term", Symbol::Type::NonTerminal},
  			{{"Eps", Symbol::Type::Terminal}}
  		)}
  	}},

  	{27, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Alternative", Symbol::Type::NonTerminal},
  			{{"Colon", Symbol::Type::Terminal}, {"Terms", Symbol::Type::NonTerminal}}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Alternative", Symbol::Type::NonTerminal},
  			{{"Colon", Symbol::Type::Terminal}, {"Terms", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{28, {
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Terms1", Symbol::Type::NonTerminal},
  			{{"Terms", Symbol::Type::NonTerminal}}
  		)},
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Terms1", Symbol::Type::NonTerminal},
  			{{"Terms", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{29, {
  		{{"Colon", Symbol::Type::Terminal}, Reduce(
  			{"Terms", Symbol::Type::NonTerminal},
  			{{"Term", Symbol::Type::NonTerminal}, {"Terms1", Symbol::Type::NonTerminal}}
  		)},
  		{{"RightAngle", Symbol::Type::Terminal}, Reduce(
  			{"Terms", Symbol::Type::NonTerminal},
  			{{"Term", Symbol::Type::NonTerminal}, {"Terms1", Symbol::Type::NonTerminal}}
  		)}
  	}}
  }),
  goto_table({
  	{0, {
  		{{"NonterminalDecl", Symbol::Type::NonTerminal}, 5},
  		{{"Program", Symbol::Type::NonTerminal}, 3},
  		{{"Declaration", Symbol::Type::NonTerminal}, 1}
  	}},

  	{1, {
  		{{"Rules", Symbol::Type::NonTerminal}, 8},
  		{{"Rule", Symbol::Type::NonTerminal}, 6}
  	}},

  	{5, {
  		{{"Declaration1", Symbol::Type::NonTerminal}, 11}
  	}},

  	{6, {
  		{{"Rules", Symbol::Type::NonTerminal}, 12},
  		{{"Rule", Symbol::Type::NonTerminal}, 6}
  	}},

  	{10, {
  		{{"NonterminalDecl", Symbol::Type::NonTerminal}, 15}
  	}},

  	{13, {
  		{{"Alternative", Symbol::Type::NonTerminal}, 17},
  		{{"Alternatives", Symbol::Type::NonTerminal}, 16}
  	}},

  	{15, {
  		{{"Declaration1", Symbol::Type::NonTerminal}, 19}
  	}},

  	{17, {
  		{{"Alternative", Symbol::Type::NonTerminal}, 17},
  		{{"Alternatives1", Symbol::Type::NonTerminal}, 22},
  		{{"Alternatives", Symbol::Type::NonTerminal}, 21}
  	}},

  	{18, {
  		{{"Terms", Symbol::Type::NonTerminal}, 27},
  		{{"Term", Symbol::Type::NonTerminal}, 23}
  	}},

  	{23, {
  		{{"Terms1", Symbol::Type::NonTerminal}, 29},
  		{{"Terms", Symbol::Type::NonTerminal}, 28},
  		{{"Term", Symbol::Type::NonTerminal}, 23}
  	}}
  }) {}
