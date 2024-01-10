#ifndef T3_VARIADIC_MACROS_H
#define T3_VARIADIC_MACROS_H

//Variadic macros doesn't work the same way it does on linux. 
//This is the brute force variation for 10 things 

#define Par_Open (
#define Curly_Open {
#define Curly_Close }
#define Par_Close )
#define Empty
#define Semicolon ;
#define Comma ,

#define Var_1(str, bef, v0 , aft, end) str bef v0 aft end
#define Var_2(str, bef, v0 , v1, aft, end) str bef v0 aft bef v1 aft end
#define Var_3(str, bef, v0, v1, v2, aft, end) str bef v0 aft bef v1 aft bef v2 aft end
#define Var_4(str, bef, v0, v1, v2, v3, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft end
#define Var_5(str, bef, v0, v1, v2, v3, v4, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft end
#define Var_6(str, bef, v0, v1, v2, v3, v4, v5, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft bef v5 aft end
#define Var_7(str, bef, v0, v1, v2, v3, v4, v5, v6, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft bef v5 aft bef v6 aft end
#define Var_8(str, bef, v0, v1, v2, v3, v4, v5, v6, v7, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft bef v5 aft bef v6 aft bef v7 aft end
#define Var_9(str, bef, v0, v1, v2, v3, v4, v5, v6, v7, v8, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft bef v5 aft bef v6 aft bef v7 aft bef v8 aft end
#define Var_10(str, bef, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, aft, end) str bef v0 aft bef v1 aft bef v2 aft bef v3 aft bef v4 aft bef v5 aft bef v6 aft bef v7 aft bef v8 aft bef v9 aft end

#define Args_1(a0) Var_1(Par_Open,Empty,a0,Empty,Par_Close)
#define Args_2(a0,a1) Var_2(Par_Open,Empty,a0 Comma,a1,Empty,Par_Close)
#define Args_3(a0,a1,a2) Var_3(Par_Open,Empty,a0 Comma,a1 Comma,a2,Empty,Par_Close)
#define Args_4(a0,a1,a2,a3) Var_4(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3,Empty,Par_Close)
#define Args_5(a0,a1,a2,a3,a4) Var_5(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4,Empty,Par_Close)
#define Args_6(a0,a1,a2,a3,a4,a5) Var_6(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4 Comma,a5,Empty,Par_Close)
#define Args_7(a0,a1,a2,a3,a4,a5,a6) Var_7(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4 Comma,a5 Comma,a6,Empty,Par_Close)
#define Args_8(a0,a1,a2,a3,a4,a5,a6,a7) Var_8(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4 Comma,a5 Comma,a6 Comma,a7,Empty,Par_Close)
#define Args_9(a0,a1,a2,a3,a4,a5,a6,a7,a8) Var_9(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4 Comma,a5 Comma,a6 Comma,a7 Comma,a8,Empty,Par_Close)
#define Args_10(a0,a1,a2,a3,a4,a5,a6,a7,a8,a9) Var_10(Par_Open,Empty,a0 Comma,a1 Comma,a2 Comma,a3 Comma,a4 Comma,a5 Comma,a6 Comma,a7 Comma,a8 Comma,a9,Empty,Par_Close)

#define Members_1(m0) Var_1(Curly_Open,Empty,m0,Semicolon,Curly_Close)
#define Members_2(m1,m0) Var_2(Curly_Open,Empty,m1,m0,Semicolon,Curly_Close)

#endif //T3_VARIADIC_MACROS_H
