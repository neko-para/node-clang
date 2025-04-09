export const enum CXErrorCode {
    Success = 0,
    Failure = 1,
    Crashed = 2,
    InvalidArguments = 3,
    ASTReadError = 4,
}

export const enum CXDiagnosticSeverity {
    Ignored = 0,
    Note = 1,
    Warning = 2,
    Error = 3,
    Fatal = 4,
}

export const enum CXLoadDiag_Error {
    None = 0,
    Unknown = 1,
    CannotLoad = 2,
    InvalidFile = 3,
}

export const enum CXDiagnosticDisplayOptions {
    SourceLocation = 1,
    Column = 2,
    SourceRanges = 4,
    Option = 8,
    CategoryId = 16,
    CategoryName = 32,
}

export const enum CXAvailabilityKind {
    Available = 0,
    Deprecated = 1,
    NotAvailable = 2,
    NotAccessible = 3,
}

export const enum CXCursor_ExceptionSpecificationKind {
    None = 0,
    DynamicNone = 1,
    Dynamic = 2,
    MSAny = 3,
    BasicNoexcept = 4,
    ComputedNoexcept = 5,
    Unevaluated = 6,
    Uninstantiated = 7,
    Unparsed = 8,
    NoThrow = 9,
}

export const enum CXChoice {
    Default = 0,
    Enabled = 1,
    Disabled = 2,
}

export const enum CXGlobalOptFlags {
    None = 0,
    ThreadBackgroundPriorityForIndexing = 1,
    ThreadBackgroundPriorityForEditing = 2,
    ThreadBackgroundPriorityForAll = 3,
}

export const enum CXTranslationUnit_Flags {
    None = 0,
    DetailedPreprocessingRecord = 1,
    Incomplete = 2,
    PrecompiledPreamble = 4,
    CacheCompletionResults = 8,
    ForSerialization = 16,
    CXXChainedPCH = 32,
    SkipFunctionBodies = 64,
    IncludeBriefCommentsInCodeCompletion = 128,
    CreatePreambleOnFirstParse = 256,
    KeepGoing = 512,
    SingleFileParse = 1024,
    LimitSkipFunctionBodiesToPreamble = 2048,
    IncludeAttributedTypes = 4096,
    VisitImplicitAttributes = 8192,
    IgnoreNonErrorsFromIncludedFiles = 16384,
    RetainExcludedConditionalBlocks = 32768,
}

export const enum CXSaveTranslationUnit_Flags {
    None = 0,
}

export const enum CXSaveError {
    None = 0,
    Unknown = 1,
    TranslationErrors = 2,
    InvalidTU = 3,
}

export const enum CXReparse_Flags {
    None = 0,
}

export const enum CXTUResourceUsageKind {
    AST = 1,
    Identifiers = 2,
    Selectors = 3,
    GlobalCompletionResults = 4,
    SourceManagerContentCache = 5,
    AST_SideTables = 6,
    SourceManager_Membuffer_Malloc = 7,
    SourceManager_Membuffer_MMap = 8,
    ExternalASTSource_Membuffer_Malloc = 9,
    ExternalASTSource_Membuffer_MMap = 10,
    Preprocessor = 11,
    PreprocessingRecord = 12,
    SourceManager_DataStructures = 13,
    Preprocessor_HeaderSearch = 14,
    MEMORY_IN_BYTES_BEGIN = 1,
    MEMORY_IN_BYTES_END = 14,
    First = 1,
    Last = 14,
}

