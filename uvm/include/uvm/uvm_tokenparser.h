#ifndef uvm_tokenparser_h
#define uvm_tokenparser_h

#include <uvm/lprefix.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <list>
#include <queue>
#include <sstream>

#include <uvm/llimits.h>
#include <uvm/lstate.h>			  
#include <uvm/lua.h>
#include <uvm/uvm_api.h>
#include <uvm/exceptions.h>

namespace uvm
{
    namespace parser
    {
        enum TOKEN_RESERVED {
            /* terminal symbols denoted by reserved words */
            LTK_AND = 237, LTK_BREAK,
            LTK_DO, LTK_ELSE, LTK_ELSEIF, LTK_END, LTK_FALSE, LTK_FOR, LTK_FUNCTION,
            LTK_GOTO, LTK_IF, LTK_IN, LTK_LOCAL, LTK_LET, LTK_OFFLINE, LTK_NIL, LTK_NOT, LTK_OR, LTK_REPEAT,
            LTK_RETURN, LTK_THEN, LTK_TRUE, LTK_UNTIL, LTK_WHILE, LTK_DEFAULT, LTK_TYPE,
            /* other terminal symbols */
            LTK_IDIV, LTK_CONCAT, LTK_DOTS, LTK_EQ, LTK_GE, LTK_LE, LTK_NE, LTK_FUNCTION_ARROW, LTK_OPTIONAL_COLON,
            LTK_SHL, LTK_SHR,
            LTK_DBCOLON, LTK_EOS,
            LTK_FLT, LTK_INT, LTK_NAME, LTK_STRING
        };

        /* number of reserved words */
#define NUM_RESERVED	(lua_cast(int, TK_WHILE-FIRST_RESERVED+1))

        class UvmParserToken
        {
		public:
            std::string token;
            std::string source_token;
            enum TOKEN_RESERVED type;
            size_t position;
            size_t linenumber; // line number (start from 1), 0 means unknown-linenumber
			size_t end_linenumber;
        };

        inline UvmParserToken eof_token()
        {
            UvmParserToken eof;
            eof.type = TOKEN_RESERVED::LTK_EOS;
            eof.position = 0;
            eof.linenumber = 0;
			eof.end_linenumber = 0;
            eof.token = "";
            return eof;
        }

		// token of literal code, used to generate code string from token
        inline UvmParserToken literal_code_token(std::string code)
        {
            UvmParserToken token;
            token.type = TOKEN_RESERVED::LTK_NAME;
            token.position = 0;
            token.linenumber = 0;
			token.end_linenumber = 0;
            token.token = code;
            token.source_token = code;
            return token;
        }

        inline bool is_eof_token(UvmParserToken &token)
        {
            return token.type == LTK_EOS;
        }

#define LUA_TOKEN_MAX_LENGTH 10240
#define EOF_TOKEN_CHAR (-1)

#define THROW_PERROR(errorstr, ...)	do{_L->err && fprintf(_L->err, errorstr, ##__VA_ARGS__); throw uvm::core::UvmException(errorstr);}while(0)

        class UvmTokenParser
        {
        private:
            std::vector<UvmParserToken> _tokens;
            size_t _pos;
            lua_State *_L;

            size_t _parsing_linenumber;
            size_t _parsing_pos;
            int *_parsing_buff; // [LUA_TOKEN_MAX_LENGTH];
            size_t _parsing_buff_len;
            size_t _cycle_count;
        private:
            UvmParserToken _parse_next_token(std::string &code);
            /*
            ** skip a sequence '[=*[' or ']=*]'; if sequence is well formed, return
            ** its number of '='s; otherwise, return a negative number (-1 iff there
            ** are no '='s after initial bracket)
            */
            int _skip_sep(std::string &code);
            void _reset_parse_buff();
            int _save_to_buff(int c);
            int _save_to_buff_and_next(int c);
            void _inc_line(std::string &code);
            void _read_long_string(std::string &code, bool is_string, int sep);
            void _read_string(std::string &code, int delimiter);
            void _read_numeral(std::string &code, std::stringstream *ss = nullptr);
            void _loadhexaesc(std::string &code, std::stringstream *ss = nullptr);
            void _loadutf8esc(std::string &code, std::stringstream *ss = nullptr);
            void _loaddecesc(std::string &code, std::stringstream *ss = nullptr);
            inline int _current_char(std::string &code);
            void _push_new_token(int type, size_t line = 0);
            bool _check_next2(std::string &code, const char *str);
            UvmParserToken _last_token() const;
            UvmParserToken _single_char_token(std::string &code, int type);
            UvmParserToken _double_chars_token(std::string &code, int type);
            UvmParserToken _three_chars_token(std::string &code, int type);
            int _next_token_char(std::string &code) const;

        public:
            UvmTokenParser(lua_State *L);
            ~UvmTokenParser();
            /************************************************************************/
            /* @throw uvm::core::UvmException                                                */
            /************************************************************************/
            void parse(const std::string &code);
            bool next();
            UvmParserToken current() const;

            UvmParserToken lookahead() const;

            inline size_t current_position() const
            {
                return _pos;
            }

			inline size_t current_parsing_linenumber() const
            {
				return _parsing_linenumber;
            }

            inline bool has_n_tokens_after(size_t n) const
            {
                return _pos + n < _tokens.size();
            }

            void goback();

            std::string dump() const;

            inline void reset_position(size_t pos = 0)
            {
                _pos = pos;
            }

			inline UvmParserToken nth_token(size_t pos) const
            {
				if (pos < _tokens.size())
					return _tokens[pos];
				else
				{
					UvmParserToken token;
					token.linenumber = 0;
					token.position = 0;
					token.end_linenumber = 0;
					token.type = (TOKEN_RESERVED)0;
					return token;
				}
            }

            inline std::vector<UvmParserToken>::iterator begin()
            {
                return _tokens.begin();
            }

            inline std::vector<UvmParserToken>::iterator end()
            {
                return _tokens.end();
            }

            inline bool hasNext() const
            {
                return _pos + 1 < _tokens.size();
            }

            inline bool eof() const
            {
                return _pos >= _tokens.size();
            }

            inline size_t size() const
            {
                return _tokens.size();
            }

            inline void replace_all_tokens(std::vector<UvmParserToken> &tokens)
            {
                _tokens = tokens;
                reset_position();
            }

            inline const std::vector<UvmParserToken> *all_tokens() const
            {
                return &_tokens;
            }
        };
    }
}

#endif
