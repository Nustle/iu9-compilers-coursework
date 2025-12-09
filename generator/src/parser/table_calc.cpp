#include "include/parser/table.h"

Table::Table()
: axiom({"E", Symbol::Type::NonTerminal}),
  action_table({
  	{0, {
  		{{"n", Symbol::Type::Terminal}, Shift(4)},
  		{{"(", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{1, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"*", Symbol::Type::Terminal}, Shift(6)}
  	}},

  	{2, {
  		{{"n", Symbol::Type::Terminal}, Shift(4)},
  		{{"(", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{3, {
  		{{"EOF", Symbol::Type::Terminal}, Accept{}}
  	}},

  	{4, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"n", Symbol::Type::Terminal}}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"n", Symbol::Type::Terminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"n", Symbol::Type::Terminal}}
  		)},
  		{{"*", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"n", Symbol::Type::Terminal}}
  		)}
  	}},

  	{5, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"+", Symbol::Type::Terminal}, Shift(9)}
  	}},

  	{6, {
  		{{"n", Symbol::Type::Terminal}, Shift(4)},
  		{{"(", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{7, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"T", Symbol::Type::NonTerminal},
  			{{"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"T", Symbol::Type::NonTerminal},
  			{{"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"T", Symbol::Type::NonTerminal},
  			{{"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{8, {
  		{{")", Symbol::Type::Terminal}, Shift(12)}
  	}},

  	{9, {
  		{{"n", Symbol::Type::Terminal}, Shift(4)},
  		{{"(", Symbol::Type::Terminal}, Shift(2)}
  	}},

  	{10, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"E", Symbol::Type::NonTerminal},
  			{{"T", Symbol::Type::NonTerminal}, {"E'", Symbol::Type::NonTerminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"E", Symbol::Type::NonTerminal},
  			{{"T", Symbol::Type::NonTerminal}, {"E'", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{11, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"*", Symbol::Type::Terminal}, Shift(6)}
  	}},

  	{12, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"(", Symbol::Type::Terminal}, {"E", Symbol::Type::NonTerminal}, {")", Symbol::Type::Terminal}}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"(", Symbol::Type::Terminal}, {"E", Symbol::Type::NonTerminal}, {")", Symbol::Type::Terminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"(", Symbol::Type::Terminal}, {"E", Symbol::Type::NonTerminal}, {")", Symbol::Type::Terminal}}
  		)},
  		{{"*", Symbol::Type::Terminal}, Reduce(
  			{"F", Symbol::Type::NonTerminal},
  			{{"(", Symbol::Type::Terminal}, {"E", Symbol::Type::NonTerminal}, {")", Symbol::Type::Terminal}}
  		)}
  	}},

  	{13, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{}
  		)},
  		{{"+", Symbol::Type::Terminal}, Shift(9)}
  	}},

  	{14, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{{"*", Symbol::Type::Terminal}, {"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)},
  		{{"+", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{{"*", Symbol::Type::Terminal}, {"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"T'", Symbol::Type::NonTerminal},
  			{{"*", Symbol::Type::Terminal}, {"F", Symbol::Type::NonTerminal}, {"T'", Symbol::Type::NonTerminal}}
  		)}
  	}},

  	{15, {
  		{{")", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{{"+", Symbol::Type::Terminal}, {"T", Symbol::Type::NonTerminal}, {"E'", Symbol::Type::NonTerminal}}
  		)},
  		{{"EOF", Symbol::Type::Terminal}, Reduce(
  			{"E'", Symbol::Type::NonTerminal},
  			{{"+", Symbol::Type::Terminal}, {"T", Symbol::Type::NonTerminal}, {"E'", Symbol::Type::NonTerminal}}
  		)}
  	}}
  }),
  goto_table({
  	{0, {
  		{{"T", Symbol::Type::NonTerminal}, 5},
  		{{"E", Symbol::Type::NonTerminal}, 3},
  		{{"F", Symbol::Type::NonTerminal}, 1}
  	}},

  	{1, {
  		{{"T'", Symbol::Type::NonTerminal}, 7}
  	}},

  	{2, {
  		{{"T", Symbol::Type::NonTerminal}, 5},
  		{{"E", Symbol::Type::NonTerminal}, 8},
  		{{"F", Symbol::Type::NonTerminal}, 1}
  	}},

  	{5, {
  		{{"E'", Symbol::Type::NonTerminal}, 10}
  	}},

  	{6, {
  		{{"F", Symbol::Type::NonTerminal}, 11}
  	}},

  	{9, {
  		{{"T", Symbol::Type::NonTerminal}, 13},
  		{{"F", Symbol::Type::NonTerminal}, 1}
  	}},

  	{11, {
  		{{"T'", Symbol::Type::NonTerminal}, 14}
  	}},

  	{13, {
  		{{"E'", Symbol::Type::NonTerminal}, 15}
  	}}
  }) {}