export const enum CXCursorKind {
    UnexposedDecl = 1,
    StructDecl = 2,
    UnionDecl = 3,
    ClassDecl = 4,
    EnumDecl = 5,
    FieldDecl = 6,
    EnumConstantDecl = 7,
    FunctionDecl = 8,
    VarDecl = 9,
    ParmDecl = 10,
    ObjCInterfaceDecl = 11,
    ObjCCategoryDecl = 12,
    ObjCProtocolDecl = 13,
    ObjCPropertyDecl = 14,
    ObjCIvarDecl = 15,
    ObjCInstanceMethodDecl = 16,
    ObjCClassMethodDecl = 17,
    ObjCImplementationDecl = 18,
    ObjCCategoryImplDecl = 19,
    TypedefDecl = 20,
    CXXMethod = 21,
    Namespace = 22,
    LinkageSpec = 23,
    Constructor = 24,
    Destructor = 25,
    ConversionFunction = 26,
    TemplateTypeParameter = 27,
    NonTypeTemplateParameter = 28,
    TemplateTemplateParameter = 29,
    FunctionTemplate = 30,
    ClassTemplate = 31,
    ClassTemplatePartialSpecialization = 32,
    NamespaceAlias = 33,
    UsingDirective = 34,
    UsingDeclaration = 35,
    TypeAliasDecl = 36,
    ObjCSynthesizeDecl = 37,
    ObjCDynamicDecl = 38,
    CXXAccessSpecifier = 39,
    FirstDecl = 1,
    LastDecl = 39,
    FirstRef = 40,
    ObjCSuperClassRef = 40,
    ObjCProtocolRef = 41,
    ObjCClassRef = 42,
    TypeRef = 43,
    CXXBaseSpecifier = 44,
    TemplateRef = 45,
    NamespaceRef = 46,
    MemberRef = 47,
    LabelRef = 48,
    OverloadedDeclRef = 49,
    VariableRef = 50,
    LastRef = 50,
    FirstInvalid = 70,
    InvalidFile = 70,
    NoDeclFound = 71,
    NotImplemented = 72,
    InvalidCode = 73,
    LastInvalid = 73,
    FirstExpr = 100,
    UnexposedExpr = 100,
    DeclRefExpr = 101,
    MemberRefExpr = 102,
    CallExpr = 103,
    ObjCMessageExpr = 104,
    BlockExpr = 105,
    IntegerLiteral = 106,
    FloatingLiteral = 107,
    ImaginaryLiteral = 108,
    StringLiteral = 109,
    CharacterLiteral = 110,
    ParenExpr = 111,
    UnaryOperator = 112,
    ArraySubscriptExpr = 113,
    BinaryOperator = 114,
    CompoundAssignOperator = 115,
    ConditionalOperator = 116,
    CStyleCastExpr = 117,
    CompoundLiteralExpr = 118,
    InitListExpr = 119,
    AddrLabelExpr = 120,
    StmtExpr = 121,
    GenericSelectionExpr = 122,
    GNUNullExpr = 123,
    CXXStaticCastExpr = 124,
    CXXDynamicCastExpr = 125,
    CXXReinterpretCastExpr = 126,
    CXXConstCastExpr = 127,
    CXXFunctionalCastExpr = 128,
    CXXTypeidExpr = 129,
    CXXBoolLiteralExpr = 130,
    CXXNullPtrLiteralExpr = 131,
    CXXThisExpr = 132,
    CXXThrowExpr = 133,
    CXXNewExpr = 134,
    CXXDeleteExpr = 135,
    UnaryExpr = 136,
    ObjCStringLiteral = 137,
    ObjCEncodeExpr = 138,
    ObjCSelectorExpr = 139,
    ObjCProtocolExpr = 140,
    ObjCBridgedCastExpr = 141,
    PackExpansionExpr = 142,
    SizeOfPackExpr = 143,
    LambdaExpr = 144,
    ObjCBoolLiteralExpr = 145,
    ObjCSelfExpr = 146,
    ArraySectionExpr = 147,
    ObjCAvailabilityCheckExpr = 148,
    FixedPointLiteral = 149,
    OMPArrayShapingExpr = 150,
    OMPIteratorExpr = 151,
    CXXAddrspaceCastExpr = 152,
    ConceptSpecializationExpr = 153,
    RequiresExpr = 154,
    CXXParenListInitExpr = 155,
    PackIndexingExpr = 156,
    LastExpr = 156,
    FirstStmt = 200,
    UnexposedStmt = 200,
    LabelStmt = 201,
    CompoundStmt = 202,
    CaseStmt = 203,
    DefaultStmt = 204,
    IfStmt = 205,
    SwitchStmt = 206,
    WhileStmt = 207,
    DoStmt = 208,
    ForStmt = 209,
    GotoStmt = 210,
    IndirectGotoStmt = 211,
    ContinueStmt = 212,
    BreakStmt = 213,
    ReturnStmt = 214,
    GCCAsmStmt = 215,
    AsmStmt = 215,
    ObjCAtTryStmt = 216,
    ObjCAtCatchStmt = 217,
    ObjCAtFinallyStmt = 218,
    ObjCAtThrowStmt = 219,
    ObjCAtSynchronizedStmt = 220,
    ObjCAutoreleasePoolStmt = 221,
    ObjCForCollectionStmt = 222,
    CXXCatchStmt = 223,
    CXXTryStmt = 224,
    CXXForRangeStmt = 225,
    SEHTryStmt = 226,
    SEHExceptStmt = 227,
    SEHFinallyStmt = 228,
    MSAsmStmt = 229,
    NullStmt = 230,
    DeclStmt = 231,
    OMPParallelDirective = 232,
    OMPSimdDirective = 233,
    OMPForDirective = 234,
    OMPSectionsDirective = 235,
    OMPSectionDirective = 236,
    OMPSingleDirective = 237,
    OMPParallelForDirective = 238,
    OMPParallelSectionsDirective = 239,
    OMPTaskDirective = 240,
    OMPMasterDirective = 241,
    OMPCriticalDirective = 242,
    OMPTaskyieldDirective = 243,
    OMPBarrierDirective = 244,
    OMPTaskwaitDirective = 245,
    OMPFlushDirective = 246,
    SEHLeaveStmt = 247,
    OMPOrderedDirective = 248,
    OMPAtomicDirective = 249,
    OMPForSimdDirective = 250,
    OMPParallelForSimdDirective = 251,
    OMPTargetDirective = 252,
    OMPTeamsDirective = 253,
    OMPTaskgroupDirective = 254,
    OMPCancellationPointDirective = 255,
    OMPCancelDirective = 256,
    OMPTargetDataDirective = 257,
    OMPTaskLoopDirective = 258,
    OMPTaskLoopSimdDirective = 259,
    OMPDistributeDirective = 260,
    OMPTargetEnterDataDirective = 261,
    OMPTargetExitDataDirective = 262,
    OMPTargetParallelDirective = 263,
    OMPTargetParallelForDirective = 264,
    OMPTargetUpdateDirective = 265,
    OMPDistributeParallelForDirective = 266,
    OMPDistributeParallelForSimdDirective = 267,
    OMPDistributeSimdDirective = 268,
    OMPTargetParallelForSimdDirective = 269,
    OMPTargetSimdDirective = 270,
    OMPTeamsDistributeDirective = 271,
    OMPTeamsDistributeSimdDirective = 272,
    OMPTeamsDistributeParallelForSimdDirective = 273,
    OMPTeamsDistributeParallelForDirective = 274,
    OMPTargetTeamsDirective = 275,
    OMPTargetTeamsDistributeDirective = 276,
    OMPTargetTeamsDistributeParallelForDirective = 277,
    OMPTargetTeamsDistributeParallelForSimdDirective = 278,
    OMPTargetTeamsDistributeSimdDirective = 279,
    BuiltinBitCastExpr = 280,
    OMPMasterTaskLoopDirective = 281,
    OMPParallelMasterTaskLoopDirective = 282,
    OMPMasterTaskLoopSimdDirective = 283,
    OMPParallelMasterTaskLoopSimdDirective = 284,
    OMPParallelMasterDirective = 285,
    OMPDepobjDirective = 286,
    OMPScanDirective = 287,
    OMPTileDirective = 288,
    OMPCanonicalLoop = 289,
    OMPInteropDirective = 290,
    OMPDispatchDirective = 291,
    OMPMaskedDirective = 292,
    OMPUnrollDirective = 293,
    OMPMetaDirective = 294,
    OMPGenericLoopDirective = 295,
    OMPTeamsGenericLoopDirective = 296,
    OMPTargetTeamsGenericLoopDirective = 297,
    OMPParallelGenericLoopDirective = 298,
    OMPTargetParallelGenericLoopDirective = 299,
    OMPParallelMaskedDirective = 300,
    OMPMaskedTaskLoopDirective = 301,
    OMPMaskedTaskLoopSimdDirective = 302,
    OMPParallelMaskedTaskLoopDirective = 303,
    OMPParallelMaskedTaskLoopSimdDirective = 304,
    OMPErrorDirective = 305,
    OMPScopeDirective = 306,
    OMPReverseDirective = 307,
    OMPInterchangeDirective = 308,
    OMPAssumeDirective = 309,
    OpenACCComputeConstruct = 320,
    OpenACCLoopConstruct = 321,
    OpenACCCombinedConstruct = 322,
    OpenACCDataConstruct = 323,
    OpenACCEnterDataConstruct = 324,
    OpenACCExitDataConstruct = 325,
    OpenACCHostDataConstruct = 326,
    OpenACCWaitConstruct = 327,
    OpenACCInitConstruct = 328,
    OpenACCShutdownConstruct = 329,
    OpenACCSetConstruct = 330,
    OpenACCUpdateConstruct = 331,
    LastStmt = 331,
    TranslationUnit = 350,
    FirstAttr = 400,
    UnexposedAttr = 400,
    IBActionAttr = 401,
    IBOutletAttr = 402,
    IBOutletCollectionAttr = 403,
    CXXFinalAttr = 404,
    CXXOverrideAttr = 405,
    AnnotateAttr = 406,
    AsmLabelAttr = 407,
    PackedAttr = 408,
    PureAttr = 409,
    ConstAttr = 410,
    NoDuplicateAttr = 411,
    CUDAConstantAttr = 412,
    CUDADeviceAttr = 413,
    CUDAGlobalAttr = 414,
    CUDAHostAttr = 415,
    CUDASharedAttr = 416,
    VisibilityAttr = 417,
    DLLExport = 418,
    DLLImport = 419,
    NSReturnsRetained = 420,
    NSReturnsNotRetained = 421,
    NSReturnsAutoreleased = 422,
    NSConsumesSelf = 423,
    NSConsumed = 424,
    ObjCException = 425,
    ObjCNSObject = 426,
    ObjCIndependentClass = 427,
    ObjCPreciseLifetime = 428,
    ObjCReturnsInnerPointer = 429,
    ObjCRequiresSuper = 430,
    ObjCRootClass = 431,
    ObjCSubclassingRestricted = 432,
    ObjCExplicitProtocolImpl = 433,
    ObjCDesignatedInitializer = 434,
    ObjCRuntimeVisible = 435,
    ObjCBoxable = 436,
    FlagEnum = 437,
    ConvergentAttr = 438,
    WarnUnusedAttr = 439,
    WarnUnusedResultAttr = 440,
    AlignedAttr = 441,
    LastAttr = 441,
    PreprocessingDirective = 500,
    MacroDefinition = 501,
    MacroExpansion = 502,
    MacroInstantiation = 502,
    InclusionDirective = 503,
    FirstPreprocessing = 500,
    LastPreprocessing = 503,
    ModuleImportDecl = 600,
    TypeAliasTemplateDecl = 601,
    StaticAssert = 602,
    FriendDecl = 603,
    ConceptDecl = 604,
    FirstExtraDecl = 600,
    LastExtraDecl = 604,
    OverloadCandidate = 700,
}

