#include <celero/Celero.h>
#include <exception>
#include <expected>
#include <iostream>
#include <optional>
#include <variant>

// Define the number of samples and iterations for benchmarking
CELERO_MAIN

// Baseline function: Returns true or false
bool BaselineFunction(bool success)
{
	return success;
}

// Exception-based function
void ExceptionFunction(bool success)
{
	if(!success)
	{
		throw std::runtime_error("Error occurred");
	}
}

// Expected-based function (using std::expected from C++23)
std::expected<void, std::string> ExpectedFunction(bool success)
{
	if(!success)
	{
		return std::unexpected("Error occurred");
	}
	return {};
}

// Error code function
enum class ErrorCode
{
	SUCCESS = 0,
	ERROR = 1
};

ErrorCode ErrorCodeFunction(bool success)
{
	return success ? ErrorCode::SUCCESS : ErrorCode::ERROR;
}

// Optional-based function using std::monostate
std::optional<std::monostate> OptionalFunction(bool success)
{
	if(!success)
	{
		return std::nullopt;
	}
	return std::monostate{};
}

// Variant-based function
std::variant<std::monostate, std::string> VariantFunction(bool success)
{
	if(!success)
	{
		return "Error occurred";
	}
	return std::monostate{};
}

// Error callback function
void ErrorCallbackFunction(bool success, void (*callback)(const std::string&))
{
	if(!success)
	{
		callback("Error occurred");
	}
}

// Callback for error reporting
void ErrorCallback(const std::string& message)
{
	// Handle error
}

// Baseline Benchmark
BASELINE(ErrorHandling, Baseline, 100, 10000000)
{
	celero::DoNotOptimizeAway(BaselineFunction(true));
	celero::DoNotOptimizeAway(BaselineFunction(false));
}

// Expected Benchmark
BENCHMARK(ErrorHandling, Expected, 50, 10000000)
{
	auto result = ExpectedFunction(true);
	celero::DoNotOptimizeAway(result.has_value());

	result = ExpectedFunction(false);
	celero::DoNotOptimizeAway(result.has_value());
}

// Error Code Benchmark
BENCHMARK(ErrorHandling, ErrorCode, 50, 10000000)
{
	celero::DoNotOptimizeAway(ErrorCodeFunction(true) == ErrorCode::SUCCESS);
	celero::DoNotOptimizeAway(ErrorCodeFunction(false) == ErrorCode::SUCCESS);
}

// Optional Benchmark
BENCHMARK(ErrorHandling, Optional, 50, 10000000)
{
	auto result = OptionalFunction(true);
	celero::DoNotOptimizeAway(result.has_value());

	result = OptionalFunction(false);
	celero::DoNotOptimizeAway(result.has_value());
}

// Variant Benchmark
BENCHMARK(ErrorHandling, Variant, 50, 10000000)
{
	auto result = VariantFunction(true);
	celero::DoNotOptimizeAway(std::holds_alternative<std::monostate>(result));

	result = VariantFunction(false);
	celero::DoNotOptimizeAway(std::holds_alternative<std::monostate>(result));
}

// Error Callback Benchmark
BENCHMARK(ErrorHandling, ErrorCallback, 50, 10000000)
{
	ErrorCallbackFunction(true, ErrorCallback);
	celero::DoNotOptimizeAway(true);

	ErrorCallbackFunction(false, ErrorCallback);
	celero::DoNotOptimizeAway(false);
}

// Exception Benchmark
BENCHMARK(ErrorHandling, Exception, 10, 5000)
{
	try
	{
		ExceptionFunction(true);
		celero::DoNotOptimizeAway(true);
	}
	catch(...)
	{
		celero::DoNotOptimizeAway(false);
	}

	try
	{
		ExceptionFunction(false);
		celero::DoNotOptimizeAway(true);
	}
	catch(...)
	{
		celero::DoNotOptimizeAway(false);
	}
}