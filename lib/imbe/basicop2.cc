/*
 * Project 25 IMBE Encoder/Decoder Fixed-Point implementation
 * Developed by Pavel Yazev E-mail: pyazev@gmail.com
 * Version 1.0 (c) Copyright 2009
 * 
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * The software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Boston, MA
 * 02110-1301, USA.
 */

/*___________________________________________________________________________
  |                                                                           |
  | Basic arithmetic operators.                                               |
  |                                                                           |
  | $Id $
  |___________________________________________________________________________|
*/

/*___________________________________________________________________________
  |                                                                           |
  |   Include-Files                                                           |
  |___________________________________________________________________________|
*/

#include <stdio.h>
#include <stdlib.h>

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#include "basic_op.h"

#if (WMOPS)
#include "count.h"
extern BASIC_OP multiCounter[MAXCOUNTERS];
extern int currCounter;

#endif

/*___________________________________________________________________________
  |                                                                           |
  |   Local Functions                                                         |
  |___________________________________________________________________________|
*/
int16_t saturate (int32_t L_var1);

/*___________________________________________________________________________
  |                                                                           |
  |   Constants and Globals                                                   |
  |___________________________________________________________________________|
*/
bool Overflow = 0;
bool Carry = 0;

/*___________________________________________________________________________
  |                                                                           |
  |   Functions                                                               |
  |___________________________________________________________________________|
*/

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : saturate                                                |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Limit the 32 bit input to the range of a 16 bit word.                  |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t 
saturate (int32_t L_var1)
{
   int16_t var_out;

   if (L_var1 > 0X00007fffL) {
      Overflow = 1;
      var_out = INT16_MAX;
   } else if (L_var1 < (int32_t) 0xffff8000L) {
      Overflow = 1;
      var_out = INT16_MIN;
   } else {
      var_out = extract_l (L_var1);
#if (WMOPS)
      multiCounter[currCounter].extract_l--;
#endif
   }

   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : add                                                     |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Performs the addition (var1+var2) with overflow control and saturation;|
  |    the 16 bit result is set at +32767 when overflow occurs or at -32768   |
  |    when underflow occurs.                                                 |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t
add(int16_t var1, int16_t var2)
{
   int16_t var_out;
   int32_t L_sum;

   L_sum = (int32_t) var1 + var2;
   var_out = saturate (L_sum);
#if (WMOPS)
   multiCounter[currCounter].add++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : sub                                                     |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Performs the subtraction (var1+var2) with overflow control and satu-   |
  |    ration; the 16 bit result is set at +32767 when overflow occurs or at  |
  |    -32768 when underflow occurs.                                          |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t sub (int16_t var1, int16_t var2)
{
   int16_t var_out;
   int32_t L_diff;

   L_diff = (int32_t) var1 - var2;
   var_out = saturate (L_diff);
#if (WMOPS)
   multiCounter[currCounter].sub++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : abs_s                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Absolute value of var1; abs_s(-32768) = 32767.                         |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 0000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t abs_s (int16_t var1)
{
   int16_t var_out;

   if (var1 == (int16_t) 0X8000)
   {
      var_out = INT16_MAX;
   }
   else
   {
      if (var1 < 0)
      {
         var_out = -var1;
      }
      else
      {
         var_out = var1;
      }
   }
#if (WMOPS)
   multiCounter[currCounter].abs_s++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : shl                                                     |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Arithmetically shift the 16 bit input var1 left var2 positions.Zero fill|
  |   the var2 LSB of the result. If var2 is negative, arithmetically shift   |
  |   var1 right by -var2 with sign extension. Saturate the result in case of |
  |   underflows or overflows.                                                |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t shl (int16_t var1, int16_t var2)
{
   int16_t var_out;
   int32_t result;

   if (var2 < 0)
   {
      if (var2 < -16)
         var2 = -16;
      var_out = shr (var1, -var2);
#if (WMOPS)
      multiCounter[currCounter].shr--;
#endif
   }
   else
   {
      result = (int32_t) var1 *((int32_t) 1 << var2);

      if ((var2 > 15 && var1 != 0) || (result != (int32_t) ((int16_t) result)))
      {
         Overflow = 1;
         var_out = (var1 > 0) ? INT16_MAX : INT16_MIN;
      }
      else
      {
         var_out = extract_l (result);
#if (WMOPS)
         multiCounter[currCounter].extract_l--;
#endif
      }
   }
#if (WMOPS)
   multiCounter[currCounter].shl++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : shr                                                     |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Arithmetically shift the 16 bit input var1 right var2 positions with    |
  |   sign extension. If var2 is negative, arithmetically shift var1 left by  |
  |   -var2 with sign extension. Saturate the result in case of underflows or |
  |   overflows.                                                              |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t shr (int16_t var1, int16_t var2)
{
   int16_t var_out;

   if (var2 < 0)
   {
      if (var2 < -16)
         var2 = -16;
      var_out = shl (var1, -var2);
#if (WMOPS)
      multiCounter[currCounter].shl--;
#endif
   }
   else
   {
      if (var2 >= 15)
      {
         var_out = (var1 < 0) ? -1 : 0;
      }
      else
      {
         if (var1 < 0)
         {
            var_out = ~((~var1) >> var2);
         }
         else
         {
            var_out = var1 >> var2;
         }
      }
   }

#if (WMOPS)
   multiCounter[currCounter].shr++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : mult                                                    |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Performs the multiplication of var1 by var2 and gives a 16 bit result  |
  |    which is scaled i.e.:                                                  |
  |             mult(var1,var2) = extract_l(L_shr((var1 times var2),15)) and  |
  |             mult(-32768,-32768) = 32767.                                  |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t mult (int16_t var1, int16_t var2)
{
   int16_t var_out;
   int32_t L_product;

   L_product = (int32_t) var1 *(int32_t) var2;

   L_product = (L_product & (int32_t) 0xffff8000L) >> 15;

   if (L_product & (int32_t) 0x00010000L)
      L_product = L_product | (int32_t) 0xffff0000L;

   var_out = saturate (L_product);
#if (WMOPS)
   multiCounter[currCounter].mult++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_mult                                                  |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   L_mult is the 32 bit result of the multiplication of var1 times var2    |
  |   with one shift left i.e.:                                               |
  |        L_mult(var1,var2) = L_shl((var1 times var2),1) and                   |
  |        L_mult(-32768,-32768) = 2147483647.                                |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_mult (int16_t var1, int16_t var2)
{
   int32_t L_var_out;

   L_var_out = (int32_t) var1 *(int32_t) var2;

   if (L_var_out != (int32_t) 0x40000000L)
   {
      L_var_out *= 2;
   }
   else
   {
      Overflow = 1;
      L_var_out = INT32_MAX;
   }

#if (WMOPS)
   multiCounter[currCounter].L_mult++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : negate                                                  |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Negate var1 with saturation, saturate in the case where input is -32768:|
  |                negate(var1) = sub(0,var1).                                |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t negate (int16_t var1)
{
   int16_t var_out;

   var_out = (var1 == INT16_MIN) ? INT16_MAX : -var1;
#if (WMOPS)
   multiCounter[currCounter].negate++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : extract_h                                               |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Return the 16 MSB of L_var1.                                            |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t ) whose value falls in the |
  |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t extract_h (int32_t L_var1)
{
   int16_t var_out;

   var_out = (int16_t) (L_var1 >> 16);
#if (WMOPS)
   multiCounter[currCounter].extract_h++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : extract_l                                               |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Return the 16 LSB of L_var1.                                            |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t ) whose value falls in the |
  |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t extract_l (int32_t L_var1)
{
   int16_t var_out;

   var_out = (int16_t) L_var1;
#if (WMOPS)
   multiCounter[currCounter].extract_l++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : round                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Round the lower 16 bits of the 32 bit input number into the MS 16 bits  |
  |   with saturation. Shift the resulting bits right by 16 and return the 16 |
  |   bit number:                                                             |
  |               round(L_var1) = extract_h(L_add(L_var1,32768))              |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t ) whose value falls in the |
  |             range : 0x8000 0000 <= L_var1 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t round (int32_t L_var1)
{
   int16_t var_out;
   int32_t L_rounded;

   L_rounded = L_add (L_var1, (int32_t) 0x00008000L);
#if (WMOPS)
   multiCounter[currCounter].L_add--;
#endif
   var_out = extract_h (L_rounded);
#if (WMOPS)
   multiCounter[currCounter].extract_h--;
   multiCounter[currCounter].round++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_mac                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
  |   result to L_var3 with saturation, return a 32 bit result:               |
  |        L_mac(L_var3,var1,var2) = L_add(L_var3,L_mult(var1,var2)).         |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_mac (int32_t L_var3, int16_t var1, int16_t var2)
{
   int32_t L_var_out;
   int32_t L_product;

   L_product = L_mult (var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_mult--;
#endif
   L_var_out = L_add (L_var3, L_product);
#if (WMOPS)
   multiCounter[currCounter].L_add--;
   multiCounter[currCounter].L_mac++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_msu                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
  |   bit result to L_var3 with saturation, return a 32 bit result:           |
  |        L_msu(L_var3,var1,var2) = L_sub(L_var3,L_mult(var1,var2)).         |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_msu (int32_t L_var3, int16_t var1, int16_t var2)
{
   int32_t L_var_out;
   int32_t L_product;

   L_product = L_mult (var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_mult--;
#endif
   L_var_out = L_sub (L_var3, L_product);
#if (WMOPS)
   multiCounter[currCounter].L_sub--;
   multiCounter[currCounter].L_msu++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_macNs                                                 |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
  |   result to L_var3 without saturation, return a 32 bit result. Generate   |
  |   carry and overflow values :                                             |
  |        L_macNs(L_var3,var1,var2) = L_add_c(L_var3,L_mult(var1,var2)).     |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |                                                                           |
  |   Caution :                                                               |
  |                                                                           |
  |    In some cases the Carry flag has to be cleared or set before using     |
  |    operators which take into account its value.                           |
  |___________________________________________________________________________|
*/

int32_t L_macNs (int32_t L_var3, int16_t var1, int16_t var2)
{
   int32_t L_var_out;

   L_var_out = L_mult (var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_mult--;
#endif
   L_var_out = L_add_c (L_var3, L_var_out);
#if (WMOPS)
   multiCounter[currCounter].L_add_c--;
   multiCounter[currCounter].L_macNs++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_msuNs                                                 |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
  |   bit result from L_var3 without saturation, return a 32 bit result. Ge-  |
  |   nerate carry and overflow values :                                      |
  |        L_msuNs(L_var3,var1,var2) = L_sub_c(L_var3,L_mult(var1,var2)).     |
  |                                                                           |
  |   Complexity weight : 1                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |                                                                           |
  |   Caution :                                                               |
  |                                                                           |
  |    In some cases the Carry flag has to be cleared or set before using     |
  |    operators which take into account its value.                           |
  |___________________________________________________________________________|
*/

int32_t L_msuNs (int32_t L_var3, int16_t var1, int16_t var2)
{
   int32_t L_var_out;

   L_var_out = L_mult (var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_mult--;
#endif
   L_var_out = L_sub_c (L_var3, L_var_out);
#if (WMOPS)
   multiCounter[currCounter].L_sub_c--;
   multiCounter[currCounter].L_msuNs++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_add                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   32 bits addition of the two 32 bits variables (L_var1+L_var2) with      |
  |   overflow control and saturation; the result is set at +2147483647 when  |
  |   overflow occurs or at -2147483648 when underflow occurs.                |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    L_var2   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_add (int32_t L_var1, int32_t L_var2)
{
   int32_t L_var_out;

   L_var_out = L_var1 + L_var2;

   if (((L_var1 ^ L_var2) & INT32_MIN) == 0)
   {
      if ((L_var_out ^ L_var1) & INT32_MIN)
      {
         L_var_out = (L_var1 < 0) ? INT32_MIN : INT32_MAX;
         Overflow = 1;
      }
   }
#if (WMOPS)
   multiCounter[currCounter].L_add++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_sub                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   32 bits subtraction of the two 32 bits variables (L_var1-L_var2) with   |
  |   overflow control and saturation; the result is set at +2147483647 when  |
  |   overflow occurs or at -2147483648 when underflow occurs.                |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    L_var2   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_sub (int32_t L_var1, int32_t L_var2)
{
   int32_t L_var_out;

   L_var_out = L_var1 - L_var2;

   if (((L_var1 ^ L_var2) & INT32_MIN) != 0)
   {
      if ((L_var_out ^ L_var1) & INT32_MIN)
      {
         L_var_out = (L_var1 < 0L) ? INT32_MIN : INT32_MAX;
         Overflow = 1;
      }
   }
#if (WMOPS)
   multiCounter[currCounter].L_sub++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_add_c                                                 |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Performs 32 bits addition of the two 32 bits variables (L_var1+L_var2+C)|
  |   with carry. No saturation. Generate carry and Overflow values. The car- |
  |   ry and overflow values are binary variables which can be tested and as- |
  |   signed values.                                                          |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    L_var2   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |                                                                           |
  |   Caution :                                                               |
  |                                                                           |
  |    In some cases the Carry flag has to be cleared or set before using     |
  |    operators which take into account its value.                           |
  |___________________________________________________________________________|
*/
int32_t L_add_c (int32_t L_var1, int32_t L_var2)
{
   int32_t L_var_out;
   int32_t L_test;
   bool carry_int = 0;

   L_var_out = L_var1 + L_var2 + Carry;

   L_test = L_var1 + L_var2;

   if ((L_var1 > 0) && (L_var2 > 0) && (L_test < 0))
   {
      Overflow = 1;
      carry_int = 0;
   }
   else
   {
      if ((L_var1 < 0) && (L_var2 < 0))
      {
         if (L_test >= 0)
         {
            Overflow = 1;
            carry_int = 1;
         }
         else
         {
            Overflow = 0;
            carry_int = 1;
         }
      }
      else
      {
         if (((L_var1 ^ L_var2) < 0) && (L_test >= 0))
         {
            Overflow = 0;
            carry_int = 1;
         }
         else
         {
            Overflow = 0;
            carry_int = 0;
         }
      }
   }

   if (Carry)
   {
      if (L_test == INT32_MAX)
      {
         Overflow = 1;
         Carry = carry_int;
      }
      else
      {
         if (L_test == (int32_t) 0xFFFFFFFFL)
         {
            Carry = 1;
         }
         else
         {
            Carry = carry_int;
         }
      }
   }
   else
   {
      Carry = carry_int;
   }

#if (WMOPS)
   multiCounter[currCounter].L_add_c++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_sub_c                                                 |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Performs 32 bits subtraction of the two 32 bits variables with carry    |
  |   (borrow) : L_var1-L_var2-C. No saturation. Generate carry and Overflow  |
  |   values. The carry and overflow values are binary variables which can    |
  |   be tested and assigned values.                                          |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    L_var2   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |                                                                           |
  |   Caution :                                                               |
  |                                                                           |
  |    In some cases the Carry flag has to be cleared or set before using     |
  |    operators which take into account its value.                           |
  |___________________________________________________________________________|
*/

int32_t L_sub_c (int32_t L_var1, int32_t L_var2)
{
   int32_t L_var_out;
   int32_t L_test;
   bool carry_int = 0;

   if (Carry)
   {
      Carry = 0;
      if (L_var2 != INT32_MIN)
      {
         L_var_out = L_add_c (L_var1, -L_var2);
#if (WMOPS)
         multiCounter[currCounter].L_add_c--;
#endif
      }
      else
      {
         L_var_out = L_var1 - L_var2;
         if (L_var1 > 0L)
         {
            Overflow = 1;
            Carry = 0;
         }
      }
   }
   else
   {
      L_var_out = L_var1 - L_var2 - (int32_t) 0X00000001L;
      L_test = L_var1 - L_var2;

      if ((L_test < 0) && (L_var1 > 0) && (L_var2 < 0))
      {
         Overflow = 1;
         carry_int = 0;
      }
      else if ((L_test > 0) && (L_var1 < 0) && (L_var2 > 0))
      {
         Overflow = 1;
         carry_int = 1;
      }
      else if ((L_test > 0) && ((L_var1 ^ L_var2) > 0))
      {
         Overflow = 0;
         carry_int = 1;
      }
      if (L_test == INT32_MIN)
      {
         Overflow = 1;
         Carry = carry_int;
      }
      else
      {
         Carry = carry_int;
      }
   }

#if (WMOPS)
   multiCounter[currCounter].L_sub_c++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_negate                                                |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Negate the 32 bit variable L_var1 with saturation; saturate in the case |
  |   where input is -2147483648 (0x8000 0000).                               |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_negate (int32_t L_var1)
{
   int32_t L_var_out;

   L_var_out = (L_var1 == INT32_MIN) ? INT32_MAX : -L_var1;
#if (WMOPS)
   multiCounter[currCounter].L_negate++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : mult_r                                                  |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Same as mult with rounding, i.e.:                                       |
  |     mult_r(var1,var2) = extract_l(L_shr(((var1 * var2) + 16384),15)) and  |
  |     mult_r(-32768,-32768) = 32767.                                        |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t mult_r (int16_t var1, int16_t var2)
{
   int16_t var_out;
   int32_t L_product_arr;

   L_product_arr = (int32_t) var1 *(int32_t) var2;       /* product */
   L_product_arr += (int32_t) 0x00004000L;      /* round */
   L_product_arr &= (int32_t) 0xffff8000L;
   L_product_arr >>= 15;       /* shift */

   if (L_product_arr & (int32_t) 0x00010000L)   /* sign extend when necessary */
   {
      L_product_arr |= (int32_t) 0xffff0000L;
   }
   var_out = saturate (L_product_arr);
#if (WMOPS)
   multiCounter[currCounter].mult_r++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_shl                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Arithmetically shift the 32 bit input L_var1 left var2 positions. Zero  |
  |   fill the var2 LSB of the result. If var2 is negative, arithmetically    |
  |   shift L_var1 right by -var2 with sign extension. Saturate the result in |
  |   case of underflows or overflows.                                        |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_shl (int32_t L_var1, int16_t var2)
{
   int32_t L_var_out=0;

   if (var2 <= 0)
   {
      if (var2 < -32)
         var2 = -32;
      L_var_out = L_shr (L_var1, -var2);
#if (WMOPS)
      multiCounter[currCounter].L_shr--;
#endif
   }
   else
   {
      for (; var2 > 0; var2--)
      {
         if (L_var1 > (int32_t) 0X3fffffffL)
         {
            Overflow = 1;
            L_var_out = INT32_MAX;
            break;
         }
         else
         {
            if (L_var1 < (int32_t) 0xc0000000L)
            {
               Overflow = 1;
               L_var_out = INT32_MIN;
               break;
            }
         }
         L_var1 *= 2;
         L_var_out = L_var1;
      }
   }
#if (WMOPS)
   multiCounter[currCounter].L_shl++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_shr                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Arithmetically shift the 32 bit input L_var1 right var2 positions with  |
  |   sign extension. If var2 is negative, arithmetically shift L_var1 left   |
  |   by -var2 and zero fill the -var2 LSB of the result. Saturate the result |
  |   in case of underflows or overflows.                                     |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var_out <= 0x7fff ffff.              |
  |___________________________________________________________________________|
*/

int32_t L_shr (int32_t L_var1, int16_t var2)
{
   int32_t L_var_out;

   if (var2 < 0)
   {
      if (var2 < -32)
         var2 = -32;
      L_var_out = L_shl (L_var1, -var2);
#if (WMOPS)
      multiCounter[currCounter].L_shl--;
#endif
   }
   else
   {
      if (var2 >= 31)
      {
         L_var_out = (L_var1 < 0L) ? -1 : 0;
      }
      else
      {
         if (L_var1 < 0)
         {
            L_var_out = ~((~L_var1) >> var2);
         }
         else
         {
            L_var_out = L_var1 >> var2;
         }
      }
   }
#if (WMOPS)
   multiCounter[currCounter].L_shr++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : shr_r                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Same as shr(var1,var2) but with rounding. Saturate the result in case of|
  |   underflows or overflows :                                               |
  |    - If var2 is greater than zero :                                       |
  |          if (sub(shl(shr(var1,var2),1),shr(var1,sub(var2,1))))            |
  |          is equal to zero                                                 |
  |                     then                                                  |
  |                     shr_r(var1,var2) = shr(var1,var2)                     |
  |                     else                                                  |
  |                     shr_r(var1,var2) = add(shr(var1,var2),1)              |
  |    - If var2 is less than or equal to zero :                              |
  |                     shr_r(var1,var2) = shr(var1,var2).                    |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int16_t shr_r (int16_t var1, int16_t var2)
{
   int16_t var_out;

   if (var2 > 15)
   {
      var_out = 0;
   }
   else
   {
      var_out = shr (var1, var2);
#if (WMOPS)
      multiCounter[currCounter].shr--;
#endif

      if (var2 > 0)
      {
         if ((var1 & ((int16_t) 1 << (var2 - 1))) != 0)
         {
            var_out++;
         }
      }
   }
#if (WMOPS)
   multiCounter[currCounter].shr_r++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : mac_r                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Add the 32 bit    |
  |   result to L_var3 with saturation. Round the LS 16 bits of the result    |
  |   into the MS 16 bits with saturation and shift the result right by 16.   |
  |   Return a 16 bit result.                                                 |
  |            mac_r(L_var3,var1,var2) = round(L_mac(L_var3,var1,var2))       |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 8000 <= L_var_out <= 0x0000 7fff.              |
  |___________________________________________________________________________|
*/

int16_t mac_r (int32_t L_var3, int16_t var1, int16_t var2)
{
   int16_t var_out;

   L_var3 = L_mac (L_var3, var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_mac--;
#endif
   L_var3 = L_add (L_var3, (int32_t) 0x00008000L);
#if (WMOPS)
   multiCounter[currCounter].L_add--;
#endif
   var_out = extract_h (L_var3);
#if (WMOPS)
   multiCounter[currCounter].extract_h--;
   multiCounter[currCounter].mac_r++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : msu_r                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Multiply var1 by var2 and shift the result left by 1. Subtract the 32   |
  |   bit result to L_var3 with saturation. Round the LS 16 bits of the res-  |
  |   ult into the MS 16 bits with saturation and shift the result right by   |
  |   16. Return a 16 bit result.                                             |
  |            msu_r(L_var3,var1,var2) = round(L_msu(L_var3,var1,var2))       |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var3   32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= L_var3 <= 0x7fff ffff.                 |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 8000 <= L_var_out <= 0x0000 7fff.              |
  |___________________________________________________________________________|
*/

int16_t msu_r (int32_t L_var3, int16_t var1, int16_t var2)
{
   int16_t var_out;

   L_var3 = L_msu (L_var3, var1, var2);
#if (WMOPS)
   multiCounter[currCounter].L_msu--;
#endif
   L_var3 = L_add (L_var3, (int32_t) 0x00008000L);
#if (WMOPS)
   multiCounter[currCounter].L_add--;
#endif
   var_out = extract_h (L_var3);
#if (WMOPS)
   multiCounter[currCounter].extract_h--;
   multiCounter[currCounter].msu_r++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_deposit_h                                             |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Deposit the 16 bit var1 into the 16 MS bits of the 32 bit output. The   |
  |   16 LS bits of the output are zeroed.                                    |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var_out <= 0x7fff 0000.                |
  |___________________________________________________________________________|
*/

int32_t L_deposit_h (int16_t var1)
{
   int32_t L_var_out;

   L_var_out = (int32_t) var1 << 16;
#if (WMOPS)
   multiCounter[currCounter].L_deposit_h++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_deposit_l                                             |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Deposit the 16 bit var1 into the 16 LS bits of the 32 bit output. The   |
  |   16 MS bits of the output are sign extended.                             |
  |                                                                           |
  |   Complexity weight : 2                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0xFFFF 8000 <= var_out <= 0x0000 7fff.                |
  |___________________________________________________________________________|
*/

int32_t L_deposit_l (int16_t var1)
{
   int32_t L_var_out;

   L_var_out = (int32_t) var1;
#if (WMOPS)
   multiCounter[currCounter].L_deposit_l++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_shr_r                                                 |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Same as L_shr(L_var1,var2) but with rounding. Saturate the result in    |
  |   case of underflows or overflows :                                       |
  |    - If var2 is greater than zero :                                       |
  |          if (L_sub(L_shl(L_shr(L_var1,var2),1),L_shr(L_var1,sub(var2,1))))|
  |          is equal to zero                                                 |
  |                     then                                                  |
  |                     L_shr_r(L_var1,var2) = L_shr(L_var1,var2)             |
  |                     else                                                  |
  |                     L_shr_r(L_var1,var2) = L_add(L_shr(L_var1,var2),1)    |
  |    - If var2 is less than or equal to zero :                              |
  |                     L_shr_r(L_var1,var2) = L_shr(L_var1,var2).            |
  |                                                                           |
  |   Complexity weight : 3                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var_out <= 0x7fff ffff.                |
  |___________________________________________________________________________|
*/

int32_t L_shr_r (int32_t L_var1, int16_t var2)
{
   int32_t L_var_out;

   if (var2 > 31)
   {
      L_var_out = 0;
   }
   else
   {
      L_var_out = L_shr (L_var1, var2);
#if (WMOPS)
      multiCounter[currCounter].L_shr--;
#endif
      if (var2 > 0)
      {
         if ((L_var1 & ((int32_t) 1 << (var2 - 1))) != 0)
         {
            L_var_out++;
         }
      }
   }
#if (WMOPS)
   multiCounter[currCounter].L_shr_r++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_abs                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    Absolute value of L_var1; Saturate in case where the input is          |
  |                                                               -214783648  |
  |                                                                           |
  |   Complexity weight : 3                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x0000 0000 <= var_out <= 0x7fff ffff.                |
  |___________________________________________________________________________|
*/

int32_t L_abs (int32_t L_var1)
{
   int32_t L_var_out;

   if (L_var1 == INT32_MIN)
   {
      L_var_out = INT32_MAX;
   }
   else
   {
      if (L_var1 < 0)
      {
         L_var_out = -L_var1;
      }
      else
      {
         L_var_out = L_var1;
      }
   }

#if (WMOPS)
   multiCounter[currCounter].L_abs++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : L_sat                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |    32 bit L_var1 is set to 2147483647 if an overflow occured or to        |
  |    -2147483648 if an underflow occured on the most recent L_add_c,        |
  |    L_sub_c, L_macNs or L_msuNs operations. The carry and overflow values  |
  |    are binary values which can be tested and assigned values.             |
  |                                                                           |
  |   Complexity weight : 4                                                   |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    L_var_out                                                              |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var_out <= 0x7fff ffff.                |
  |___________________________________________________________________________|
*/

int32_t L_sat (int32_t L_var1)
{
   int32_t L_var_out;

   L_var_out = L_var1;

   if (Overflow)
   {

      if (Carry)
      {
         L_var_out = INT32_MIN;
      }
      else
      {
         L_var_out = INT32_MAX;
      }

      Carry = 0;
      Overflow = 0;
   }
#if (WMOPS)
   multiCounter[currCounter].L_sat++;
#endif
   return (L_var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : norm_s                                                  |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Produces the number of left shift needed to normalize the 16 bit varia- |
  |   ble var1 for positive values on the interval with minimum of 16384 and  |
  |   maximum of 32767, and for negative values on the interval with minimum  |
  |   of -32768 and maximum of -16384; in order to normalize the result, the  |
  |   following operation must be done :                                      |
  |                    norm_var1 = shl(var1,norm_s(var1)).                    |
  |                                                                           |
  |   Complexity weight : 15                                                  |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0xffff 8000 <= var1 <= 0x0000 7fff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 0000 <= var_out <= 0x0000 000f.                |
  |___________________________________________________________________________|
*/

int16_t norm_s (int16_t var1)
{
   int16_t var_out;

   if (var1 == 0)
   {
      var_out = 0;
   }
   else
   {
      if (var1 == (int16_t) 0xffff)
      {
         var_out = 15;
      }
      else
      {
         if (var1 < 0)
         {
            var1 = ~var1;
         }
         for (var_out = 0; var1 < 0x4000; var_out++)
         {
            var1 <<= 1;
         }
      }
   }

#if (WMOPS)
   multiCounter[currCounter].norm_s++;
#endif
   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : div_s                                                   |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Produces a result which is the fractional integer division of var1  by  |
  |   var2; var1 and var2 must be positive and var2 must be greater or equal  |
  |   to var1; the result is positive (leading bit equal to 0) and truncated  |
  |   to 16 bits.                                                             |
  |   If var1 = var2 then div(var1,var2) = 32767.                             |
  |                                                                           |
  |   Complexity weight : 18                                                  |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    var1                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 0000 <= var1 <= var2 and var2 != 0.            |
  |                                                                           |
  |    var2                                                                   |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : var1 <= var2 <= 0x0000 7fff and var2 != 0.            |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 0000 <= var_out <= 0x0000 7fff.                |
  |             It's a Q15 value (point between b15 and b14).                 |
  |___________________________________________________________________________|
*/

int16_t
div_s (int16_t var1, int16_t var2)
{
   int16_t var_out = 0;
   int16_t iteration;
   int32_t L_num;
   int32_t L_denom;

   if((var1 > var2) || (var1 < 0) || (var2 < 0)) {
      printf ("Division Error var1=%d  var2=%d\n", var1, var2);
      abort(); /* exit (0); */
   }
   if(0 == var2) {
      printf ("Division by 0, Fatal error \n");
      abort(); /* exit (0); */
   }
   if (var1 == 0) {
      var_out = 0;
   } else {
      if (var1 == var2) {
         var_out = INT16_MAX;
      } else {
         L_num = L_deposit_l (var1);
#if (WMOPS)
         multiCounter[currCounter].L_deposit_l--;
#endif
         L_denom = L_deposit_l (var2);
#if (WMOPS)
         multiCounter[currCounter].L_deposit_l--;
#endif

         for (iteration = 0; iteration < 15; iteration++) {
            var_out <<= 1;
            L_num <<= 1;

            if (L_num >= L_denom) {
               L_num = L_sub (L_num, L_denom);
#if (WMOPS)
               multiCounter[currCounter].L_sub--;
#endif
               var_out = add (var_out, 1);
#if (WMOPS)
               multiCounter[currCounter].add--;
#endif
            }
         }
      }
   }

#if (WMOPS)
   multiCounter[currCounter].div_s++;
#endif

   return (var_out);
}

/*___________________________________________________________________________
  |                                                                           |
  |   Function Name : norm_l                                                  |
  |                                                                           |
  |   Purpose :                                                               |
  |                                                                           |
  |   Produces the number of left shifts needed to normalize the 32 bit varia-|
  |   ble L_var1 for positive values on the interval with minimum of          |
  |   1073741824 and maximum of 2147483647, and for negative values on the in-|
  |   terval with minimum of -2147483648 and maximum of -1073741824; in order |
  |   to normalize the result, the following operation must be done :         |
  |                   norm_L_var1 = L_shl(L_var1,norm_l(L_var1)).             |
  |                                                                           |
  |   Complexity weight : 30                                                  |
  |                                                                           |
  |   Inputs :                                                                |
  |                                                                           |
  |    L_var1                                                                 |
  |             32 bit long signed integer (int32_t) whose value falls in the  |
  |             range : 0x8000 0000 <= var1 <= 0x7fff ffff.                   |
  |                                                                           |
  |   Outputs :                                                               |
  |                                                                           |
  |    none                                                                   |
  |                                                                           |
  |   Return Value :                                                          |
  |                                                                           |
  |    var_out                                                                |
  |             16 bit short signed integer (int16_t) whose value falls in the |
  |             range : 0x0000 0000 <= var_out <= 0x0000 001f.                |
  |___________________________________________________________________________|
*/

int16_t
norm_l(int32_t L_var1)
{
   int16_t var_out;

   if(L_var1 == 0) {
      var_out = 0;
   } else {
      if (L_var1 == (int32_t) 0xffffffffL) {
         var_out = 31;
      } else {
         if (L_var1 < 0) {
            L_var1 = ~L_var1;
         }
         for(var_out = 0; L_var1 < (int32_t) 0x40000000L; var_out++)
         {
            L_var1 <<= 1;
         }
      }
   }

#if (WMOPS)
   multiCounter[currCounter].norm_l++;
#endif
   return (var_out);
}
