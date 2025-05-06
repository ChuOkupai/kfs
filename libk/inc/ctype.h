#pragma once

/**
 * Checks if a character is alphanumeric.
 * @param c The character to check.
 * @return Non-zero if the character is alphanumeric, zero otherwise.
 */
int isalnum(int c);

/**
 * Checks if a character is alphabetic.
 * @param c The character to check.
 * @return Non-zero if the character is alphabetic, zero otherwise.
 */
int isalpha(int c);

/**
 * Checks if a character is a valid ASCII character.
 * @param c The character to check.
 * @return Non-zero if the character is ASCII, zero otherwise.
 */
int isascii(int c);

/**
 * Checks if a character is blank (space or tab).
 * @param c The character to check.
 * @return Non-zero if the character is blank, zero otherwise.
 */
int isblank(int c);

/**
 * Checks if a character is a control character.
 * @param c The character to check.
 * @return Non-zero if the character is a control character, zero otherwise.
 */
int iscntrl(int c);

/**
 * Checks if a character is a digit.
 * @param c The character to check.
 * @return Non-zero if the character is a digit, zero otherwise.
 */
int isdigit(int c);

/**
 * Checks if a character is printable and not a space.
 * @param c The character to check.
 * @return Non-zero if the character is graphical, zero otherwise.
 */
int isgraph(int c);

/**
 * Checks if a character is lowercase.
 * @param c The character to check.
 * @return Non-zero if the character is lowercase, zero otherwise.
 */
int islower(int c);

/**
 * Checks if a character is printable.
 * @param c The character to check.
 * @return Non-zero if the character is printable, zero otherwise.
 */
int isprint(int c);

/**
 * Checks if a character is a punctuation character.
 * @param c The character to check.
 * @return Non-zero if the character is punctuation, zero otherwise.
 */
int ispunct(int c);

/**
 * Checks if a character is a whitespace character.
 * @param c The character to check.
 * @return Non-zero if the character is whitespace, zero otherwise.
 */
int isspace(int c);

/**
 * Checks if a character is uppercase.
 * @param c The character to check.
 * @return Non-zero if the character is uppercase, zero otherwise.
 */
int isupper(int c);

/**
 * Checks if a character is a hexadecimal digit.
 * @param c The character to check.
 * @return Non-zero if the character is a hexadecimal digit, zero otherwise.
 */
int isxdigit(int c);

/**
 * Converts a character to lowercase.
 * @param c The character to convert.
 * @return The lowercase version of the character, or the character unchanged if not uppercase.
 */
int tolower(int c);

/**
 * Converts a character to uppercase.
 * @param c The character to convert.
 * @return The uppercase version of the character, or the character unchanged if not lowercase.
 */
int toupper(int c);
