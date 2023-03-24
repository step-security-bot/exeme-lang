// Part of the Exeme Language Project, under the MIT license. See '/LICENSE' for
// license information. SPDX-License-Identifier: MIT License.

#pragma once

#include "../includes.c"

/**
 * Used to identify different lexer tokens.
 */
enum LexerTokens {
	LEXERTOKENS_NONE,

	LEXERTOKENS_KEYWORD,
	LEXERTOKENS_IDENTIFIER,

	LEXERTOKENS_CHR,
	LEXERTOKENS_STRING,
	LEXERTOKENS_INTEGER,
	LEXERTOKENS_FLOAT,

	// Arithmetic operators
	LEXERTOKENS_MODULO,			// '%'
	LEXERTOKENS_EXPONENT,		// '**'
	LEXERTOKENS_DIVISION,		// '/'
	LEXERTOKENS_FLOOR_DIVISION, // '//'
	LEXERTOKENS_MULTIPLICATION, // '*'
	LEXERTOKENS_ADDITION,		// '+'
	LEXERTOKENS_SUBTRACTION,	// '-'

	// Comparison / Relational operators
	LEXERTOKENS_EQUAL_TO,			   // '=='
	LEXERTOKENS_NOT_EQUAL_TO,		   // '!='
	LEXERTOKENS_GREATER_THAN,		   // '>'
	LEXERTOKENS_LESS_THAN,			   // '<'
	LEXERTOKENS_GREATER_THAN_OR_EQUAL, // '>='
	LEXERTOKENS_LESS_THAN_OR_EQUAL,	   // '<='

	// Logical operators
	LEXERTOKENS_LOGICAL_AND, // '&&'
	LEXERTOKENS_LOGICAL_OR,	 // '||'
	LEXERTOKENS_LOGICAL_NOT, // '!'

	// Bitwise operators
	LEXERTOKENS_BITWISE_AND,		 // '&'
	LEXERTOKENS_BITWISE_OR,			 // '|'
	LEXERTOKENS_BITWISE_XOR,		 // '^'
	LEXERTOKENS_BITWISE_NOT,		 // '~'
	LEXERTOKENS_BITWISE_LEFT_SHIFT,	 // '<<'
	LEXERTOKENS_BITWISE_RIGHT_SHIFT, // '>>'

	// Assignment operators
	LEXERTOKENS_ASSIGNMENT, // '='

	LEXERTOKENS_MODULO_ASSIGNMENT,		   // '%='
	LEXERTOKENS_EXPONENT_ASSIGNMENT,	   // '**='
	LEXERTOKENS_DIVISION_ASSIGNMENT,	   // '/='
	LEXERTOKENS_FLOOR_DIVISION_ASSIGNMENT, // '//='
	LEXERTOKENS_MULTIPLICATION_ASSIGNMENT, // '*='
	LEXERTOKENS_ADDITION_ASSIGNMENT,	   // '+='
	LEXERTOKENS_SUBTRACTION_ASSIGNMENT,	   // '-='

	LEXERTOKENS_BITWISE_AND_ASSIGNMENT,			// '&='
	LEXERTOKENS_BITWISE_OR_ASSIGNMENT,			// '|='
	LEXERTOKENS_BITWISE_XOR_ASSIGNMENT,			// '^='
	LEXERTOKENS_BITWISE_NOT_ASSIGNMENT,			// '~='
	LEXERTOKENS_BITWISE_LEFT_SHIFT_ASSIGNMENT,	// '<<='
	LEXERTOKENS_BITWISE_RIGHT_SHIFT_ASSIGNMENT, // '>>='

	// Member / Pointer operators
	LEXERTOKENS_DOT,   // '.'
	LEXERTOKENS_ARROW, // '->'
	LEXERTOKENS_AT,	   // '@'

	// Syntactic constructs
	LEXERTOKENS_OPEN_BRACE,			// '('
	LEXERTOKENS_OPEN_SQUARE_BRACE,	// '['
	LEXERTOKENS_OPEN_CURLY_BRACE,	// '{'
	LEXERTOKENS_CLOSE_BRACE,		// ')'
	LEXERTOKENS_CLOSE_SQUARE_BRACE, // ']'
	LEXERTOKENS_CLOSE_CURLY_BRACE,	// '}'

	// Other operators
	LEXERTOKENS_COMMA,			  // ','
	LEXERTOKENS_COLON,			  // ':'
	LEXERTOKENS_SCOPE_RESOLUTION, // '::'

	// Misc
	LEXERTOKENS_COMMENT,
};

/**
 * Contains the names of each of the lexer token identifiers.
 */
