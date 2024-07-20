#pragma once


// Base buildup LogUtilities

// Get line number of code where the log/debug is called
#define SPM_CODE_LINE (FString::FromInt(__LINE__))

// Get namespaced function name e.g. ClassA::FuncB
#define SPM_NAMESPACED_FUNC_NAME (FString(__FUNCTION__))

// Get only class name e.g. ClassA
#define SPM_CLASS_NAME (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

// Get only function name e.g. FuncB
#define SPM_FUNC_NAME (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

// Get function signature
#define SPM_FUNC_SIGNATURE (FString(__FUNCSIG__))

// Get class WITH line number where the log/debug is called e.g. ClassA(LN)
#define SPM_CLASS_LINE_CONTEXT (SPM_CLASS_NAME + "(" + SPM_CODE_LINE + ")")
// Get namespaced function WITH line number where the log/debug is called e.g. ClassA::FuncB(LN)
#define SPM_CLASS_FULL_CONTEXT (SPM_NAMESPACED_FUNC_NAME + "(" + SPM_CODE_LINE + ")")


// Buildup for SuppressableLogMessages
extern TAutoConsoleVariable<bool> CVarSuppressFuncLogs;
extern TAutoConsoleVariable<bool> CVarCheckPartialFuncNameOverlap;
extern TAutoConsoleVariable<FString> CVarSuppressableFuncNames;

bool GetSuppressFuncLogsStatus();
bool GetCheckPartialFuncNameOverlap();
TArray<FString> GetSuppressableFuncNames();
bool ShouldSuppressFunc(FString InFunc);

#define BOOL_SUPPRESS_FUNC_LOG_STATUS() (GetSuppressFuncLogsStatus())
#define SUPPRESSABLE_LOG_FUNC_NAMES() (GetSuppressableFuncNames())
#define SHOULD_SUPPRESS_LOG_IN_FUNC() (ShouldSuppressFunc(SPM_FUNC_NAME) )

#define SUPPRESSABLE_LOG_WRAPPER(Suppressable,Action)                                   \
    do {                                                                                \
        if (!Suppressable)                                                              \
        {                                                                               \
            Action;                                                                     \
        }                                                                               \
        else if (!BOOL_SUPPRESS_FUNC_LOG_STATUS() && !SHOULD_SUPPRESS_LOG_IN_FUNC()) {  \
            Action;                                                                     \
        }                                                                               \
    } while (0)



// Suppressable log message macros

/** Macro providing a suppressable log (of level LOG) message via UE_LOG
Params:
   * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
   * bool           Suppressable    - Wether or not this message should be suppressable or not.
   * FString        OutputMessage   - Message which should be logged.
*/
#define SPM_LOG(LogCategory,Suppressable,OutputMessage) SUPPRESSABLE_LOG_WRAPPER(                       \
    Suppressable,                                                                                       \
    UE_LOG(LogCategory, Log, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString(OutputMessage))          \
)                                                                                                       \

/** Macro providing a suppressable log message (of level LOG) via UE_LOG with formatable message
 Params:
    * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
    * bool           Suppressable    - Wether or not this message should be suppressable or not.
    * FString        FormatString    - Message which should be logged. (formatting args follow this argument)
*/
#define SPM_LOG_PRINTF(LogCategory,Suppressable,FormatString, ... ) SUPPRESSABLE_LOG_WRAPPER(                                           \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Log, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))              \
)                                                                                                                                       \

/** Macro providing a suppressable log (of level WARNING) message via UE_LOG
Params:
   * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
   * bool           Suppressable    - Wether or not this message should be suppressable or not.
   * FString        OutputMessage   - Message which should be logged.
*/
#define SPM_WARNING(LogCategory,Suppressable,OutputMessage) SUPPRESSABLE_LOG_WRAPPER(                       \
    Suppressable,                                                                                           \
    UE_LOG(LogCategory, Warning, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString(OutputMessage))          \
)                                                                                                           \

/** Macro providing a suppressable log message (of level WARNING) via UE_LOG with formatable message
 Params:
    * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
    * bool           Suppressable    - Wether or not this message should be suppressable or not.
    * FString        FormatString    - Message which should be logged. (formatting args follow this argument)
*/
#define SPM_WARNING_PRINTF(LogCategory,Suppressable,FormatString, ... ) SUPPRESSABLE_LOG_WRAPPER(                                       \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Warning, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))          \
)                                                                                                                                       \

