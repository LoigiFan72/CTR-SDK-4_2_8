/*---------------------------------------------------------------------------*
  Project:  Horizon
  File:     math_Equation.cpp

  Copyright (C)2009-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Rev: 46347 $
 *---------------------------------------------------------------------------*/

#include <nn/math.h>

#include <nn/math/math_Equation.h>
#include <nn/math/math_Arithmetic.h>
#include <nn/math/math_Triangular.h>
#include <nn/types.h>

namespace nn { namespace math {


namespace
{
    // Maximum error for determining equality
    const f32 EPS = 2e-4f;


    /*!--------------------------------------------------------------------------*
      Name:        spow<int>
    
      
                   
    
      
      
    
      
     *---------------------------------------------------------------------------*/
    template <int idx>
    NN_MATH_INLINE f32 
    spow(f32 x)
    {
        return spow<idx-1>(x) * x;
    }

    template <>
    NN_MATH_INLINE f32 
    spow<1>(f32 x)
    {
        return x;
    }

    /*!--------------------------------------------------------------------------*
      Name:        SolveEquation2
    
      
                   
    
      
                   
                   
      
    
      
                   
     *---------------------------------------------------------------------------*/
    int 
    SolveEquation2(f32* root, /*f32 a==1,*/ f32 b, f32 c)
    {
        if( b == 0 )
        {
            if( c < -EPS )      // c < 0
            {
                f32 r_c = FSqrt(-c);
                root[0] =   r_c;
                root[1] = - r_c;
                return 2;
            }
            else if( c <= EPS ) // c == 0
            {
                root[0] = 0;
                return 1;
            }
            else                // c > 0
            {
                return 0;
            }
        }
        else
        {
            f32 A = b / 2;
            f32 B = c / spow<2>(A);
            f32 D = 1 - B;

            if( D > 0 )
            {
                f32 C = -1 - FSqrt(D);

                root[0] = A * C;
                root[1] = A * B / C;

                return 2;
            }
            else if( FAbs(D) < EPS )
            {
                root[0] = -A;

                return 1;
            }
            else
            {
                return 0;
            }
        }
    }



