#ifndef __CHARCODE_H__
#define __CHARCODE_H__

#define MAX_NUMBER_LEN 10 // Ho?c giá tr? phù h?p v?i yêu c?u c?a b?n

typedef enum {
  CHAR_SPACE,
  CHAR_LETTER,
  CHAR_DIGIT,
  CHAR_PLUS,
  CHAR_MINUS,
  CHAR_TIMES,
  CHAR_SLASH,
  CHAR_LT,
  CHAR_GT,
  CHAR_EXCLAIMATION,
  CHAR_EQ,
  CHAR_COMMA,
  CHAR_PERIOD,
  CHAR_COLON,
  CHAR_SEMICOLON,
  CHAR_SINGLEQUOTE,
  CHAR_LPAR,
  CHAR_RPAR,
  CHAR_TAB,           // Thêm CHAR_TAB
  CHAR_NEWLINE,       // Thêm CHAR_NEWLINE
  CHAR_UNKNOWN
} CharCode;

extern CharCode charCodes[256];  // Khai báo m?ng charCodes ki?u CharCode

void initializeCharCodes();  // Khai báo hàm kh?i t?o m?ng charCodes

#endif

