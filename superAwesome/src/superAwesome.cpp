#include <superAwesome.h>
#include <limits>

namespace rd {

constexpr const char* happy = "Dog wags tail";
constexpr const int daNumber = 42;

int SuperAwesomeFunction(int numToAdd) {
	if (numToAdd > std::numeric_limits<int>::max() - daNumber) {
		return std::numeric_limits<int>::max();
	}
	return daNumber + numToAdd;
}

const char* PetDog() {
	return happy;
}

} // namespace rd