export const enum CXLinkageKind {
    Invalid = 0,
    NoLinkage = 1,
    Internal = 2,
    UniqueExternal = 3,
    External = 4,
}

export const enum CXVisibilityKind {
    Invalid = 0,
    Hidden = 1,
    Protected = 2,
    Default = 3,
}

export const enum CXLanguageKind {
    Invalid = 0,
    C = 1,
    ObjC = 2,
    CPlusPlus = 3,
}

export const enum CXTLSKind {
    None = 0,
    Dynamic = 1,
    Static = 2,
}

export const enum CXTypeKind {
    Invalid = 0,
    Unexposed = 1,
    Void = 2,
    Bool = 3,
    Char_U = 4,
    UChar = 5,
    Char16 = 6,
    Char32 = 7,
    UShort = 8,
    UInt = 9,
    ULong = 10,
    ULongLong = 11,
    UInt128 = 12,
    Char_S = 13,
    SChar = 14,
    WChar = 15,
    Short = 16,
    Int = 17,
    Long = 18,
    LongLong = 19,
    Int128 = 20,
    Float = 21,
    Double = 22,
    LongDouble = 23,
    NullPtr = 24,
    Overload = 25,
    Dependent = 26,
    ObjCId = 27,
    ObjCClass = 28,
    ObjCSel = 29,
    Float128 = 30,
    Half = 31,
    Float16 = 32,
    ShortAccum = 33,
    Accum = 34,
    LongAccum = 35,
    UShortAccum = 36,
    UAccum = 37,
    ULongAccum = 38,
    BFloat16 = 39,
    Ibm128 = 40,
    FirstBuiltin = 2,
    LastBuiltin = 40,
    Complex = 100,
    Pointer = 101,
    BlockPointer = 102,
    LValueReference = 103,
    RValueReference = 104,
    Record = 105,
    Enum = 106,
    Typedef = 107,
    ObjCInterface = 108,
    ObjCObjectPointer = 109,
    FunctionNoProto = 110,
    FunctionProto = 111,
    ConstantArray = 112,
    Vector = 113,
    IncompleteArray = 114,
    VariableArray = 115,
    DependentSizedArray = 116,
    MemberPointer = 117,
    Auto = 118,
    Elaborated = 119,
    Pipe = 120,
    OCLImage1dRO = 121,
    OCLImage1dArrayRO = 122,
    OCLImage1dBufferRO = 123,
    OCLImage2dRO = 124,
    OCLImage2dArrayRO = 125,
    OCLImage2dDepthRO = 126,
    OCLImage2dArrayDepthRO = 127,
    OCLImage2dMSAARO = 128,
    OCLImage2dArrayMSAARO = 129,
    OCLImage2dMSAADepthRO = 130,
    OCLImage2dArrayMSAADepthRO = 131,
    OCLImage3dRO = 132,
    OCLImage1dWO = 133,
    OCLImage1dArrayWO = 134,
    OCLImage1dBufferWO = 135,
    OCLImage2dWO = 136,
    OCLImage2dArrayWO = 137,
    OCLImage2dDepthWO = 138,
    OCLImage2dArrayDepthWO = 139,
    OCLImage2dMSAAWO = 140,
    OCLImage2dArrayMSAAWO = 141,
    OCLImage2dMSAADepthWO = 142,
    OCLImage2dArrayMSAADepthWO = 143,
    OCLImage3dWO = 144,
    OCLImage1dRW = 145,
    OCLImage1dArrayRW = 146,
    OCLImage1dBufferRW = 147,
    OCLImage2dRW = 148,
    OCLImage2dArrayRW = 149,
    OCLImage2dDepthRW = 150,
    OCLImage2dArrayDepthRW = 151,
    OCLImage2dMSAARW = 152,
    OCLImage2dArrayMSAARW = 153,
    OCLImage2dMSAADepthRW = 154,
    OCLImage2dArrayMSAADepthRW = 155,
    OCLImage3dRW = 156,
    OCLSampler = 157,
    OCLEvent = 158,
    OCLQueue = 159,
    OCLReserveID = 160,
    ObjCObject = 161,
    ObjCTypeParam = 162,
    Attributed = 163,
    OCLIntelSubgroupAVCMcePayload = 164,
    OCLIntelSubgroupAVCImePayload = 165,
    OCLIntelSubgroupAVCRefPayload = 166,
    OCLIntelSubgroupAVCSicPayload = 167,
    OCLIntelSubgroupAVCMceResult = 168,
    OCLIntelSubgroupAVCImeResult = 169,
    OCLIntelSubgroupAVCRefResult = 170,
    OCLIntelSubgroupAVCSicResult = 171,
    OCLIntelSubgroupAVCImeResultSingleReferenceStreamout = 172,
    OCLIntelSubgroupAVCImeResultDualReferenceStreamout = 173,
    OCLIntelSubgroupAVCImeSingleReferenceStreamin = 174,
    OCLIntelSubgroupAVCImeDualReferenceStreamin = 175,
    OCLIntelSubgroupAVCImeResultSingleRefStreamout = 172,
    OCLIntelSubgroupAVCImeResultDualRefStreamout = 173,
    OCLIntelSubgroupAVCImeSingleRefStreamin = 174,
    OCLIntelSubgroupAVCImeDualRefStreamin = 175,
    ExtVector = 176,
    Atomic = 177,
    BTFTagAttributed = 178,
    HLSLResource = 179,
    HLSLAttributedResource = 180,
}

