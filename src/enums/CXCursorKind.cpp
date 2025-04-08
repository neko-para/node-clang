#include "enums.h"

#include <clang-c/Index.h>

std::map<std::string, int> makeCXCursorKindEnum()
{
    std::map<std::string, int> result;

    /* Declarations */
    /**
     * A declaration whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed declarations have the same operations as any other kind
     * of declaration; one can extract their location information,
     * spelling, find their definitions, etc. However, the specific kind
     * of the declaration is not reported.
     */
    ENUM_ADD(UnexposedDecl);
    /** A C or C++ struct. */
    ENUM_ADD(StructDecl);
    /** A C or C++ union. */
    ENUM_ADD(UnionDecl);
    /** A C++ class. */
    ENUM_ADD(ClassDecl);
    /** An enumeration. */
    ENUM_ADD(EnumDecl);
    /**
     * A field (in C) or non-static data member (in C++) in a
     * struct, union, or C++ class.
     */
    ENUM_ADD(FieldDecl);
    /** An enumerator constant. */
    ENUM_ADD(EnumConstantDecl);
    /** A function. */
    ENUM_ADD(FunctionDecl);
    /** A variable. */
    ENUM_ADD(VarDecl);
    /** A function or method parameter. */
    ENUM_ADD(ParmDecl);
    /** An Objective-C \@interface. */
    ENUM_ADD(ObjCInterfaceDecl);
    /** An Objective-C \@interface for a category. */
    ENUM_ADD(ObjCCategoryDecl);
    /** An Objective-C \@protocol declaration. */
    ENUM_ADD(ObjCProtocolDecl);
    /** An Objective-C \@property declaration. */
    ENUM_ADD(ObjCPropertyDecl);
    /** An Objective-C instance variable. */
    ENUM_ADD(ObjCIvarDecl);
    /** An Objective-C instance method. */
    ENUM_ADD(ObjCInstanceMethodDecl);
    /** An Objective-C class method. */
    ENUM_ADD(ObjCClassMethodDecl);
    /** An Objective-C \@implementation. */
    ENUM_ADD(ObjCImplementationDecl);
    /** An Objective-C \@implementation for a category. */
    ENUM_ADD(ObjCCategoryImplDecl);
    /** A typedef. */
    ENUM_ADD(TypedefDecl);
    /** A C++ class method. */
    ENUM_ADD(CXXMethod);
    /** A C++ namespace. */
    ENUM_ADD(Namespace);
    /** A linkage specification, e.g. 'extern "C"'. */
    ENUM_ADD(LinkageSpec);
    /** A C++ constructor. */
    ENUM_ADD(Constructor);
    /** A C++ destructor. */
    ENUM_ADD(Destructor);
    /** A C++ conversion function. */
    ENUM_ADD(ConversionFunction);
    /** A C++ template type parameter. */
    ENUM_ADD(TemplateTypeParameter);
    /** A C++ non-type template parameter. */
    ENUM_ADD(NonTypeTemplateParameter);
    /** A C++ template template parameter. */
    ENUM_ADD(TemplateTemplateParameter);
    /** A C++ function template. */
    ENUM_ADD(FunctionTemplate);
    /** A C++ class template. */
    ENUM_ADD(ClassTemplate);
    /** A C++ class template partial specialization. */
    ENUM_ADD(ClassTemplatePartialSpecialization);
    /** A C++ namespace alias declaration. */
    ENUM_ADD(NamespaceAlias);
    /** A C++ using directive. */
    ENUM_ADD(UsingDirective);
    /** A C++ using declaration. */
    ENUM_ADD(UsingDeclaration);
    /** A C++ alias declaration */
    ENUM_ADD(TypeAliasDecl);
    /** An Objective-C \@synthesize definition. */
    ENUM_ADD(ObjCSynthesizeDecl);
    /** An Objective-C \@dynamic definition. */
    ENUM_ADD(ObjCDynamicDecl);
    /** An access specifier. */
    ENUM_ADD(CXXAccessSpecifier);

    ENUM_ADD(FirstDecl);
    ENUM_ADD(LastDecl);

    /* References */
    ENUM_ADD(FirstRef);
    ENUM_ADD(ObjCSuperClassRef);
    ENUM_ADD(ObjCProtocolRef);
    ENUM_ADD(ObjCClassRef);
    /**
     * A reference to a type declaration.
     *
     * A type reference occurs anywhere where a type is named but not
     * declared. For example, given:
     *
     * \code
     * typedef unsigned size_type;
     * size_type size;
     * \endcode
     *
     * The typedef is a declaration of size_type (TypedefDecl),
     * while the type of the variable "size" is referenced. The cursor
     * referenced by the type of size is the typedef for size_type.
     */
    ENUM_ADD(TypeRef);
    ENUM_ADD(CXXBaseSpecifier);
    /**
     * A reference to a class template, function template, template
     * template parameter, or class template partial specialization.
     */
    ENUM_ADD(TemplateRef);
    /**
     * A reference to a namespace or namespace alias.
     */
    ENUM_ADD(NamespaceRef);
    /**
     * A reference to a member of a struct, union, or class that occurs in
     * some non-expression context, e.g., a designated initializer.
     */
    ENUM_ADD(MemberRef);
    /**
     * A reference to a labeled statement.
     *
     * This cursor kind is used to describe the jump to "start_over" in the
     * goto statement in the following example:
     *
     * \code
     *   start_over:
     *     ++counter;
     *
     *     goto start_over;
     * \endcode
     *
     * A label reference cursor refers to a label statement.
     */
    ENUM_ADD(LabelRef);

    /**
     * A reference to a set of overloaded functions or function templates
     * that has not yet been resolved to a specific function or function template.
     *
     * An overloaded declaration reference cursor occurs in C++ templates where
     * a dependent name refers to a function. For example:
     *
     * \code
     * template<typename T> void swap(T&, T&);
     *
     * struct X { ... };
     * void swap(X&, X&);
     *
     * template<typename T>
     * void reverse(T* first, T* last) {
     *   while (first < last - 1) {
     *     swap(*first, *--last);
     *     ++first;
     *   }
     * }
     *
     * struct Y { };
     * void swap(Y&, Y&);
     * \endcode
     *
     * Here, the identifier "swap" is associated with an overloaded declaration
     * reference. In the template definition, "swap" refers to either of the two
     * "swap" functions declared above, so both results will be available. At
     * instantiation time, "swap" may also refer to other functions found via
     * argument-dependent lookup (e.g., the "swap" function at the end of the
     * example).
     *
     * The functions \c clang_getNumOverloadedDecls() and
     * \c clang_getOverloadedDecl() can be used to retrieve the definitions
     * referenced by this cursor.
     */
    ENUM_ADD(OverloadedDeclRef);

    /**
     * A reference to a variable that occurs in some non-expression
     * context, e.g., a C++ lambda capture list.
     */
    ENUM_ADD(VariableRef);

    ENUM_ADD(LastRef);

    /* Error conditions */
    ENUM_ADD(FirstInvalid);
    ENUM_ADD(InvalidFile);
    ENUM_ADD(NoDeclFound);
    ENUM_ADD(NotImplemented);
    ENUM_ADD(InvalidCode);
    ENUM_ADD(LastInvalid);

    /* Expressions */
    ENUM_ADD(FirstExpr);

    /**
     * An expression whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed expressions have the same operations as any other kind
     * of expression; one can extract their location information,
     * spelling, children, etc. However, the specific kind of the
     * expression is not reported.
     */
    ENUM_ADD(UnexposedExpr);

    /**
     * An expression that refers to some value declaration, such
     * as a function, variable, or enumerator.
     */
    ENUM_ADD(DeclRefExpr);

    /**
     * An expression that refers to a member of a struct, union,
     * class, Objective-C class, etc.
     */
    ENUM_ADD(MemberRefExpr);

    /** An expression that calls a function. */
    ENUM_ADD(CallExpr);

    /** An expression that sends a message to an Objective-C
     object or class. */
    ENUM_ADD(ObjCMessageExpr);

    /** An expression that represents a block literal. */
    ENUM_ADD(BlockExpr);

    /** An integer literal.
     */
    ENUM_ADD(IntegerLiteral);

    /** A floating point number literal.
     */
    ENUM_ADD(FloatingLiteral);

    /** An imaginary number literal.
     */
    ENUM_ADD(ImaginaryLiteral);

    /** A string literal.
     */
    ENUM_ADD(StringLiteral);

    /** A character literal.
     */
    ENUM_ADD(CharacterLiteral);

    /** A parenthesized expression, e.g. "(1)".
     *
     * This AST node is only formed if full location information is requested.
     */
    ENUM_ADD(ParenExpr);

    /** This represents the unary-expression's (except sizeof and
     * alignof).
     */
    ENUM_ADD(UnaryOperator);

    /** [C99 6.5.2.1] Array Subscripting.
     */
    ENUM_ADD(ArraySubscriptExpr);

    /** A builtin binary operation expression such as "x + y" or
     * "x <= y".
     */
    ENUM_ADD(BinaryOperator);

    /** Compound assignment such as "+=".
     */
    ENUM_ADD(CompoundAssignOperator);

    /** The ?: ternary operator.
     */
    ENUM_ADD(ConditionalOperator);

    /** An explicit cast in C (C99 6.5.4) or a C-style cast in C++
     * (C++ [expr.cast]), which uses the syntax (Type)expr.
     *
     * For example: (int)f.
     */
    ENUM_ADD(CStyleCastExpr);

    /** [C99 6.5.2.5]
     */
    ENUM_ADD(CompoundLiteralExpr);

    /** Describes an C or C++ initializer list.
     */
    ENUM_ADD(InitListExpr);

    /** The GNU ENUM_ADDress of label extension, representing &&label.
     */
    ENUM_ADD(AddrLabelExpr);

    /** This is the GNU Statement Expression extension: ({int X=4; X;})
     */
    ENUM_ADD(StmtExpr);

    /** Represents a C11 generic selection.
     */
    ENUM_ADD(GenericSelectionExpr);

    /** Implements the GNU __null extension, which is a name for a null
     * pointer constant that has integral type (e.g., int or long) and is the same
     * size and alignment as a pointer.
     *
     * The __null extension is typically only used by system headers, which define
     * NULL as __null in C++ rather than using 0 (which is an integer that may not
     * match the size of a pointer).
     */
    ENUM_ADD(GNUNullExpr);

    /** C++'s static_cast<> expression.
     */
    ENUM_ADD(CXXStaticCastExpr);

    /** C++'s dynamic_cast<> expression.
     */
    ENUM_ADD(CXXDynamicCastExpr);

    /** C++'s reinterpret_cast<> expression.
     */
    ENUM_ADD(CXXReinterpretCastExpr);

    /** C++'s const_cast<> expression.
     */
    ENUM_ADD(CXXConstCastExpr);

    /** Represents an explicit C++ type conversion that uses "functional"
     * notion (C++ [expr.type.conv]).
     *
     * Example:
     * \code
     *   x = int(0.5);
     * \endcode
     */
    ENUM_ADD(CXXFunctionalCastExpr);

    /** A C++ typeid expression (C++ [expr.typeid]).
     */
    ENUM_ADD(CXXTypeidExpr);

    /** [C++ 2.13.5] C++ Boolean Literal.
     */
    ENUM_ADD(CXXBoolLiteralExpr);

    /** [C++0x 2.14.7] C++ Pointer Literal.
     */
    ENUM_ADD(CXXNullPtrLiteralExpr);

    /** Represents the "this" expression in C++
     */
    ENUM_ADD(CXXThisExpr);

    /** [C++ 15] C++ Throw Expression.
     *
     * This handles 'throw' and 'throw' assignment-expression. When
     * assignment-expression isn't present, Op will be null.
     */
    ENUM_ADD(CXXThrowExpr);

    /** A new expression for memory allocation and constructor calls, e.g:
     * "new CXXNewExpr(foo)".
     */
    ENUM_ADD(CXXNewExpr);

    /** A delete expression for memory deallocation and destructor calls,
     * e.g. "delete[] pArray".
     */
    ENUM_ADD(CXXDeleteExpr);

    /** A unary expression. (noexcept, sizeof, or other traits)
     */
    ENUM_ADD(UnaryExpr);

    /** An Objective-C string literal i.e. @"foo".
     */
    ENUM_ADD(ObjCStringLiteral);

    /** An Objective-C \@encode expression.
     */
    ENUM_ADD(ObjCEncodeExpr);

    /** An Objective-C \@selector expression.
     */
    ENUM_ADD(ObjCSelectorExpr);

    /** An Objective-C \@protocol expression.
     */
    ENUM_ADD(ObjCProtocolExpr);

    /** An Objective-C "bridged" cast expression, which casts between
     * Objective-C pointers and C pointers, transferring ownership in the process.
     *
     * \code
     *   NSString *str = (__bridge_transfer NSString *)CFCreateString();
     * \endcode
     */
    ENUM_ADD(ObjCBridgedCastExpr);

    /** Represents a C++0x pack expansion that produces a sequence of
     * expressions.
     *
     * A pack expansion expression contains a pattern (which itself is an
     * expression) followed by an ellipsis. For example:
     *
     * \code
     * template<typename F, typename ...Types>
     * void forward(F f, Types &&...args) {
     *  f(static_cast<Types&&>(args)...);
     * }
     * \endcode
     */
    ENUM_ADD(PackExpansionExpr);

    /** Represents an expression that computes the length of a parameter
     * pack.
     *
     * \code
     * template<typename ...Types>
     * struct count {
     *   static const unsigned value = sizeof...(Types);
     * };
     * \endcode
     */
    ENUM_ADD(SizeOfPackExpr);

    /* Represents a C++ lambda expression that produces a local function
     * object.
     *
     * \code
     * void abssort(float *x, unsigned N) {
     *   std::sort(x, x + N,
     *             [](float a, float b) {
     *               return std::abs(a) < std::abs(b);
     *             });
     * }
     * \endcode
     */
    ENUM_ADD(LambdaExpr);

    /** Objective-c Boolean Literal.
     */
    ENUM_ADD(ObjCBoolLiteralExpr);

    /** Represents the "self" expression in an Objective-C method.
     */
    ENUM_ADD(ObjCSelfExpr);

    /** OpenMP 5.0 [2.1.5, Array Section].
     * OpenACC 3.3 [2.7.1, Data Specification for Data Clauses (Sub Arrays)]
     */
    ENUM_ADD(ArraySectionExpr);

    /** Represents an @available(...) check.
     */
    ENUM_ADD(ObjCAvailabilityCheckExpr);

    /**
     * Fixed point literal
     */
    ENUM_ADD(FixedPointLiteral);

    /** OpenMP 5.0 [2.1.4, Array Shaping].
     */
    ENUM_ADD(OMPArrayShapingExpr);

    /**
     * OpenMP 5.0 [2.1.6 Iterators]
     */
    ENUM_ADD(OMPIteratorExpr);

    /** OpenCL's ENUM_ADDrspace_cast<> expression.
     */
    ENUM_ADD(CXXAddrspaceCastExpr);

    /**
     * Expression that references a C++20 concept.
     */
    ENUM_ADD(ConceptSpecializationExpr);

    /**
     * Expression that references a C++20 requires expression.
     */
    ENUM_ADD(RequiresExpr);

    /**
     * Expression that references a C++20 parenthesized list aggregate
     * initializer.
     */
    ENUM_ADD(CXXParenListInitExpr);

    /**
     *  Represents a C++26 pack indexing expression.
     */
    ENUM_ADD(PackIndexingExpr);

    ENUM_ADD(LastExpr);

    /* Statements */
    ENUM_ADD(FirstStmt);
    /**
     * A statement whose specific kind is not exposed via this
     * interface.
     *
     * Unexposed statements have the same operations as any other kind of
     * statement; one can extract their location information, spelling,
     * children, etc. However, the specific kind of the statement is not
     * reported.
     */
    ENUM_ADD(UnexposedStmt);

    /** A labelled statement in a function.
     *
     * This cursor kind is used to describe the "start_over:" label statement in
     * the following example:
     *
     * \code
     *   start_over:
     *     ++counter;
     * \endcode
     *
     */
    ENUM_ADD(LabelStmt);

    /** A group of statements like { stmt stmt }.
     *
     * This cursor kind is used to describe compound statements, e.g. function
     * bodies.
     */
    ENUM_ADD(CompoundStmt);

    /** A case statement.
     */
    ENUM_ADD(CaseStmt);

    /** A default statement.
     */
    ENUM_ADD(DefaultStmt);

    /** An if statement
     */
    ENUM_ADD(IfStmt);

    /** A switch statement.
     */
    ENUM_ADD(SwitchStmt);

    /** A while statement.
     */
    ENUM_ADD(WhileStmt);

    /** A do statement.
     */
    ENUM_ADD(DoStmt);

    /** A for statement.
     */
    ENUM_ADD(ForStmt);

    /** A goto statement.
     */
    ENUM_ADD(GotoStmt);

    /** An indirect goto statement.
     */
    ENUM_ADD(IndirectGotoStmt);

    /** A continue statement.
     */
    ENUM_ADD(ContinueStmt);

    /** A break statement.
     */
    ENUM_ADD(BreakStmt);

    /** A return statement.
     */
    ENUM_ADD(ReturnStmt);

    /** A GCC inline assembly statement extension.
     */
    ENUM_ADD(GCCAsmStmt);
    ENUM_ADD(AsmStmt);

    /** Objective-C's overall \@try-\@catch-\@finally statement.
     */
    ENUM_ADD(ObjCAtTryStmt);

    /** Objective-C's \@catch statement.
     */
    ENUM_ADD(ObjCAtCatchStmt);

    /** Objective-C's \@finally statement.
     */
    ENUM_ADD(ObjCAtFinallyStmt);

    /** Objective-C's \@throw statement.
     */
    ENUM_ADD(ObjCAtThrowStmt);

    /** Objective-C's \@synchronized statement.
     */
    ENUM_ADD(ObjCAtSynchronizedStmt);

    /** Objective-C's autorelease pool statement.
     */
    ENUM_ADD(ObjCAutoreleasePoolStmt);

    /** Objective-C's collection statement.
     */
    ENUM_ADD(ObjCForCollectionStmt);

    /** C++'s catch statement.
     */
    ENUM_ADD(CXXCatchStmt);

    /** C++'s try statement.
     */
    ENUM_ADD(CXXTryStmt);

    /** C++'s for (* : *) statement.
     */
    ENUM_ADD(CXXForRangeStmt);

    /** Windows Structured Exception Handling's try statement.
     */
    ENUM_ADD(SEHTryStmt);

    /** Windows Structured Exception Handling's except statement.
     */
    ENUM_ADD(SEHExceptStmt);

    /** Windows Structured Exception Handling's finally statement.
     */
    ENUM_ADD(SEHFinallyStmt);

    /** A MS inline assembly statement extension.
     */
    ENUM_ADD(MSAsmStmt);

    /** The null statement ";": C99 6.8.3p3.
     *
     * This cursor kind is used to describe the null statement.
     */
    ENUM_ADD(NullStmt);

    /** Adaptor class for mixing declarations with statements and
     * expressions.
     */
    ENUM_ADD(DeclStmt);

    /** OpenMP parallel directive.
     */
    ENUM_ADD(OMPParallelDirective);

    /** OpenMP SIMD directive.
     */
    ENUM_ADD(OMPSimdDirective);

    /** OpenMP for directive.
     */
    ENUM_ADD(OMPForDirective);

    /** OpenMP sections directive.
     */
    ENUM_ADD(OMPSectionsDirective);

    /** OpenMP section directive.
     */
    ENUM_ADD(OMPSectionDirective);

    /** OpenMP single directive.
     */
    ENUM_ADD(OMPSingleDirective);

    /** OpenMP parallel for directive.
     */
    ENUM_ADD(OMPParallelForDirective);

    /** OpenMP parallel sections directive.
     */
    ENUM_ADD(OMPParallelSectionsDirective);

    /** OpenMP task directive.
     */
    ENUM_ADD(OMPTaskDirective);

    /** OpenMP master directive.
     */
    ENUM_ADD(OMPMasterDirective);

    /** OpenMP critical directive.
     */
    ENUM_ADD(OMPCriticalDirective);

    /** OpenMP taskyield directive.
     */
    ENUM_ADD(OMPTaskyieldDirective);

    /** OpenMP barrier directive.
     */
    ENUM_ADD(OMPBarrierDirective);

    /** OpenMP taskwait directive.
     */
    ENUM_ADD(OMPTaskwaitDirective);

    /** OpenMP flush directive.
     */
    ENUM_ADD(OMPFlushDirective);

    /** Windows Structured Exception Handling's leave statement.
     */
    ENUM_ADD(SEHLeaveStmt);

    /** OpenMP ordered directive.
     */
    ENUM_ADD(OMPOrderedDirective);

    /** OpenMP atomic directive.
     */
    ENUM_ADD(OMPAtomicDirective);

    /** OpenMP for SIMD directive.
     */
    ENUM_ADD(OMPForSimdDirective);

    /** OpenMP parallel for SIMD directive.
     */
    ENUM_ADD(OMPParallelForSimdDirective);

    /** OpenMP target directive.
     */
    ENUM_ADD(OMPTargetDirective);

    /** OpenMP teams directive.
     */
    ENUM_ADD(OMPTeamsDirective);

    /** OpenMP taskgroup directive.
     */
    ENUM_ADD(OMPTaskgroupDirective);

    /** OpenMP cancellation point directive.
     */
    ENUM_ADD(OMPCancellationPointDirective);

    /** OpenMP cancel directive.
     */
    ENUM_ADD(OMPCancelDirective);

    /** OpenMP target data directive.
     */
    ENUM_ADD(OMPTargetDataDirective);

    /** OpenMP taskloop directive.
     */
    ENUM_ADD(OMPTaskLoopDirective);

    /** OpenMP taskloop simd directive.
     */
    ENUM_ADD(OMPTaskLoopSimdDirective);

    /** OpenMP distribute directive.
     */
    ENUM_ADD(OMPDistributeDirective);

    /** OpenMP target enter data directive.
     */
    ENUM_ADD(OMPTargetEnterDataDirective);

    /** OpenMP target exit data directive.
     */
    ENUM_ADD(OMPTargetExitDataDirective);

    /** OpenMP target parallel directive.
     */
    ENUM_ADD(OMPTargetParallelDirective);

    /** OpenMP target parallel for directive.
     */
    ENUM_ADD(OMPTargetParallelForDirective);

    /** OpenMP target update directive.
     */
    ENUM_ADD(OMPTargetUpdateDirective);

    /** OpenMP distribute parallel for directive.
     */
    ENUM_ADD(OMPDistributeParallelForDirective);

    /** OpenMP distribute parallel for simd directive.
     */
    ENUM_ADD(OMPDistributeParallelForSimdDirective);

    /** OpenMP distribute simd directive.
     */
    ENUM_ADD(OMPDistributeSimdDirective);

    /** OpenMP target parallel for simd directive.
     */
    ENUM_ADD(OMPTargetParallelForSimdDirective);

    /** OpenMP target simd directive.
     */
    ENUM_ADD(OMPTargetSimdDirective);

    /** OpenMP teams distribute directive.
     */
    ENUM_ADD(OMPTeamsDistributeDirective);

    /** OpenMP teams distribute simd directive.
     */
    ENUM_ADD(OMPTeamsDistributeSimdDirective);

    /** OpenMP teams distribute parallel for simd directive.
     */
    ENUM_ADD(OMPTeamsDistributeParallelForSimdDirective);

    /** OpenMP teams distribute parallel for directive.
     */
    ENUM_ADD(OMPTeamsDistributeParallelForDirective);

    /** OpenMP target teams directive.
     */
    ENUM_ADD(OMPTargetTeamsDirective);

    /** OpenMP target teams distribute directive.
     */
    ENUM_ADD(OMPTargetTeamsDistributeDirective);

    /** OpenMP target teams distribute parallel for directive.
     */
    ENUM_ADD(OMPTargetTeamsDistributeParallelForDirective);

    /** OpenMP target teams distribute parallel for simd directive.
     */
    ENUM_ADD(OMPTargetTeamsDistributeParallelForSimdDirective);

    /** OpenMP target teams distribute simd directive.
     */
    ENUM_ADD(OMPTargetTeamsDistributeSimdDirective);

    /** C++2a std::bit_cast expression.
     */
    ENUM_ADD(BuiltinBitCastExpr);

    /** OpenMP master taskloop directive.
     */
    ENUM_ADD(OMPMasterTaskLoopDirective);

    /** OpenMP parallel master taskloop directive.
     */
    ENUM_ADD(OMPParallelMasterTaskLoopDirective);

    /** OpenMP master taskloop simd directive.
     */
    ENUM_ADD(OMPMasterTaskLoopSimdDirective);

    /** OpenMP parallel master taskloop simd directive.
     */
    ENUM_ADD(OMPParallelMasterTaskLoopSimdDirective);

    /** OpenMP parallel master directive.
     */
    ENUM_ADD(OMPParallelMasterDirective);

    /** OpenMP depobj directive.
     */
    ENUM_ADD(OMPDepobjDirective);

    /** OpenMP scan directive.
     */
    ENUM_ADD(OMPScanDirective);

    /** OpenMP tile directive.
     */
    ENUM_ADD(OMPTileDirective);

    /** OpenMP canonical loop.
     */
    ENUM_ADD(OMPCanonicalLoop);

    /** OpenMP interop directive.
     */
    ENUM_ADD(OMPInteropDirective);

    /** OpenMP dispatch directive.
     */
    ENUM_ADD(OMPDispatchDirective);

    /** OpenMP masked directive.
     */
    ENUM_ADD(OMPMaskedDirective);

    /** OpenMP unroll directive.
     */
    ENUM_ADD(OMPUnrollDirective);

    /** OpenMP metadirective directive.
     */
    ENUM_ADD(OMPMetaDirective);

    /** OpenMP loop directive.
     */
    ENUM_ADD(OMPGenericLoopDirective);

    /** OpenMP teams loop directive.
     */
    ENUM_ADD(OMPTeamsGenericLoopDirective);

    /** OpenMP target teams loop directive.
     */
    ENUM_ADD(OMPTargetTeamsGenericLoopDirective);

    /** OpenMP parallel loop directive.
     */
    ENUM_ADD(OMPParallelGenericLoopDirective);

    /** OpenMP target parallel loop directive.
     */
    ENUM_ADD(OMPTargetParallelGenericLoopDirective);

    /** OpenMP parallel masked directive.
     */
    ENUM_ADD(OMPParallelMaskedDirective);

    /** OpenMP masked taskloop directive.
     */
    ENUM_ADD(OMPMaskedTaskLoopDirective);

    /** OpenMP masked taskloop simd directive.
     */
    ENUM_ADD(OMPMaskedTaskLoopSimdDirective);

    /** OpenMP parallel masked taskloop directive.
     */
    ENUM_ADD(OMPParallelMaskedTaskLoopDirective);

    /** OpenMP parallel masked taskloop simd directive.
     */
    ENUM_ADD(OMPParallelMaskedTaskLoopSimdDirective);

    /** OpenMP error directive.
     */
    ENUM_ADD(OMPErrorDirective);

    /** OpenMP scope directive.
     */
    ENUM_ADD(OMPScopeDirective);

    /** OpenMP reverse directive.
     */
    ENUM_ADD(OMPReverseDirective);

    /** OpenMP interchange directive.
     */
    ENUM_ADD(OMPInterchangeDirective);

    /** OpenMP assume directive.
     */
    ENUM_ADD(OMPAssumeDirective);

    /** OpenACC Compute Construct.
     */
    ENUM_ADD(OpenACCComputeConstruct);

    /** OpenACC Loop Construct.
     */
    ENUM_ADD(OpenACCLoopConstruct);

    /** OpenACC Combined Constructs.
     */
    ENUM_ADD(OpenACCCombinedConstruct);

    /** OpenACC data Construct.
     */
    ENUM_ADD(OpenACCDataConstruct);

    /** OpenACC enter data Construct.
     */
    ENUM_ADD(OpenACCEnterDataConstruct);

    /** OpenACC exit data Construct.
     */
    ENUM_ADD(OpenACCExitDataConstruct);

    /** OpenACC host_data Construct.
     */
    ENUM_ADD(OpenACCHostDataConstruct);

    /** OpenACC wait Construct.
     */
    ENUM_ADD(OpenACCWaitConstruct);

    /** OpenACC init Construct.
     */
    ENUM_ADD(OpenACCInitConstruct);

    /** OpenACC shutdown Construct.
     */
    ENUM_ADD(OpenACCShutdownConstruct);

    /** OpenACC set Construct.
     */
    ENUM_ADD(OpenACCSetConstruct);

    /** OpenACC update Construct.
     */
    ENUM_ADD(OpenACCUpdateConstruct);

    ENUM_ADD(LastStmt);

    /**
     * Cursor that represents the translation unit itself.
     *
     * The translation unit cursor exists primarily to act as the root
     * cursor for traversing the contents of a translation unit.
     */
    ENUM_ADD(TranslationUnit);

    /* Attributes */
    ENUM_ADD(FirstAttr);
    /**
     * An attribute whose specific kind is not exposed via this
     * interface.
     */
    ENUM_ADD(UnexposedAttr);

    ENUM_ADD(IBActionAttr);
    ENUM_ADD(IBOutletAttr);
    ENUM_ADD(IBOutletCollectionAttr);
    ENUM_ADD(CXXFinalAttr);
    ENUM_ADD(CXXOverrideAttr);
    ENUM_ADD(AnnotateAttr);
    ENUM_ADD(AsmLabelAttr);
    ENUM_ADD(PackedAttr);
    ENUM_ADD(PureAttr);
    ENUM_ADD(ConstAttr);
    ENUM_ADD(NoDuplicateAttr);
    ENUM_ADD(CUDAConstantAttr);
    ENUM_ADD(CUDADeviceAttr);
    ENUM_ADD(CUDAGlobalAttr);
    ENUM_ADD(CUDAHostAttr);
    ENUM_ADD(CUDASharedAttr);
    ENUM_ADD(VisibilityAttr);
    ENUM_ADD(DLLExport);
    ENUM_ADD(DLLImport);
    ENUM_ADD(NSReturnsRetained);
    ENUM_ADD(NSReturnsNotRetained);
    ENUM_ADD(NSReturnsAutoreleased);
    ENUM_ADD(NSConsumesSelf);
    ENUM_ADD(NSConsumed);
    ENUM_ADD(ObjCException);
    ENUM_ADD(ObjCNSObject);
    ENUM_ADD(ObjCIndependentClass);
    ENUM_ADD(ObjCPreciseLifetime);
    ENUM_ADD(ObjCReturnsInnerPointer);
    ENUM_ADD(ObjCRequiresSuper);
    ENUM_ADD(ObjCRootClass);
    ENUM_ADD(ObjCSubclassingRestricted);
    ENUM_ADD(ObjCExplicitProtocolImpl);
    ENUM_ADD(ObjCDesignatedInitializer);
    ENUM_ADD(ObjCRuntimeVisible);
    ENUM_ADD(ObjCBoxable);
    ENUM_ADD(FlagEnum);
    ENUM_ADD(ConvergentAttr);
    ENUM_ADD(WarnUnusedAttr);
    ENUM_ADD(WarnUnusedResultAttr);
    ENUM_ADD(AlignedAttr);
    ENUM_ADD(LastAttr);

    /* Preprocessing */
    ENUM_ADD(PreprocessingDirective);
    ENUM_ADD(MacroDefinition);
    ENUM_ADD(MacroExpansion);
    ENUM_ADD(MacroInstantiation);
    ENUM_ADD(InclusionDirective);
    ENUM_ADD(FirstPreprocessing);
    ENUM_ADD(LastPreprocessing);

    /* Extra Declarations */
    /**
     * A module import declaration.
     */
    ENUM_ADD(ModuleImportDecl);
    ENUM_ADD(TypeAliasTemplateDecl);
    /**
     * A static_assert or _Static_assert node
     */
    ENUM_ADD(StaticAssert);
    /**
     * a friend declaration.
     */
    ENUM_ADD(FriendDecl);
    /**
     * a concept declaration.
     */
    ENUM_ADD(ConceptDecl);

    ENUM_ADD(FirstExtraDecl);
    ENUM_ADD(LastExtraDecl);

    /**
     * A code completion overload candidate.
     */
    ENUM_ADD(OverloadCandidate);

    return result;
}
