#ifndef __ERROR_H__
#define __ERROR_H__

// �?nh nghia enum ErrorCode cho c�c l?i
typedef enum {
    ERR_ENDOFCOMMENT,              // L?i k?t th�c comment
    ERR_IDENTTOOLONG,              // L?i t�n qu� d�i
    ERR_INVALIDCHARCONSTANT,       // L?i h?ng char kh�ng h?p l?
    ERR_INVALIDSYMBOL,             // L?i k� t? kh�ng h?p l?
    ERR_INVALID_CHARCONST,         // L?i k� t? h?ng kh�ng h?p l? (d�ng trong scanner.c)
    ERR_UNKNOWN_CHAR               // L?i k� t? kh�ng x�c d?nh (d�ng trong scanner.c)
} ErrorCode;

// �?nh nghia th�ng b�o l?i
#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALID_CHARCONST "Invalid char constant!"
#define ERM_UNKNOWN_CHAR "Unknown char!"

// H�m x? l� l?i
void error(ErrorCode err, int lineNo, int colNo);

#endif

