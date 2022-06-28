cmake_minimum_required(VERSION 3.5)

project(PrimeNumberGenerator)

add_library(PrimeNumberGenerator
	./primeNumberGenerator.cpp
)
#set(SOURCES ./PrimeNumberGenerator.cpp)
target_include_directories(PrimeNumberGenerator
	PUBLIC
        PrimeNumberGenerator
)

target_compile_options(PrimeNumberGenerator
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4>
)

set(CPACK_PACKAGE_NAME "PrimeNumberGenerator")
set(CPACK_PACKAGE_VENDOR "eric-huynh.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hello - CPack Component Installation Example")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Hello CPack Component Example")

# This must always be last!
include(CPack)
