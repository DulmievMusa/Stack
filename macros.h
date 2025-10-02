#ifndef MACROS_H
#define MACROS_H


#define FG_BG_ANSI "\033[41;97m"
#define RESET_ANSI "\033[0m"
#define TEST_FALED_ANSI "\033[44;97m"
#define MyAssert(need_to_call_assert) AssertOfMusa(need_to_call_assert, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define StackDump(stack) PrintErrorsofStack(stack, __FILE__, __PRETTY_FUNCTION__, __LINE__)


#define SetStackIsNullError(errors) errors |= (1 << 0)
#define SetCanaryDiedError(errors) errors |= (1 << 1)
#define SetSizeisNegativeError(errors) errors |= (1 << 2)
#define SetCapacityIsNegativeError(errors) errors |= (1 << 3)
#define SetStackDataisNullError(errors) errors |= (1 << 4)
#define SetSizeIsNullError(errors) errors |= (1 << 5)


#define IsStackNullError(errors) errors & (1 << 0)
#define IsCanaryDiedError(errors) errors & (1 << 1)
#define IsSizeNegativeError(errors) errors & (1 << 2)
#define IsCapacityNegativeError(errors) errors & (1 << 3)
#define IsStackDataNullError(errors) errors & (1 << 4)
#define IsSizeNullError(errors) errors & (1 << 5)


#endif