    /*!--------------------------------------------------------------------------*
      Name:        SolveEquation3
    
      
                   
    
      
    
      
     *---------------------------------------------------------------------------*/
    f32 
    SolveEquation3(/*f32* root, f32 a==1,*/ f32 b, f32 c, f32 d)
    {
        f32 q   = (spow<2>(b) - 3 * c) / 9;
        f32 r   = (2 * spow<3>(b) - 9 * b * c + 27 * d) / 54;
        f32 D   = spow<3>(q) - spow<2>(r);
        f32 b_3 = b / 3;

        if( D > EPS )
        {
            f32 theta   = AcosRad( r / FSqrt(spow<3>(q)) );
            f32 theta_3 = theta/3;
            f32 r_q2    = -2 * FSqrt(q);

            return r_q2 * CosRad(theta_3) - b_3;
        }
        else if( D < - EPS )
        {
            f32 r3_Dr = FCbrt( FSqrt(- D) + FAbs(r) );
            f32 xp    = r3_Dr + q / r3_Dr;

            return - FCopySign(xp, r) - b_3;
        }
        else
        {
            f32 xp  = FSqrt(q);

            return FCopySign(xp, r) - b_3;
        }
    }
}







/*!--------------------------------------------------------------------------*
  Name:        SolveEquation2
  
  
               
               
  
               
  
               
 


 *---------------------------------------------------------------------------*/
int 
SolveEquation2(f32* root, f32 a, f32 b, f32 c)
{
    NN_POINTER_TASSERT_(root);
    NN_TASSERT_( a != 0 );

    if( b != 0 )
    {
        // Standard solution formula
        //   With the standard solution equation, x = {-b ± √(b^2 - 4ac)} / 2a, when finding a solution when the sign of -b and the ± of the -b ± √(omitted) portion, subtraction of close value occurs and precision drops a lot.
        //
        // 
        // To avoid this, set one side of the solution to x = b{-1 - √(1 - 4ac/b^2)} / 2a, factor out b, and solve. 
        //
        // 
        // For the other side, apply the relationship between the solution and the coefficients (αβ = a / c) to the above formula, and solve using x = 2c / b{-1 - √(1 - 4ac/b^2)}.
        //   
        // 
        //
        // 

        f32 A = b / (2 * a);
        f32 B = c / (a * A * A);
        f32 D = 1 - B;

        if( D > EPS )
        {
            f32 C = -1 - FSqrt(D);

            root[0] = A * C;
            root[1] = A * B / C;

            return 2;
        }
        else if( D >= - EPS )
        {
            root[0] = -A;

            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        // When using this method, division by 0 will occur if b = 0, so handle as appropriate. 

        f32 c_a = - c / a;

        if( c_a > EPS )
        {
            f32 r_c_a = FSqrt(c_a);
            root[0] = + r_c_a;
            root[1] = - r_c_a;
            return 2;
        }
        else if( c_a >= - EPS )
        {
            root[0] = 0;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}



/*!--------------------------------------------------------------------------*
  Name:        SolveEquation3
  
  
               
               
  
               
  
               
 


 *---------------------------------------------------------------------------*/
int 
SolveEquation3(f32* root, f32 a, f32 b, f32 c, f32 d)
{
    NN_POINTER_TASSERT_(root);
    NN_TASSERT_( a != 0 );

    //---- Divide both sides of the equation by the coefficient of the term of highest degree so that the coefficient for that term is 1.
    b /= a;
    c /= a;
    d /= a;

    //---- Find the value of the fundamental descriminant D
    f32 q = (spow<2>(b) - 3 * c) / 9;
    f32 r = (2 * spow<3>(b) - 9 * b * c + 27 * d) / 54;
    f32 D = spow<3>(q) - spow<2>(r);

    f32 b_3 = b / 3;

    if( D > EPS )
    {
        f32 theta   = AcosRad( r / FSqrt(spow<3>(q)) );
        f32 theta_3 = theta/3;
        f32 r_q2    = -2 * FSqrt(q);

        root[0] = r_q2 * CosRad(theta_3 + 0 * F_PI / 3) - b_3;
        root[1] = r_q2 * CosRad(theta_3 + 2 * F_PI / 3) - b_3;
        root[2] = r_q2 * CosRad(theta_3 + 4 * F_PI / 3) - b_3;

        return 3;
    }
    else if( D < - EPS )
    {
        f32 r3_Dr = FCbrt( FSqrt(- D) + FAbs(r) );
        f32 xp    = r3_Dr + q / r3_Dr;

        root[0] = - FCopySign(xp, r) - b_3;

        return 1;
    }
    else
    {
        f32 xp  = FSqrt(q);
        f32 sxp = FCopySign(xp, r);

        root[0] =  1 * sxp - b_3;
        root[1] = -2 * sxp - b_3;

        return 2;
    }
}



/*!--------------------------------------------------------------------------*
  Name:        SolveEquation4
  
               
  
               
               
  
               
  
               
 


 *---------------------------------------------------------------------------*/
int 
SolveEquation4(f32* root, f32 a, f32 b, f32 c, f32 d, f32 e)
{
    NN_POINTER_TASSERT_(root);
    NN_TASSERT_( a != 0 );

    f32 m, n, y;

    //---- Divide both sides of the equation by the coefficient of the term of highest degree so that the coefficient for that term is 1.
    b /= a;
    c /= a;
    d /= a;
    e /= a;

    //---- Complete the square
    {
        // Positing t = x + b/4 leads to x = t - b/4 
        // The third degree term disappears if the above is used to substitute for x and then simplification is applied.
        //   t^4 + pt^2 + qt + r = 0
        // results. Here, p, q, r are each as given below.

        f32 p = - 3.f * spow<2>(b) / 8 + c;
        f32 q = spow<3>(b) / 8 - b * c / 2 + d;
        f32 r = - 3.f * spow<4>(b) / 256 + spow<2>(b) * c / 16 - b * d / 4 + e;


        // Consider completing the square in a form such as the following for the formula for t.
        //   (t^2 + y)^2 = (mt + n)^2   ------- (1)

        if( q != 0 )
        {
            // First, for any value y for t^2
            //   (t^2 + y)^2 = 2yt^2 + y^2 - (pt^2 + qt + r)
            //               = (2y - p)t^2 + qt + (y^2 - r)   ------- (2)
            // can be used to complete the square.
            // To finally complete the square on the right side as well, it needs to meet the fundamental descriminant of the quadratic on the right side D = 0, and use:
            //   q^2 - 4(2y - p)(y^2 - r) = 0
            // and find y that satisfies the above formula. Organizing for y gives
            //   y^3 - (p/2)y^2 - ry + (pr/2 - (q^2)/8) = 0
            // Solving this cubic equation, one solution can be used as y.

            y = SolveEquation3(-p / 2, -r, p * r / 2 - spow<2>(q) / 8);


            // (1) Expanding the right side gives
            //   (mt + n)^2 = m^2t^2 + 2mnt + n^2
            // Get the following by comparing this with Equation (2).

            n = FSqrt(spow<2>(y) - r);
            m = -q / (2 * n);
        }
        else
        {
            // When q = 0, y = p/2, ±sqrt(r) results when solving the above cubic equation
            // Given SolveEquation3, if ±sqrt(r) is selected, n = 0 results,
            // and division by 0 occurs.
            // Finally, if p = q = r = 0, then n must equal 0.
            // Avoid all this.

            y = p / 2;
            n = FSqrt(spow<2>(y) - r);
            m = 0;
        }
    }

    // Since the given equation has been converted to the form of Equation 1, solve it.
    // Taking the square root of both sides of Equation 1 results in,
    //   t^2 + y = ±(mt + n)
    // This can be represented using two quadratic formulas:
    //   t^2 + mt + (y + n) = 0
    //   t^2 - mt + (y - n) = 0
    // The value of t is found by solving these.
    // x is then found using x = t - b/4.

    int nRoot = 0;
    f32 b4    = b / 4;

    //---- Quadratic equation 1
    {
        f32 root01[2];
        
        int nRoot01 = SolveEquation2(root01, m, y + n);
        
        root[nRoot]   = root01[0] - b4;
        root[nRoot+1] = root01[1] - b4;
        nRoot += nRoot01;
    }

    //---- Quadratic equation 2
    {
        f32 root23[2];
        
        int nRoot23 = SolveEquation2(root23, -m, y - n);

        root[nRoot]   = root23[0] - b4;
        root[nRoot+1] = root23[1] - b4;
        nRoot += nRoot23;
    }

    return nRoot;
}


}}  // nw::math