export const enum CXCallingConv {
    Default = 0,
    C = 1,
    X86StdCall = 2,
    X86FastCall = 3,
    X86ThisCall = 4,
    X86Pascal = 5,
    AAPCS = 6,
    AAPCS_VFP = 7,
    X86RegCall = 8,
    IntelOclBicc = 9,
    Win64 = 10,
    X86_64Win64 = 10,
    X86_64SysV = 11,
    X86VectorCall = 12,
    Swift = 13,
    PreserveMost = 14,
    PreserveAll = 15,
    AArch64VectorCall = 16,
    SwiftAsync = 17,
    AArch64SVEPCS = 18,
    M68kRTD = 19,
    PreserveNone = 20,
    RISCVVectorCall = 21,
    Invalid = 100,
    Unexposed = 200,
}

export const enum CXTemplateArgumentKind {
    Null = 0,
    Type = 1,
    Declaration = 2,
    NullPtr = 3,
    Integral = 4,
    Template = 5,
    TemplateExpansion = 6,
    Expression = 7,
    Pack = 8,
    Invalid = 9,
}

export const enum CXTypeNullabilityKind {
    NonNull = 0,
    Nullable = 1,
    Unspecified = 2,
    Invalid = 3,
    NullableResult = 4,
}

export const enum CXTypeLayoutError {
    Invalid = -1,
    Incomplete = -2,
    Dependent = -3,
    NotConstantSize = -4,
    InvalidFieldName = -5,
    Undeduced = -6,
}