struct array LexerTokenNames = {
	54,
	(const void *[]){
		"",
		"keyword",
		"identifier",
		"char",
		"string",
		"integer",
		"float",
		"modulo operator",
		"exponent operator",
		"division operator",
		"floor division operator",
		"multiplication operator",
		"addition operator",
		"subtraction operator",
		"equal to operator",
		"not equal to operator",
		"greater then operator",
		"less than operator",
		"greater than or equal operator",
		"less than or equal operator",
		"logical and operator",
		"logical or operator",
		"logical not operator",
		"bitwise AND operator",
		"bitwise OR operator",
		"bitwise XOR operator",
		"bitwise NOT operator",
		"bitwise left shift",
		"bitwise right shift",
		"assignment operator",
		"modulo assignment operator",
		"exponent assignment operator",
		"divison assignment operator",
		"floor division assignment operator",
		"multiplication assignment operator",
		"addition assignment operator",
		"subtraction assignment operator",
		"bitwise AND assignment operator",
		"bitwise OR assignment operator",
		"bitwise XOR assignment operator",
		"bitwise NOT assignment operator",
		"bitwise left shift assignment operator",
		"bitwise right shift assignment operator",
		"dot operator",
		"arrow operator",
		"address of operator",
		"open brace",
		"open square brace",
		"open curly brace",
		"close brace",
		"close sqaure brace",
		"close curly brace",
		"comma",
		"colon",
		"scope resolution operator",
		"comment",
	},
};

/**
 * Represents a lexer token.
 * Stores data relating to it.
 */
struct LexerToken {
	const char *value;
	enum LexerTokens identifier;
	size_t startChrIndex, chrIndex, lineNum;
};

#define LEXERTOKEN_STRUCT_SIZE sizeof(struct LexerToken)

/**
 * Creates a new LexerToken struct.
 *
 * @param value         - Value of the token.
 * @param identifier    - Token identifier.
 * @param startChrIndex - Start char index of token.
 * @param chrIndex      - End char index of the token.
 * @param lineNum       - Line num of the token.
 */
const struct LexerToken *lexerToken_new(const char *value,
										enum LexerTokens identifier,
										size_t startChrIndex, size_t chrIndex,
										size_t lineNum) {
	struct LexerToken *self = malloc(LEXERTOKEN_STRUCT_SIZE);

	self->value = value;
	self->identifier = identifier;
	self->startChrIndex = startChrIndex;
	self->chrIndex = chrIndex;
	self->lineNum = lineNum;

	return self;
}

/**
 * Represents a lexer class.
 * Handles logic for lexing a file.
 */
struct Lexer {
	bool closed;
	char chr, prevChr;
	const char *FILE_PATH;
	FILE *filePointer;
	size_t unGetTokens, chrIndex, lineNum;
	struct array *tokens;
};

/**
 * Prints an error and exits.
 * Operates on the given lexer struct.
 *
 * @param self          - The corresponding lexer struct.
 * @param ERROR_MSG     - The error message.
 * @param token         - The erroneous token.
 */
noreturn void lexer_error(struct Lexer *self, const char *ERROR_MSG,
						  const struct LexerToken *token) {
	size_t length, lineNum = 0;
	char *line;
	FILE *filePointer = fopen(self->FILE_PATH, "r");

	printf("%s%s--> %s%s\n", F_BRIGHT_BLUE, S_BOLD, S_RESET, self->FILE_PATH);

	while (true) {
		line = "";

		while (true) {
			char chr = (char)fgetc(filePointer);

			if (chr == '\n' || chr == EOF) {
				break;
			}

			strncat(line, &chr, 1);
		}

		lineNum++;

		if (lineNum == self->lineNum) {
			break;
		}
	}

	length = strlen(ulToString(self->chrIndex)) + 3;

	printf("%zu | %s\n", self->lineNum, line);

	if (token == NULL) {
		printf("%s^ %s%serror: %s%s\n", repeatChr(' ', self->chrIndex),
			   F_BRIGHT_RED, S_BOLD, S_RESET, ERROR_MSG);
	} else {
		self->lineNum = token->lineNum;
		self->chrIndex = token->chrIndex;

		printf("%s%s %s%serror: %s%s\n",
			   repeatChr(' ', length + token->startChrIndex),
			   repeatChr('^', self->chrIndex - token->startChrIndex + 1),
			   F_BRIGHT_RED, S_BOLD, S_RESET, ERROR_MSG);
	}

	exit(EXIT_FAILURE);
}

/**
 * Gets the next character.
 * Operates on the given lexer struct.
 *
 * @param self           - The corresponding lexer struct.
 * @param skipWhitespace - Whether to skip whitespace characters.
 *
 * @return Whether the next character was got successfully.
 */
bool lexer_getChr(struct Lexer *self, bool skipWhitespace) {
	if (self->closed) {
		return false;
	} else if (self->chr == '\n') {
		return false;
	}

	while (true) {
		self->prevChr = self->chr;
		self->chr = (char)fgetc(self->filePointer);

		if (self->chr == EOF ||
			ferror(self->filePointer) != 0) { // End of file (hopefully)
			fclose(self->filePointer);
			self->closed = true;
			return false;
		}

		self->chrIndex++;

		if (self->chr == '\n') {
			return false;
		}

		if (skipWhitespace) { // Keep going till we encounter a character
							  // that is not whitespace
			if (!isspace(self->chr)) { // Not whitespace
				break;
			}
		} else {
			break;
		}
	}

	return true;
}