/** Macro providing a suppressable log (of level ERROR) message via UE_LOG
Params:
   * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
   * bool           Suppressable    - Wether or not this message should be suppressable or not.
   * FString        OutputMessage   - Message which should be logged.
*/
#define SPM_ERROR(LogCategory,Suppressable,OutputMessage) SUPPRESSABLE_LOG_WRAPPER(                                                     \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Error, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString(OutputMessage))                                        \
)                                                                                                                                       \

/** Macro providing a suppressable log message (of level ERRIR) via UE_LOG with formatable message
 Params:
    * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
    * bool           Suppressable    - Wether or not this message should be suppressable or not.
    * FString        FormatString    - Message which should be logged. (formatting args follow this argument)
*/
#define SPM_ERROR_PRINTF(LogCategory,Suppressable,FormatString, ... ) SUPPRESSABLE_LOG_WRAPPER(                                         \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Error, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))            \
)                                                                                                                                       \

/** Macro providing a suppressable log (of level FATAL) message via UE_LOG
Params:
   * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
   * bool           Suppressable    - Wether or not this message should be suppressable or not.
   * FString        OutputMessage   - Message which should be logged.
*/
#define SPM_FATAL(LogCategory,Suppressable,OutputMessage) SUPPRESSABLE_LOG_WRAPPER(                                                     \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Fatal, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString(OutputMessage))                                        \
)                                                                                                                                       \

/** Macro providing a suppressable log message (of level FATAL) via UE_LOG with formatable message
 Params:
    * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
    * bool           Suppressable    - Wether or not this message should be suppressable or not.
    * FString        FormatString    - Message which should be logged. (formatting args follow this argument)
*/
#define SPM_FATAL_PRINTF(LogCategory,Suppressable,FormatString, ... ) SUPPRESSABLE_LOG_WRAPPER(                                         \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Fatal, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))            \
)                                                                                                                                       \

/** Macro providing a suppressable log (of level DISPLAY) message via UE_LOG
Params:
   * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
   * bool           Suppressable    - Wether or not this message should be suppressable or not.
   * FString        OutputMessage   - Message which should be logged.
*/
#define SPM_DISPLAY(LogCategory,Suppressable,OutputMessage) SUPPRESSABLE_LOG_WRAPPER(                                                   \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Display, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString(OutputMessage))                                      \
)                                                                                                                                       \

/** Macro providing a suppressable log message (of level DISPLAY) via UE_LOG with formatable message
 Params:
    * FLogCategory   LogCategory     - Defines the category which the message should be logged in.
    * bool           Suppressable    - Wether or not this message should be suppressable or not.
    * FString        FormatString    - Message which should be logged. (formatting args follow this argument)
*/
#define SPM_DISPLAY_PRINTF(LogCategory,Suppressable,FormatString, ... ) SUPPRESSABLE_LOG_WRAPPER(                                       \
    Suppressable,                                                                                                                       \
    UE_LOG(LogCategory, Display, TEXT("%s: %s"), *SPM_CLASS_FULL_CONTEXT, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__))          \
)                                                                                                                                       \

// Additional Helpers

#define SPM_DSC_MSG(OutputMessage) (GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, *(SPM_CLASS_FULL_CONTEXT + ": " + OutputMessage)) )
#define SPM_DSC_MSG_PRINTF(FormatString , ...) (GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, *(SPM_CLASS_FULL_CONTEXT + ": " + (FString::Printf(TEXT(FormatString), ##__VA_ARGS__ )))) )
#define SPM_DSC_MSG_PRINTF_TICK(FormatString , ...) (GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Black, *(SPM_CLASS_FULL_CONTEXT + ": " + (FString::Printf(TEXT(FormatString), ##__VA_ARGS__ )))) )

/** Macro providing a string evaluation of given boolean (simple ternay-operator wrapper)
 Params:
  * bool            EvalBoolean     - Boolean variable which should be evaluated
*/
#define BOOL_FSTRING_EVAL(EvalBoolean) (EvalBoolean ? FString("True") : FString("False"))