export const enum CXRefQualifierKind {
    None = 0,
    LValue = 1,
    RValue = 2,
}

export const enum CX_CXXAccessSpecifier {
    InvalidAccessSpecifier = 0,
    Public = 1,
    Protected = 2,
    Private = 3,
}

export const enum CX_StorageClass {
    Invalid = 0,
    None = 1,
    Extern = 2,
    Static = 3,
    PrivateExtern = 4,
    OpenCLWorkGroupLocal = 5,
    Auto = 6,
    Register = 7,
}

export const enum CX_BinaryOperatorKind {
    Invalid = 0,
    PtrMemD = 1,
    PtrMemI = 2,
    Mul = 3,
    Div = 4,
    Rem = 5,
    Add = 6,
    Sub = 7,
    Shl = 8,
    Shr = 9,
    Cmp = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    GE = 14,
    EQ = 15,
    NE = 16,
    And = 17,
    Xor = 18,
    Or = 19,
    LAnd = 20,
    LOr = 21,
    Assign = 22,
    MulAssign = 23,
    DivAssign = 24,
    RemAssign = 25,
    AddAssign = 26,
    SubAssign = 27,
    ShlAssign = 28,
    ShrAssign = 29,
    AndAssign = 30,
    XorAssign = 31,
    OrAssign = 32,
    Comma = 33,
    LAST = 33,
}

