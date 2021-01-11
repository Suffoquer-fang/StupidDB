/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DATABASE = 258,
     DATABASES = 259,
     TABLE = 260,
     TABLES = 261,
     SHOW = 262,
     CREATE = 263,
     DROP = 264,
     USE = 265,
     PRIMARY = 266,
     KEY = 267,
     NOT = 268,
     SQLNULL = 269,
     INSERT = 270,
     INTO = 271,
     VALUES = 272,
     DELETE = 273,
     FROM = 274,
     WHERE = 275,
     UPDATE = 276,
     SET = 277,
     SELECT = 278,
     IS = 279,
     TOKEN_INT = 280,
     VARCHAR = 281,
     DEFAULT = 282,
     CONSTRAINT = 283,
     CHANGE = 284,
     ALTER = 285,
     ADD = 286,
     RENAME = 287,
     DESC = 288,
     INDEX = 289,
     AND = 290,
     DATE = 291,
     FLOAT = 292,
     FOREIGN = 293,
     REFERENCES = 294,
     ON = 295,
     TO = 296,
     EXIT = 297,
     EQ = 298,
     NE = 299,
     LT = 300,
     GT = 301,
     LE = 302,
     GE = 303,
     IDENTIFIER = 304,
     VALUE_INT = 305,
     VALUE_FLOAT = 306,
     VALUE_STRING = 307
   };
#endif
/* Tokens.  */
#define DATABASE 258
#define DATABASES 259
#define TABLE 260
#define TABLES 261
#define SHOW 262
#define CREATE 263
#define DROP 264
#define USE 265
#define PRIMARY 266
#define KEY 267
#define NOT 268
#define SQLNULL 269
#define INSERT 270
#define INTO 271
#define VALUES 272
#define DELETE 273
#define FROM 274
#define WHERE 275
#define UPDATE 276
#define SET 277
#define SELECT 278
#define IS 279
#define TOKEN_INT 280
#define VARCHAR 281
#define DEFAULT 282
#define CONSTRAINT 283
#define CHANGE 284
#define ALTER 285
#define ADD 286
#define RENAME 287
#define DESC 288
#define INDEX 289
#define AND 290
#define DATE 291
#define FLOAT 292
#define FOREIGN 293
#define REFERENCES 294
#define ON 295
#define TO 296
#define EXIT 297
#define EQ 298
#define NE 299
#define LT 300
#define GT 301
#define LE 302
#define GE 303
#define IDENTIFIER 304
#define VALUE_INT 305
#define VALUE_FLOAT 306
#define VALUE_STRING 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

