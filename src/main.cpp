#include <celero/Celero.h>
#include <exception>
#include <expected>
#include <iostream>
#include <optional>
#include <variant>

// Define the number of samples and iterations for benchmarking
CELERO_MAIN

// Function prototypes for different error handling techniques
bool baselineFunction(bool);
void exceptionFunction(bool);
std::expected<void, std::string> expectedFunction(bool);
int errorCodeFunction(bool);
std::optional<std::monostate> optionalFunction(bool);
std::variant<std::monostate, std::string> variantFunction(bool);
void errorCallbackFunction(bool, void (*)(const std::string&));

// Baseline function: Returns true or false
bool baselineFunction(bool success)
{
	return success;
}

// Exception-based function
void exceptionFunction(bool success)
{
	if(!success)
	{
		throw std::runtime_error("Error occurred");
	}
}

// Expected-based function (using std::expected from C++23)
std::expected<void, std::string> expectedFunction(bool success)
{
	if(!success)
	{
		return std::unexpected("Error occurred");
	}
	return {};
}

// Error code function
enum ErrorCode
{
	SUCCESS = 0,
	ERROR = 1
};

int errorCodeFunction(bool success)
{
	return success ? SUCCESS : ERROR;
}

// Optional-based function using std::monostate
std::optional<std::monostate> optionalFunction(bool success)
{
	if(!success)
	{
		return std::nullopt;
	}
	return std::monostate{};
}

// Variant-based function
std::variant<std::monostate, std::string> variantFunction(bool success)
{
	if(!success)
	{
		return "Error occurred";
	}
	return std::monostate{};
}

// Error callback function
void errorCallbackFunction(bool success, void (*callback)(const std::string&))
{
	if(!success)
	{
		callback("Error occurred");
	}
}

// Callback for error reporting
void errorCallback(const std::string& message)
{
	// Handle error
}

// Baseline Benchmark
BASELINE(ErrorHandling, Baseline, 100, 10000000)
{
	celero::DoNotOptimizeAway(baselineFunction(true));
	celero::DoNotOptimizeAway(baselineFunction(false));
}

// Expected Benchmark
BENCHMARK(ErrorHandling, Expected, 50, 10000000)
{
	auto result = expectedFunction(true);
	celero::DoNotOptimizeAway(result.has_value());

	result = expectedFunction(false);
	celero::DoNotOptimizeAway(result.has_value());
}

// Error Code Benchmark
BENCHMARK(ErrorHandling, ErrorCode, 50, 10000000)
{
	celero::DoNotOptimizeAway(errorCodeFunction(true) == SUCCESS);
	celero::DoNotOptimizeAway(errorCodeFunction(false) == SUCCESS);
}

// Optional Benchmark
BENCHMARK(ErrorHandling, Optional, 50, 10000000)
{
	auto result = optionalFunction(true);
	celero::DoNotOptimizeAway(result.has_value());

	result = optionalFunction(false);
	celero::DoNotOptimizeAway(result.has_value());
}

// Variant Benchmark
BENCHMARK(ErrorHandling, Variant, 50, 10000000)
{
	auto result = variantFunction(true);
	celero::DoNotOptimizeAway(std::holds_alternative<std::monostate>(result));

	result = variantFunction(false);
	celero::DoNotOptimizeAway(std::holds_alternative<std::monostate>(result));
}

// Error Callback Benchmark
BENCHMARK(ErrorHandling, ErrorCallback, 50, 10000000)
{
	errorCallbackFunction(true, errorCallback);
	celero::DoNotOptimizeAway(true);

	errorCallbackFunction(false, errorCallback);
	celero::DoNotOptimizeAway(false);
}

// Exception Benchmark
BENCHMARK(ErrorHandling, Exception, 10, 5000)
{
	try
	{
		exceptionFunction(true);
		celero::DoNotOptimizeAway(true);
	}
	catch(...)
	{
		celero::DoNotOptimizeAway(false);
	}

	try
	{
		exceptionFunction(false);
		celero::DoNotOptimizeAway(true);
	}
	catch(...)
	{
		celero::DoNotOptimizeAway(false);
	}
}