export const enum CXChildVisitResult {
    Break = 0,
    Continue = 1,
    Recurse = 2,
}

export const enum CXPrintingPolicyProperty {
    Indentation = 0,
    SuppressSpecifiers = 1,
    SuppressTagKeyword = 2,
    IncludeTagDefinition = 3,
    SuppressScope = 4,
    SuppressUnwrittenScope = 5,
    SuppressInitializers = 6,
    ConstantArraySizeAsWritten = 7,
    AnonymousTagLocations = 8,
    SuppressStrongLifetime = 9,
    SuppressLifetimeQualifiers = 10,
    SuppressTemplateArgsInCXXConstructors = 11,
    Bool = 12,
    Restrict = 13,
    Alignof = 14,
    UnderscoreAlignof = 15,
    UseVoidForZeroParams = 16,
    TerseOutput = 17,
    PolishForDeclaration = 18,
    Half = 19,
    MSWChar = 20,
    IncludeNewlines = 21,
    MSVCFormatting = 22,
    ConstantsAsWritten = 23,
    SuppressImplicitBase = 24,
    FullyQualifiedName = 25,
    LastProperty = 25,
}

export const enum CXObjCPropertyAttrKind {
    noattr = 0,
    readonly = 1,
    getter = 2,
    assign = 4,
    readwrite = 8,
    retain = 16,
    copy = 32,
    nonatomic = 64,
    setter = 128,
    atomic = 256,
    weak = 512,
    strong = 1024,
    unsafe_unretained = 2048,
    class = 4096,
}

