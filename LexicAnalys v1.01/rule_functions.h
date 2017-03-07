/*
 * rule_functions.h
 *
 *  Created on: 19.12.2010
 *      Author: Serov Artem, Penkin Ivan, Krepak Vitaliy, Kovalkov Konstantin, Smirnov Igor
 */

#ifndef RULEFUNCTIONS_H_INCLUDED
#define RULEFUNCTIONS_H_INCLUDED
int   Error              	(char* cur, int code, int count);
int   AddToken           	(char* cur, int code, int count);
int   DoNothing          	(char* cur, int code, int count);
int   NumConcat          	(char* cur, int code, int count);
int   NameConcat         	(char* cur, int code, int count);

#endif // RULEFUNCTIONS_H_INCLUDED
