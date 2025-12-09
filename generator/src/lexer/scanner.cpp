#include "include/lexer/scanner.h"
#include <string>
#include <regex>

struct RegexDomain {
    DomainTag tag;
    regex pattern;

    RegexDomain(DomainTag tag, const regex &pattern)
    : tag(tag), pattern(pattern) {}
};

vector<RegexDomain> regexes = {
        RegexDomain(DomainTag::NonTerminal, regex(R"([A-Za-z][A-Za-z0-9]*'*)")),
        RegexDomain(DomainTag::Terminal, regex(R"("[^\n"']+")")),
        RegexDomain(DomainTag::Colon, regex(R"(:)")),
        RegexDomain(DomainTag::Eps, regex(R"(@)")),
        RegexDomain(DomainTag::LeftAngle, regex(R"(<)")),
        RegexDomain(DomainTag::RightAngle, regex(R"(>)")),
        RegexDomain(DomainTag::LeftBrace, regex(R"(\{)")),
        RegexDomain(DomainTag::RightBrace, regex(R"(\})")),
        RegexDomain(DomainTag::Comma, regex(R"(,)")),
};
regex WhiteSpaceRegex = regex(R"([ \t\n\r]+)");
regex CommentRegex = regex(R"(--[^\n]*)");


unique_ptr <Token> Scanner::NextToken() {
    smatch m;
    auto program_rest = program.substr(cur.GetIndex());

    size_t lex_len = 0;
    DomainTag lex_tag;

    while (lex_len == 0) {
        if (cur.EndOfProgram()) {
            return make_unique<EOFToken>(cur, cur);
        }
        if (regex_search(program_rest, m, WhiteSpaceRegex, regex_constants::match_continuous)) {
            size_t len = m.str(0).size();
            cur += len;
        } else if (regex_search(program_rest, m, CommentRegex, regex_constants::match_continuous)) {
            size_t len = m.str(0).size();
            Position start = cur;
            start += 2;
            cur += len;
            comments.emplace_back(start, cur);
        } else {
            for (auto &rd: regexes) {
                if (regex_search(program_rest, m, rd.pattern, regex_constants::match_continuous)) {
                    size_t len = m.str(0).size();
                    if (len > lex_len) {
                        lex_len = len;
                        lex_tag = rd.tag;
                    }
                }
            }
            if (lex_len == 0) {
                compiler->AddMessage(cur, MessageType::Error, "unexpected char");
                cur++;
            }
        }

        program_rest = program.substr(cur.GetIndex());
    }

    Position start(&program), end(&program);
    if (lex_tag == DomainTag::Terminal) {
        cur++;
        start = cur;
        cur += lex_len - 2;
        end = cur;
        cur++;
    } else {
        start = cur;
        cur += lex_len;
        end = cur;
    }
    string lex = program.substr(start.GetIndex(), end.GetIndex() - start.GetIndex());

    switch (lex_tag) {
        case DomainTag::Terminal: {
            return make_unique<TerminalToken>(
                    lex,
                    start,
                    end
            );
        }
        case DomainTag::NonTerminal: {
            return make_unique<NonTerminalToken>(
                    lex,
                    start,
                    end
            );
        }
        default: {
            return make_unique<SpecToken>(
                    lex_tag,
                    start,
                    end
            );
        }
    }
}