export const enum CXObjCDeclQualifierKind {
    None = 0,
    In = 1,
    Inout = 2,
    Out = 4,
    Bycopy = 8,
    Byref = 16,
    Oneway = 32,
}

export const enum CXNameRefFlags {
    Qualifier = 1,
    TemplateArgs = 2,
    SinglePiece = 4,
}

export const enum CXTokenKind {
    Punctuation = 0,
    Keyword = 1,
    Identifier = 2,
    Literal = 3,
    Comment = 4,
}

export const enum CXCompletionChunkKind {
    Optional = 0,
    TypedText = 1,
    Text = 2,
    Placeholder = 3,
    Informative = 4,
    CurrentParameter = 5,
    LeftParen = 6,
    RightParen = 7,
    LeftBracket = 8,
    RightBracket = 9,
    LeftBrace = 10,
    RightBrace = 11,
    LeftAngle = 12,
    RightAngle = 13,
    Comma = 14,
    ResultType = 15,
    Colon = 16,
    SemiColon = 17,
    Equal = 18,
    HorizontalSpace = 19,
    VerticalSpace = 20,
}

export const enum CXCodeComplete_Flags {
    IncludeMacros = 1,
    IncludeCodePatterns = 2,
    IncludeBriefComments = 4,
    SkipPreamble = 8,
    IncludeCompletionsWithFixIts = 16,
}

export const enum CXCompletionContext {
    Unexposed = 0,
    AnyType = 1,
    AnyValue = 2,
    ObjCObjectValue = 4,
    ObjCSelectorValue = 8,
    CXXClassTypeValue = 16,
    DotMemberAccess = 32,
    ArrowMemberAccess = 64,
    ObjCPropertyAccess = 128,
    EnumTag = 256,
    UnionTag = 512,
    StructTag = 1024,
    ClassTag = 2048,
    Namespace = 4096,
    NestedNameSpecifier = 8192,
    ObjCInterface = 16384,
    ObjCProtocol = 32768,
    ObjCCategory = 65536,
    ObjCInstanceMessage = 131072,
    ObjCClassMessage = 262144,
    ObjCSelectorName = 524288,
    MacroName = 1048576,
    NaturalLanguage = 2097152,
    IncludedFile = 4194304,
    Unknown = 8388607,
}

