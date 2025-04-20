
template <class _Ty1>
using _Conditional_type = _Ty1;

template <class _Ty1>
struct _Const_lvalue_cond_oper
{
};

template <class _Ty1>
requires requires { typename _Conditional_type<const _Ty1>; }
struct _Const_lvalue_cond_oper<_Ty1>
{
};
