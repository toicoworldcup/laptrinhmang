#ifndef __ERROR_H__
#define __ERROR_H__

// Ð?nh nghia enum ErrorCode cho các l?i
typedef enum {
    ERR_ENDOFCOMMENT,              // L?i k?t thúc comment
    ERR_IDENTTOOLONG,              // L?i tên quá dài
    ERR_INVALIDCHARCONSTANT,       // L?i h?ng char không h?p l?
    ERR_INVALIDSYMBOL,             // L?i ký t? không h?p l?
    ERR_INVALID_CHARCONST,         // L?i ký t? h?ng không h?p l? (dùng trong scanner.c)
    ERR_UNKNOWN_CHAR               // L?i ký t? không xác d?nh (dùng trong scanner.c)
} ErrorCode;

// Ð?nh nghia thông báo l?i
#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALID_CHARCONST "Invalid char constant!"
#define ERM_UNKNOWN_CHAR "Unknown char!"

// Hàm x? lý l?i
void error(ErrorCode err, int lineNo, int colNo);

#endif