/**
 * Un-gets the current character.
 * Operates on the given lexer struct.
 *
 * @param self - The corresponding lexer struct.
 *
 * @return Whether the current character was un-got successfully.
 */
bool lexer_unGetChr(struct Lexer *self) {
	if (self->closed) {
		return false;
	}

	ungetc(self->chr, self->filePointer);

	self->chrIndex--;
	self->chr = self->prevChr;
	self->prevChr = '\0';

	if (ferror(self->filePointer) != 0) {
		fclose(self->filePointer);
		panic(
			stringConcatenate(2, "failed to unget char in ", self->FILE_PATH));
	}

	return true;
}

/**
 * Gets the next line.
 * Operates on the given lexer struct.
 *
 * @param self        - The corresponding lexer struct.
 * @param getNextLine - Get the next line even if the EOL has not been reached.
 *
 * @return Whether the next line was got successfully.
 */
bool lexer_getLine(struct Lexer *self, bool getNextLine) {
	if (self->closed) {
		return false;
	}

	if (!getNextLine &&
		self->chr != '\n') { // Not reached the end of the line yet
		return true;
	}

	self->prevChr = self->chr;
	self->chr = '\0';

	self->chrIndex = negativeIndex;
	self->lineNum++;

	return true;
}

/**
 * Returns the escaped version of the current character.
 * Operates on the given lexer struct.
 *
 * @param self - The corresponding lexer struct.
 *
 * @return The escaped version of the current character.
 */
char lexer_escapeChr(struct Lexer *self) {
	switch (self->chr) {
	case 'b':
		return '\b';
	case 'f':
		return '\f';
	case 'n':
		return '\n';
	case 'r':
		return '\r';
	case 't':
		return '\t';
	case 'v':
		return '\v';
	case '\'':
		return '\'';
	case '"':
		return '"';
	case '\\':
		return '\\';
	}

	lexer_error(self, "invalid escape sequence",
				lexerToken_new("", LEXERTOKENS_NONE, self->chrIndex - 1,
							   self->chrIndex, self->lineNum));
}

/**
 * Checks for a trailing character.
 * Operates on the given lexer struct.
 *
 * @param self - The corresponding lexer struct.
 *
 * @return Whether the trailing character was found.
 */
bool lexer_checkForTrailingChr(struct Lexer *self, char chr) {
	bool found = true;

	if (lexer_getChr(self, false)) {
		if (self->chr != chr) {
			found = false;
		}
	} else {
		found = false;
	}

	if (!found) {
		lexer_unGetChr(self); // Only if a match is not found.
	}

	return found;
}

/**
 * Checks for an unexpected continuation of the current token.
 * Operates on the given lexer struct.
 *
 * @param self  - The corresponding lexer struct.
 * @param token - The current token.
 */
void lexer_checkForContinuation(struct Lexer *self, const char *token) {
	if (lexer_getChr(self, false)) {
		if (!isspace(self->chr) && !isalnum(self->chr)) {
			lexer_error(self,
						stringConcatenate(3,
										  "unexpected continuation of token '",
										  token, "'"),
						NULL);
		}

		lexer_unGetChr(self);
	}
}

/**
 * Lex a '=' token.
 * Operates on the given lexer struct.
 *
 * @param self - The corresponding lexer struct.
 */
void lexer_lexEquals(struct Lexer *self) {
	const struct LexerToken *token = NULL;

	if (lexer_checkForTrailingChr(self, self->chr)) {
		token = lexerToken_new("==", LEXERTOKENS_EQUAL_TO, self->chrIndex - 1,
							   self->chrIndex, self->lineNum);
	} else {
		token = lexerToken_new("=", LEXERTOKENS_ASSIGNMENT, self->chrIndex - 1,
							   self->chrIndex, self->lineNum);
	}

	array_insert(self->tokens, self->tokens->length, token);

	lexer_checkForContinuation(self, token->value);
}

/**
 * Lex a character.
 * Operates on the given lexer struct.
 *
 * @param self - The corresponding lexer struct.
 */
void lexChr(struct Lexer *self) {
	bool includeChr = false;
	char *chr = NULL;
	size_t chrLen = 0, startChrIndex = self->chrIndex;

	while (lexer_getChr(self, false)) {
		if (chrLen > 1) {
			lexer_error(self, "multi-character char",
						lexerToken_new("", LEXERTOKENS_NONE, startChrIndex,
									   self->chrIndex, self->lineNum));
		}

		if (self->chr == '\'') {
			array_insert(self->tokens, self->tokens->length,
						 lexerToken_new(chr, LEXERTOKENS_CHR, startChrIndex,
										self->chrIndex, self->lineNum));
			return;
		}

		chrLen++;

		if (includeChr) {
			chr += lexer_escapeChr(self);
			includeChr = false;
		} else if (self->chr != '\\') {
			chr += self->chr;
		} else {
			chrLen--;
			includeChr = true;
		}
	}

	lexer_unGetChr(self);
	lexer_error(self, "unterminated char", NULL);
}
