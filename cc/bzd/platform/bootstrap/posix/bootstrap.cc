// std
#include <cstring>
#include <csignal>
#include <iostream>

#include <cxxabi.h>
#include <execinfo.h>
#include <iomanip>
#include <memory>

namespace {
const char* getSignalName(int sig) noexcept
{
    switch (sig)
    {
    case SIGINT:
                return "SIGINT";
            case SIGILL:
                return "SIGILL";
            case SIGABRT:
                return "SIGABRT";
            case SIGFPE:
                return "SIGFPE";
            case SIGSEGV:
                return "SIGSEGV";
            case SIGTERM:
                return "SIGTERM";
            case SIGHUP:
                return "SIGHUP";
            case SIGQUIT:
                return "SIGQUIT";
            case SIGTRAP:
                return "SIGTRAP";
            case SIGKILL:
                return "SIGKILL";
            case SIGBUS:
                return "SIGBUS";
            case SIGSYS:
                return "SIGSYS";
            case SIGPIPE:
                return "SIGPIPE";
            case SIGALRM:
                return "SIGALRM";
            case SIGURG:
                return "SIGURG";
            case SIGSTOP:
                return "SIGSTOP";
            case SIGTSTP:
                return "SIGTSTP";
            case SIGCONT:
                return "SIGCONT";
            case SIGCHLD:
                return "SIGCHLD";
            case SIGTTIN:
                return "SIGTTIN";
            case SIGTTOU:
                return "SIGTTOU";
            case SIGPOLL:
                return "SIGPOLL";
            case SIGXCPU:
                return "SIGXCPU";
            case SIGXFSZ:
                return "SIGXFSZ";
            case SIGVTALRM:
                return "SIGVTALRM";
            case SIGPROF:
                return "SIGPROF";
            case SIGUSR1:
                return "SIGUSR1";
            case SIGUSR2:
                return "SIGUSR2";
            default:
                return "<unknown>";
        }
    }

bool demangle(char* pBuffer, const size_t size, const char* const pSymbol) noexcept
{
	int status;
	try
	{
		const std::unique_ptr<char, decltype(&std::free)> demangled(abi::__cxa_demangle(pSymbol, 0, 0, &status), &std::free);
		std::strncpy(pBuffer, ((demangled && status == 0) ? demangled.get() : pSymbol), size);
	}
	catch (...)
	{
		// Ignore and return false
		return false;
	}
	return (size > 0 && pBuffer[0] != '\0');
}

void callStack(std::ostream& out) noexcept
{
	constexpr size_t MAX_STACK_LEVEL = 64;
	void* addresses[MAX_STACK_LEVEL];

	const int nbLevels = ::backtrace(addresses, MAX_STACK_LEVEL);
	const std::unique_ptr<char*, decltype(&std::free)> symbols(::backtrace_symbols(addresses, nbLevels), &std::free);

	for (int level = 0; level < nbLevels; ++level)
	{
		char* pSymbol = symbols.get()[level];
		const char* pSourcePath = nullptr;
		const char* pFunction = nullptr;
		const char* pOffset = nullptr;

		// Look for the source path
		{
			const auto pEnd = std::strchr(pSymbol, '(');
			if (pEnd)
			{
				*pEnd = '\0';
				pSourcePath = pSymbol;
				pSymbol = pEnd + 1;
			}
		}

		// Look for the function
		if (pSourcePath)
		{
			const auto pEnd = std::strchr(pSymbol, '+');
			if (pEnd)
			{
				*pEnd = '\0';
				pFunction = pSymbol;
				pSymbol = pEnd + 1;
			}
		}

		// Look for the offset
		if (pFunction)
		{
			const auto pEnd = std::strchr(pSymbol, ')');
			if (pEnd)
			{
				*pEnd = '\0';
				pOffset = pSymbol;
				pSymbol = pEnd + 1;
			}
		}

		// Print stack trace number and memory address
		out << "#" << std::dec << std::left << std::setfill(' ') << std::setw(3) << level << "0x" << std::setfill('0') << std::hex
			<< std::right << std::setw(16) << reinterpret_cast<uint64_t>(addresses[level]);

		char pBuffer[1024];
		if (pFunction)
		{
			if (demangle(pBuffer, sizeof(pBuffer), pFunction))
			{
				out << " in " << pBuffer;
				if (pOffset)
				{
					out << "+" << pOffset;
				}
			}
		}

		out << " (" << pSourcePath << ")";
		out << std::endl;
	}
}

void sigHandler(const int sig, siginfo_t* /*info*/, void* /*secret*/)
{
	// Ensure only one instance is running at a time
    static volatile bool sigHandlerInProgress = false;
    if (sigHandlerInProgress)
    {
        return;
    }
	sigHandlerInProgress = true;

    std::cout << "\nCaught signal: " << getSignalName(sig) << std::endl;
	callStack(std::cout);
	std::exit(sig);
}
} // namespace

bool installBootstrap()
{
	struct sigaction sa
	{
	};
	sa.sa_sigaction = static_cast<void (*)(int, siginfo_t*, void*)>(sigHandler);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	for (const auto& signal :
		 {SIGABRT, SIGALRM, SIGBUS,	 SIGCHLD, SIGCONT, SIGFPE,	SIGHUP,	 SIGILL,  SIGINT, SIGKILL, SIGPIPE, SIGQUIT,   SIGSEGV, SIGSTOP,
		  SIGTERM, SIGTSTP, SIGTTIN, SIGTTOU, SIGUSR1, SIGUSR2, SIGPOLL, SIGPROF, SIGSYS, SIGTRAP, SIGURG,	SIGVTALRM, SIGXCPU, SIGXFSZ})
	{
		sigaction(signal, &sa, nullptr);
		/*
		if (sigaction(signal, &sa, nullptr) < 0) {
			return false;
		}*/
	}
	return true;
}

static bool isBootstrapInstalled = installBootstrap();