export const enum CXEvalResultKind {
    Int = 1,
    Float = 2,
    ObjCStrLiteral = 3,
    StrLiteral = 4,
    CFStr = 5,
    Other = 6,
    UnExposed = 0,
}

export const enum CXVisitorResult {
    Break = 0,
    Continue = 1,
}

export const enum CXResult {
    Success = 0,
    Invalid = 1,
    VisitBreak = 2,
}

export const enum CXIdxEntityKind {
    Unexposed = 0,
    Typedef = 1,
    Function = 2,
    Variable = 3,
    Field = 4,
    EnumConstant = 5,
    ObjCClass = 6,
    ObjCProtocol = 7,
    ObjCCategory = 8,
    ObjCInstanceMethod = 9,
    ObjCClassMethod = 10,
    ObjCProperty = 11,
    ObjCIvar = 12,
    Enum = 13,
    Struct = 14,
    Union = 15,
    CXXClass = 16,
    CXXNamespace = 17,
    CXXNamespaceAlias = 18,
    CXXStaticVariable = 19,
    CXXStaticMethod = 20,
    CXXInstanceMethod = 21,
    CXXConstructor = 22,
    CXXDestructor = 23,
    CXXConversionFunction = 24,
    CXXTypeAlias = 25,
    CXXInterface = 26,
    CXXConcept = 27,
}

export const enum CXIdxEntityLanguage {
    None = 0,
    C = 1,
    ObjC = 2,
    CXX = 3,
    Swift = 4,
}

export const enum CXIdxEntityCXXTemplateKind {
    NonTemplate = 0,
    Template = 1,
    TemplatePartialSpecialization = 2,
    TemplateSpecialization = 3,
}

export const enum CXIdxAttrKind {
    Unexposed = 0,
    IBAction = 1,
    IBOutlet = 2,
    IBOutletCollection = 3,
}

export const enum CXIdxDeclInfoFlags {
    Flag_Skipped = 1,
}

export const enum CXIdxObjCContainerKind {
    ForwardRef = 0,
    Interface = 1,
    Implementation = 2,
}

export const enum CXIdxEntityRefKind {
    Direct = 1,
    Implicit = 2,
}

export const enum CXSymbolRole {
    None = 0,
    Declaration = 1,
    Definition = 2,
    Reference = 4,
    Read = 8,
    Write = 16,
    Call = 32,
    Dynamic = 64,
    AddressOf = 128,
    Implicit = 256,
}

export const enum CXIndexOptFlags {
    None = 0,
    SuppressRedundantRefs = 1,
    IndexFunctionLocalSymbols = 2,
    IndexImplicitTemplateInstantiations = 4,
    SuppressWarnings = 8,
    SkipParsedBodiesInSession = 16,
}

export const enum CXBinaryOperatorKind {
    Invalid = 0,
    PtrMemD = 1,
    PtrMemI = 2,
    Mul = 3,
    Div = 4,
    Rem = 5,
    Add = 6,
    Sub = 7,
    Shl = 8,
    Shr = 9,
    Cmp = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    GE = 14,
    EQ = 15,
    NE = 16,
    And = 17,
    Xor = 18,
    Or = 19,
    LAnd = 20,
    LOr = 21,
    Assign = 22,
    MulAssign = 23,
    DivAssign = 24,
    RemAssign = 25,
    AddAssign = 26,
    SubAssign = 27,
    ShlAssign = 28,
    ShrAssign = 29,
    AndAssign = 30,
    XorAssign = 31,
    OrAssign = 32,
    Comma = 33,
}

export const enum CXUnaryOperatorKind {
    Invalid = 0,
    PostInc = 1,
    PostDec = 2,
    PreInc = 3,
    PreDec = 4,
    AddrOf = 5,
    Deref = 6,
    Plus = 7,
    Minus = 8,
    Not = 9,
    LNot = 10,
    Real = 11,
    Imag = 12,
    Extension = 13,
    Coawait = 14,
}
